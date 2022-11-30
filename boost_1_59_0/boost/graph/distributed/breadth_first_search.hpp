// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_PARALLEL_BFS_HPP
#define BOOST_GRAPH_PARALLEL_BFS_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/distributed/concepts.hpp>
#include <boost/graph/distributed/detail/filtered_queue.hpp>
#include <boost/graph/distributed/queue.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/pending/queue.hpp>
#include <boost/graph/parallel/properties.hpp>
#include <boost/graph/parallel/container_traits.hpp>

namespace boost {
  namespace detail {
    /** @brief A unary predicate that decides when to push into a
     *         breadth-first search queue.
     *
     *  This predicate stores a color map that is used to determine
     *  when to push. If it is provided with a key for which the color
     *  is white, it darkens the color to gray and returns true (so
     *  that the value will be pushed appropriately); if the color is
     *  not white, it returns false so that the vertex will be
     *  ignored.
     */
    template<typename ColorMap>
    struct darken_and_push
    {
      typedef typename property_traits<ColorMap>::key_type argument_type;
      typedef bool result_type;

      explicit darken_and_push(const ColorMap& color) : color(color) { }

      bool operator()(const argument_type& value) const
      {
        typedef color_traits<typename property_traits<ColorMap>::value_type>
          Color;
        if (get(color, value) == Color::white()) {
          put(color, value, Color::gray());
          return true;
        } else {
          return false;
        }
      }

      ColorMap color;
    };

    template<typename IndexMap>
    struct has_not_been_seen
    {
      typedef bool result_type;

      has_not_been_seen() { }

      has_not_been_seen(std::size_t n, IndexMap index_map)
        : seen(n), index_map(index_map) {}

      template<typename Key>
      result_type operator()(Key key)
      {
        bool result = seen[get(index_map, key)];
        seen[get(index_map, key)] = true;
        return !result;
      }

      void swap(has_not_been_seen& other)
      {
        using std::swap;
        swap(seen, other.seen);
        swap(index_map, other.index_map);
      }

    private:
      dynamic_bitset<> seen;
      IndexMap index_map;
    };

    template<typename IndexMap>
    inline void
    swap(has_not_been_seen<IndexMap>& x, has_not_been_seen<IndexMap>& y)
    {
      x.swap(y);
    }

    template <class DistributedGraph, class ColorMap, class BFSVisitor,
              class BufferRef, class VertexIndexMap>
    inline void
    parallel_bfs_helper
      (DistributedGraph& g,
       typename graph_traits<DistributedGraph>::vertex_descriptor s,
       ColorMap color,
       BFSVisitor vis,
       BufferRef Q,
       VertexIndexMap)
    {
      set_property_map_role(vertex_color, color);
      color.set_consistency_model(0);
      breadth_first_search(g, s, Q.ref, vis, color);
    }

    template <class DistributedGraph, class ColorMap, class BFSVisitor,
              class VertexIndexMap>
    void parallel_bfs_helper
      (DistributedGraph& g,
       typename graph_traits<DistributedGraph>::vertex_descriptor s,
       ColorMap color,
       BFSVisitor vis,
       boost::param_not_found,
       VertexIndexMap vertex_index)
    {
      using boost::graph::parallel::process_group;

      typedef graph_traits<DistributedGraph> Traits;
      typedef typename Traits::vertex_descriptor Vertex;
      typedef typename boost::graph::parallel::process_group_type<DistributedGraph>::type 
        process_group_type;

      set_property_map_role(vertex_color, color);
      color.set_consistency_model(0);

      // Buffer default
      typedef typename property_map<DistributedGraph, vertex_owner_t>
        ::const_type vertex_owner_map;
      typedef boost::graph::distributed::distributed_queue<
                process_group_type, vertex_owner_map, queue<Vertex>, 
                detail::darken_and_push<ColorMap> > queue_t;
      queue_t Q(process_group(g),
                get(vertex_owner, g),
                detail::darken_and_push<ColorMap>(color));
      breadth_first_search(g, s, Q, vis, color);
    }

    template <class DistributedGraph, class ColorMap, class BFSVisitor,
              class P, class T, class R>
    void bfs_helper
      (DistributedGraph& g,
       typename graph_traits<DistributedGraph>::vertex_descriptor s,
       ColorMap color,
       BFSVisitor vis,
       const bgl_named_params<P, T, R>& params,
       boost::mpl::true_)
        {
            parallel_bfs_helper
        (g, s, color, vis, get_param(params, buffer_param_t()),
         choose_const_pmap(get_param(params, vertex_index),  g, vertex_index));
        }
  }
}

#endif // BOOST_GRAPH_PARALLEL_BFS_HPP

/* breadth_first_search.hpp
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
*/