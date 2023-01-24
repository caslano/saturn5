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
1LfogXjOaTvtM5X+pCEx+HXRpsVt9tYKKXfMIUfCnZZkM2GqnsVZ4CZ08kRutpy+89Py1eAkJBDOnAo3UsedP1Y3iboDA6W0glEwcE1pHJj0xqMwUGxnVExpCJL16nQNw7x9MPbvUnGOelxZ2fJa1261XePOgygaumpzs+ITZClbmsQzSSXhfXbMqvYnQOtk1z8xWBcPWW8OMdw7BybQuJqXCnjUbY0a3K3N5O4Wji26QJOEg4T1WYiroACFJ1tbw3K8w7GbcmAxKn+HclRfOU36w97YQTwq0CB8NcXfI9ltxGInB0SdcuHYRbgE8el2C56nHaQcymmq2nW94qgsnPX9JdDk705ZxwmXEKerKdO49fdg4/cW2zseDmEN306ebMmGUkvjy4d4TzOLvxLYfhUAACa8GI29z6YFGpuRybxQ290fGg1w4jPqD0jvufVj9mYkOFtpxikre9psCIIX1BXJY3sv+mqFS/X9Sb9c0phXUaG3E93d66vCkz/MDPZ501X6FUzB8dHr7W6AG5EHHHeTdFxU/XoxaraRzcnqPHM1yOeDXTGOqMgRbd6tDokYNh3Dt4z6SuXBNClV5lr9Au1Z3nBAKI1cltQMSw+PZwJbnKEpf9YGlWHdqCnsrWn9qvAL4eeMrBhBIC9JfcIwhiFz9HxaftlLdTKp5nhlRPa2NBvzC8aka7XNqAq1ORjuEeD6jTuktiIv57JV
*/