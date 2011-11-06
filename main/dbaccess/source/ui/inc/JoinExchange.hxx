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


#ifndef DBAUI_JOINEXCHANGE_HXX
#define DBAUI_JOINEXCHANGE_HXX

#ifndef DBAUI_DBEXCHANGE_HXX
#include "dbexchange.hxx"
#endif
#ifndef DBAUI_TABLEWINDOWLISTBOX_HXX
#include "TableWindowListBox.hxx"
#endif

#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_XUNOTUNNEL_HPP_
#include <com/sun/star/lang/XUnoTunnel.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif

namespace dbaui
{
	//==================================================================
	// OJoinExchObj :
	// Zusaetzliche Daten fuer das Erzeugen von Joins in der JoinShell
	//==================================================================

	typedef ::cppu::ImplHelper1< ::com::sun::star::lang::XUnoTunnel > OJoinExchObj_Base;
	class OJoinExchObj
					:public TransferableHelper
					,public OJoinExchObj_Base
	{
		static String			m_sJoinFormat;
		sal_Bool				m_bFirstEntry;

	protected:
		OJoinExchangeData			m_jxdSourceDescription;
		IDragTransferableListener*	m_pDragListener;

		virtual ~OJoinExchObj();
	public:
		OJoinExchObj(const OJoinExchangeData& jxdSource,sal_Bool _bFirstEntry=sal_False);
		

		// XInterface
		virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& aType ) throw(::com::sun::star::uno::RuntimeException);
		virtual void SAL_CALL acquire(  ) throw();
		virtual void SAL_CALL release(  ) throw();

		// XUnoTunnel
	    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& _rIdentifier ) throw(::com::sun::star::uno::RuntimeException);

		void StartDrag( Window* pWindow, sal_Int8 nDragSourceActions, IDragTransferableListener* _pListener );

		static OJoinExchangeData	GetSourceDescription(const ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable >& _rxObject);
		static sal_Bool				isFormatAvailable( const DataFlavorExVector& _rFormats ,SotFormatStringId _nSlotID=SOT_FORMATSTR_ID_SBA_JOIN);

	protected:
		virtual void				AddSupportedFormats();
		virtual sal_Bool			GetData( const ::com::sun::star::datatransfer::DataFlavor& rFlavor );
		virtual void				DragFinished( sal_Int8 nDropAction );

		static ::com::sun::star::uno::Sequence< sal_Int8 > getUnoTunnelImplementationId();

    private:
        using TransferableHelper::StartDrag;
	};
}
#endif // DBAUI_JOINEXCHANGE_HXX


