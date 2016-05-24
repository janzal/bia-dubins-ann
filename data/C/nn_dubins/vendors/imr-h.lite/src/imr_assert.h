/*
 * File name: imr_assert.h
 * Date:      2008/08/05 20:23
 * Author:    Jan Faigl
 */

#ifndef __IMR_ASSERT_H__
#define __IMR_ASSERT_H__

#include "common/imr_exceptions.h"

namespace imr {

#define ASSERT_ARGUMENT(cond, msg) if (!(cond)) throw imr::argument_error(msg);
#define ASSERT_IO(cond, msg) if (!(cond)) throw imr::io_error(msg);

   template<class T>
      inline void assert_exception(bool cond, const std::string& msg) __attribute__((always_inline));

   inline void assert_argument(bool cond, const std::string& msg) __attribute__((always_inline));

   template<class T>
      inline void assert_exception(bool cond, const std::string& msg) {
         if (!cond) {
            throw T(msg);
         }
      }


   inline void assert_argument(bool cond, const std::string& msg) {
      assert_exception<imr::argument_error>(cond, msg);
   }

   inline void assert_usage(bool cond, const std::string& msg) {
      assert_exception<imr::bad_usage>(cond, msg);
   }

   inline void assert_io(bool cond, const std::string& msg) {
      assert_exception<imr::io_error>(cond, msg);
   }

} //end namespace imr


#endif

/* end of imr_assert.h */
