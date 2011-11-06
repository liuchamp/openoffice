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



#ifndef _SDR_ATTRIBUTE_SDRTEXTATTRIBUTE_HXX
#define _SDR_ATTRIBUTE_SDRTEXTATTRIBUTE_HXX

#include <sal/types.h>
#include <svx/xenum.hxx>
#include <editeng/outlobj.hxx>
#include <svx/sdtaitm.hxx>

//////////////////////////////////////////////////////////////////////////////
// predefines

class SdrText;

namespace drawinglayer { namespace animation { 
	class AnimationEntryList; 
}}

namespace drawinglayer { namespace attribute { 
	class SdrFormTextAttribute; 
}}

namespace drawinglayer { namespace attribute {
	class ImpSdrTextAttribute;
}}

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace attribute
	{
		class SdrTextAttribute
		{
        private:
            ImpSdrTextAttribute*		mpSdrTextAttribute;

		public:
            /// constructors/assignmentoperator/destructor
			SdrTextAttribute(
				const SdrText& rSdrText, 
                const OutlinerParaObject& rOutlinerParaObject,
				XFormTextStyle eFormTextStyle, 
				sal_Int32 aTextLeftDistance, 
				sal_Int32 aTextUpperDistance,
				sal_Int32 aTextRightDistance, 
				sal_Int32 aTextLowerDistance, 
                SdrTextHorzAdjust aSdrTextHorzAdjust,
                SdrTextVertAdjust aSdrTextVertAdjust,
				bool bContour, 
                bool bFitToSize, 
				bool bHideContour, 
                bool bBlink, 
				bool bScroll,
                bool bInEditMode,
                bool bFixedCellHeight,
				bool bWrongSpell);
			SdrTextAttribute();
			SdrTextAttribute(const SdrTextAttribute& rCandidate);
			SdrTextAttribute& operator=(const SdrTextAttribute& rCandidate);
			~SdrTextAttribute();

            // checks if the incarnation is default constructed
            bool isDefault() const;

            // compare operator
			bool operator==(const SdrTextAttribute& rCandidate) const;

			// data read access
			const SdrText& getSdrText() const;
            const OutlinerParaObject& getOutlinerParaObject() const;
			bool isContour() const;
			bool isFitToSize() const;
			bool isHideContour() const;
			bool isBlink() const;
			bool isScroll() const;
            bool isInEditMode() const;
            bool isFixedCellHeight() const;
			bool isWrongSpell() const;
            const SdrFormTextAttribute& getSdrFormTextAttribute() const;
			sal_Int32 getTextLeftDistance() const;
			sal_Int32 getTextUpperDistance() const;
			sal_Int32 getTextRightDistance() const;
			sal_Int32 getTextLowerDistance() const;
            sal_uInt32 getPropertiesVersion() const;
            SdrTextHorzAdjust getSdrTextHorzAdjust() const;
            SdrTextVertAdjust getSdrTextVertAdjust() const;

			// helpers: animation timing generators
			void getBlinkTextTiming(
				drawinglayer::animation::AnimationEntryList& rAnimList) const;
			void getScrollTextTiming(
				drawinglayer::animation::AnimationEntryList& rAnimList, 
				double fFrameLength, 
				double fTextLength) const;
		};
	} // end of namespace attribute
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////

#endif // _SDR_ATTRIBUTE_SDRTEXTATTRIBUTE_HXX

// eof
