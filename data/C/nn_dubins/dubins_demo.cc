/*
 * File name: dubins_demo.cc
 * Date:      2016/03/08 12:46
 * Author:    Jan Faigl
 */

#include <boost/foreach.hpp>

#include <logging.h>
#include <imr_assert.h>
#include <imr_file_utils.h>
#include <shapes.h>

#include "dubins_types.h"
#include "dubins_demo.h"
#include "canvasview_opendubins.h"

using namespace imr::gui;

using imr::logger;

#define foreach BOOST_FOREACH

/// ----------------------------------------------------------------------------
/// Class CDubinsDemo
/// ----------------------------------------------------------------------------

/// - static method ------------------------------------------------------------
imr::CConfig &CDubinsDemo::getConfig(imr::CConfig& config) {
   config.add<std::string>("output", "output directory to store particular results and outputs", "./");
   config.add<std::string>("result-canvas-output",
	 "file name for final canvas output (eps,png,pdf,svg) are supported");
   config.add<std::string>("result-canvas-suffixes",
	 "comman separated list of exptensis e.g. png,pdf.  if specified  several result images are created, with particular suffix to the resultCanvasOutput");
   config.add<double>("canvas-border", "Free space around the canvas", 10);
   config.add<std::string>("draw-shape-targets", "Shape of the target", Shape::CITY());
   config.add<std::string>("draw-shape-point", "Shape of the point", Shape::MAP_VERTEX());
   config.add<std::string>("draw-shape-path", "Shape of the path", Shape::RED_LINE());
   config.add<std::string>("draw-shape-lb", "Shape of the lower bound", Shape::GREEN_LINE());
   return config;
}

/// - constructor --------------------------------------------------------------
CDubinsDemo::CDubinsDemo(imr::CConfig& config) : cfg(config), canvas(0) {
   output = cfg.get<std::string>("output");
   resultCanvasOutput = cfg.get<std::string>("result-canvas-output");
}

/// - destructor ---------------------------------------------------------------
CDubinsDemo::~CDubinsDemo() {
}

/// - public method ------------------------------------------------------------
void CDubinsDemo::demo(void) {

   DubinsState st1 = DubinsState(1.457263388306534, 0.920334720105449, 4.452661657060169);
   DubinsPoint pt2 = DubinsPoint(0.0, 0.0);
   DubinsState st3 = DubinsState(-0.852260021094242, 0.920334720105449, 2.577472632371558);

   DubinsPointVector pts;
   pts.push_back(st1.point);
   pts.push_back(pt2);
   pts.push_back(st3.point);


   if (canvas) { // update canvas area to fit the points and dubins 
      const double BORDER = cfg.get<double>("canvas-border");
      *canvas << canvas::AREA;
      foreach(const DubinsPoint& pt, pts) {
	 *canvas << pt.x + BORDER << pt.y + BORDER << pt.x - BORDER << pt.y - BORDER;
      }
      *canvas << canvas::END;
   }

   double radius = 1.0;
   // resolution - angular_resolution = 2*pi / resolution
   int initialResolution = 360;

   Dubins3Point d3p = Dubins3Point(st1, pt2, st3, radius, initialResolution);

   if (canvas) { //draw end points and middle point
      *canvas << "points" << canvas::POINT
	 << CShape(cfg.get<std::string>("draw-shape-targets")) 
	 << st1 << st3
	 << CShape(cfg.get<std::string>("draw-shape-point")) 
	 << pt2
	 << canvas::REDRAW;
   } 

   // it is possible to increase resolution in any time
//   d3p.split(1024);

   INFO("Actual solution (lower bound = " << d3p.lowerBoundPathLen() << "), (upper bound = " << d3p.feasibleSolutionLen() << ")");
   INFO(">>> Center heading is " << d3p.centerHeading());


   if (canvas) { //draw feasible solution
      DEBUG("Found feasible solution");
      *canvas 
	 << "dubins" << CShape(cfg.get<std::string>("draw-shape-path"))
	 << d3p.feasibleSolution()
	 << canvas::REDRAW;
   }

//   if (canvas) { //draw lower bound solution
//      DEBUG("Found lower bound (unfeasible) solution");
//      *canvas 
//	 << "lb" << CShape(cfg.get<std::string>("draw-shape-lb"))
//	 << d3p.lowerBoundPath()
//	 << canvas::REDRAW;
//  }
   saveCanvas();
}

/// - private method -----------------------------------------------------------
std::string CDubinsDemo::getOutputPath(const std::string filename, std::string& dir) {
   if (!output.empty()) {
      dir = (output[output.size() - 1] == '/') ? output : output + "/";
      return dir + filename;
   } else {
      dir = "./";
      return filename;
   }
}

/// - private method -----------------------------------------------------------
void CDubinsDemo::saveCanvas(void) {
   if (canvas && !resultCanvasOutput.empty()) {
      std::string dir;
      std::string suffixes(cfg.get<std::string>("result-canvas-suffixes"));
      if (!suffixes.empty()) {
	 std::string::size_type cur = 0;
	 std::string::size_type next;
	 do {
	    next = suffixes.find(',', cur);
	    const std::string& ext = suffixes.substr(cur, next - cur);
	    if (!ext.empty()) {
	       std::string file = getOutputPath(resultCanvasOutput + "." + ext, dir);
	       imr::assert_io(imr::createDirectory(dir), "Can not create file in path'" + dir + "'");
	       canvas->redraw();
	       imr::assert_io(canvas->save(file), "Can create output canvas file '" + file + "'");
	    }
	    cur = next + 1;
	 } while (next != std::string::npos);

      } else {
	 std::string file = getOutputPath(resultCanvasOutput, dir);
	 imr::assert_io(imr::createDirectory(dir), "Can not create file in path'" + dir + "'");
	 canvas->redraw();
	 imr::assert_io(canvas->save(file), "Can create output canvas file '" + file + "'");
      }
   }
}

/* end of dubins_demo.cc */
