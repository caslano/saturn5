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
+sD7ortZeHiQio+JQt1xMtyhcKZLva5hHg+5SS0/9m7BXJlLtqb2hu3KY4H5arx7hLERXcLHfYa8SFukOy2iPlNyz7FIzyHhnPhZZ2KkxJWID2ly3Jeh2cQPRARPBiWawvRAe36Mp6KSpJ4o+voDHhwpcE9wLpUzzvRw3JQubk6KGCaqj2t3JclccyTNQdix7iR85lImzS124YOmu0Y1z5RHkdeVICIcUp1zor3OOVO9rplRxd5E1pnGiZxpkmBYTYfTvWF6g9x5MNjxMRJ0Ur+4OkKXLSN9gcsuWC7HJMoy65/zwjQjblv9NZZ49WWmh2GWkYJa3aPwW5lf/Rx4PCYdJmuzR0TsC8cwEKWtaGgmkfMdY4GkK0leL9PigxjnbKm3SwwBd1NMolSUKMPr8MBU7gfBlLnypGAuBkPrQ+PTJ330VN05aLX5/Z4XcfU+2T0LyEUYFEKJePfomBPOn2+1RYj3u2bJXQpnikLidYUrwARwxSukXVLwuBWQBGxuXy7D++Xpy73Z7nthbtHVZ4tWD6Ay14wK25UUbuhZBmbA8vCuie44SdiuB8PrJRu7hju1jF0609kgMXy27CcQd9dced7gCQw8yc8fy3HN7y3WZbNha5qJMZjGuh+ImO1uhPEWP5EBjd23+kE5YWQFMQ5DKzpJJm4yYfN2iQ35suWp7qPQfIIcOTS6hF7INb8vE9+7EVr3JndihDih
*/