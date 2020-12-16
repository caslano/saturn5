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
2A0+CfvCp+AQ+DQcA5+B+XA/XAZ7wpWwF9wAe8NbVD/nHtXP2ROgn7MCvgJXwY9UT+efcDWMcfn0dMrAjbAKXA9rwxtgQ9XPaQw3wbbwdjgJbobT4FZ4qerfXAHvgivh3XADvBfeBu+Dj8AH4F74IHwa7oF/hQ/BE/Ax+BHcBt1uuW4pj+9b+n2n37VtMCmW1Gnyo/qR5+N72BT+ALvB0/75qJTrodCCU4ALFkI3XAQjtfxHwU0wGm6FcfBOWBr+GcbDIzARvgPLwg9gefgVrAi/gSnQm9iq0AWrwRhYHabCGrABrAlbwFrwAlhHn7/jln5X6HdSG/1WOuzf44br8tpfgHXhi/ACeAh2gJ/D/v49TCSc77qPwHnwFfgH+CpcC1+Dm+AxfU7fgI/CN+Hj8G14EP4N/gW+o3pwf4fvwvdV/+0j6CStJ2Fp+DFMhp/AqvBTWA9+DuM9vnmqp2awPm0+69Ni0vLPTEdrTH7JnNX/Bz2t/5U5q79Z3azbnSX6WT9DP+vX0s2aQz22HnM/5lB+iY5Wya/kV/Ir+f0v/37p+f9Z52j+/yMhY//IQsb+kQWP/RuZM3CtP5W5Qub0Iy9urQCVe8y6ALbfiGLG8x8JM56/JGAdwXd0HUHvPvVVlOtxGVjfP26d9ZPz0H1+R5g53C0b+PqYo60Us0ZfR5HdgKRx0fFrM2e3nfhpxXWnaD+zHbfONdd4KhRdf9D0NS8W/+uc4/BbZCzajIfeJX7yZX2+R4qMQ+8Wt/nk06xi56hXgFeKn03OSQ4XsvBjyBvF31xnV0eEFTrf2x4Dvln8LXBe6HCGjhPrnOf54ucW58WOmIA5y3lyTXs4ukncFzqDxop1zvnl4rZZ1mS8RsZbuKeWZcYArhf3pc7+jihNp/qRcYsCMw4wWvL+MCNV402//B9ENjDcnGkz/n+7nGOOs4vDjayIXx2b3wVXir8VzuLmNafBVfTf1wgeOzZmRpG5zFvMXGZk8fZcZuI16/udTLTHhJdj/oEdN53nHDzHOZHnJknHlZLhWBih6wOOO4Mx4NRG9hhwRIPQsdgf6oeOxf4dWdGx2GNG1lbsLxl7G7FXNXG3ljiuVzvPsjkXz1HI+OzGYsZntxUZny2NbI+ZV5wnY1e7wswrTiuZV/yT4zVnO/5yruYVp8RI+p+/6Nla+zcNXl0lf+iY6oPalcwrfvA3PK94r3kfynta5vO25Ph+aOn6f1VgU1gNXgDHwvZwAuwAF8Be8BrYGy6FfeBq2Ff7NfvDHXAA3AkHwfvhYPhHOBQe1HhfgN3hMdgDvglHwnfhKPghHAs/gZ11HKILjILpMBZmwJpwPKwPp8LW8BrYFS6FfeAyOAQuh6PhCpgNV8K5cBW8AU6AO+FEeC+cAv+k8R6COfAInA7fgLnwLTgDfgnz4Wk4E5Yhn2fB6vBSeD68DPaEV8Cx8Eo4D86FK+ECuA5eDQ/AP8BDcBW0KBNRM2V+7Rn325b02f7++2ztubUl82r/o77bkn7bs+63/VXn1VL3Wdav3P5HGQe9vXPS/t8e0v5HFtL+Rxai+x+FrPj2+Lwk3onaHl+o7/IozZdITFvCbTxf9JHT03NyMzNyUEPMmpybXpCZMX1Cei5JzZ1e4GuHWMX+UrsQOe5x0naal+CgzyF9gC/ckMLc/IyJFPEgfcjFeptakp7zYGW4Hpddko55vhz99/0C6rdhWH11dTd6jxXrYWf0uzky2rGar7lGr/hd8b+M75tWrO3hDmnfJ2s79bj4uwF/F/Cudpq26kGJv0LRdr2EKwsTxP0RQpXmmwidSJHb4WLMml050h5NVX33Ab41umZOCNCBbEQ7NcZup4p5GrOQe70=
*/