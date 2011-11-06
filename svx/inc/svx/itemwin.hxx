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


#ifndef _SVX_ITEMWIN_HXX
#define _SVX_ITEMWIN_HXX

#include <vcl/bitmap.hxx>

#include <svx/dlgctrl.hxx>
#include "svx/svxdllapi.h"

// forward ---------------------------------------------------------------

class XLineColorItem;
class XLineWidthItem;
class SfxObjectShell;

// class SvxLineBox ------------------------------------------------------

class SvxLineBox : public LineLB
{
	BmpColorMode	meBmpMode;
	sal_uInt16			nCurPos;
	Timer			aDelayTimer;
    Size            aLogicalSize;
    sal_Bool            bRelease;
	SfxObjectShell* mpSh;
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame > mxFrame;

#ifdef _SVX_ITEMWIN_CXX
					DECL_LINK( DelayHdl_Impl, Timer * );

	void			ReleaseFocus_Impl();
#endif
public:
	SvxLineBox( Window* pParent, 
                const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame >& rFrame,
				WinBits nBits = WB_BORDER | WB_DROPDOWN | WB_AUTOHSCROLL );
	~SvxLineBox();

	void FillControl();

protected:
	virtual void 	Select();
	virtual long	PreNotify( NotifyEvent& rNEvt );
	virtual long	Notify( NotifyEvent& rNEvt );
    virtual void    DataChanged( const DataChangedEvent& rDCEvt );

};

// class SvxColorBox -----------------------------------------------------

class SvxColorBox : public ColorLB
{
	using Window::Update;

	sal_uInt16			nCurPos;
	sal_uInt16			nId;
	Timer			aDelayTimer;
    Size            aLogicalSize;
    sal_Bool            bRelease;
    ::rtl::OUString maCommand;
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame > mxFrame;

#ifdef _SVX_ITEMWIN_CXX
					DECL_LINK( DelayHdl_Impl, Timer * );

	void			ReleaseFocus_Impl();
#endif

public:
	SvxColorBox( Window* pParent, 
                 const rtl::OUString& rCommand,
                 const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame >& rFrame,
				 WinBits nBits = WB_BORDER | WB_DROPDOWN | WB_AUTOHSCROLL );
	~SvxColorBox();

	void			Update( const XLineColorItem* pItem );

protected:
	virtual void 	Select();
	virtual long	PreNotify( NotifyEvent& rNEvt );
	virtual long	Notify( NotifyEvent& rNEvt );
    virtual void    DataChanged( const DataChangedEvent& rDCEvt );

};

// class SvxMetricField --------------------------------------------------

class SVX_DLLPUBLIC SvxMetricField : public MetricField
{
	using Window::Update;

	String			aCurTxt;
	SfxMapUnit		ePoolUnit;
	FieldUnit		eDlgUnit;
    Size            aLogicalSize;
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame > mxFrame;

#ifdef _SVX_ITEMWIN_CXX
	void			ReleaseFocus_Impl();
#endif

protected:
	virtual void 	Modify();
	virtual void    Down();
	virtual void    Up();		// Nur zur Sicherheit

	virtual long	PreNotify( NotifyEvent& rNEvt );
	virtual long	Notify( NotifyEvent& rNEvt );
    virtual void    DataChanged( const DataChangedEvent& rDCEvt );

public:
	SvxMetricField( Window* pParent, 
                    const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame >& rFrame,
					WinBits nBits = WB_BORDER | WB_SPIN | WB_REPEAT );
	~SvxMetricField();

	void			Update( const XLineWidthItem* pItem );
	void			SetCoreUnit( SfxMapUnit eUnit );
	void			RefreshDlgUnit();
};

// class SvxFillTypeBox --------------------------------------------------

class SvxFillTypeBox : public FillTypeLB
{
public:
	SvxFillTypeBox( Window* pParent, WinBits nBits = WB_BORDER | WB_DROPDOWN | WB_AUTOHSCROLL );
	~SvxFillTypeBox();

	void			Selected() { bSelect = sal_True; }
    sal_Bool            IsRelease() { return bRelease;}

protected:
	virtual long	PreNotify( NotifyEvent& rNEvt );
	virtual long	Notify( NotifyEvent& rNEvt );

private:
	sal_uInt16			nCurPos;
	sal_Bool			bSelect;
    sal_Bool            bRelease;

#ifdef _SVX_ITEMWIN_CXX
	void			ReleaseFocus_Impl();
#endif
};

// class SvxFillAttrBox --------------------------------------------------

class SvxFillAttrBox : public FillAttrLB
{
public:
	SvxFillAttrBox( Window* pParent, WinBits nBits = WB_BORDER | WB_DROPDOWN | WB_AUTOHSCROLL );
	~SvxFillAttrBox();

    sal_Bool            IsRelease() { return bRelease;}

protected:
	virtual long	PreNotify( NotifyEvent& rNEvt );
	virtual long	Notify( NotifyEvent& rNEvt );
	virtual void	Select();

private:
	sal_uInt16			nCurPos;
    sal_Bool            bRelease;

#ifdef _SVX_ITEMWIN_CXX
	void			ReleaseFocus_Impl();
#endif
};

#endif // #ifndef _SVX_ITEMWIN_HXX

