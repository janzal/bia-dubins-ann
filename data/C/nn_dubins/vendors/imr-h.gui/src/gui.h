/*
 * File name: gui.h
 * Date:      2005/10/03 16:24
 * Author:    Jan Faigl
 * History: based on CGui.h
 */

#ifndef __Cgui_H__
#define __Cgui_H__

#include "renderer.h"
#include "guihandler.h"

namespace imr {
   namespace gui {

      using namespace render;

      /// 
      /// @brief general gui class with a basic rendere, gui is running in own thread
      /// 
      class CGui {
         public:
            typedef imr::gui::CGuiHandler Handler;

            virtual ~CGui() {}

            /*
               virtual void execute(void) = 0;
               */
            virtual void stop(void) = 0;

            /// ----------------------------------------------------------------------------
            /// @brief hasUseInput
            /// 
            /// @return true if gui has user interactive input  (like click)
            /// ----------------------------------------------------------------------------
            virtual bool hasUserInput(void) { return true; }

            virtual CRenderer * getRenderer(void) = 0;
            virtual Handler * getHandler(void) = 0;
            virtual void redraw(void) = 0;
      };

   } //end namespace gui
} //end namespace imr
#endif

/* end of CGui.h */
