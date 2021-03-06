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



#ifndef _CPPCANVAS_VCLFACTORY_HXX
#define _CPPCANVAS_VCLFACTORY_HXX

#include <cppcanvas/canvas.hxx>
#include <cppcanvas/bitmapcanvas.hxx>
#include <cppcanvas/spritecanvas.hxx>
#include <cppcanvas/polypolygon.hxx>
#include <cppcanvas/bitmap.hxx>
#include <cppcanvas/renderer.hxx>
#include <cppcanvas/text.hxx>
#include <cppcanvas/sprite.hxx>

#include <cppcanvas/cppcanvasdllapi.h>

class Window;
class Bitmap;
class BitmapEx;
class Polygon;
class PolyPolygon;
class Size;
class Graphic;
class GDIMetaFile;
class Animation;

namespace rtl
{
    class OUString;
}
namespace com { namespace sun { namespace star { namespace rendering 
{
    class  XBitmapCanvas;
    class  XSpriteCanvas;
} } } }

/* Definition of VCLFactory class */

namespace cppcanvas
{
    /** The VCLFactory creates Canvas objects for various VCL
        OutputDevice primitives, such as windows, polygons, bitmaps
        and metafiles.

        Please note that the objects created for a specific Canvas can
        only be drawn on exactly that canvas. You have to regenerate
        them for different canvases.
     */
    class CPPCANVAS_DLLPUBLIC VCLFactory
    {
    public:
        static VCLFactory& getInstance();

        BitmapCanvasSharedPtr 	createCanvas( const ::Window& rVCLWindow );
        BitmapCanvasSharedPtr 	createCanvas( const ::com::sun::star::uno::Reference< 
                                              			::com::sun::star::rendering::XBitmapCanvas >& xCanvas );

        SpriteCanvasSharedPtr 	createSpriteCanvas( const ::Window& rVCLWindow ) const;
        SpriteCanvasSharedPtr 	createSpriteCanvas( const ::com::sun::star::uno::Reference< 
                                              				 ::com::sun::star::rendering::XSpriteCanvas >& xCanvas ) const;
        SpriteCanvasSharedPtr 	createFullscreenSpriteCanvas( const ::Window& rVCLWindow, const Size& rFullscreenSize ) const;

        /** Create a polygon from a tools::Polygon

			The created polygon initially has the same size in user
			coordinate space as the source polygon
         */
        PolyPolygonSharedPtr 	createPolyPolygon( const CanvasSharedPtr&, const ::Polygon& rPoly ) const;
        PolyPolygonSharedPtr 	createPolyPolygon( const CanvasSharedPtr&, const ::PolyPolygon& rPoly ) const;

        /** Create an uninitialized bitmap with the given size
         */
        BitmapSharedPtr 		createBitmap( const CanvasSharedPtr&, const ::Size& rSize ) const; 

        /** Create an uninitialized alpha bitmap with the given size
         */
        BitmapSharedPtr 		createAlphaBitmap( const CanvasSharedPtr&, const ::Size& rSize ) const; 

        /** Create a bitmap from a VCL Bitmap
         */
        BitmapSharedPtr 		createBitmap( const CanvasSharedPtr&, const ::Bitmap& rBitmap ) const; 
        BitmapSharedPtr 		createBitmap( const CanvasSharedPtr&, const ::BitmapEx& rBmpEx ) const;

        /** Create a renderer object from a Graphic

			The created renderer initially draws the graphic
			one-by-one units large, in user coordinate space
         */
        RendererSharedPtr 		createRenderer( const CanvasSharedPtr&			rCanvas, 
                                                const ::Graphic& 				rGraphic,
                                                const Renderer::Parameters& 	rParms ) const;
        /** Create a renderer object from a Metafile

			The created renderer initially draws the metafile
			one-by-one units large, in user coordinate space
         */
        RendererSharedPtr 		createRenderer( const CanvasSharedPtr&			rCanvas, 
                                                const ::GDIMetaFile& 			rMtf,
                                                const Renderer::Parameters& 	rParms ) const;

        /** Create an animated sprite from a VCL animation
         */
        SpriteSharedPtr 		createAnimatedSprite( const SpriteCanvasSharedPtr&, const ::Animation& rAnim ) const;

        /** Create a text portion with the given content string 
         */
        TextSharedPtr 			createText( const CanvasSharedPtr&, const ::rtl::OUString& ) const;

    private:
        friend struct InitInstance;

        // singleton
        VCLFactory();
        ~VCLFactory();

        // default: disabled copy/assignment
        VCLFactory(const VCLFactory&);
        VCLFactory& operator=( const VCLFactory& );
    };

}

#endif /* _CPPCANVAS_VCLFACTORY_HXX */
