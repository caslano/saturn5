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
bIPXx/odn2gO3da+MOL7CotNbkmvZ7W/L+l+wmKTW9L9mc4xJD3Yek8B6H6g164/kG7SH6jxUf+ls1+iJfBaYCTixb1K37Xzy1LKSksL8mCfSvuu3bOhAL0yD17WHdB5E+S31kzyD1KMb3iFZZVV/A1b8reX3yKvIX85+xUR9RqlTekdj5B2oaW9pyHEnyaShY3iZEqZbaS94DKSEYv2sdM32YvR2rfr3PxJ+ZW6DTWgk8skRGVBxYyCChRX6iPcQjI/o29MH0BSbbI97V+plbqb4uUivLUYIsKlXay9RD8MaldxUJMHui6vJckzvg3noeKN7/oTKO4ItpvoEUfmYWZRflWh1C24QHGCkYcxlK8MtPt2yN4JlwyGl1C3L8INAz2Yv1++7OGf0wAIXAmXhDiRSEvEqGe4UFlFk2a78dkO9Ql6CtIEHa4b5a0V+mqUZkfGJmr5IYIQqL9eYUkIH4Yy0TdC/I32gJ/6GNFmgYZ+BBr1I6JVg4a+odvilrodaGfQZDujLnqGXaJ6QAs3tup0ZIfzHOcvREfGtQjZpPU/zE7SaLc3m93M20naND9O/kne9DeYf7Zs10ZHqR1lXxfc1+M5fPHv1fAP7Ysxq7yEQ86n4T6GXVm7faBow3bu3vidyrPY14FY7VDvo9G/7hDbcW53lu0b+14xy9df2jOerslzSN0AD3vGE4B/pTxO9QuRPKh3k+3VT9VwpBHJNpmrjqn+Uz6pyhYRahvKdEU8VQO6+qUQdb5FtCL5OZAWTmUe5OehkyLHXXcKb+rnZ/9RCXL42/Vxl3Jcpd+O2gu32vjl+ooCJlFcp9/tip/YB/chnMvmJwbaXnJ0YDu+x6m+lsIedizavbkYh/a7CzlMUnrhGxO+J0MDZI6vL/V1J6Uxqai0qLIQ3UHqc0QCR1G5P1LgJ/uk7tdV/+eKk8L1/NZTbsG/Gg9SJVpfmjcasP7LEJ43elPeX4G89qIPxm06RtAo8K7D37vgnhH1xetwH4H+FZxNCRYNUL6rlFiRquSJh5SGpnrB+DTZZ7y2hurcHkRWEhvar8ZHn0jus3NOqGHjEdIAYQFyvkqnOAWSzrod+E2cPsldWXS9yS7mHtSp2Xbie+R3CKOfzZw50631NCfHWUw8PW2BOMkZzW3/BtXPLNv96OcH4V5RrpZj53bi7ybTaEL5C5Y2/xZS3B7ML/MgbWxfeo3K6aevY368jkXyuvU3Ci/yy3a0FKdxaNVpsqGeSrJbMk1RSZxemiyjp/3fQuAFkpnvZ+j0lOTOUjsSr0E9gEZ8k+0cXhsvUvyJfjn2z5Wh2lgA3dK3zGuQ1KU6T31znL0dLPppNL2++tiDRVO7TNNqD5jGcz3qh1l+JfZXlN5I08t49moLdwAogSRjmF9ttlRb8LwliGek3xuKQ3wP1wq2YnPhguwOEWlPpDkqWWh2Oqtyi7NRa9S2z6vloz7blvxH4H+zxph3G8ZyH+U6rgZGmuvfjbFRiR0NfG14ToikvPT224/x9D5cfcwZg+G+hOtm/0Jpj3ow6UapuyI5DwyhcW+z6fPAZKr7k4oWro/5VNQXwo22Qz36meaYibOrCird6soFj1xP+pGsH1l/Dq1Faf1JcVK455wIHk4PIVQXnaOozAUYd9LGfhsqa4KpT1ZWuSdO19ZxLkMI8aT7jbafVLqh7Na8OynvtdoH5f53itaZxvIOBh+Sd60pTZg9ZXtQTtY1jKSyTrZX2gZSvN4IO0v9fybH43bV9co4rWcpXpotHCe0VRuLb/gI0SRY012wz/9bYHxgW1WnLMCqU2bsX5fSPJHIfjlveOqXybLdSeGNSLdMT28w0huOzhDkd9O2IHtgkKM=
*/