/*
 * File name: guifactory.cc
 * Date:      2007/03/07 21:50
 * Author:    Jan Faigl
 */

#include <string>
#include <stdexcept>
#include <cstring>
#include "guifactory.h"

#include "logging.h"

#ifdef GUITK
#include "guitk.h"
#endif
#include "cairogui.h" //TODO rename

using namespace imr::gui;
#ifdef GUITK
using imr::gui::tk::CGuiTK;
#endif
using imr::gui::cairo::CCairoGui;

/// ----------------------------------------------------------------------------
/// Class CGuiFactory
/// ----------------------------------------------------------------------------
imr::CConfig & CGuiFactory::getConfig(CConfig & config) {
#ifndef GUITK
   config.add<std::string>("gui", "possible values are [ cairo | cairo-nowin ] others gui is not created", ""); 
#else
   config.add<std::string>("gui", "possible values are [ cairo | cairo-nowin | tcltk ] others gui is not created", ""); 
#endif
   // implementaton of theses parameters by particular gui is optional
   config.add<bool>("nowait", "nowait for gui close", false);
   config.add<int>("gui-width", "width of default canvas view", 640);
   config.add<int>("gui-height", "height of default canvas view", 480);
   config.add<int>("gui-border-x", "x coords of default canvas view", 10);
   config.add<int>("gui-border-y", "y coords of default canvas view", 10);
   /*   
        config.add<int>("gui-export-width", "width of export view", 640);
        config.add<int>("gui-export-height", "height of export view", 480);
        */
   config.add<double>("gui-aspect-ratio", "width/height, if <= 0 fit to canvas", -1);
   config.add<std::string>("gui-background-color", "Background color", "bisque3"); //gray
   config.add<double>("gui-background-alpha", "Background alpha", 1.0);
   config.add<bool>("gui-antialiasing", "enable/disable antialiasing", 1);
   config.add<std::string>("gui-wm_class-name", "WM_CLASS class name", "imr-gui");
   config.add<std::string>("gui-wm_class", "WM_CLASS class", "IMR_Gui");
   config.add<std::string>("gui-canvas-save-file", "canvas save file by pressing F2", "");
   return config;
}

/// ----------------------------------------------------------------------------
CGui * CGuiFactory::createGui(int argc, char ** argv) {
   CGui * gui = 0;
   switch (getGuiType(argc, argv)) {
#ifdef GUITK
      case TCLTK:  
         gui = new tk::CGuiTK(argc, argv);
         break;
#endif
      case CAIRO: //CAIRO is default gui
      default:
         {
            cairo::CCairoGui * cairo = new cairo::CCairoGui(argc, argv);
            cairo->execute(); //cairo gui must be explicitely executed
            gui = cairo;
         } 
         break;
   }
   return gui;
}

/// ----------------------------------------------------------------------------
CGui * CGuiFactory::createGui(const char * guiName) {
   CGui * gui = 0;
   if (strcmp(guiName, "cairo") == 0) {
      cairo::CCairoGui * cairo = new cairo::CCairoGui(0, 0);
      cairo->execute(); //cairo gui must be explicitely executed
      gui = cairo;
   }
   if (strcmp(guiName, "cairo-nowin") == 0) {
      cairo::CCairoGui * cairo = new cairo::CCairoGui(0, 0, true);
      cairo->execute();
      gui = cairo;
   }
#ifdef GUITK
   if (strcmp(guiName, "tcltk") == 0) {
      gui = new tk::CGuiTK(0, 0);
   }
#endif
   if (!gui) {
      throw std::runtime_error(std::string("Unknown GUI name '" + std::string(guiName) + "'").c_str());
   }
   return gui;
}

/// ----------------------------------------------------------------------------
CGui * CGuiFactory::createGui(CConfig & cfg) {
   CGui * gui = 0;
   std::string guiName = cfg.get<std::string>("gui");
   if (guiName == "cairo") {
      cairo::CCairoGui * cairo = new cairo::CCairoGui(cfg);
      cairo->execute(); //cairo gui must be explicitely executed
      gui = cairo;
   }
   if (guiName == "cairo-nowin") {
      cairo::CCairoGui * cairo = new cairo::CCairoGui(cfg, true);
      cairo->execute();
      gui = cairo;
   }
#ifdef GUITK
   if (guiName == "tcltk") {
      gui = new tk::CGuiTK(0, 0);
   }
#endif
   if (!gui && !guiName.empty() && guiName != "none") {
      WARN("Unknown GUI name '" << guiName + "'");
   }
   return gui;
}

/// ----------------------------------------------------------------------------
std::string CGuiFactory::getGuiStrType(void) {
#ifdef GUITK
   return "cairo | cairo-nowin | tcltk";
#else
   return "cairo | cairo-nowin";
#endif
}

/// ----------------------------------------------------------------------------
CGuiFactory::TGuiType CGuiFactory::getGuiType(int argc, char ** argv) {
   TGuiType ret = NOTDEFINED;
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-cairo") == 0) {
         ret = CAIRO;
         break;
      }
#ifdef GUITK
      if (strcmp(argv[i], "-tcltk") == 0) {
         ret = TCLTK;
         break;
      }
#endif
   }
   return ret;
}



/* end of guifactory.cc */
