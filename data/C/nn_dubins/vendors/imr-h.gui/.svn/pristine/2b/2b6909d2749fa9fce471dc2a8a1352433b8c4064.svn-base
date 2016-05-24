/*
 * File name: cairogui.h
 * Date:      2007/02/17 18:28
 * Author:    Jan Faigl
 */

#ifndef __CAIROGUI_H__
#define __CAIROGUI_H__

#include "gui.h"
#include "renderer.h"
#include "concurrent/thread.h"
#include "imr_config.h"

#include "canvascontainer.h"
#include "guilistener.h"
#include "cairowin.h"

namespace imr {
   namespace gui {
      namespace cairo {

         class CCairoGui : public imr::concurrent::CThread, public imr::gui::CGui {
            typedef imr::concurrent::CThread ThreadBase;
            public:
            typedef imr::gui::render::CRenderer Renderer;
            public:

            //@deprecated
            CCairoGui(int iArgc, char ** iArgv, bool fake = false);
            CCairoGui(CConfig & cfg, bool fake = false);
            ~CCairoGui();
            void stop(void);
            bool hasUserInput(void) { return userInput; }
            Renderer * getRenderer(void);
            Handler * getHandler(void);
            void redraw(void);

            void execute(void);
            private:
            const bool userInput;
            Mutex * mtx;
            CCanvasContainer * canvas;
            Renderer * renderer;
            Handler * handler;
            CCairoWin * win;
            private:
            void threadBody(void);
            imr::gui::CGuiListener* listener;
            bool fakeWin;
         };
      } //end namespace cairo
   } //end namespace gui
} //end namespace imr


#endif

/* end of cairogui.h */
