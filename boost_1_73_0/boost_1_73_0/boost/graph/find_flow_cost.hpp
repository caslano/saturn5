//=======================================================================
// Copyright 2013 University of Warsaw.
// Authors: Piotr Wygocki
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_FIND_FLOW_COST_HPP
#define BOOST_GRAPH_FIND_FLOW_COST_HPP

#include <boost/graph/iteration_macros.hpp>

namespace boost
{

template < class Graph, class Capacity, class ResidualCapacity, class Weight >
typename property_traits< Weight >::value_type find_flow_cost(const Graph& g,
    Capacity capacity, ResidualCapacity residual_capacity, Weight weight)
{
    typedef typename property_traits< Weight >::value_type Cost;

    Cost cost = 0;
    BGL_FORALL_EDGES_T(e, g, Graph)
    {
        if (get(capacity, e) > Cost(0))
        {
            cost += (get(capacity, e) - get(residual_capacity, e))
                * get(weight, e);
        }
    }
    return cost;
}

template < class Graph, class P, class T, class R >
typename detail::edge_weight_value< Graph, P, T, R >::type find_flow_cost(
    const Graph& g, const bgl_named_params< P, T, R >& params)
{
    return find_flow_cost(g,
        choose_const_pmap(get_param(params, edge_capacity), g, edge_capacity),
        choose_const_pmap(get_param(params, edge_residual_capacity), g,
            edge_residual_capacity),
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight));
}

template < class Graph >
typename property_traits<
    typename property_map< Graph, edge_capacity_t >::type >::value_type
find_flow_cost(const Graph& g)
{
    bgl_named_params< int, buffer_param_t > params(0);
    return find_flow_cost(g, params);
}

} // boost

#endif /* BOOST_GRAPH_FIND_FLOW_COST_HPP */

/* find_flow_cost.hpp
T+6LjMCjS4EjIhyvz5XMc8BLTKScBXgCcEPAQ0FGIm9ulMTPc6IoroLcluXz4WcBbojc2tpiwupzOAqNtQceRCktodAghH3ecSqL4+r36itIC54aH34r8DfZh3fj8Nqz1wLFwU+LBc24Q2duzbTYmeTQanytSVUA7eyCIyyox9cloBUjItu1/fO39azIS/8wOy5VcivMvUqSCDglGPmF5nHUoMvoRpnhYzwvc0FpgcMCCa7IaQbxCCdkYOi8uNqP4eJ7cIAKPJfTWQgO/h0fGniAz5eDs5nNEgiEQCsNet3+RW9AfpXipZpjPeOZE4mn+WAW/uTZDDCPs/A6pvAst4UC/v0uA/cHsQH8OZAROJmfJz4ETWBCpoweRW1YuqA9bmF9K0+0eOHkvNvttfuXZwO/e95tL5WLZKFzQhy7DkpKOnyK5gjMOHkSwKXGUm9BEAE+zyGPhJco8PAcxrw6Puu3D1GvogIFy5WzbtPg4s44V9GXtrSBZjfJhnMCejUClWt/oSX2YTsEtoFg9hut5aQAiDLAwlRZ7f9p9859tgUPTMJ4zZJDnm5Q+tD0UeKHCgXm7D6eetFEmhM/FkrYBoKcx85SpzIQPnYimrvHwmnmuH7oEnRAGAKsr8Y9ci7t5859BKyI0u/cWElq
*/