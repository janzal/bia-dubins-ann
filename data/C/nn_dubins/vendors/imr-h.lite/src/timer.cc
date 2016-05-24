/*
 * File name: timer.cc
 * Date:      2005/10/31 08:33
 * Author:    Jan Faigl
 */

#include <cstdlib>
#include <sys/resource.h>

#include "timer.h"

using namespace imr;

//----------------------------------------------------------------------------
//Class CTimer
//----------------------------------------------------------------------------
CTimer::CTimer() {
   timeSec_ = 0;
   time_ = 0;
   start();
}

//----------------------------------------------------------------------------
void CTimer::start(void) {
   userStart_ = getUserTime();
   sysStart_ = getSysTime();
   gettimeofday(&start_, NULL);
}

//----------------------------------------------------------------------------
void CTimer::stop(void) {
   userStop_ = getUserTime();
   sysStop_ = getSysTime();
   gettimeofday(&end_, NULL);
   userTime_ = userStop_ - userStart_;
   sysTime_ = sysStop_ - sysStart_;
   time_ = (end_.tv_sec-start_.tv_sec)*1000+(end_.tv_usec-start_.tv_usec)/1000;
   timeSec_ = time_/1000.0;
}

//----------------------------------------------------------------------------
void CTimer::reset(void) {
   timeSec_ = 0.0;
   time_ = 0;
}

//----------------------------------------------------------------------------
double CTimer::time(void) {
   return timeSec_;
}

//----------------------------------------------------------------------------
long CTimer::timeMS(void) {
   return time_;
}

//----------------------------------------------------------------------------
double CTimer::userTime(void) {
   return userTime_;
}

//----------------------------------------------------------------------------
double CTimer::sysTime(void) {
   return sysTime_;
}

//----------------------------------------------------------------------------
long CTimer::getTime(void) {
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec;
}

//----------------------------------------------------------------------------
double CTimer::getUserTime(void) {
   struct rusage usage;
   double ret = 0.0;
   int r = getrusage( RUSAGE_SELF, &usage);
   if ( r == 0) {
      ret = double( usage.ru_utime.tv_sec)               // seconds
         + double( usage.ru_utime.tv_usec) / 1000000.0; // microseconds
   } 
   return ret;
}

//----------------------------------------------------------------------------
double CTimer::getSysTime(void) {
   struct rusage usage;
   double ret = 0.0;
   int r = getrusage( RUSAGE_SELF, &usage);
   if ( r == 0) {
      ret = double( usage.ru_stime.tv_sec)               // seconds
         + double( usage.ru_stime.tv_usec) / 1000000.0; // microseconds
   } 
   return ret;
}

/* end of timer.cc */
