/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_svl.hxx"

#include <stdio.h>

#include <com/sun/star/ucb/XSimpleFileAccess.hpp>
#include <com/sun/star/ucb/XCommandEnvironment.hpp>
#include <com/sun/star/ucb/InsertCommandArgument.hpp>
#include <com/sun/star/ucb/NameClashException.hpp>
#include <com/sun/star/io/WrongFormatException.hpp>

#include <osl/time.h>
#include <osl/security.hxx>
#include <osl/socket.hxx>

#include <rtl/string.hxx>
#include <rtl/ustring.hxx>
#include <rtl/strbuf.hxx>
#include <rtl/ustrbuf.hxx>

#include <comphelper/processfactory.hxx>

#include <tools/urlobj.hxx>
#include <unotools/bootstrap.hxx>

#include <ucbhelper/content.hxx>

#include <unotools/useroptions.hxx>

#include <svl/documentlockfile.hxx>

using namespace ::com::sun::star;

namespace svt {

sal_Bool DocumentLockFile::m_bAllowInteraction = sal_True;

// ----------------------------------------------------------------------
DocumentLockFile::DocumentLockFile( const ::rtl::OUString& aOrigURL, const uno::Reference< lang::XMultiServiceFactory >& xFactory )
: LockFileCommon( aOrigURL, xFactory, ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( ".~lock." ) ) )
{
}

// ----------------------------------------------------------------------
DocumentLockFile::~DocumentLockFile()
{
}

// ----------------------------------------------------------------------
void DocumentLockFile::WriteEntryToStream( uno::Sequence< ::rtl::OUString > aEntry, uno::Reference< io::XOutputStream > xOutput )
{
    ::osl::MutexGuard aGuard( m_aMutex );

    ::rtl::OUStringBuffer aBuffer;

    for ( sal_Int32 nEntryInd = 0; nEntryInd < aEntry.getLength(); nEntryInd++ )
    {
        aBuffer.append( EscapeCharacters( aEntry[nEntryInd] ) );
        if ( nEntryInd < aEntry.getLength() - 1 )
            aBuffer.append( (sal_Unicode)',' );
        else
            aBuffer.append( (sal_Unicode)';' );
    }

    ::rtl::OString aStringData( ::rtl::OUStringToOString( aBuffer.makeStringAndClear(), RTL_TEXTENCODING_UTF8 ) );
    uno::Sequence< sal_Int8 > aData( (sal_Int8*)aStringData.getStr(), aStringData.getLength() );
    xOutput->writeBytes( aData );
}

// ----------------------------------------------------------------------
sal_Bool DocumentLockFile::CreateOwnLockFile()
{
    ::osl::MutexGuard aGuard( m_aMutex );

    try
    {
        uno::Reference< io::XStream > xTempFile(
            m_xFactory->createInstance( ::rtl::OUString::createFromAscii( "com.sun.star.io.TempFile" ) ),
            uno::UNO_QUERY_THROW );
        uno::Reference< io::XSeekable > xSeekable( xTempFile, uno::UNO_QUERY_THROW );

        uno::Reference< io::XInputStream > xInput = xTempFile->getInputStream();
        uno::Reference< io::XOutputStream > xOutput = xTempFile->getOutputStream();

        if ( !xInput.is() || !xOutput.is() )
            throw uno::RuntimeException();

        uno::Sequence< ::rtl::OUString > aNewEntry = GenerateOwnEntry();
        WriteEntryToStream( aNewEntry, xOutput );
        xOutput->closeOutput();

        xSeekable->seek( 0 );

        uno::Reference < ::com::sun::star::ucb::XCommandEnvironment > xEnv;
        ::ucbhelper::Content aTargetContent( m_aURL, xEnv );

        ucb::InsertCommandArgument aInsertArg;
        aInsertArg.Data = xInput;
        aInsertArg.ReplaceExisting = sal_False;
        uno::Any aCmdArg;
        aCmdArg <<= aInsertArg;
        aTargetContent.executeCommand( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "insert" ) ), aCmdArg );

        // try to let the file be hidden if possible
        try {
            aTargetContent.setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "IsHidden" ) ), uno::makeAny( sal_True ) );
        } catch( uno::Exception& ) {}
    }
    catch( ucb::NameClashException& )
    {
        return sal_False;
    }

    return sal_True;
}

// ----------------------------------------------------------------------
uno::Sequence< ::rtl::OUString > DocumentLockFile::GetLockData()
{
    ::osl::MutexGuard aGuard( m_aMutex );

    uno::Reference< io::XInputStream > xInput = OpenStream();
    if ( !xInput.is() )
        throw uno::RuntimeException();

    const sal_Int32 nBufLen = 32000;
    uno::Sequence< sal_Int8 > aBuffer( nBufLen );

    sal_Int32 nRead = 0;

    nRead = xInput->readBytes( aBuffer, nBufLen );
    xInput->closeInput();

    if ( nRead == nBufLen )
        throw io::WrongFormatException();

    sal_Int32 nCurPos = 0;
    return ParseEntry( aBuffer, nCurPos );
}

// ----------------------------------------------------------------------
uno::Reference< io::XInputStream > DocumentLockFile::OpenStream()
{
    ::osl::MutexGuard aGuard( m_aMutex );

    uno::Reference< lang::XMultiServiceFactory > xFactory = ::comphelper::getProcessServiceFactory();
        uno::Reference< ::com::sun::star::ucb::XSimpleFileAccess > xSimpleFileAccess(
            xFactory->createInstance( ::rtl::OUString::createFromAscii("com.sun.star.ucb.SimpleFileAccess") ),
            uno::UNO_QUERY_THROW );

    // the file can be opened readonly, no locking will be done
    return xSimpleFileAccess->openFileRead( m_aURL );
}

// ----------------------------------------------------------------------
sal_Bool DocumentLockFile::OverwriteOwnLockFile()
{
    // allows to overwrite the lock file with the current data
    try
    {
        uno::Reference < ::com::sun::star::ucb::XCommandEnvironment > xEnv;
        ::ucbhelper::Content aTargetContent( m_aURL, xEnv );

        uno::Sequence< ::rtl::OUString > aNewEntry = GenerateOwnEntry();

        uno::Reference< io::XStream > xStream = aTargetContent.openWriteableStreamNoLock();
        uno::Reference< io::XOutputStream > xOutput = xStream->getOutputStream();
        uno::Reference< io::XTruncate > xTruncate( xOutput, uno::UNO_QUERY_THROW );

        xTruncate->truncate();
        WriteEntryToStream( aNewEntry, xOutput );
        xOutput->closeOutput();
    }
    catch( uno::Exception& )
    {
        return sal_False;
    }

    return sal_True;
}

// ----------------------------------------------------------------------
void DocumentLockFile::RemoveFile()
{
    ::osl::MutexGuard aGuard( m_aMutex );

    // TODO/LATER: the removing is not atomar, is it possible in general to make it atomar?
    uno::Sequence< ::rtl::OUString > aNewEntry = GenerateOwnEntry();
    uno::Sequence< ::rtl::OUString > aFileData = GetLockData();

    if ( aFileData.getLength() < LOCKFILE_ENTRYSIZE )
        throw io::WrongFormatException();

    if ( !aFileData[LOCKFILE_SYSUSERNAME_ID].equals( aNewEntry[LOCKFILE_SYSUSERNAME_ID] )
      || !aFileData[LOCKFILE_LOCALHOST_ID].equals( aNewEntry[LOCKFILE_LOCALHOST_ID] )
      || !aFileData[LOCKFILE_USERURL_ID].equals( aNewEntry[LOCKFILE_USERURL_ID] ) )
        throw io::IOException(); // not the owner, access denied

    uno::Reference< lang::XMultiServiceFactory > xFactory = ::comphelper::getProcessServiceFactory();
    uno::Reference< ::com::sun::star::ucb::XSimpleFileAccess > xSimpleFileAccess(
        xFactory->createInstance( ::rtl::OUString::createFromAscii("com.sun.star.ucb.SimpleFileAccess") ),
        uno::UNO_QUERY_THROW );
    xSimpleFileAccess->kill( m_aURL );
}

} // namespace svt

