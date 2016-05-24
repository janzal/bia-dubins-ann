/*
 * File name: nodeloader.h
 * Date:      2005/10/26 17:51
 * Author:    Jan Faigl
 */

#ifndef __NODELOADER_H__
#define __NODELOADER_H__

#include <fstream>
#include <string>
#include <list>

namespace imr {

   template <class T, class Container = typename std::list<T> >
      class CNodeLoader {
         public:
            typedef T Node;
            typedef Container NodeList;
            static NodeList load(const std::string& filename) {
               NodeList nodes;
               std::ifstream in(filename.c_str());
               if (in) {
                  while (in) {
                     T n;
                     if (in >> n) {
                        nodes.push_back(n);
                     }
                  }
               }
               return nodes;
            }
      };

}

#endif

/* end of nodeloader.h */
