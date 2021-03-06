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
#include "precompiled_connectivity.hxx"
#include "file/fanalyzer.hxx"
#include "connectivity/sqlparse.hxx"
#include <osl/diagnose.h>
#include <tools/debug.hxx>
#include <comphelper/extract.hxx>
#include "connectivity/sqlnode.hxx"
#include "connectivity/dbexception.hxx"
#include "file/FConnection.hxx"
#include "resource/file_res.hrc"

using namespace ::connectivity;
using namespace ::connectivity::file;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::container;

DBG_NAME( file_OSQLAnalyzer )
//------------------------------------------------------------------
OSQLAnalyzer::OSQLAnalyzer(OConnection* _pConnection)
			   :m_pConnection(_pConnection)
               ,m_bHasSelectionCode(sal_False)
               ,m_bSelectionFirstTime(sal_True)
{
	DBG_CTOR( file_OSQLAnalyzer, NULL );
	m_aCompiler = new OPredicateCompiler(this);
	m_aInterpreter = new OPredicateInterpreter(m_aCompiler);
}

// -----------------------------------------------------------------------------
OSQLAnalyzer::~OSQLAnalyzer()
{
	DBG_DTOR( file_OSQLAnalyzer, NULL );
}

// -----------------------------------------------------------------------------
void OSQLAnalyzer::setIndexes(const Reference< XNameAccess>& _xIndexes)
{
	m_aCompiler->m_xIndexes = _xIndexes;
}
//------------------------------------------------------------------
void OSQLAnalyzer::start(OSQLParseNode* pSQLParseNode)
{
	if (SQL_ISRULE(pSQLParseNode,select_statement))
	{
		DBG_ASSERT(pSQLParseNode->count() >= 4,"OFILECursor: Fehler im Parse Tree");

		// check that we don't use anything other than count(*) as function
		OSQLParseNode* pSelection = pSQLParseNode->getChild(2);
		if ( SQL_ISRULE(pSelection,scalar_exp_commalist) )
		{
			for (sal_uInt32 i = 0; i < pSelection->count(); i++)
			{
				OSQLParseNode *pColumnRef = pSelection->getChild(i)->getChild(0);
				if (	( SQL_ISRULE(pColumnRef,set_fct_spec) && pColumnRef->count() == 4 )
					||	SQL_ISRULE(pColumnRef,char_value_fct)
					||	SQL_ISRULE(pColumnRef,char_substring_fct)
					||	SQL_ISRULE(pColumnRef,position_exp)
					||	SQL_ISRULE(pColumnRef,fold)
					||	SQL_ISRULE(pColumnRef,length_exp)
                    ||	SQL_ISRULE(pColumnRef,num_value_exp)
                    ||	SQL_ISRULE(pColumnRef,term)
                    ||	SQL_ISRULE(pColumnRef,factor)
					||	SQL_ISRULE(pColumnRef,set_fct_spec) )
				{
					::vos::ORef<OPredicateCompiler>		pCompiler = new OPredicateCompiler(this);
					pCompiler->setOrigColumns(m_aCompiler->getOrigColumns());
					::vos::ORef<OPredicateInterpreter>	pInterpreter = new OPredicateInterpreter(pCompiler);
					pCompiler->execute( pColumnRef );
					m_aSelectionEvaluations.push_back( TPredicates(pCompiler,pInterpreter) );
				}
				else if ( ( SQL_ISRULE(pColumnRef,general_set_fct) && pColumnRef->count() != 4 ) )
				{
					m_pConnection->throwGenericSQLException(STR_QUERY_COMPLEX_COUNT,NULL);
				}
				else
                {
                    if  (   SQL_ISPUNCTUATION( pColumnRef, "*" )
                        ||  (   SQL_ISRULE( pColumnRef, column_ref )
                            &&  ( pColumnRef->count() == 3 )
                            &&  ( pColumnRef->getChild(0)->getNodeType() == SQL_NODE_NAME )
                            &&  SQL_ISPUNCTUATION( pColumnRef->getChild(1), "." )
                            &&  SQL_ISRULE( pColumnRef->getChild(2), column_val )
                            &&  SQL_ISPUNCTUATION( pColumnRef->getChild(2)->getChild(0), "*" )
                            )
                        )
                    {
                        // push one element for each column of our table
                        const Reference< XNameAccess > xColumnNames( m_aCompiler->getOrigColumns() );
                        const Sequence< ::rtl::OUString > aColumnNames( xColumnNames->getElementNames() );
                        for ( sal_Int32 j=0; j<aColumnNames.getLength(); ++j )
					        m_aSelectionEvaluations.push_back( TPredicates() );
                    }
                    else
					    m_aSelectionEvaluations.push_back( TPredicates() );
                }
			}
		}
	}

	m_aCompiler->start(pSQLParseNode);
}

//------------------------------------------------------------------
void OSQLAnalyzer::bindRow(OCodeList& rCodeList,const OValueRefRow& _pRow,OEvaluateSetList& _rEvaluateSetList)
{
	// Zaehlen, wieviele Kriterien
	// wenn nur ein Kriterium, und das entsprechende Feld ist indiziert
	// dann wird der Index verwendet

	OEvaluateSet*		pEvaluateSet = NULL;

	for (OCodeList::iterator aIter = rCodeList.begin(); aIter != rCodeList.end(); ++aIter)
	{
		OOperandAttr* pAttr = PTR_CAST(OOperandAttr,(*aIter));
		if (pAttr)
		{
			if (pAttr->isIndexed() && !m_aCompiler->hasORCondition())
			{
				OCode* pCode1 = *(aIter + 1);
				OCode* pCode2 = *(aIter + 2);

				if (PTR_CAST(OOperand,pCode1))
					pEvaluateSet = pAttr->preProcess(PTR_CAST(OBoolOperator,pCode2), PTR_CAST(OOperand,pCode1));
				else
					pEvaluateSet = pAttr->preProcess(PTR_CAST(OBoolOperator,pCode1));
			}

			if (pEvaluateSet)
			{
				_rEvaluateSetList.push_back(pEvaluateSet);
				pEvaluateSet = NULL;
			}
			pAttr->bindValue(_pRow);
		}
	}
}
//------------------------------------------------------------------
void OSQLAnalyzer::bindSelectRow(const OValueRefRow& _pRow)
{
	// first the select part
	OEvaluateSetList	aEvaluateSetList;
	for ( ::std::vector< TPredicates >::iterator aIter = m_aSelectionEvaluations.begin(); aIter != m_aSelectionEvaluations.end();++aIter)
	{
		if ( aIter->first.isValid() )
			bindRow( aIter->first->m_aCodeList,_pRow,aEvaluateSetList);
	}
}
//------------------------------------------------------------------
::std::vector<sal_Int32>* OSQLAnalyzer::bindEvaluationRow(OValueRefRow& _pRow)
{
	OEvaluateSetList	aEvaluateSetList;
	bindRow( m_aCompiler->m_aCodeList,_pRow,aEvaluateSetList);

	::std::vector<sal_Int32>*	pKeySet		 = NULL;
	OEvaluateSet*				pEvaluateSet = NULL;

	// Keyset erzeugen mit kleinster Liste
	if(!aEvaluateSetList.empty())
	{
		// welche Liste hat den kleinsten count ?
		OEvaluateSetList::iterator i = aEvaluateSetList.begin();
		pEvaluateSet = *(i);
		for(++i; i != aEvaluateSetList.end();++i)
		{
			OEvaluateSet*	pEvaluateSetComp = (*i);
			for(OEvaluateSet::reverse_iterator j = pEvaluateSet->rbegin(); j != pEvaluateSet->rend(); ++j)
			{
				if (pEvaluateSetComp->find(j->second) != pEvaluateSetComp->end())
					pEvaluateSet->erase(j->second);
			}
		}
		pKeySet = new ::std::vector<sal_Int32>(pEvaluateSet->size());
		sal_Int32 k=0;
		for(OEvaluateSet::iterator j = pEvaluateSet->begin(); j != pEvaluateSet->end(); ++j,++k)
		{
			(*pKeySet)[k] = j->second;
		}

		// alle loeschen
		for(i = aEvaluateSetList.begin(); i != aEvaluateSetList.end();++i)
			delete (*i);
	}

	return pKeySet;
}

//------------------------------------------------------------------
void OSQLAnalyzer::describeParam(::vos::ORef<OSQLColumns> rParameterColumns)
{
	OCodeList& rCodeList	= m_aCompiler->m_aCodeList;
	OCodeStack aCodeStack;

	if (!rCodeList.size())
        return;     // kein Praedikat
	if (!rParameterColumns->get().size())
		return; // keine Parameter

    // Anlegen von Columns, die eine genauere Beschreibung fuer die enthalten
	::vos::ORef<OSQLColumns> aNewParamColumns = new OSQLColumns(*rParameterColumns);


    // Anlegen einer Testzeile, wird benoetigt um die Parameter zu beschreiben
	OValueRefRow aParameterRow  = new OValueRefVector(rParameterColumns->get().size());
	bindParameterRow(aParameterRow);

	OValueRefRow aTestRow = new OValueRefVector(Reference< XIndexAccess>(m_aCompiler->getOrigColumns(),UNO_QUERY)->getCount());
	delete bindEvaluationRow(aTestRow);					// Binden der Attribute an die Values

	for(OCodeList::iterator aIter = rCodeList.begin(); aIter != rCodeList.end(); ++aIter)
	{
		OOperand* pOperand = PTR_CAST(OOperand,(*aIter));
		OOperator* pOperator = PTR_CAST(OOperator,(*aIter));
		if (pOperand)
			aCodeStack.push(pOperand);
		else
		{
            if (pOperator->getRequestedOperands() == 2)     // bei zwei Operatoren ist es moeglich
			{												// einen Parameter weiter zu spezifizieren
				OOperandParam *pParam  = PTR_CAST(OOperandParam,aCodeStack.top());
				if (pParam)  // Anpassen des ParameterTyps, wenn der linke Operand ein Attribut ist
				{
					OOperandAttr *pLeft	 = PTR_CAST(OOperandAttr,*(rCodeList.end() - 2));
					if (pLeft)
					{
						Reference< XPropertySet> xCol;
						Reference< XIndexAccess>(m_aCompiler->getOrigColumns(),UNO_QUERY)->getByIndex(pLeft->getRowPos()) >>= xCol;
                        OSL_ENSURE(xCol.is(), "Ungueltige Struktur");
						pParam->describe(xCol, aNewParamColumns);
					}
				}
			}
			pOperator->Exec(aCodeStack);
		}
	}
	OOperand* pOperand = aCodeStack.top();
	aCodeStack.pop();

	OSL_ENSURE(aCodeStack.size() == 0, "StackFehler");
	OSL_ENSURE(pOperand, "StackFehler");
	if (IS_TYPE(OOperandResult,pOperand))
		delete pOperand;
	else
		OSL_ENSURE(0,"Illegal here!");

	rParameterColumns = aNewParamColumns;
	//	m_aCompiler->setParameterColumns(rParameterColumns);
}

// -----------------------------------------------------------------------------
OOperandAttr* OSQLAnalyzer::createOperandAttr(sal_Int32 _nPos,
											  const Reference< XPropertySet>& _xCol,
											  const Reference< XNameAccess>& /*_xIndexes*/)
{
	return new OOperandAttr(static_cast<sal_uInt16>(_nPos),_xCol);
}
// -----------------------------------------------------------------------------
sal_Bool OSQLAnalyzer::hasRestriction() const
{
	return m_aCompiler->hasCode();
}
// -----------------------------------------------------------------------------
sal_Bool OSQLAnalyzer::hasFunctions() const
{
	if ( m_bSelectionFirstTime )
	{
		m_bSelectionFirstTime = sal_False;
		for ( ::std::vector< TPredicates >::const_iterator aIter = m_aSelectionEvaluations.begin(); aIter != m_aSelectionEvaluations.end() && !m_bHasSelectionCode ;++aIter)
		{
			if ( aIter->first.isValid() )
				m_bHasSelectionCode = aIter->first->hasCode();
		}
	}
	return m_bHasSelectionCode;;
}
// -----------------------------------------------------------------------------
void OSQLAnalyzer::setSelectionEvaluationResult(OValueRefRow& _pRow,const ::std::vector<sal_Int32>& _rColumnMapping)
{
	sal_Int32 nPos = 1;
	for ( ::std::vector< TPredicates >::iterator aIter = m_aSelectionEvaluations.begin(); aIter != m_aSelectionEvaluations.end();++aIter,++nPos)
	{
		if ( aIter->second.isValid() )
		{
			// the first column (index 0) is for convenience only. The first real select column is no 1.
			sal_Int32	map = nPos;
			if ( nPos < static_cast< sal_Int32 >( _rColumnMapping.size() ) )
				map = _rColumnMapping[nPos];
            if ( map > 0 )
			    aIter->second->startSelection( (_pRow->get())[map] );
		}
	}
}
// -----------------------------------------------------------------------------
void OSQLAnalyzer::dispose()
{
	m_aCompiler->dispose();
	for ( ::std::vector< TPredicates >::iterator aIter = m_aSelectionEvaluations.begin(); aIter != m_aSelectionEvaluations.end();++aIter)
	{
		if ( aIter->first.isValid() )
			aIter->first->dispose();
	}
}
// -----------------------------------------------------------------------------
void OSQLAnalyzer::setOrigColumns(const OFileColumns& rCols)
{
	m_aCompiler->setOrigColumns(rCols);
	for ( ::std::vector< TPredicates >::iterator aIter = m_aSelectionEvaluations.begin(); aIter != m_aSelectionEvaluations.end();++aIter)
	{
		if ( aIter->first.isValid() )
			aIter->first->setOrigColumns(rCols);
	}
}
// -----------------------------------------------------------------------------
