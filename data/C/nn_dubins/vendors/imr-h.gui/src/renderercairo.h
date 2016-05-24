/*
 * File name: renderercairo.h
 * Date:      2007/02/17 18:38
 * Author:    Jan Faigl
 */

#ifndef __RENDERERCAIRO_H__
#define __RENDERERCAIRO_H__

//#include "sdl_thread/waitobject.h"

#include "logging.h"
#include "imr_config.h"


#include "renderer.h"
#include "shapes.h"
#include "view_transform.h"

#include "cairowin.h"
#include "canvascontainer.h"

using imr::gui::cairo::CCanvasContainer;
using imr::gui::cairo::CCairoWin;

namespace imr { namespace gui { namespace render {

   class CRendererCairo : public CRenderer {
      static bool initialized;
      TObjectType state;
      //transformation
      CViewTransform transform;
      /*	    double view_x;
		    double view_y;
		    double kx;
		    double ky;
		    double x_border; 
		    double y_border;

		    double _x;
		    double _y;
		    */	    /*double minx;
			      double maxx;
			      double miny;
			      double maxy;
			      */	    
      int exportWidth;
      int exportHeight;
      int count;
      CCanvasContainer* canvas;
      CCairoWin* win;
      imr::gui::cairo::SCanvasObject* _obj;


      public:
      CRendererCairo(CCanvasContainer* iCanvas, CCairoWin* iWin);
      CRendererCairo(CCanvasContainer* iCanvas, CCairoWin* iWin, CConfig& cfg);
      virtual ~CRendererCairo();

      void setDimension(int width, int height);

      void setArea(double minX, double maxX, double minY, double maxY);

      void canvas2Real(double iX, double iY, double* oX, double* oY);

      void real2Canvas(double iX, double iY, double* oX, double* oY);

      void redraw(void);

      void drawPoint(double iX, double iY, const std::string& tags, const CShape& shape);

      void clearObjects(const std::string& tags);

      void setHandler(Handler* handler);

      //TODO remove
      //       void initialization(int argc, char ** argv, CWaitObject* iRendererInit);

      bool isInitialized(void);

      bool open(TObjectType object, const std::string& tag, const CShape& shape);

      bool close(void);

      void reset(void);

      void addPoint(double x, double y);

      //           void setExportDimension(int width, int height);

      bool save(const std::string& filename);

      unsigned char* getGrayscale(int& width, int& height);

      bool shutdownRequest(void);

      void getObjectsNames(double x, double y, std::list<std::string>& lst);

      void getObjects(double x, double y, Manager::ObjectList& objects);

      Manager& getManager(void);

      void setBackgroundColor(const SColor& color);

      const CViewTransform& getTransform(void);

      protected:
      bool antialiasing;
   };
} } } //end namespace imr::gui::render

#endif

/* end of renderercairo.h */
