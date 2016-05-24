/*
 * File name: imr_string_utils.h
 * Date:      2009/07/25 13:20
 * Author:    Jan Faigl
 */

#ifndef __IMR_STRING_UTILS_H__
#define __IMR_STRING_UTILS_H__

#include <string>
#include <vector>

namespace imr {
   typedef std::vector<std::string> StringVector;

   StringVector& string_split(const std::string& str, char sep, StringVector& tokens) {
      tokens.clear();
      std::string::size_type cur = 0;
      std::string::size_type next;
      do {
         next = str.find(sep, cur);
         tokens.push_back(str.substr(cur, next - cur));
         cur = next + 1;
      } while (next != std::string::npos);
      return tokens;
   }

} //end namespace imr


#endif

/* end of imr_string_utils.h */
