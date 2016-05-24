/*
 * File name: guifactory.h
 * Date:      2007/03/07 21:49
 * Author:    Jan Faigl
 */

#ifndef __GUIFACTORY_H__
#define __GUIFACTORY_H__

#include <string>

#include "imr_config.h"

#include "gui.h"

#include "guievent.h"
#include "guihandler.h"
#include "guilistener.h"

namespace imr {
   namespace gui {

      typedef imr::gui::SGuiEvent Event;
      typedef imr::gui::CGuiListener Listener;
      typedef imr::gui::CGuiHandler Handler;
      typedef imr::gui::CGui Gui;

      /// ----------------------------------------------------------------------------
      /// @brief 
      /// ----------------------------------------------------------------------------
      class CGuiFactory {
         public:
            enum TGuiType {NOTDEFINED, 
#ifdef GUITK
               TCLTK, 
#endif
               CAIRO};
            static CConfig & getConfig(CConfig & config);

            /// @deprecated ----------------------------------------------------------------
            static CGui * createGui(int argc, char ** argv);

            /// @deprecated ----------------------------------------------------------------
            static CGui * createGui(const char * guiName);

            static CGui * createGui(CConfig & cfg);

            static std::string getGuiStrType(void);
         private:
            static TGuiType getGuiType(int argc, char ** argv);
      };
   } //end namespace gui
} //end namespace imr


#endif

/* end of guifactory.h */
