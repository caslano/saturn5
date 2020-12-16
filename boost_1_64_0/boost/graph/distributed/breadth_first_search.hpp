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
A3+Et8Gf4DL4M7xf9x5+FEZr+Vhg6fu7vtef0O8Hs7V8jtD+TyasCcfAxnASbKb+djALdoLZ8BqYA+eq/2b13wbHwUdgLtwFL4M/wzzodkm62h7reyt8ooT2eJXbX28ege3go3A4XA+nwg2wGD4BF8An4R/UvxL+Ea5WPcYdxPa8YSOP1QeXi5uHW4HbjNuHO4mrhiF8Gi4DV4RbhFuH24E7jEto7LEa4vrg8nDzcCtwm3F7cSdx1ZqQBm4QrhC3ALcOtw13EBfXFBtPXAdcJq4Ytxy3GbcPdxJXGYP75rh0XB5uPu5h3Fack/18xjO0Q4Tr3tHY06OH34vRfhNcOq4QtwD3MG42aWyBe3CHcVZzzy+yv0/v5fpN9or22d5XK8H+fhdu83+B/X0h+eJkg7+unvufssNfStrb4Eb4j+zx9/RynbZNfkJvvjrgnGzzu/R2/eb2+b/ENr+Q87Lt84mfSTq/cD/p6bjcM7DNX9rb9Zvb51do7vm32+g/w3UexKmtvnQKbXt92NzzH2Wzn9rHdUZ2+23RV9t92lTicj1FuAW4VbjNuL24EzhvC9pTXDouDzcbtxy3EbcDtx8X1fKszf7/299vu/9f1pRCn/H/P2n777PdP5YSYeOPLMLGH1mojX+yyjw+mWwQ1n/woCDdaL8uW9vZshiRpfcfMMiOHyeyfv39e4nZ8tIq5/9+nbva8ooi79Sxi+61pmkTLufBNm+2blWRodivK1dmy2uKvHPHbj37dA2Wp6o8veOgHsHyc/RcNIaR11K5xjDyc81xe3flkoz8PJ9cd94LPvcG/uN2Dc6X8/1pkCsd+wTrNtJztM8vYq9DlUfudajyyL0ORe681yFhznsdanjEXocid97rUMOd9zqUcMe9Dglz3utQw533OpRwx70OCXPc61DDnfc61HDnvQ4l3HGvQ8Ic9zokzHmvQ8Kc9zqUcMe9Dglz3OtQwx33OtRw570ONdx5r0MJd9zrkDDHvQ4Jc9zrUMOd9zrUcOe9DiX81HsdHks59V6H6ITvdWjq82GR9+1iiW6cyJBgo8359O9J0+efT/VMect8l89UO+9zXMSB5WFCVX60889Hys4e7XtCjJ7Cwrpj8vzffn9O8a+/fHmQvWMt0T9Oe2jsXzSNWoG1lfmtqZhv3qpDrCS1o68pfperAf8mG5vOrJzJRZinYe0ZiJtu4lYzNlDVxO92nW955JiXyzf2CVOmTOUBFfSduoroTWKXN7ekdYlJq4rZx+uY+M+X63VVlXSyp0gaXRP7u3TdOf+5htjpDPHKN29jlzQU3Rmid5X6NW1dj7xiedH3X5ee34sSfmGJ59JR0p+SX6D6/dC/RcLHqT+gn2L0SR8bPzv9ORLe1qQfe7Guw8839UExvrnMjFlxXgllircFvqk/7/V/U78Af2mxzUOGznb4J7hF5zW9BBtSsl44zb0nZb/BdmozM3mysV+ljMk615erzWMPs8a1XYZSkKcbe9igMqJxMiBlgDBTBowdjauqyLmnYTaPZSz52+dmfBi+CJPQbXJxYN4ca28XFuRnk5xdFwrlRLXcq25jc/9Hi/9ht09/TWXRzxo7oUDrQEC/odmjaKT414u+y28zKPqBujbMn757GSPwWhc0jfN0fovL2tseP5a8A61h9Odi2Revnpxvea4ljvKJBRG6nRO5aP6QdfDpP879GssaYWX8to9xVolr+p8vaU835edABzl2iTZx38p5vaTnzlmL7j6+q90m5/NTCuphbcnDotOas47XdALHYM83uQaNI2ZQtp2m5hd/kl3GFuhhOYcKZq7OZvE3cicZfbZZJEZwGzFGdGa7/xx5nUHHGduyedDekc8=
*/