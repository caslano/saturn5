// Copyright (C) 2005-2006 The Trustees of Indiana University.
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Peter Gottschling
//           Douglas Gregor
//           Andrew Lumsdaine

#include <boost/graph/iteration_macros.hpp>
#include <boost/property_map/parallel/global_index_map.hpp>

#ifndef BOOST_GRAPH_DISTRIBUTED_GRAPH_UTILITY_INCLUDE
#define BOOST_GRAPH_DISTRIBUTED_GRAPH_UTILITY_INCLUDE

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

namespace boost { namespace graph {

  template <class Property, class Graph>
  void property_on_inedges(Property p, const Graph& g) 
  {
    BGL_FORALL_VERTICES_T(u, g, Graph)
      BGL_FORALL_INEDGES_T(u, e, g, Graph)
      request(p, e);
    synchronize(p);
  }
  
  // For reverse graphs
  template <class Property, class Graph>
  void property_on_outedges(Property p, const Graph& g) 
  {
    BGL_FORALL_VERTICES_T(u, g, Graph)
      BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
        request(p, e);
    synchronize(p);
  }

  template <class Property, class Graph>
  void property_on_successors(Property p, const Graph& g) 
  {
    BGL_FORALL_VERTICES_T(u, g, Graph)
      BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
        request(p, target(e, g));
    synchronize(p);
  }
  
  template <class Property, class Graph>
  void property_on_predecessors(Property p, const Graph& g) 
  {
    BGL_FORALL_VERTICES_T(u, g, Graph)
      BGL_FORALL_INEDGES_T(u, e, g, Graph)
        request(p, source(e, g));
    synchronize(p);
  }
  
  // Like successors and predecessors but saves one synchronize (and a call)
  template <class Property, class Graph>
  void property_on_adjacents(Property p, const Graph& g) 
  {
    BGL_FORALL_VERTICES_T(u, g, Graph) {
      BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
        request(p, target(e, g));
      BGL_FORALL_INEDGES_T(u, e, g, Graph)
        request(p, source(e, g));
    }
    synchronize(p);
  }

  template <class PropertyIn, class PropertyOut, class Graph>
  void copy_vertex_property(PropertyIn p_in, PropertyOut p_out, Graph& g)
  {
    BGL_FORALL_VERTICES_T(u, g, Graph)
      put(p_out, u, get(p_in, g));
  }

  template <class PropertyIn, class PropertyOut, class Graph>
  void copy_edge_property(PropertyIn p_in, PropertyOut p_out, Graph& g)
  {
    BGL_FORALL_EDGES_T(e, g, Graph)
      put(p_out, e, get(p_in, g));
  }


  namespace distributed {

    // Define global_index<Graph>  global(graph);
    // Then global(v) returns global index of v
    template <typename Graph>
    struct global_index
    {
      typedef typename property_map<Graph, vertex_index_t>::const_type
      VertexIndexMap;
      typedef typename property_map<Graph, vertex_global_t>::const_type
      VertexGlobalMap;

      explicit global_index(Graph const& g)
        : global_index_map(process_group(g), num_vertices(g), get(vertex_index, g),
                           get(vertex_global, g)) {}

      int operator() (typename graph_traits<Graph>::vertex_descriptor v)
      { return get(global_index_map, v); }
    
    protected:
      boost::parallel::global_index_map<VertexIndexMap, VertexGlobalMap> 
      global_index_map;
    };

    template<typename T>
    struct additive_reducer {
      BOOST_STATIC_CONSTANT(bool, non_default_resolver = true);
      
      template<typename K>
      T operator()(const K&) const { return T(0); }
      
      template<typename K>
      T operator()(const K&, const T& local, const T& remote) const { return local + remote; }
    };

    template <typename T>
    struct choose_min_reducer {
      BOOST_STATIC_CONSTANT(bool, non_default_resolver = true);
      
      template<typename K>
      T operator()(const K&) const { return (std::numeric_limits<T>::max)(); }
      
      template<typename K>
      T operator()(const K&, const T& x, const T& y) const 
      { return x < y ? x : y; }
    };

    // To use a property map syntactically like a function
    template <typename PropertyMap>
    struct property_map_reader
    {
      explicit property_map_reader(PropertyMap pm) : pm(pm) {}

      template <typename T>
      typename PropertyMap::value_type
      operator() (const T& v)
      {
        return get(pm, v);
      }
    private:
      PropertyMap pm;
    };

  } // namespace distributed

}} // namespace boost::graph

#endif // BOOST_GRAPH_DISTRIBUTED_GRAPH_UTILITY_INCLUDE

/* distributed_graph_utility.hpp
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
*/