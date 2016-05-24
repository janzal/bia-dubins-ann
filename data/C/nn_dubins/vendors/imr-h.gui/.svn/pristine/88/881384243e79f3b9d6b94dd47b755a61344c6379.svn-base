/*
 * File name: mouseclick.h
 * Date:      2007/08/29 06:29
 * Author:    Jan Faigl
 */

#ifndef __MOUSECLICK_H__
#define __MOUSECLICK_H__


#include "concurrent/waitobject.h"

#include "gui.h"
#include "guievent.h"
#include "guilistener.h"

namespace imr {
   namespace gui {
      class CMouseClick : CGuiListener {
         public:
            typedef SGuiEvent Event;

            /// ----------------------------------------------------------------------------
            /// @brief CWaitForClick
            /// 
            /// @param iGui 
            /// ----------------------------------------------------------------------------
            CMouseClick(CGui & iGui);

            ~CMouseClick();

            bool handle(Event & event);

            /// ----------------------------------------------------------------------------
            /// @brief getMouseClick return click coords in current real coords
            /// 
            /// @param oX 
            /// @param oY 
            /// ----------------------------------------------------------------------------
            void getMouseClick(double & oX, double & oY);

         private:
            typedef imr::concurrent::CWaitObject::Mutex Mutex;
            typedef imr::concurrent::CWaitObject::ScopedLock ScopedLock;

         private:
            CGui & gui;
            imr::concurrent::CWaitObject clickWait;
            bool enabled;
            Mutex enableMtx;
            double x;
            double y;

      };


   } //end namespace gui
} //end namespace imr 


#endif

/* end of mouseclick.h */
