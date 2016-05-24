/*
 * File name: canvasview_text_format.cc
 * Date:      2008/09/10 11:24
 * Author:    Jan Faigl
 */

#include <boost/foreach.hpp>

#include "shapes.h"
#include "colors.h"
#include "canvasview_text_format.h"

#include "imr_assert.h"
#include "logging.h"

using namespace imr::gui;

#define foreach BOOST_FOREACH

static imr::CLoggerPtr logger = imr::getLogger("canvasview_text_format");

#define debug(logger, str) LOG4CXX_DEBUG(logger, str);
#define info(logger, str) LOG4CXX_INFO(logger, str);

typedef imr::loader::CTextFormatLoader Loader;

namespace imr {  namespace gui { 
   namespace loader = imr::loader;

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const loader::Map& m) {
      canvas << canvas::AREA << gui::AddCoords<Loader::CoordsAccessor>(m().map_points, m().map_points.begin(), m().map_points.end()) << canvas::END; 
      canvas << Shape::MAP_BORDER << canvas::POLYGON << "map border" << gui::AddCoords<Loader::IndexCoordsAccessor>(m().map_points, m().map_border.begin(), m().map_border.end()) << canvas::END;
      canvas << Shape::MAP_OBSTACLE << "map obstacle";
      for (Loader::IndexesList::const_iterator hole = m().map_obstacles.begin(); hole != m().map_obstacles.end(); hole++) {
         canvas << gui::AddCoords<Loader::IndexCoordsAccessor>(m().map_points, hole->begin(), hole->end()) << canvas::END;
      }
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const loader::Border& m) {
      canvas << gui::AddCoords<Loader::IndexCoordsAccessor>(m().map_points, m().map_border.begin(), m().map_border.end()) << canvas::END;
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const loader::Obstacles& m) {
      for (Loader::IndexesList::const_iterator hole = m().map_obstacles.begin(); hole != m().map_obstacles.end(); hole++) {
         canvas << gui::AddCoords<Loader::IndexCoordsAccessor>(m().map_points, hole->begin(), hole->end()) << canvas::END;
      }
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const loader::ConvexRegions& m) {
      Colors::DEFAULT.reset();
      canvas << Shape::POLYGON << Width(1);
      for (Loader::IndexesList::const_iterator region = m().map_convex_regions.begin(); region != m().map_convex_regions.end(); region++) {
         canvas << FillColor(Colors::DEFAULT.next());
         canvas << AddCoords<Loader::IndexCoordsAccessor>(m().map_points, region->begin(), region->end()) << canvas::END;
      }
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const loader::VisibleCities& m) {
      canvas << Shape::BLUE_LINE << canvas::LINE;
      for (int i = 0; i < m().map_vertex_visible_cities.size(); i++) {
         BOOST_FOREACH(const int& vt,  m().map_vertex_visible_cities[i]) {
            canvas << m().map_points[i] << m().city_points[vt];
         }
      }
      canvas << Shape::RED_LINE;
      for (int i = 0; i < m().city_vertex_visible_cities.size(); i++) {
         BOOST_FOREACH(const int& vt,  m().city_vertex_visible_cities[i]) {
            canvas << m().city_points[i] << m().city_points[vt];
         }
      }
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const loader::VisibilityGraphs& m) {
      canvas << Shape::BLUE_LINE << canvas::LINE;
      for (int i = 0; i < m().map_vertices_visibility_graphs.size(); i++) {
         BOOST_FOREACH(const int& vt,  m().map_vertices_visibility_graphs[i]) {
            canvas << m().map_points[i] << m().map_points[vt];
         }
      }
      canvas << Shape::RED_LINE;
      for (int i = 0; i < m().city_map_visibility_graphs.size(); i++) {
         BOOST_FOREACH(const int& vt,  m().city_map_visibility_graphs[i]) {
            canvas << m().city_points[i] << m().map_points[vt];
         }
      } 
      canvas << Shape::GREEN_LINE;
      for (int i = 0; i < m().city_vertex_visible_cities.size(); i++) {
         BOOST_FOREACH(const int& vt,  m().city_vertex_visible_cities[i]) {
            canvas << m().city_points[i] << m().city_points[vt];
         }
      }
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const loader::ConvexRegionsNoShape& m) {
      for (Loader::IndexesList::const_iterator region = m().map_convex_regions.begin(); region != m().map_convex_regions.end(); region++) {
         canvas << AddCoords<Loader::IndexCoordsAccessor>(m().map_points, region->begin(), region->end()) << canvas::END;
      }
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const loader::CityPoints& m) {
      BOOST_FOREACH(const Loader::Point& ct, m().city_points) {
         canvas << ct; 
      }
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const loader::MapPoints& m) {
      canvas << m().map_points;
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const loader::CTextFormatLoader::Point& pt) {
      canvas << pt.x << pt.y;
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const loader::CTextFormatLoader::Points& points) {
      BOOST_FOREACH(const Loader::Point& pt, points) {
         canvas << pt.x << pt.y;
      }
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::PointsVector& points) {
      BOOST_FOREACH(const Loader::Points& pts, points) {
            canvas << pts << canvas::END;
      }
      return canvas;
   }

   /// ----------------------------------------------------------------------------
   imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const imr::loader::CTriangularMesh::Node& n) {
      canvas << *n.point;
      return canvas;
   }

} } //end namespace imr::gui

/// ----------------------------------------------------------------------------
void setRange(int size, int & from, int & to) {
   if (from < 0) {
      from = 0;
      to = size - 1; //for loops are <=
   } else if (from < size && to < 0) {
      to = from;
   } else {
      imr::assert_argument(from < size && to < size, "range out of bound");
   }
}

/// ----------------------------------------------------------------------------
/// Class CCanvasViewTextFormat
/// ----------------------------------------------------------------------------
imr::CConfig & CCanvasViewTextFormat::getConfig(CConfig & config) {
   /*   config.add<std::string>("map-border-color", "color for map border", Shape::MAP_BORDER.getPenColorStr());
        config.add<std::string>("map-border-fill-color", "fill color for map border", Shape::MAP_BORDER.getFillColorStr());
        config.add<std::string>("map-obstacle-color", "color for map obstacles", Shape::MAP_OBSTACLE.getPenColorStr());
        config.add<std::string>("map-obstacle-fill-color", "fill color for obstacles", Shape::MAP_OBSTACLE.getFillColorStr());
        */
   config.add<std::string>("canvas-background-color", "canvas background color", "white");
   config.add<std::string>("map-border-color", "fill color for map border", Shape::MAP_BORDER.getFillColorStr());
   config.add<std::string>("map-obstacle-color", "fill color for obstacles", Shape::MAP_OBSTACLE.getFillColorStr());
   return config;
}

/// ----------------------------------------------------------------------------
CCanvasViewTextFormat::CCanvasViewTextFormat(CGui & gui) : CCanvas<imr::loader::CTextFormatLoader::Point>(gui) {
   drawAll = true;
}

/// ----------------------------------------------------------------------------
CCanvasViewTextFormat::~CCanvasViewTextFormat() {

}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::setArea(const Loader::Points & points) {
   renderer->open(render::AREA, tags, shape);
   foreach(const Point & pt, points) {
      renderer->addPoint(pt.x, pt.y);
   }
   renderer->close();
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::addPoint(const Point & pt) {
   renderer->addPoint(pt.x, pt.y);
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::addPoint(const Loader::Points & points, const int i) {
   renderer->addPoint(points[i].x, points[i].y);
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawPoints(const Loader::Points & points) {
   foreach(const Loader::Point & pt, points) {
      renderer->drawPoint(pt.x, pt.y, tags, shape);
   }
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawPolygon(const Loader::Points & points, const Loader::Indexes & polygon) {
   renderer->open(render::POLYGON, tags, shape);
   foreach(const int i, polygon) {
      addPoint(points, i);
   }
   renderer->close();
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawMap(const Loader & loader) {
   ShapeSaver save(shape);
   renderer->open(render::AREA, tags, shape);
   foreach(const Point & pt, loader.map_points) {
      renderer->addPoint(pt.x, pt.y);
   }
   renderer->close();
   CShape shapeSave = shape;
   shape = Shape::MAP_BORDER;
   drawPolygon(loader.map_points, loader.map_border);
   shape = Shape::MAP_OBSTACLE;
   foreach(const Loader::Indexes & obstacle, loader.map_obstacles) {
      drawPolygon(loader.map_points, obstacle);
   }
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawMap(const Loader & loader, imr::CConfig & cfg) {
   ShapeSaver save(shape);
   renderer->open(render::AREA, tags, shape);
   foreach(const Point & pt, loader.map_points) {
      renderer->addPoint(pt.x, pt.y);
   }
   renderer->setBackgroundColor(CShape::getColor(cfg.get<std::string>("canvas-background-color")));
   shape.setFillColor(cfg.get<std::string>("map-border-color"));
   renderer->close();
   //TODO move to init
   CShape shapeSave = shape;
   shape = Shape::MAP_BORDER;
   //   shape.setPenColor(cfg.get<std::string>("map-border-color"));
   //   shape.setFillColor(cfg.get<std::string>("map-border-fill-color"));
   shape.setFillColor(cfg.get<std::string>("map-border-color"));
   *this << "map map_border";
   drawPolygon(loader.map_points, loader.map_border);
   shape = Shape::MAP_OBSTACLE;
   //   shape.setPenColor(cfg.get<std::string>("map-obstacle-color"));
   //   shape.setFillColor(cfg.get<std::string>("map-obstacle-fill-color"));
   *this << "map map_obstacle";
   shape.setFillColor(cfg.get<std::string>("map-obstacle-color"));
   foreach(const Loader::Indexes & obstacle, loader.map_obstacles) {
      drawPolygon(loader.map_points, obstacle);
   }
}
/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawCities(const Loader & loader, int from, int to) {
   setRange(loader.city_points.size(), from, to);
   for (int i = from; i <= to; i++) {
      drawPoint(loader.city_points[i]);
   }
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawVisGraphVertices(const Loader & loader, int from, int to) {
   ShapeSaver save(shape);
   setRange(loader.map_points.size(), from, to);
   for (int i = from; i <= to; i++) {
      const Loader::Point & pt(loader.map_points[i]);
      foreach(const int j, loader.map_vertices_visibility_graphs[i]) {
         shape = Shape::GREEN_BOLD_LINE;
         drawLine(pt, loader.map_points[j]);
         shape = Shape::ORANGE_POINT;
         drawPoint(loader.map_points[j]);
      }
      shape = Shape::DEPOT;
      drawPoint(pt);
      drawNext();
   }
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawVisGraphCities(const Loader & loader, int from, int to) {
   ShapeSaver save(shape);
   setRange(loader.city_points.size(), from, to);
   for (int i = from; i <= to; i++) {
      const Loader::Point & pt(loader.city_points[i]);
      foreach(const int j, loader.city_map_visibility_graphs[i]) {
         shape = Shape::GREEN_BOLD_LINE;
         drawLine(pt, loader.map_points[j]);
         shape = Shape::ORANGE_POINT;
         drawPoint(loader.map_points[j]);
      }
      shape = Shape::DEPOT;
      drawPoint(pt);
      drawNext();
   }
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawVisRegionVertices(const Loader & loader, int from, int to) {
   ShapeSaver save(shape);
   setRange(loader.map_points.size(), from, to);
   for (int i = from; i <= to; i++) {
      const Loader::Point & pt(loader.map_points[i]);
      renderer->open(render::POLYGON, tags, Shape::FREESPACE_HIGHLIGHT);
      foreach(const int j, loader.map_vertices_visibility_regions[i]) {
         addPoint(loader.points[j]);
      }
      renderer->close();
      foreach(const int j, loader.map_vertices_visibility_regions[i]) {
         shape = j < loader.map_points.size() ? Shape::ORANGE_POINT : Shape::RED_POINT;
         drawPoint(loader.points[j]);
      }
      shape = Shape::DEPOT;
      drawPoint(pt);
      drawNext();
   }
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawVisRegionCities(const Loader & loader, int from, int to) {
   ShapeSaver save(shape);
   setRange(loader.city_points.size(), from, to);
   for (int i = from; i <= to; i++) {
      //     debug(logger, "Draw visibility region for city:" << i);
      const Loader::Point & pt(loader.city_points[i]);
      renderer->open(render::POLYGON, tags, Shape::FREESPACE_HIGHLIGHT);
      foreach(const int j, loader.city_map_visibility_regions[i]) {
         addPoint(loader.points[j]);
      }
      renderer->close();
      foreach(const int j, loader.city_map_visibility_regions[i]) {
         shape = j < loader.map_points.size() ? Shape::ORANGE_POINT : Shape::RED_POINT;
         drawPoint(loader.points[j]);
         /* debug(logger, "draw point:" << j);
            click();*/
      }
      shape = Shape::DEPOT;
      drawPoint(pt);
      drawNext();
   }
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawVisCities(const Loader & loader, int from, int to) {
   ShapeSaver save(shape);
   setRange(loader.city_points.size(), from, to);
   for (int i = from; i <= to; i++) {
      debug(logger, "Draw visible cities from city:" << i);
      const Loader::Point & pt(loader.city_points[i]);
      shape = Shape::GREEN_BOLD_LINE;
      foreach(const int c, loader.city_vertex_visible_cities[i]) {
         drawLine(pt, loader.city_points[c]);
      }
      shape = Shape::ORANGE_POINT;
      foreach(const int c, loader.city_vertex_visible_cities[i]) {
         drawPoint(loader.city_points[c]);
      }
      shape = Shape::DEPOT;
      drawPoint(pt);
      drawNext();
   }
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawConvexRegions(const Loader & loader, int from, int to) {
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawPoints(const Loader & loader, int from, int to) {
   setRange(loader.points.size(), from, to);
   for (int i = from; i < to; i++) {
      drawPoint(loader.points[i]);
   }
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::enableDrawAll(void) {
   drawAll = true;
}

/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::enableDrawOne(void) {
   drawAll = false;
}

/// ----------------------------------------------------------------------------
/// Protected methods
/// ----------------------------------------------------------------------------
void CCanvasViewTextFormat::drawNext(void) {
   if (!drawAll) {
      click();
      clear(tags);
   }
}
/* end of canvasview_text_format.cc */
