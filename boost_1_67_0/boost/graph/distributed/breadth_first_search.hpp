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