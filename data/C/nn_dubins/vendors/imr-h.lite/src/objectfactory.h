/*
 * File name: objectfactory.h
 * Date:      2007/07/23 17:51
 * Author:    Jan Faigl
 */

#ifndef __OBJECTFACTORY_H__
#define __OBJECTFACTORY_H__

#include <vector>
#include <stdexcept>

#include "stringconversions.h"


namespace imr {

   template <class T, class TT> 
      class CDefaultAccess {
         public:
            static TT get(T & t) {
               return t.getID();
            }
      };

   template <class T, class TT, class TTT = CDefaultAccess<T, TT> >
      class CObjectFactory {
         public:
            typedef T Object;
            typedef TT ObjectID;
            typedef TTT IDAccess;
            typedef std::vector<T*> Objects;

            CObjectFactory() { 

            }

            ~CObjectFactory() {
               for (typename Objects::iterator it = objects.begin(); it != objects.end(); it++) {
                  delete *it;
               }
            }

            /// ----------------------------------------------------------------------------
            /// @brief registerObject
            /// 
            /// @param object 
            /// ----------------------------------------------------------------------------
            void registerObject(Object * object) {
               if (object != 0) {
                  for(int i = objects.size(); i <= IDAccess::get(*object); i++) {
                     objects.push_back(0);
                  }
                  if (objects[IDAccess::get(*object)] == 0) {
                     objects[IDAccess::get(*object)] = object;
                  } else {
                     throw std::runtime_error("Object already registered id '" + imr::string_format<ObjectID>(IDAccess::get(*object)) + "'");
                  }
               }  
            }

            /// ----------------------------------------------------------------------------
            /// @brief createObject
            /// 
            /// @param id 
            /// 
            /// @return 
            /// ----------------------------------------------------------------------------
            Object * createObject(ObjectID id)  {
               Object * object = 0;
               if (id > 0 && id < objects.size() && objects[id] != 0) {
                  object = objects[id]->newInstance();
               } else {
                  throw std::runtime_error("Can no create object with id '" + imr::string_format<ObjectID>(id) + "'");
               }
               return object;
            }
         private:
            Objects objects;
            ObjectID null;
      };

} //end namespace imr


#endif

/* end of objectfactory.h */
