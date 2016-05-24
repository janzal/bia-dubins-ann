/*
 * File name: cairowinfake.h
 * Date:      2007/08/21 21:30
 * Author:    Jan Faigl
 */

#ifndef __CAIROWINFAKE_H__
#define __CAIROWINFAKE_H__

#include "cairowin.h"

namespace imr {
   namespace gui {
      namespace cairo {
         class CCairoWinFake : public CCairoWin {
            public:
               CCairoWinFake(CCanvasContainer * iCanvas = 0);
               ~CCairoWinFake();
               void initialize(void);
               void redraw(void);
               void invalidate(void);
               void start(void);
               void stop(void);
               void handleEvents(void);
               void setBackgroundColor(const SColor& color);
         };

      } //end namespace cairo
   } //end namespace gui
} //end namespace imr


#endif

/* end of cairowinfake.h */
