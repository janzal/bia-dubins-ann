/*
 * File name: tdubins.cc
 * Date:      2016/02/05 08:54
 * Author:    Jan Faigl
 */

#include <fstream>
#include <limits.h>

#include <boost/foreach.hpp>

#include <boost/program_options.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <logging.h>
#include <imr_exceptions.h>
#include <timerN.h>
#include <perf_timer.h>
#include <shapes.h>
#include <guifactory.h>
#include <win_adjust_size.h>

#include <imr_config.h>
#include <boost_args_config.h>

#include "dubins_types.h"
#include "dubins_demo.h"

using imr::logger;

namespace po = boost::program_options;
namespace fs = boost::filesystem;

const std::string SOM_DUBINS_VERSION = "0.1";

using namespace imr;
using namespace imr::gui;

typedef imr::gui::CCanvasBase Canvas;

typedef CDubinsDemo Solver;

//TODO typedef std::vector<Coords> CoordsVector;
//TODO typedef std::vector<CoordsVector> CoordsVectorVector;

/// ----------------------------------------------------------------------------
/// Program options variables
/// ----------------------------------------------------------------------------
std::string guiType = "none";

imr::CConfig guiConfig;
imr::CConfig dubinsConfig;
std::string canvasOutput = "";

/// ----------------------------------------------------------------------------
/// Global variable
/// ----------------------------------------------------------------------------
imr::gui::CGui* g = 0;
#define GUI(x)  if(gui) { x;}

/// ----------------------------------------------------------------------------

bool parseArgs(int argc, char* argv[]) {
   bool ret = true;
   std::string configFile;
   std::string guiConfigFile;
   std::string loggerCfg = "";

   po::options_description desc("General options");
   desc.add_options()
      ("help,h", "produce help message")
      ("config,c", po::value<std::string>(&configFile)->default_value(std::string(argv[0]) + ".cfg"),
       "configuration file")
      ("logger-config,l", po::value<std::string>(&loggerCfg)->default_value(loggerCfg),
       "logger configuration file")
      ("config-gui", po::value<std::string>(&guiConfigFile)->default_value(std::string(argv[0]) + "-gui.cfg"),
       "dedicated gui configuration file")
   ;
   try {
      po::options_description guiOptions("Gui options");
      imr::gui::CGuiFactory::getConfig(guiConfig);
      imr::gui::CWinAdjustSize::getConfig(guiConfig);
      guiConfig.add<double>("gui-add-x",
	    "add the given value to the loaded goals x coord to determine the canvas size and transformation",
	    0);
      guiConfig.add<double>("gui-add-y",
	    "add the given value to the loaded goals y coord to determine the canvas size and transformation",
	    0);
      boost_args_add_options(guiConfig, "", guiOptions);
      guiOptions.add_options()
	 ("canvas-output", po::value<std::string>(&canvasOutput), "result canvas outputfile");

      po::options_description dubinsOptions("Dubins solver options");
      dubinsConfig.add<bool>("simple-txt-demo", "Just txt demo when enabled", "false");
      boost_args_add_options(Solver::getConfig(dubinsConfig), "", dubinsOptions);


      po::options_description cmdline_options;
      cmdline_options.add(desc).add(guiOptions).add(dubinsOptions);

      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, cmdline_options), vm);
      po::notify(vm);

      std::ifstream ifs(configFile.c_str());
      store(parse_config_file(ifs, cmdline_options), vm);
      po::notify(vm);
      ifs.close();
      ifs.open(guiConfigFile.c_str());
      store(parse_config_file(ifs, cmdline_options), vm);
      po::notify(vm);
      ifs.close();

      if (vm.count("help")) {
	 std::cerr << std::endl;
	 std::cerr << "Dubins SOM-based solver ver. " << SOM_DUBINS_VERSION << std::endl;
	 std::cerr << cmdline_options << std::endl;
	 ret = false;
      }
      if (
	    ret &&
	    loggerCfg != "" &&
	    fs::exists(fs::path(loggerCfg))
	 ) {
	 imr::initLogger("dubins", loggerCfg.c_str());
      } else {
	 imr::initLogger("dubins");
      }
      /*
      const std::string& problemFile = dubinsConfig.get<std::string>("problem");
      if (!fs::exists(fs::path(problemFile))) {
	 ERROR("Problem file '" + problemFile + "' does not exists");
	 ret = false;
      }
      */
   } catch (std::exception &e) {
      std::cerr << std::endl;
      std::cerr << "Error in parsing arguments: " << e.what() << std::endl;
      ret = false;
   }
   return ret;
}

/// - local demo function ------------------------------------------------------
void demoTxt(void) {
   DubinsState point1 = DubinsState(0, 0, 0);
   DubinsPoint point2 = DubinsPoint(1, 1);
   DubinsState point3 = DubinsState(2, 2, 2);

   double radius = 1.0;
   // resolution - angular_resolution = 2*pi / resolution
   int initialResolution = 8;

   Dubins3Point d3p = Dubins3Point(point1, point2, point3, radius, initialResolution);

   // it is possible to increase resolution in any time
   d3p.split(initialResolution * 8);

   std::cout << "Actual solution (lower bound = " << d3p.lowerBoundPathLen() << "), (upper bound = "
      << d3p.feasibleSolutionLen() << ")" << std::endl;

   std::cout << std::endl << "Found feasible solution : " << std::endl;
   for(const DubinsManeuver& m : d3p.feasibleSolution()){
      std::cout << m << std::endl;
   }
   std::cout << ">>> Center heading is " << d3p.centerHeading() << std::endl;

   std::cout << std::endl << "Found lower bound (unfeasible) solution : " << std::endl;
   for(const DubinsManeuver& m : d3p.lowerBoundPath()){
      std::cout << m << std::endl;
   }
}

/// - local gui helper ---------------------------------------------------------
DubinsPointVector& addCoords(DubinsPointVector& pts) {
   pts.push_back(DubinsPoint(0, 0));
   pts.push_back(DubinsPoint(1, 1));
   return pts;
}

/// - Main program -------------------------------------------------------------
int main(int argc, char* argv[]) {
   Canvas* canvas = 0;
   int ret = -1;
   if (parseArgs(argc, argv)) {
      try {
	 INFO("Start Logging");
	 if (dubinsConfig.get<bool>("simple-txt-demo")) {
	    demoTxt();
	 } else { 
	    DubinsPointVector pts;

	    addCoords(pts); //needed to adjust the window size to keep the aspect ratio
	    imr::gui::CWinAdjustSize::adjust(pts, guiConfig); //
	    if ((g = gui::CGuiFactory::createGui(guiConfig)) != 0) {
	       INFO("Start gui " + guiConfig.get<std::string>("gui"));
	       canvas = new Canvas(*g);
	    }
	    imr::CPerfTimer t("Dubins demo time real: ");
	    CDubinsDemo dubins(dubinsConfig);
	    dubins.setCanvas(canvas);
	    dubins.demo();
	    t.stop();
	    if (canvas) {
	       if (canvasOutput.size()) {
		  canvas->save(canvasOutput);
	       }
	       if (!guiConfig.get<bool>("nowait")) {
		  INFO("click to exit");
		  canvas->click();
	       }
	       delete canvas;
	       delete g;
	    }
	 } //end gui demo
      } catch (imr::exception &e) {
	 ERROR("Exception " << e.what() << "!");
      } catch (std::exception &e) {
	 ERROR("Runtime error " << e.what() << "!");
      }
      INFO("End Logging");
      ret = EXIT_SUCCESS;
   }
   imr::shutdownLogger();
   return ret;
}

/* end of tdubins.cc */
