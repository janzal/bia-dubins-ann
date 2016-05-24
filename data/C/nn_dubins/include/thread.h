/*
 * File name: threadB.h
 * Date:      2006/09/11 11:37
 * Author:    Jan Faigl
 */

#ifndef __THREADB_H__
#define __THREADB_H__

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

#include "threadwrapper.h"


namespace imr {
   namespace concurrent {
      typedef boost::mutex::scoped_lock ScopedLock; 
      typedef boost::mutex Mutex;
      typedef boost::condition Condition;


      /// ----------------------------------------------------------------------------
      /// @brief Thread implementation encapsulation
      /// threadBody and stop must be implemented 
      /// threadBody is main thread code
      /// stop is safe stop of thread execution code it is used in destructor
      /// thread is created by execute method, which call threadBody method
      /// ----------------------------------------------------------------------------
      class CThread {
         friend class CThreadWrapper<CThread>;
         public:
         typedef boost::mutex::scoped_lock ScopedLock; 
         typedef boost::mutex Mutex;
         typedef boost::condition Condition;

         CThread();
         virtual ~CThread();



         bool isRunning(void);
         bool isFinished(void);

         void join(void);
         void yield(void);

         //TODO
         //void sleep(long ms);



         /// ----------------------------------------------------------------------------
         /// @brief create thread and starts execution of run method
         /// ----------------------------------------------------------------------------
         void execute(void);

         /// ----------------------------------------------------------------------------
         /// @brief if thread is running stop it
         /// ----------------------------------------------------------------------------
         virtual void stop(void) = 0;

         protected:
         void terminate(void);

         /// ----------------------------------------------------------------------------
         /// @brief threadBody main thread loop called if 
         /// ----------------------------------------------------------------------------
         virtual void threadBody(void) = 0;

         // private:
         protected:
         CThreadWrapper<CThread> * _wrapper; 
         boost::thread * _thrd;

         bool _running;
         bool _finished;
      };
   } //end namespace concurrent
} //end namespace imr


#endif

/* end of threadB.h */
