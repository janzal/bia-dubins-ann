/*
 * File name: guilistener.h
 * Date:      2005/11/18 12:19
 * Author:    Jan Faigl
 */

#ifndef __GUILISTENER_H__
#define __GUILISTENER_H__

#include "guievent.h"

namespace imr {
   namespace gui {

      /// 
      /// @brief general class to handle events
      /// 
      class CGuiListener {
         public:

            typedef SGuiEvent Event;

            virtual ~CGuiListener() {}
            /// 
            /// @brief handle given event
            /// 
            /// @param event 
            /// 
            /// @return  true if event is handled otherwise false
            /// 
            virtual bool handle(Event & event) = 0;
      };

   } //end namespace gui
} //end namespace imr

#endif

/* end of guilistener.h */
