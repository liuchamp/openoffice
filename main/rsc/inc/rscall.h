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


#ifndef _RSCALL_H
#define _RSCALL_H

#include <tools/string.hxx>
#include <rsctools.hxx>
#include <rscerror.h>
#include <rscdef.hxx>
#include <rschash.hxx>
#include <rtl/alloc.h>

/******************* T y p e s *******************************************/
typedef char * CLASS_DATA;	// Zeiger auf die Daten einer Klasse

/******************* C l a s s e s	 F o r w a r d s *********************/
class RscCompiler;
class RscTop;
class RscTypCont;
class RscIncList;

/******************* G l o b a l   V a r i a b l e s *********************/
extern ByteString*	pStdParType;
extern ByteString*	pStdPar1;
extern ByteString*	pStdPar2;
extern ByteString*	pWinParType;
extern ByteString*	pWinPar1;
extern ByteString*	pWinPar2;
extern sal_uInt32		nRefDeep;
extern sal_uInt32		nRsc_XYMAPMODEId;
extern sal_uInt32		nRsc_WHMAPMODEId;
extern sal_uInt32		nRsc_X;
extern sal_uInt32		nRsc_Y;
extern sal_uInt32		nRsc_WIDTH;
extern sal_uInt32		nRsc_HEIGHT;
extern sal_uInt32		nRsc_DELTALANG;
extern sal_uInt32		nRsc_DELTASYSTEM;
extern sal_uInt32		nRsc_EXTRADATA;
extern AtomContainer*   pHS;

/******************* D e f i n e s ***************************************/

#define HELP_FLAG		  0x0001  // Hilfe anzeigen
#define NOPREPRO_FLAG	  0x0002  // kein Preprozesor
#define NOSYNTAX_FLAG	  0x0004  // keine Syntaxanalyse
#define NOLINK_FLAG 	  0x0008  // nicht linken
#define NORESFILE_FLAG	  0x0010  // keine .res-Datei erzeugen
#define DEFINE_FLAG 	  0x0020  // es wurde Definitionen angegeben
#define INCLUDE_FLAG	  0x0040  // der Include-Pfad wurde erweitert
#define MSCPREPRO_FLAG	  0x0080  // spezial Preprozessor
#define PRINTSYNTAX_FLAG  0x0100  // Syntax ausgeben
#define PRELOAD_FLAG	  0x0200  // Alle Ressourcen Preloaden
#define SMART_FLAG		  0x0400  // abgekuertze Name
#define SRSDEFAULT_FLAG   0x1000  // immer der Default geschrieben
#define NOSYSRESTEST_FLAG 0x2000  // ueberprueft nicht die Richtigkeit von (bmp, ico, cur)


/******************* T y p e s *******************************************/
enum RSCCLASS_TYPE	{ RSCCLASS_BOOL, RSCCLASS_STRING, RSCCLASS_NUMBER,
						RSCCLASS_CONST, RSCCLASS_COMPLEX, RSCCLASS_ENUMARRAY };

typedef void (* VarEnumCallbackProc)( void * pData, RSCCLASS_TYPE, Atom );

/******************* S t r u c t s ***************************************/
struct RSCINST {
	RscTop *	pClass;
	CLASS_DATA	pData;

				RSCINST(){ pClass = NULL; pData = NULL; }
				RSCINST( RscTop * pCl, CLASS_DATA pClassData ){
					pClass = pCl;
					pData = pClassData;
				}
	sal_Bool		IsInst() const { return( pData != NULL ); }
};

/********************** S U B I N F O S T R U C T ************************/
struct SUBINFO_STRUCT {
	SUBINFO_STRUCT(){ nPos = 0; pClass = NULL; };
	RscId	     aId;	 // Identifier der Resource
	sal_uInt32	 nPos;	 // Position der Resource
	RscTop *     pClass; // Klasse des Eintrages
};

/******************* F u n c t i o n *************************************/
void InitRscCompiler();

#endif // _RSCALL_H
