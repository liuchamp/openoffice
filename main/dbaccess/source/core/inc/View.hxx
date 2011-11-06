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



#ifndef DBACCESS_VIEW_HXX
#define DBACCESS_VIEW_HXX

#include "connectivity/sdbcx/VView.hxx"

/** === begin UNO includes === **/
#include <com/sun/star/sdbcx/XAlterView.hpp>
#include <com/sun/star/sdb/tools/XViewAccess.hpp>
/** === end UNO includes === **/

#include <comphelper/uno3.hxx>
#include <cppuhelper/implbase1.hxx>

//........................................................................
namespace dbaccess
{
//........................................................................

	//====================================================================
	//= View
	//====================================================================
    typedef ::connectivity::sdbcx::OView                                View_Base;
    typedef ::cppu::ImplHelper1< ::com::sun::star::sdbcx::XAlterView >  View_IBASE;
    class View :public View_Base
                ,public View_IBASE
	{
    public:
        View(
            const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _rxConnection,
            sal_Bool _bCaseSensitive,
            const ::rtl::OUString& _rCatalogName,
            const ::rtl::OUString& _rSchemaName,
            const ::rtl::OUString& _rName
        );

        // UNO
        DECLARE_XINTERFACE()
        DECLARE_XTYPEPROVIDER()

        // XAlterView
        virtual void SAL_CALL alterCommand( const ::rtl::OUString& NewCommand ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);

    protected:
        virtual ~View();

    protected:
        // OPropertyContainer
        virtual void SAL_CALL getFastPropertyValue( ::com::sun::star::uno::Any& _rValue, sal_Int32 _nHandle ) const;

    private:
         ::com::sun::star::uno::Reference< ::com::sun::star::sdb::tools::XViewAccess>     m_xViewAccess;
        sal_Int32       m_nCommandHandle;
    private:
        using View_Base::getFastPropertyValue;
	};

//........................................................................
} // namespace dbaccess
//........................................................................

#endif // DBACCESS_VIEW_HXX
