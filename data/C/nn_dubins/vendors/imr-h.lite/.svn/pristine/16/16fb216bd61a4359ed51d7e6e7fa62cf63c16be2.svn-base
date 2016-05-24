/*
 * File name: solver_algorithms.h
 * Date:      2009/04/19 07:36
 * Author:    Jan Faigl
 */

#ifndef __SOLVER_ALGORITHMS_H__
#define __SOLVER_ALGORITHMS_H__

#include <map>
#include <sstream>

#include "imr_exceptions.h"
#include "imr_config.h"

namespace imr {

   /* 
    * SolverBase is common parent of all solvers 
    *
    * The Solver derived class of SolverBase must have public type Base 
    * which must the SolverBase type
    * also each SolverBase must have public static method getName() which return std:string
    */

   /// ----------------------------------------------------------------------------
   /// @brief 
   /// ----------------------------------------------------------------------------
   template <class SolverBase>
      class SolverWrapperBase {
         public:
            SolverWrapperBase() {}
            virtual ~SolverWrapperBase() {}
            virtual imr::CConfig& getConfig(CConfig& config) = 0;
            virtual SolverBase* create(CConfig& config) = 0;
      };

   /// ----------------------------------------------------------------------------
   /// @brief 
   /// ----------------------------------------------------------------------------
   template<class Solver>
      class SolverWrapper : public SolverWrapperBase<typename Solver::Base> {
         public:
            SolverWrapper() : SolverWrapperBase<typename Solver::Base>() {}
            CConfig& getConfig(CConfig& config) {
               return Solver::getConfig(config);

            }
            typename Solver::Base* create(CConfig& config) {
               return new Solver(config);
            }
      };

   /// ----------------------------------------------------------------------------
   /// @brief 
   /// ----------------------------------------------------------------------------
   template<class SolverBase>
      class CAlgorithms {
         typedef typename std::map<typename std::string, SolverWrapperBase<SolverBase>* > SolverMap;
         public:
         /// ----------------------------------------------------------------------------
         static CConfig& getConfig(CConfig& config) {
            //           init();
            typename std::stringstream str;
            str << "possible solvers: ";
            for (typename SolverMap::iterator it = map.begin(); it != map.end(); it++) {
               str << it->first << ", ";
            }
            config.add<typename std::string>("solver", str.str());
            return config;
         }

         static typename std::string getSolvers() {
            typename std::stringstream str;
            str << "possible solvers: ";
            for (typename SolverMap::iterator it = map.begin(); it != map.end(); it++) {
               str << it->first << ", ";
            }
            return str.str();
         }

         /// ----------------------------------------------------------------------------
         static CConfig& getConfig(const typename std::string& solver, CConfig& config) {
            //init();
            typename SolverMap::iterator it = map.find(solver);
            if (it == map.end()) {
               throw imr::bad_code("Solver '" + solver + "' has not been found");
            }
            return it->second->getConfig(config);
         }

         /// ----------------------------------------------------------------------------
         static SolverBase* getSolver(const typename std::string& solver, imr::CConfig& config) {
            //           init();
            typename SolverMap::iterator it = map.find(solver);
            if (it == map.end()) {
               throw imr::bad_code("Solver '" + solver + "' has not been found");
            }
            return it->second->create(config);
         }

         template<class T>
            static void registerSolver(void) {
               if (map.find(T::getName()) == map.end()) {
                  map[T::getName()] = new SolverWrapper<T>();
               } else {
                  throw imr::bad_code("Solver '" + T::getName() + "' already exits");
               }
            }

         /* solver registration must be performed outside of this class 
            registerSolver<CTesting>();
            */
         private:
         static bool init_;
         static SolverMap map;
      };

   // declare static attributies
   template<class T> bool CAlgorithms<T>::init_ = false;
   template<class T> typename imr::CAlgorithms<T>::SolverMap CAlgorithms<T>::map;

} //end namespace imr


#endif

/* end of solver_algorithms.h */
