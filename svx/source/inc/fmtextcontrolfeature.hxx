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



#ifndef SVX_SOURCE_INC_FMTEXTCONTROLFEATURE_HXX
#define SVX_SOURCE_INC_FMTEXTCONTROLFEATURE_HXX

/** === begin UNO includes === **/
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/frame/XDispatch.hpp>
#include <com/sun/star/frame/XStatusListener.hpp>
#include <com/sun/star/util/URL.hpp>
/** === end UNO includes === **/
#include <cppuhelper/implbase1.hxx>
#include "fmslotinvalidator.hxx"

//........................................................................
namespace svx
{
//........................................................................

	//====================================================================
	//= FmTextControlFeature
	//====================================================================
    typedef ::cppu::WeakImplHelper1 <   ::com::sun::star::frame::XStatusListener
                                    >   FmTextControlFeature_Base;

    class FmTextControlFeature : public FmTextControlFeature_Base
	{
    private:
        ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch >
                                        m_xDispatcher;
        ::com::sun::star::util::URL     m_aFeatureURL;
        ::com::sun::star::uno::Any      m_aFeatureState;
        SfxSlotId                       m_nSlotId;
        ISlotInvalidator*               m_pInvalidator;
        bool                            m_bFeatureEnabled;

    public:
        /** constructs an FmTextControlFeature object
        @param _rxDispatcher
            the dispatcher which the instance should work with
        @param _rFeatureURL
            the URL which the instance should be responsible for
        */
        FmTextControlFeature(
            const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch >& _rxDispatcher,
            const ::com::sun::star::util::URL& _rFeatureURL,
            SfxSlotId _nId,
            ISlotInvalidator* _pInvalidator
        );

        /// determines whether the feature we're responsible for is currently enabled
        inline  bool                                isFeatureEnabled( ) const { return m_bFeatureEnabled; }
        inline  const ::com::sun::star::uno::Any&   getFeatureState( ) const { return m_aFeatureState; }

        /** dispatches the feature URL to the dispatcher
        */
        void    dispatch() const SAL_THROW(());

        /** dispatches the feature URL to the dispatcher, with passing the given arguments
        */
        void    dispatch( const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& _rArgs ) const SAL_THROW(());

        /// releases any resources associated with this instance
        void    dispose() SAL_THROW(());

    protected:
        ~FmTextControlFeature();

    protected:
        // XStatusListener
        virtual void SAL_CALL statusChanged( const ::com::sun::star::frame::FeatureStateEvent& State ) throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw (::com::sun::star::uno::RuntimeException);
	};

//........................................................................
} // namespace svx
//........................................................................

#endif // SVX_SOURCE_INC_FMTEXTCONTROLFEATURE_HXX

