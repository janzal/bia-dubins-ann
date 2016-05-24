/*
 * File name: canvas_object_loader.h
 * Date:      2009/07/25 22:41
 * Author:    Jan Faigl
 */

#ifndef __CANVAS_OBJECT_LOADER_H__
#define __CANVAS_OBJECT_LOADER_H__

#include <istream>
#include <string>

#include "canvas.h"

namespace imr { namespace gui {

   class CCanvasObjectLoader {
      public:
         CCanvasObjectLoader(const std::string& filename, CCanvasBase& canvas);

      protected:
         void load(std::istream& in, CCanvasBase& canvas);
   };

} } //end namespace imr::gui


#endif

/* end of canvas_object_loader.h */
