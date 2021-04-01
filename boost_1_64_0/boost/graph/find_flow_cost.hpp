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
DJ/Wud9VKq7/8W3+kZ0egQaAX+EV5uz/clZhNcnx3C6Ne7RM8fSwXc+Utuvq51V304qVyb3PRz9fOy2wiYPdsXu/fSqaxY+6rwHN56KiidfV9gxah0oYCGcA9Ry78OSdnZYUbC5Ta9xptNa174SYiRe58LFlv4g1b6a3H3RXToWjVrgFLDTjFQBBpPfsAd4OkJKW0CBsypyUWyEEGWQgZzM6ivhkWOOLjXtmb+GWkwFO5QNDGOaFiRSrdIErMmbLAdTavY+c+XbDF3fGPYbC6epvDpHS0IjO0mmySviGRCXJZavsCNOSbdrbrbAyx2DWm2QyyIcet5VYeyc7Ac8JzT8FIPYuh2aKVMtmR/MyrswBEJcww6gpfSunvz0MG9HVFAb73t5lJ9XOVDCv4FcTYhmFwX8F4CTzC0mDXEMxyLeHIYVVyZyXl494wcOSSFbLcLNSmgWDblViVsrolEf4VWjyVne/pHs7daKdFYzs85VOasgI1Ahtc0den+UHdpot/Qo/EcJIYZqzLl+frAd0/xALldskU/3N/uOFKPKzhzHZZ870TsCTzBjJFQ==
*/