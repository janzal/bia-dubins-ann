/*
 * File name: cairogui.cc
 * Date:      2007/02/17 18:35
 * Author:    Jan Faigl
 */

#include "cairogui.h"
#include "logging.h"
#include "guievent.h"
#include "renderercairo.h"

#include "cairowinfake.h"
#include "cairoxwin.h"
//#include "cairoxrender.h"
//#include "cairogtkwin.h"

using namespace imr::gui::cairo;

/*
   config.add<int>("gui-width", "width of default canvas view", 640);
   config.add<int>("gui-height", "height of default canvas view", 480);
   config.add<int>("gui-border-x", "x coords of default canvas view", 10);
   config.add<int>("gui-border-y", "y coords of default canvas view", 10);
   */

using imr::logger;

class CCanvasListener: public imr::gui::CGuiListener {
   public:
      CCanvasListener(imr::gui::render::CRenderer* renderer, const std::string& saveFile) : imr::gui::CGuiListener(), saveFile(saveFile), renderer(renderer) {}
      virtual ~CCanvasListener() {}

      bool handle(imr::gui::SGuiEvent& event) {
         bool ret = false;
         if (event.type == imr::gui::SGuiEvent::KEY_PRESS) {
            if (event.keyCode == 68 && !saveFile.empty()) { // F2
               ret = renderer->save(saveFile);
               if (ret) {
                  INFO("Canvas has been saved into '" << saveFile << "'");
               } else {
                  WARN("Error occurs during saving canvas into '" << saveFile << "'");
               }
            }
         }
         return ret;
      }
   private:
      std::string saveFile;
      imr::gui::render::CRenderer* renderer;

};

/// ----------------------------------------------------------------------------
// /Class CCairoGui
/// - @deprecated --------------------------------------------------------------
CCairoGui::CCairoGui(int iArgc, char ** iArgv, bool fake) : imr::concurrent::CThread(), userInput(!fake) {
   mtx = new Mutex(); 
   canvas = new CCanvasContainer;
   if (fake) {
      win = new CCairoWinFake(canvas);
   } else {
      win = new CCairoXWin(canvas);
      //  win = new CCairoXRender(iArgc, iArgv, canvas);
   }
   //   win = new CCairoGTKWin(iArgc, iArgv, canvas);
   //  win->setSize(1024, 768); //TODO as cmd args
   win->setSize(640, 480);
   renderer = new imr::gui::render::CRendererCairo(canvas, win);
   handler = new Handler;
   win->setHandler(handler);
   //win->initialize();
}

/// ----------------------------------------------------------------------------
CCairoGui::CCairoGui(CConfig &  cfg, bool fake) : imr::concurrent::CThread(), userInput(!fake) {
   mtx = new Mutex(); 
   canvas = new CCanvasContainer;
   if (fake) {
      win = new CCairoWinFake(canvas);
      fakeWin = true;
   } else {
      win = new CCairoXWin(canvas);
      //  win = new CCairoXRender(iArgc, iArgv, canvas);
      fakeWin = false;
   }
   //   win = new CCairoGTKWin(iArgc, iArgv, canvas);
   win->setWMClass(cfg.get<std::string>("gui-wm_class-name"), cfg.get<std::string>("gui-wm_class"));
   win->setSize(cfg.get<int>("gui-width"), cfg.get<int>("gui-height"));
   canvas->setBackgroundColor(SColor(cfg.get<std::string>("gui-background-color")), cfg.get<double>("gui-background-alpha"));
   renderer = new imr::gui::render::CRendererCairo(canvas, win, cfg);
   handler = new Handler;
   win->setHandler(handler);
   listener = new CCanvasListener(renderer, cfg.get<std::string>("gui-canvas-save-file"));
   handler->registerListener(listener);
   //win->initialize();
}
/// ----------------------------------------------------------------------------
CCairoGui::~CCairoGui() {
   stop();
   join();
   //  std::cout << "destructor" << std::endl;
   if (win) {
      delete win;
   }
   if (renderer) {
      delete renderer;
   }
   handler->unregisterListener(listener);
   delete listener;
   delete handler;
   delete canvas;
   delete mtx;
}

/// ----------------------------------------------------------------------------
CCairoGui::Renderer * CCairoGui::getRenderer(void) {
   return renderer;
}

/// ----------------------------------------------------------------------------
CCairoGui::Handler * CCairoGui::getHandler(void) {
   return handler;
}

/// ----------------------------------------------------------------------------
void CCairoGui::redraw(void) {
   if (renderer) {
      renderer->redraw();
   }
}

/// ----------------------------------------------------------------------------
void CCairoGui::execute(void) {
      win->initialize();
   if (fakeWin) {
      win->start();
   } else {
      ThreadBase::execute();
   }
}

/// ----------------------------------------------------------------------------
void CCairoGui::stop(void) {
   {
      ScopedLock lk(*mtx);
      win->stop();
   }
}

/// ----------------------------------------------------------------------------
/// Private methods
/// ----------------------------------------------------------------------------
void CCairoGui::threadBody(void) {
   win->start();
}

/* end of cairogui.cc */
