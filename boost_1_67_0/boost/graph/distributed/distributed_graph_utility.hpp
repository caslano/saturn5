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