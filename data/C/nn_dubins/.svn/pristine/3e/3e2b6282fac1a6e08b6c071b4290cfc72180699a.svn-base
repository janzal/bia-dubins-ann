/*
 * File name: dubins_demo.h
 * Date:      2016/03/08 12:46
 * Author:    Jan Faigl
 */

#ifndef __DUBINS_DEMO_H__
#define __DUBINS_DEMO_H__

#include <string>

#include <canvas.h>
#include <imr_config.h>

class CDubinsDemo {
   typedef imr::gui::CCanvasBase Canvas;

   public:
      static imr::CConfig& getConfig(imr::CConfig& config);

      CDubinsDemo(imr::CConfig& config);
      ~CDubinsDemo();

      void setCanvas(Canvas* canvas) { this->canvas = canvas; }
      void demo(void);

   private:
      std::string getOutputPath(const std::string filename, std::string& dir);
      void saveCanvas(void);

   private:
      imr::CConfig& cfg;
      Canvas* canvas;
      std::string output;
      std::string resultCanvasOutput;
};


#endif

/* end of dubins_demo.h */
