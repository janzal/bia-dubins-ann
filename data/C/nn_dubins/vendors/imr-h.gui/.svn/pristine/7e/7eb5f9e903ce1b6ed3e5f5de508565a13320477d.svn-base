/*
 * File name: canvascontainer.h
 * Date:      2007/02/18 17:53
 * Author:    Jan Faigl
 */

#ifndef __CANVASCONTAINER_H__
#define __CANVASCONTAINER_H__

#include <string>
#include <vector>

#include <cairo.h>

#include "renderer.h"
#include "shape.h"
#include "concurrent/thread.h"
#include "manager.h"

using imr::gui::manager::CObject;
using imr::gui::CShape;
using imr::gui::SColor;


namespace imr { namespace gui { namespace cairo {
   struct SCanvasObject : public CObject {
      const std::string name;

      SCanvasObject(ObjectType type, const std::string& tags, const CShape& shape);
      virtual ~SCanvasObject();
      void draw(cairo_t*cr);
      bool in_stroke(cairo_t* cr, double x, double y);
      std::ostream& operator<<(std::ostream& out) {
         return out << "cairo canvas object does not support to string conversion";
      }      
   };

   class CCanvasDrawer : public imr::gui::manager::CObjectExecutor {
      cairo_t* cr;
      public:
      CCanvasDrawer(cairo_t* iCr);

      void setCairo(cairo_t* iCr);
      void execute(imr::gui::manager::CObject* obj);

   };


   /// ----------------------------------------------------------------------------
   /// @brief 
   /// ----------------------------------------------------------------------------
   class CCanvasContainer {
      typedef imr::concurrent::ScopedLock ScopedLock;
      typedef imr::concurrent::Mutex Mutex;
      typedef imr::gui::manager::CManager Manager;
      Manager manager;
      CCanvasDrawer* drawer;

      SColor backgroundColor;

      cairo_t* cr;

      public:
      CCanvasContainer();
      ~CCanvasContainer();


      //TODO x, y from user select
      void draw(cairo_t* cr);

      void drawBackground(cairo_t* cr, int width, int height, double zoom);
      void setBackgroundColor(const SColor& color, double alpha = 1.0);

      /// added object is managed by canvascontainer
      /// so it is deleted in CCanvasContainer destructor
      void addObject(SCanvasObject* object);


      void clearObjects(const std::string& tags);

      void getObjectsNames(double x, double y, std::list<std::string>& lst);
      void getObjects(double x, double y, Manager::ObjectList& objects);


      Manager& getManager(void) {
         return manager;
      }   

      private:
      Mutex mtx;
   };

} } } //end namespace imr::gui::cairo

#endif

/* end of canvascontainer.h */
