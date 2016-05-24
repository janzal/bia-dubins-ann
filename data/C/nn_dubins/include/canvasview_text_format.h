/*
 * File name: canvasview_text_format.h
 * Date:      2008/09/10 11:24
 * Author:    Jan Faigl
 */

#ifndef __CANVASVIEW_TEXT_FORMAT_H__
#define __CANVASVIEW_TEXT_FORMAT_H__

#include "canvas.h"

#include "text_format_loader.h"
#include "imr_config.h"

namespace imr { namespace loader {



   /// ----------------------------------------------------------------------------
   /// @brief 
   /// ----------------------------------------------------------------------------
   template<int t>
      class LoaderWrapper {
         enum { type = t };
         public:
         LoaderWrapper(const imr::loader::CTextFormatLoader& l) : l(l) {}
         const imr::loader::CTextFormatLoader& operator()(void) const { return l; }
         private:
         const imr::loader::CTextFormatLoader& l;
      };
   typedef enum {
      MAP,
      BORDER,
      OBSTALCES,
      CONVEX_REGIONS,
      VISIBILE_CITIES,
      VISIBILITY_GRAPHS,
      CITY_POINTS,
      MAP_POINTS,
      CONVEX_REGIONS_NOSHAPE
   } TLoaderParts;

   typedef LoaderWrapper<MAP> Map;
   typedef LoaderWrapper<BORDER> Border;
   typedef LoaderWrapper<OBSTALCES> Obstacles;
   typedef LoaderWrapper<CONVEX_REGIONS> ConvexRegions;
   typedef LoaderWrapper<VISIBILE_CITIES> VisibleCities;
   typedef LoaderWrapper<VISIBILITY_GRAPHS> VisibilityGraphs;
   typedef LoaderWrapper<CITY_POINTS> CityPoints;
   typedef LoaderWrapper<MAP_POINTS> MapPoints;
   typedef LoaderWrapper<CONVEX_REGIONS_NOSHAPE> ConvexRegionsNoShape;
} } // end namespace imr::loader 

namespace imr { namespace gui {
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::Map& m);
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::Border& m);
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::Obstacles& m);
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::ConvexRegions& m);
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::VisibleCities& m);
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::VisibilityGraphs& m);
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::CityPoints& m);
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::MapPoints& m);
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::CTextFormatLoader::Point& pt);
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::CTextFormatLoader::Points& points);
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::PointsVector& points);
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::ConvexRegionsNoShape& m);

   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::CTriangularMesh::Node& n);


   /// ----------------------------------------------------------------------------
   /// @brief 
   /// ----------------------------------------------------------------------------
   class CCanvasViewTextFormat : public CCanvas<imr::loader::CTextFormatLoader::Point> {
      public:
         static CConfig & getConfig(CConfig & config);

         typedef imr::loader::CTextFormatLoader Loader;

         CCanvasViewTextFormat(CGui & gui);
         ~CCanvasViewTextFormat();


         void setArea(const Loader::Points & points);

         void addPoint(const Point & pt);

         void addPoint(const Loader::Points & points, const int i);

         void drawPoints(const Loader::Points & points);

         void drawPolygon(const Loader::Points & points, const Loader::Indexes & polygon);

         void drawMap(const Loader & loader);
         void drawMap(const Loader & loader, imr::CConfig & cfg);


         /// ----------------------------------------------------------------------------
         /// @brief drawCities
         /// 
         /// @param loader 
         /// @param from  -1 all cities
         /// @param to    -1 all (from == -1) or just one city (from)
         /// ----------------------------------------------------------------------------
         void drawCities(const Loader & loader, int from = -1, int to = -1);

         void drawVisGraphVertices(const Loader & loader, int from = -1, int to = -1);

         void drawVisGraphCities(const Loader & loader, int from = -1, int to = -1);

         void drawVisRegionVertices(const Loader & loader, int from = -1, int to = -1);

         void drawVisRegionCities(const Loader & loader, int from = -1, int to = -1);

         void drawVisCities(const Loader & loader, int from = -1, int to = -1);

         void drawConvexRegions(const Loader & loader, int from = -1, int to = -1);

         void drawPoints(const Loader & loader, int from = -1, int to = -1);

         /// ----------------------------------------------------------------------------
         /// @brief enableDrawAll draw all range at once
         /// ----------------------------------------------------------------------------
         void enableDrawAll(void);

         /// ----------------------------------------------------------------------------
         /// @brief enableDrawOce draw one item from range and wait for click, after click
         ///        all objects with current tags is cleared
         /// ----------------------------------------------------------------------------
         void enableDrawOne(void);

      protected:
         void drawNext(void);

         bool drawAll;

   };

} } //end namespace imr::gui

#endif

/* end of canvasview_text_format.h */
