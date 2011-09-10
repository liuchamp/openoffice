#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2000, 2010 Oracle and/or its affiliates.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# This file is part of OpenOffice.org.
#
# OpenOffice.org is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3
# only, as published by the Free Software Foundation.
#
# OpenOffice.org is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License version 3 for more details
# (a copy is included in the LICENSE file that accompanied this code).
#
# You should have received a copy of the GNU Lesser General Public License
# version 3 along with OpenOffice.org.	If not, see
# <http://www.openoffice.org/license.html>
# for a copy of the LGPLv3 License.
#
#*************************************************************************

$(eval $(call gb_Package_Package,drawinglayer_inc,$(SRCDIR)/drawinglayer/inc))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/drawinglayerdllapi.h,drawinglayer/drawinglayerdllapi.h))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/drawinglayer_primitivetypes2d.hxx,drawinglayer/primitive2d/drawinglayer_primitivetypes2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/transparenceprimitive2d.hxx,drawinglayer/primitive2d/transparenceprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/animatedprimitive2d.hxx,drawinglayer/primitive2d/animatedprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/backgroundcolorprimitive2d.hxx,drawinglayer/primitive2d/backgroundcolorprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/baseprimitive2d.hxx,drawinglayer/primitive2d/baseprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/bitmapprimitive2d.hxx,drawinglayer/primitive2d/bitmapprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/borderlineprimitive2d.hxx,drawinglayer/primitive2d/borderlineprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/chartprimitive2d.hxx,drawinglayer/primitive2d/chartprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/controlprimitive2d.hxx,drawinglayer/primitive2d/controlprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/discretebitmapprimitive2d.hxx,drawinglayer/primitive2d/discretebitmapprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/discreteshadowprimitive2d.hxx,drawinglayer/primitive2d/discreteshadowprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/embedded3dprimitive2d.hxx,drawinglayer/primitive2d/embedded3dprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/fillbitmapprimitive2d.hxx,drawinglayer/primitive2d/fillbitmapprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/fillgradientprimitive2d.hxx,drawinglayer/primitive2d/fillgradientprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawin	glayer/primitive2d/fillhatchprimitive2d.hxx,drawinglayer/primitive2d/fillhatchprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/graphicprimitive2d.hxx,drawinglayer/primitive2d/graphicprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/gridprimitive2d.hxx,drawinglayer/primitive2d/gridprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/groupprimitive2d.hxx,drawinglayer/primitive2d/groupprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/helplineprimitive2d.hxx,drawinglayer/primitive2d/helplineprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/hiddengeometryprimitive2d.hxx,drawinglayer/primitive2d/hiddengeometryprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/invertprimitive2d.hxx,drawinglayer/primitive2d/invertprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/markerarrayprimitive2d.hxx,drawinglayer/primitive2d/markerarrayprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/maskprimitive2d.hxx,drawinglayer/primitive2d/maskprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/mediaprimitive2d.hxx,drawinglayer/primitive2d/mediaprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/metafileprimitive2d.hxx,drawinglayer/primitive2d/metafileprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/modifiedcolorprimitive2d.hxx,drawinglayer/primitive2d/modifiedcolorprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/pagepreviewprimitive2d.hxx,drawinglayer/primitive2d/pagepreviewprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/pointarrayprimitive2d.hxx,drawinglayer/primitive2d/pointarrayprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/polygonprimitive2d.hxx,drawinglayer/primitive2d/polygonprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/polypolygonprimitive2d.hxx,drawinglayer/primitive2d/polypolygonprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/primitivetools2d.hxx,drawinglayer/primitive2d/primitivetools2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/sdrdecompositiontools2d.hxx,drawinglayer/primitive2d/sdrdecompositiontools2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/sceneprimitive2d.hxx,drawinglayer/primitive2d/sceneprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/shadowprimitive2d.hxx,drawinglayer/primitive2d/shadowprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/structuretagprimitive2d.hxx,drawinglayer/primitive2d/structuretagprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/textenumsprimitive2d.hxx,drawinglayer/primitive2d/textenumsprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/texteffectprimitive2d.hxx,drawinglayer/primitive2d/texteffectprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/textlayoutdevice.hxx,drawinglayer/primitive2d/textlayoutdevice.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/textprimitive2d.hxx,drawinglayer/primitive2d/textprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/textdecoratedprimitive2d.hxx,drawinglayer/primitive2d/textdecoratedprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/texthierarchyprimitive2d.hxx,drawinglayer/primitive2d/texthierarchyprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/transformprimitive2d.hxx,drawinglayer/primitive2d/transformprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/unifiedtransparenceprimitive2d.hxx,drawinglayer/primitive2d/unifiedtransparenceprimitive2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive2d/wrongspellprimitive2d.hxx,drawinglayer/primitive2d/wrongspellprimitive2d.hxx))

$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/drawinglayer_primitivetypes3d.hxx,drawinglayer/primitive3d/drawinglayer_primitivetypes3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/baseprimitive3d.hxx,drawinglayer/primitive3d/baseprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/groupprimitive3d.hxx,drawinglayer/primitive3d/groupprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/hatchtextureprimitive3d.hxx,drawinglayer/primitive3d/hatchtextureprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/modifiedcolorprimitive3d.hxx,drawinglayer/primitive3d/modifiedcolorprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/polygonprimitive3d.hxx,drawinglayer/primitive3d/polygonprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/polygontubeprimitive3d.hxx,drawinglayer/primitive3d/polygontubeprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/polypolygonprimitive3d.hxx,drawinglayer/primitive3d/polypolygonprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/sdrcubeprimitive3d.hxx,drawinglayer/primitive3d/sdrcubeprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/sdrdecompositiontools3d.hxx,drawinglayer/primitive3d/sdrdecompositiontools3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/sdrextrudelathetools3d.hxx,drawinglayer/primitive3d/sdrextrudelathetools3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/sdrextrudeprimitive3d.hxx,drawinglayer/primitive3d/sdrextrudeprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/sdrlatheprimitive3d.hxx,drawinglayer/primitive3d/sdrlatheprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/sdrpolypolygonprimitive3d.hxx,drawinglayer/primitive3d/sdrpolypolygonprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/sdrprimitive3d.hxx,drawinglayer/primitive3d/sdrprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/sdrsphereprimitive3d.hxx,drawinglayer/primitive3d/sdrsphereprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/shadowprimitive3d.hxx,drawinglayer/primitive3d/shadowprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/textureprimitive3d.hxx,drawinglayer/primitive3d/textureprimitive3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/primitive3d/transformprimitive3d.hxx,drawinglayer/primitive3d/transformprimitive3d.hxx))

$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/animation/animationtiming.hxx,drawinglayer/animation/animationtiming.hxx))

$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/geometry/viewinformation2d.hxx,drawinglayer/geometry/viewinformation2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/geometry/viewinformation3d.hxx,drawinglayer/geometry/viewinformation3d.hxx))

$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor2d/baseprocessor2d.hxx,drawinglayer/processor2d/baseprocessor2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor2d/vclprocessor2d.hxx,drawinglayer/processor2d/vclprocessor2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor2d/vclpixelprocessor2d.hxx,drawinglayer/processor2d/vclpixelprocessor2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor2d/vclmetafileprocessor2d.hxx,drawinglayer/processor2d/vclmetafileprocessor2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor2d/canvasprocessor.hxx,drawinglayer/processor2d/canvasprocessor.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor2d/contourextractor2d.hxx,drawinglayer/processor2d/contourextractor2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor2d/linegeometryextractor2d.hxx,drawinglayer/processor2d/linegeometryextractor2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor2d/hittestprocessor2d.hxx,drawinglayer/processor2d/hittestprocessor2d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor2d/textaspolygonextractor2d.hxx,drawinglayer/processor2d/textaspolygonextractor2d.hxx))

$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor3d/baseprocessor3d.hxx,drawinglayer/processor3d/baseprocessor3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor3d/cutfindprocessor3d.hxx,drawinglayer/processor3d/cutfindprocessor3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor3d/defaultprocessor3d.hxx,drawinglayer/processor3d/defaultprocessor3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/processor3d/zbufferprocessor3d.hxx,drawinglayer/processor3d/zbufferprocessor3d.hxx))

$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/fillgradientattribute.hxx,drawinglayer/attribute/fillgradientattribute.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/fillhatchattribute.hxx,drawinglayer/attribute/fillhatchattribute.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/fillbitmapattribute.hxx,drawinglayer/attribute/fillbitmapattribute.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/fontattribute.hxx,drawinglayer/attribute/fontattribute.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/materialattribute3d.hxx,drawinglayer/attribute/materialattribute3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/sdrallattribute3d.hxx,drawinglayer/attribute/sdrallattribute3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/sdrlineattribute.hxx,drawinglayer/attribute/sdrlineattribute.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/sdrlinestartendattribute.hxx,drawinglayer/attribute/sdrlinestartendattribute.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/sdrshadowattribute.hxx,drawinglayer/attribute/sdrshadowattribute.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/sdrfillattribute.hxx,drawinglayer/attribute/sdrfillattribute.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/sdrobjectattribute3d.hxx,drawinglayer/attribute/sdrobjectattribute3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/sdrlightattribute3d.hxx,drawinglayer/attribute/sdrlightattribute3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/sdrlightingattribute3d.hxx,drawinglayer/attribute/sdrlightingattribute3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/sdrsceneattribute3d.hxx,drawinglayer/attribute/sdrsceneattribute3d.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/sdrfillbitmapattribute.hxx,drawinglayer/attribute/sdrfillbitmapattribute.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/strokeattribute.hxx,drawinglayer/attribute/strokeattribute.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/lineattribute.hxx,drawinglayer/attribute/lineattribute.hxx))
$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/attribute/linestartendattribute.hxx,drawinglayer/attribute/linestartendattribute.hxx))

$(eval $(call gb_Package_add_file,drawinglayer_inc,inc/drawinglayer/texture/texture.hxx,drawinglayer/texture/texture.hxx))
