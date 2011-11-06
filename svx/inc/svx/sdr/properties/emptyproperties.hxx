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



#ifndef _SDR_PROPERTIES_EMPTYPROPERTIES_HXX
#define _SDR_PROPERTIES_EMPTYPROPERTIES_HXX

#include <svx/sdr/properties/properties.hxx>
#include "svx/svxdllapi.h"

//////////////////////////////////////////////////////////////////////////////

namespace sdr
{
	namespace properties
	{
		class SVX_DLLPUBLIC EmptyProperties : public BaseProperties
		{
		protected:
			// the to be used ItemSet
			SfxItemSet*										mpEmptyItemSet;

			// create a new itemset
			virtual SfxItemSet& CreateObjectSpecificItemSet(SfxItemPool& rPool);

			// test changeability for a single item
			virtual sal_Bool AllowItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0) const;

			// Do the ItemChange, may do special handling
			virtual void ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0);

			// Called after ItemChange() is done for all items.
			virtual void PostItemChange(const sal_uInt16 nWhich);

			// react on ItemSet changes
			virtual void ItemSetChanged(const SfxItemSet& rSet);

		public:
			// basic constructor
			EmptyProperties(SdrObject& rObj);

			// constructor for copying, but using new object
			EmptyProperties(const EmptyProperties& rProps, SdrObject& rObj);

			// destructor
			virtual ~EmptyProperties();
			
			// Clone() operator, normally just calls the local copy constructor
			virtual BaseProperties& Clone(SdrObject& rObj) const;

			// get itemset
			virtual const SfxItemSet& GetObjectItemSet() const;

			// set single item
			virtual void SetObjectItem(const SfxPoolItem& rItem);

			// set single item direct, do not do any notifies or things like that
			virtual void SetObjectItemDirect(const SfxPoolItem& rItem);

			// clear single item
			virtual void ClearObjectItem(const sal_uInt16 nWhich = 0);

			// clear single item direct, do not do any notifies or things like that.
			// Also supports complete deleteion of items when default parameter 0 is used.
			virtual void ClearObjectItemDirect(const sal_uInt16 nWhich = 0);

			// set complete item set
			virtual void SetObjectItemSet(const SfxItemSet& rSet);

			// set a new StyleSheet and broadcast
			virtual void SetStyleSheet(SfxStyleSheet* pNewStyleSheet, sal_Bool bDontRemoveHardAttr);

			// get the installed StyleSheet
			virtual SfxStyleSheet* GetStyleSheet() const;
		};
	} // end of namespace properties
} // end of namespace sdr

#endif //_SDR_PROPERTIES_EMPTYPROPERTIES_HXX

// eof
