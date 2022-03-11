// Copyright 2010 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Andrew Lumsdaine

#ifndef BOOST_GRAPH_RANDOM_SPANNING_TREE_HPP
#define BOOST_GRAPH_RANDOM_SPANNING_TREE_HPP

#include <vector>
#include <boost/assert.hpp>
#include <boost/graph/loop_erased_random_walk.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/named_function_params.hpp>

namespace boost
{

namespace detail
{
    // Use Wilson's algorithm (based on loop-free random walks) to generate a
    // random spanning tree.  The distribution of edges used is controlled by
    // the next_edge() function, so this version allows either weighted or
    // unweighted selection of trees.
    // Algorithm is from http://en.wikipedia.org/wiki/Uniform_spanning_tree
    template < typename Graph, typename PredMap, typename ColorMap,
        typename NextEdge >
    void random_spanning_tree_internal(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s, PredMap pred,
        ColorMap color, NextEdge next_edge)
    {
        typedef
            typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;

        BOOST_ASSERT(num_vertices(g)
            >= 1); // g must also be undirected (or symmetric) and connected

        typedef color_traits< typename property_traits< ColorMap >::value_type >
            color_gen;
        BGL_FORALL_VERTICES_T(v, g, Graph) put(color, v, color_gen::white());

        std::vector< vertex_descriptor > path;

        put(color, s, color_gen::black());
        put(pred, s, graph_traits< Graph >::null_vertex());

        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            if (get(color, v) != color_gen::white())
                continue;
            loop_erased_random_walk(g, v, next_edge, color, path);
            for (typename std::vector<
                     vertex_descriptor >::const_reverse_iterator i
                 = path.rbegin();
                 boost::next(i)
                 != (typename std::vector<
                     vertex_descriptor >::const_reverse_iterator)path.rend();
                 ++i)
            {
                typename std::vector<
                    vertex_descriptor >::const_reverse_iterator j
                    = i;
                ++j;
                BOOST_ASSERT(get(color, *j) == color_gen::gray());
                put(color, *j, color_gen::black());
                put(pred, *j, *i);
            }
        }
    }
}

// Compute a uniformly-distributed spanning tree on a graph.  Use Wilson's
// algorithm:
// @inproceedings{wilson96generating,
//    author = {Wilson, David Bruce},
//    title = {Generating random spanning trees more quickly than the cover
//    time}, booktitle = {STOC '96: Proceedings of the twenty-eighth annual ACM
//    symposium on Theory of computing}, year = {1996}, isbn = {0-89791-785-5},
//    pages = {296--303},
//    location = {Philadelphia, Pennsylvania, United States},
//    doi = {http://doi.acm.org/10.1145/237814.237880},
//    publisher = {ACM},
//    address = {New York, NY, USA},
//  }
//
template < typename Graph, typename Gen, typename PredMap, typename ColorMap >
void random_spanning_tree(const Graph& g, Gen& gen,
    typename graph_traits< Graph >::vertex_descriptor root, PredMap pred,
    static_property_map< double >, ColorMap color)
{
    unweighted_random_out_edge_gen< Graph, Gen > random_oe(gen);
    detail::random_spanning_tree_internal(g, root, pred, color, random_oe);
}

// Compute a weight-distributed spanning tree on a graph.
template < typename Graph, typename Gen, typename PredMap, typename WeightMap,
    typename ColorMap >
void random_spanning_tree(const Graph& g, Gen& gen,
    typename graph_traits< Graph >::vertex_descriptor root, PredMap pred,
    WeightMap weight, ColorMap color)
{
    weighted_random_out_edge_gen< Graph, WeightMap, Gen > random_oe(
        weight, gen);
    detail::random_spanning_tree_internal(g, root, pred, color, random_oe);
}

template < typename Graph, typename Gen, typename P, typename T, typename R >
void random_spanning_tree(
    const Graph& g, Gen& gen, const bgl_named_params< P, T, R >& params)
{
    using namespace boost::graph::keywords;
    typedef bgl_named_params< P, T, R > params_type;
    BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(params_type, params)
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;
    vertex_descriptor default_vertex = *vertices(g).first;
    vertex_descriptor start_vertex = arg_pack[_root_vertex | default_vertex];
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::predecessor_map >::type pred_map
        = arg_pack[_predecessor_map];
    static_property_map< double > default_weight_map(1.);
    typename boost::parameter::value_type< arg_pack_type,
        boost::graph::keywords::tag::weight_map,
        static_property_map< double > >::type e_w_map
        = arg_pack[_weight_map | default_weight_map];
    typename boost::detail::map_maker< Graph, arg_pack_type,
        boost::graph::keywords::tag::color_map,
        boost::default_color_type >::map_type c_map
        = boost::detail::make_color_map_from_arg_pack(g, arg_pack);
    random_spanning_tree(g, gen, start_vertex, pred_map, e_w_map, c_map);
}
}

#include <boost/graph/iteration_macros_undef.hpp>

#endif // BOOST_GRAPH_RANDOM_SPANNING_TREE_HPP

/* random_spanning_tree.hpp
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
*/