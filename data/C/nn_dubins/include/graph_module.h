/*
 * File name: graph_module.h
 * Date:      2011/02/17 17:06
 * Author:    Jan Faigl
 */

#ifndef __GRAPH_MODULE_H__
#define __GRAPH_MODULE_H__

#include "loader_module.h"
#include "loader_types.h"

namespace imr {  namespace loader {

   class CGraph : public CModule {
      typedef enum {
         GRAPH_NODES = 0,   /// - is followed by set of points in format label x y, where label 
         ///                  is int and x and y are doubles
         GRAPH_EDGES = 1,   /// followed by a list of triplets (i v1 v2) where
         ///                i is the index of the edge 
         ///                v1 and v2 are indexes of the graph nodes, i.e., v1 < n and v2 < n, where n is the size of graph nodes section
         GRAPH_CITY_NODES = 2, /// - list of indexes of nodes that represent cities (should be first in the GRAPH_NODES
         GRAPH_EDGES_COSTS = 3, /// - optinal, followed by a pair (i c) where i is the edge index and c associated costs (double)
         GRAPH_DEPOTS = 4, /// - list of indexes of nodes (goals) that reprsent starting goals aka depots in routing problems
         GRAPH_NUM = 5,
         NONE = 6
      } TSections;

      static const std::string name;

      public:
      typedef imr::loader::Point Point;
      typedef imr::loader::Points Points;
      typedef imr::loader::EdgeNode Edge;

      public:

      CGraph();
      ~CGraph();

      CModule* createInstance(void) const { return new CGraph(); }

      const std::string& getName(void) const;

      const std::string& getFirstSection(void) const;

      std::vector<std::string>& getSections(std::vector<std::string>& sections);

      CGraph& operator=(const CGraph& mp);

      void clear(void);

      void parse(std::istream& in, std::string& line);

      void print(std::ostream& out) const;

      void fill(const CModule* module);

      Points& nodes(void) { return nodes_; }
      EdgeNodeVector& edges(void) { return edges_; }
      Indexes& cities(void) { return cities_; }
      LabeledCostVector& edgesCosts(void) { return edgesCosts_; }
      Indexes& depots(void) { return depots_; }

      const Points& nodes(void) const { return nodes_; }
      const EdgeNodeVector& edges(void) const { return edges_; }
      const Indexes& cities(void) const { return cities_; }
      const LabeledCostVector& edgesCosts(void) const { return edgesCosts_; }
      const Indexes& depots(void) const { return depots_; }

      private:
      TSections getSection(const std::string& name) const;

      protected:

      Points nodes_;
      EdgeNodeVector edges_;
      Indexes cities_;
      LabeledCostVector edgesCosts_;
      Indexes depots_;
   };

} } //end namespace imr::loader 

#endif

/* end of graph_module.h */
