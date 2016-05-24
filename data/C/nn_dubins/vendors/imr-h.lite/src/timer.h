/*
 * File name: timer.h
 * Date:      2005/10/31 08:31
 * Author:    Jan Faigl
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <sys/time.h>

namespace imr {

   class CTimer {
      struct timeval start_;
      struct timeval end_;
      double userStart_;
      double userStop_;
      double sysStart_;
      double sysStop_;
      long time_;
      double timeSec_;
      double userTime_;
      double sysTime_;
      public:
      CTimer();

      void start(void);
      void stop(void);
      void reset(void);
      double time(void);
      long timeMS(void);

      /// --------------------------------------------------------------------------
      /// @brief userTime
      /// 
      /// @return user time in second
      /// ----------------------------------------------------------------------------
      double userTime(void);

      double sysTime(void);

      static long getTime(void);

      static double getUserTime(void);

      static double getSysTime(void);

   };

}
#endif

/* end of timer.h */
