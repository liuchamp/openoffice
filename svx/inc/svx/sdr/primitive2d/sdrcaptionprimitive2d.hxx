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



#ifndef INCLUDED_SDR_PRIMITIVE2D_SDRCAPTIONPRIMITIVE2D_HXX
#define INCLUDED_SDR_PRIMITIVE2D_SDRCAPTIONPRIMITIVE2D_HXX

#include <drawinglayer/primitive2d/baseprimitive2d.hxx>
#include <basegfx/matrix/b2dhommatrix.hxx>
#include <svx/sdr/attribute/sdrlinefillshadowtextattribute.hxx>
#include <basegfx/polygon/b2dpolygon.hxx>

//////////////////////////////////////////////////////////////////////////////
// predefines

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace primitive2d
	{
		class SdrCaptionPrimitive2D : public BufferedDecompositionPrimitive2D
		{
		private:
			::basegfx::B2DHomMatrix						maTransform;
			attribute::SdrLineFillShadowTextAttribute	maSdrLFSTAttribute;
			::basegfx::B2DPolygon						maTail;
			double										mfCornerRadiusX;	// [0.0..1.0] relative to 1/2 width
			double										mfCornerRadiusY;	// [0.0..1.0] relative to 1/2 height

		protected:
			// local decomposition.
			virtual Primitive2DSequence create2DDecomposition(const geometry::ViewInformation2D& aViewInformation) const;

		public:
			SdrCaptionPrimitive2D(
				const ::basegfx::B2DHomMatrix& rTransform, 
				const attribute::SdrLineFillShadowTextAttribute& rSdrLFSTAttribute,
				const ::basegfx::B2DPolygon& rTail, 
				double fCornerRadiusX = 0.0, 
				double fCornerRadiusY = 0.0);

			// compare operator
			virtual bool operator==(const BasePrimitive2D& rPrimitive) const;

			// data access
			const ::basegfx::B2DHomMatrix& getTransform() const { return maTransform; }
			const attribute::SdrLineFillShadowTextAttribute& getSdrLFSTAttribute() const { return maSdrLFSTAttribute; }
			const ::basegfx::B2DPolygon& getTail() const { return maTail; }
			double getCornerRadiusX() const { return mfCornerRadiusX; }
			double getCornerRadiusY() const { return mfCornerRadiusY; }
			bool isCornerRadiusUsed() const { return (0.0 != mfCornerRadiusX || 0.0 != mfCornerRadiusY); }

			// provide unique ID
			DeclPrimitrive2DIDBlock()
		};
	} // end of namespace primitive2d
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////

#endif //INCLUDED_SDR_PRIMITIVE2D_SDRCAPTIONPRIMITIVE2D_HXX

// eof
