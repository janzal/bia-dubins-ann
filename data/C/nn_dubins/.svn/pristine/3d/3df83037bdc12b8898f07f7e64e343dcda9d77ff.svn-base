/*
 * File name: canvasview_opendubins.h
 * Date:      2016/03/08 12:29
 * Author:    Jan Faigl
 */

#ifndef __CANVASVIEW_OPENDUBINS_H__
#define __CANVASVIEW_OPENDUBINS_H__

#include <cmath>

#include <gui.h>
#include <colors.h>
#include <renderer.h>
#include <canvas.h>

#include "dubins_types.h"

/// ----------------------------------------------------------------------------
inline imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const DubinsArc& arc) {
   if (fabs(arc.angle) > DUBINS_ANGLE_TOLERANCE) {
      DubinsPoint p1 = arc.getCenter();
      double startAngle = -M_PI / 2 - arc.state.ang;
      if (arc.angle >= 0) {
	 startAngle += M_PI;
      }

      double endAngle = -M_PI / 2 - arc.state.ang - arc.angle;
      if (arc.angle >= 0) {
	 endAngle += M_PI;
      }

      if (arc.angle >= 0) {
	 std::swap(startAngle, endAngle);
      }

      while (endAngle <= startAngle) {
	 endAngle += 2 * M_PI;
      }
      canvas << imr::gui::canvas::ARC << p1.x << p1.y << arc.radius << startAngle << endAngle;
   }
   return canvas;
}

/// ----------------------------------------------------------------------------
inline imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const DubinsManeuver& maneuver) {
   DubinsArc arc1 = maneuver.getFirstArc();
   DubinsArc arc2 = maneuver.getSecondArc();

   canvas << arc1 << arc2;
   if (maneuver.isCCC) {
      DubinsArc carc = maneuver.getCenterArc();
      canvas << carc;
   } else {
      DubinsLine line = maneuver.getCenter();
      canvas << imr::gui::canvas::ARROW_LINE << line.p1.x << line.p1.y << line.p2.x << line.p2.y; 
   }
   canvas << imr::gui::canvas::END;
   return canvas;
}

/// ----------------------------------------------------------------------------
inline imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const std::vector<DubinsManeuver>& dubinsPath) {
   BOOST_FOREACH(const DubinsManeuver& maneuver, dubinsPath) {
      canvas << maneuver;
   }
   return canvas;
}

/// ----------------------------------------------------------------------------
inline imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const DubinsPoint& pt) {
   canvas << pt.x << pt.y;
   return canvas;
}

/// ----------------------------------------------------------------------------
inline imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const std::vector<DubinsPoint>& pts) {
   BOOST_FOREACH(const DubinsPoint& pt, pts) {
      canvas << pt.x << pt.y;
   }
   return canvas;
}




/// ----------------------------------------------------------------------------
inline imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const DubinsState& state) {
   canvas << state.point.x << state.point.y;
   return canvas;
}

/// ----------------------------------------------------------------------------
inline imr::gui::CCanvasBase& operator<<(imr::gui::CCanvasBase& canvas, const std::vector<DubinsState>& states) {
   BOOST_FOREACH(const DubinsState& state, states) {
      canvas << state.point.x << state.point.y;
   }
   return canvas;
}

#endif

/* end of canvasview_opendubins.h */
