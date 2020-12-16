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
bJfPkmb7e6BTQ98DbUefFvt7pqYc9oa+Wzo59N3SYfSTQt85bUcfMd8ttc/RHmq+v2nfg3pgnO9CHoT73I/Z5e2NlNjfA3ozxXz/19qfmhnnu5CzzHch7XL7l5TY91P/Ff9Hmuzve/4txf6+57fMenHs72buH+e7mQeY72bG+q6HSMHBdmw4hXYsdO/rYaF7X0eQr6XEbsdeh6cdM98jTg59jzhKPphzWOCi0PewKsCZra6cFud7svvE+Z7s9FHfkw3d39tqn7eYGed7phnhc1LIg833Q+192oeoD77j+YF98P9rH3jju333cnzn/YXd7Po49v+D1GdkAbIfvbnfTUv/PqpB9EPI1EpXZiGLkFXIdmQnshc5iFRVrsxEFiGjyKuQVYQjiuyDH0QOI9U6V05EEk/SwcR31D14ieBq77t8oXvuksGEg/2MhIf2SgXCtR+4o9reD0p6GrzT1pt0Tgndg5UaujdrQuieuUjo3ripoXvgpnnued/+3vvAB3jPgw8M3bM00dwrZuMo+rTQvWdpoXui0s29Z+DQPUiTwQO8H8w9ZT7uwP0Uc0+ZjZ/lebApBwep2H8v41556Q02XA12TZznU2vs5yM19vMZoeczweaeMXASOBucDM4Bx/t+VfZF4z6cME4l5KnHjru97+3Viy7oHXdp/wuda17/4hd2rf7xGRvPuKrulwtnPHn93AOPu6dxz8KPn7PPjx97deD6muTmy7q6t/xz7V/2VK65+LIn1hYnJI5T48Sf7/ztc/dN2bZ2d8rfzvpkVektza/VHnLB1Sd97ba0K3c8vOQwlfRo1uQDO+6desQR13/h+nnRhKc+dW1xYufIpvK5Rz554yWnd81PmKVeWvb4SX/9+RMfXXrf7cde0znhym+//UbbecdFvzplydn71B3+yAxx8mKk+5ZJz1xUt+XyxvN/f9fisovffuzQF370vcb236s1V/+svyYhc8VIyw/OKj563SFLI5PeuP+Fise3z/j4VV+5+xPfWFJRmDfxwXEJmdOm3jF/7VdPnjr5jB3zKp9JWJ28bMeMK2457ZSet7/76Jt7IvclZGZ8/egvn/G7vkf3FJ93zKzZxc+ufunPp75206a3l09/cXnpjy6aLe1NKP8qQvlXF8q/tlD+bQ/l385Q/nXVhOo3OMUr3+BUr/yDJ3j1F5wGHgGng1Nr7f3gGeBJ4Kxauz7lgKfELU8JZzrl6VOfUrt35g+dnH/Gs8kP9d+w+MGLN//1R9dfd/aLC/OOznjrrDUro3te/t5lOWmZN/QWbmlcW7X2zVe+dOiDVz593If3PeSVE69veunbd01rP6jsJ9GXZp27+Jfz9i88/KJ3Hjp9wfi50046rO2VaScPfvbvG1efuGpZwoo5vasPueWqp/PmzumI7Lnoc5+Zcuijr++ZfVPZGrdAfqr92F2nXFlxx2fUzL/+6cPD2f3J+/6++6Vr5qw+svuxnJ+99JeBkw+J/u2Tbz7z8Kmnbt3+1tCCyZ+Yc/Xrb91x1H3X/u6+ly7fWrqoeuEF9zycdf+q3+an//rbD2xKnNN82F2bkt+aOWHe3DNve7X1id8UXXHCxPEnr3wuctFLZ72x/LrHXpn6g8aX3/znFZuvypz34M1LX5M68fcd37zkB08c/f2anx33xhfvK61Lf/S15yYnXLf6rS27l37t/m8/O/Po33enPHzGDdMuf2JD2pNzd9R+Zsfu/b554Zsn9e+/41v3PP2IePHMiuTXky5dtS7/D923f+nS0tkPfPYTN6XvM+nCnDOemfuJyS/s9+WcF16f9ZNLLvnjP7K2ZM4/Z3b/O2/P/f4lt176wBt3PnDjlC+emJA7Oe+aLw4=
*/