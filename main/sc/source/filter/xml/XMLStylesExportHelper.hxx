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



#ifndef SC_XMLSTYLESEXPORTHELPER_HXX
#define SC_XMLSTYLESEXPORTHELPER_HXX

#include <vector>
#include <list>
#include <com/sun/star/uno/Any.h>
#include <com/sun/star/table/CellRangeAddress.hpp>
#include <com/sun/star/table/CellAddress.hpp>
#include <com/sun/star/sheet/ConditionOperator.hpp>
#include <com/sun/star/sheet/ValidationAlertStyle.hpp>
#include <com/sun/star/sheet/ValidationType.hpp>

class ScDocument;
class ScXMLExport;

struct ScMyValidation
{
	rtl::OUString				sName;
	rtl::OUString				sErrorMessage;
	rtl::OUString				sErrorTitle;
	rtl::OUString				sImputMessage;
	rtl::OUString				sImputTitle;
	rtl::OUString				sFormula1;
	rtl::OUString				sFormula2;
	com::sun::star::table::CellAddress			aBaseCell;
	com::sun::star::sheet::ValidationAlertStyle	aAlertStyle;
	com::sun::star::sheet::ValidationType		aValidationType;
	com::sun::star::sheet::ConditionOperator	aOperator;
    sal_Int16                   nShowList;
	sal_Bool					bShowErrorMessage;
	sal_Bool					bShowImputMessage;
	sal_Bool					bIgnoreBlanks;

								ScMyValidation();
								~ScMyValidation();

	sal_Bool					IsEqual(const ScMyValidation& aVal) const;
};

typedef std::vector<ScMyValidation>			ScMyValidationVec;

class ScMyValidationsContainer
{
private:
	ScMyValidationVec			aValidationVec;
	const rtl::OUString			sEmptyString;
	const rtl::OUString			sERRALSTY;
	const rtl::OUString			sIGNOREBL;
    const rtl::OUString         sSHOWLIST;
	const rtl::OUString			sTYPE;
	const rtl::OUString			sSHOWINP;
	const rtl::OUString			sSHOWERR;
	const rtl::OUString			sINPTITLE;
	const rtl::OUString			sINPMESS;
	const rtl::OUString			sERRTITLE;
	const rtl::OUString			sERRMESS;
	const rtl::OUString			sOnError;
	const rtl::OUString			sEventType;
	const rtl::OUString			sStarBasic;
	const rtl::OUString			sScript;
	const rtl::OUString			sLibrary;
	const rtl::OUString			sMacroName;

public:
								ScMyValidationsContainer();
								~ScMyValidationsContainer();
	sal_Bool					AddValidation(const com::sun::star::uno::Any& aAny,
									sal_Int32& nValidationIndex);
	rtl::OUString				GetCondition(ScXMLExport& rExport, const ScMyValidation& aValidation);
	rtl::OUString				GetBaseCellAddress(ScDocument* pDoc, const com::sun::star::table::CellAddress& aCell);
	void						WriteMessage(ScXMLExport& rExport,
									const rtl::OUString& sTitle, const rtl::OUString& sMessage,
									const sal_Bool bShowMessage, const sal_Bool bIsHelpMessage);
	void						WriteValidations(ScXMLExport& rExport);
	const rtl::OUString&		GetValidationName(const sal_Int32 nIndex);
};

//==============================================================================

struct ScMyDefaultStyle
{
	sal_Int32	nIndex;
	sal_Int32	nRepeat;
	sal_Bool	bIsAutoStyle;

	ScMyDefaultStyle() : nIndex(-1), nRepeat(1),
		bIsAutoStyle(sal_True) {}
};

typedef std::vector<ScMyDefaultStyle> ScMyDefaultStyleList;

class ScFormatRangeStyles;

class ScMyDefaultStyles
{
	ScMyDefaultStyleList* pRowDefaults;
	ScMyDefaultStyleList* pColDefaults;

	sal_Int32 GetStyleNameIndex(const ScFormatRangeStyles* pCellStyles,
		const sal_Int32 nTable, const sal_Int32 nPos,
		const sal_Int32 i, const sal_Bool bRow, sal_Bool& bIsAutoStyle);
	void FillDefaultStyles(const sal_Int32 nTable,
		const sal_Int32 nLastRow, const sal_Int32 nLastCol,
		const ScFormatRangeStyles* pCellStyles, ScDocument* pDoc,
		const sal_Bool bRow);
public:
	ScMyDefaultStyles() : pRowDefaults(NULL), pColDefaults(NULL) {}
	~ScMyDefaultStyles();

	void FillDefaultStyles(const sal_Int32 nTable,
		const sal_Int32 nLastRow, const sal_Int32 nLastCol,
		const ScFormatRangeStyles* pCellStyles, ScDocument* pDoc);

	const ScMyDefaultStyleList* GetRowDefaults() { return pRowDefaults; }
	const ScMyDefaultStyleList* GetColDefaults() { return pColDefaults; }
};

struct ScMyRowFormatRange
{
	sal_Int32	nStartColumn;
	sal_Int32	nRepeatColumns;
	sal_Int32	nRepeatRows;
	sal_Int32	nIndex;
	sal_Int32	nValidationIndex;
	sal_Bool	bIsAutoStyle;

	ScMyRowFormatRange();
	sal_Bool operator<(const ScMyRowFormatRange& rRange) const;
};

typedef std::list<ScMyRowFormatRange> ScMyRowFormatRangesList;

class ScRowFormatRanges
{
	ScMyRowFormatRangesList		aRowFormatRanges;
	const ScMyDefaultStyleList*	pRowDefaults;
	const ScMyDefaultStyleList*	pColDefaults;
	sal_uInt32					nSize;

	void AddRange(const sal_Int32 nPrevStartCol, const sal_Int32 nRepeat, const sal_Int32 nPrevIndex,
		const sal_Bool bPrevAutoStyle, const ScMyRowFormatRange& rFormatRange);

public:
	ScRowFormatRanges();
	ScRowFormatRanges(const ScRowFormatRanges* pRanges);
	~ScRowFormatRanges();

	void SetRowDefaults(const ScMyDefaultStyleList* pDefaults) { pRowDefaults = pDefaults; }
	void SetColDefaults(const ScMyDefaultStyleList* pDefaults) { pColDefaults = pDefaults; }
	void Clear();
	void AddRange(ScMyRowFormatRange& rFormatRange, const sal_Int32 nStartRow);
	sal_Bool GetNext(ScMyRowFormatRange& rFormatRange);
	sal_Int32 GetMaxRows();
	sal_Int32 GetSize();
	void Sort();
};

typedef std::vector<rtl::OUString*>		ScMyOUStringVec;

struct ScMyFormatRange
{
	com::sun::star::table::CellRangeAddress aRangeAddress;
	sal_Int32								nStyleNameIndex;
	sal_Int32								nValidationIndex;
	sal_Int32								nNumberFormat;
	sal_Bool								bIsAutoStyle;

	ScMyFormatRange();
	sal_Bool operator< (const ScMyFormatRange& rRange) const;
};

typedef std::list<ScMyFormatRange>			ScMyFormatRangeAddresses;
typedef std::vector<ScMyFormatRangeAddresses*>	ScMyFormatRangeListVec;

class ScFormatRangeStyles
{
	ScMyFormatRangeListVec		aTables;
	ScMyOUStringVec				aStyleNames;
	ScMyOUStringVec				aAutoStyleNames;
	const ScMyDefaultStyleList*	pRowDefaults;
	const ScMyDefaultStyleList*	pColDefaults;

public:
	ScFormatRangeStyles();
	~ScFormatRangeStyles();

	void SetRowDefaults(const ScMyDefaultStyleList* pDefaults) { pRowDefaults = pDefaults; }
	void SetColDefaults(const ScMyDefaultStyleList* pDefaults) { pColDefaults = pDefaults; }
	void AddNewTable(const sal_Int32 nTable);
	sal_Bool AddStyleName(rtl::OUString* pString, sal_Int32& rIndex, const sal_Bool bIsAutoStyle = sal_True);
	sal_Int32 GetIndexOfStyleName(const rtl::OUString& rString, const rtl::OUString& rPrefix, sal_Bool& bIsAutoStyle);
	// does not delete ranges
	sal_Int32 GetStyleNameIndex(const sal_Int32 nTable, const sal_Int32 nColumn, const sal_Int32 nRow,
		sal_Bool& bIsAutoStyle) const;
	// deletes not necessary ranges if wanted
	sal_Int32 GetStyleNameIndex(const sal_Int32 nTable, const sal_Int32 nColumn, const sal_Int32 nRow,
        sal_Bool& bIsAutoStyle, sal_Int32& nValidationIndex, sal_Int32& nNumberFormat, const sal_Int32 nRemoveBeforeRow);
	void GetFormatRanges(const sal_Int32 nStartColumn, const sal_Int32 nEndColumn, const sal_Int32 nRow,
					const sal_Int32 nTable, ScRowFormatRanges* pFormatRanges);
	void AddRangeStyleName(const com::sun::star::table::CellRangeAddress aCellRangeAddress, const sal_Int32 nStringIndex,
					const sal_Bool bIsAutoStyle, const sal_Int32 nValidationIndex, const sal_Int32 nNumberFormat);
	rtl::OUString* GetStyleNameByIndex(const sal_Int32 nIndex, const sal_Bool bIsAutoStyle);
	void Sort();
};

class ScColumnRowStylesBase
{
	ScMyOUStringVec				aStyleNames;

public:
	ScColumnRowStylesBase();
    virtual ~ScColumnRowStylesBase();

	virtual void AddNewTable(const sal_Int32 nTable, const sal_Int32 nFields) = 0;
	sal_Int32 AddStyleName(rtl::OUString* pString);
	sal_Int32 GetIndexOfStyleName(const rtl::OUString& rString, const rtl::OUString& rPrefix);
	virtual rtl::OUString* GetStyleName(const sal_Int32 nTable, const sal_Int32 nField) = 0;
	rtl::OUString* GetStyleNameByIndex(const sal_Int32 nIndex);
};

struct ScColumnStyle
{
	sal_Int32	nIndex;
	sal_Bool	bIsVisible;

	ScColumnStyle() : nIndex(-1), bIsVisible(sal_True) {}
};


typedef std::vector<ScColumnStyle>	ScMyColumnStyleVec;
typedef std::vector<ScMyColumnStyleVec>	ScMyColumnVectorVec;

class ScColumnStyles : public ScColumnRowStylesBase
{
	ScMyColumnVectorVec				aTables;

public:
	ScColumnStyles();
	~ScColumnStyles();

	virtual void AddNewTable(const sal_Int32 nTable, const sal_Int32 nFields);
	sal_Int32 GetStyleNameIndex(const sal_Int32 nTable, const sal_Int32 nField,
		sal_Bool& bIsVisible);
	void AddFieldStyleName(const sal_Int32 nTable, const sal_Int32 nField, const sal_Int32 nStringIndex, const sal_Bool bIsVisible);
	virtual rtl::OUString* GetStyleName(const sal_Int32 nTable, const sal_Int32 nField);
};

typedef std::vector<sal_Int32>	ScMysalInt32Vec;
typedef std::vector<ScMysalInt32Vec>	ScMyRowVectorVec;

class ScRowStyles : public ScColumnRowStylesBase
{
	ScMyRowVectorVec				aTables;

public:
	ScRowStyles();
	~ScRowStyles();

	virtual void AddNewTable(const sal_Int32 nTable, const sal_Int32 nFields);
	sal_Int32 GetStyleNameIndex(const sal_Int32 nTable, const sal_Int32 nField);
	void AddFieldStyleName(const sal_Int32 nTable, const sal_Int32 nField, const sal_Int32 nStringIndex);
	void AddFieldStyleName(const sal_Int32 nTable, const sal_Int32 nStartField, const sal_Int32 nStringIndex, const sal_Int32 nEndField);
	virtual rtl::OUString* GetStyleName(const sal_Int32 nTable, const sal_Int32 nField);
};

#endif

