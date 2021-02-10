//=======================================================================
// Copyright 2013 University of Warsaw.
// Authors: Piotr Wygocki
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_AUGMENT_HPP
#define BOOST_GRAPH_AUGMENT_HPP

#include <boost/graph/filtered_graph.hpp>

namespace boost
{
namespace detail
{

    template < class Graph, class ResCapMap >
    filtered_graph< const Graph, is_residual_edge< ResCapMap > > residual_graph(
        const Graph& g, ResCapMap residual_capacity)
    {
        return filtered_graph< const Graph, is_residual_edge< ResCapMap > >(
            g, is_residual_edge< ResCapMap >(residual_capacity));
    }

    template < class Graph, class PredEdgeMap, class ResCapMap,
        class RevEdgeMap >
    inline void augment(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor src,
        typename graph_traits< Graph >::vertex_descriptor sink, PredEdgeMap p,
        ResCapMap residual_capacity, RevEdgeMap reverse_edge)
    {
        typename graph_traits< Graph >::edge_descriptor e;
        typename graph_traits< Graph >::vertex_descriptor u;
        typedef typename property_traits< ResCapMap >::value_type FlowValue;

        // find minimum residual capacity along the augmenting path
        FlowValue delta = (std::numeric_limits< FlowValue >::max)();
        e = get(p, sink);
        do
        {
            BOOST_USING_STD_MIN();
            delta = min BOOST_PREVENT_MACRO_SUBSTITUTION(
                delta, get(residual_capacity, e));
            u = source(e, g);
            e = get(p, u);
        } while (u != src);

        // push delta units of flow along the augmenting path
        e = get(p, sink);
        do
        {
            put(residual_capacity, e, get(residual_capacity, e) - delta);
            put(residual_capacity, get(reverse_edge, e),
                get(residual_capacity, get(reverse_edge, e)) + delta);
            u = source(e, g);
            e = get(p, u);
        } while (u != src);
    }

} // namespace detail
} // namespace boost

#endif /* BOOST_GRAPH_AUGMENT_HPP */

/* augment.hpp
ewES2cUZEUGchT4J6CMjKfMYf9Q0EppKEm8AHYj7XEggmEkeRxfAmxHJ0q1AGsiehiIm9JHykK6BEZUkkDIRP3e7XpaGIH3Xjz3R9fLjXwRyW5zkDoTY0h2JE0lkTDLBOgR3dsg29vkGn6AQACbZOuQi6JTSAKvI78YpESwMkRbgcSa02IzYRj0d3EYSkJhLfIg4EsjqKYi3tY2gR6SyydIIGIEeYJMfg5o7JIMgStVmdfKchdGpUvBB05Ty+iSOQBhyPLDJxD4mayq46JAPE2c8Xznkw2C5HMycOzK/JoPZHRK7mcxGYHoOzFLCnpOUCWCeEr5NQs58w/P7fbpHR6945IWZz8gxWs8VTGbJRXCMCxuic4Z/Mh68t9zp5C0kjCt3fFoivQn5Wojg6iL4tQl0xUYmaoWF7cTyRwvJrn60Ee62013ZlvthPr0GglVyT3G4UUj7xPIF9SwoRuCFR981Jyo3AaHAq/jnjBGl4u9sRrlLGOZ9FmVb8p8jgvzc2dy1nYFjkV/IOSQd0j0jK8wZG/Co44g9S1tSyY7Be4mAkESnUx4cxVAngKimYjvzBVDodfLseoZREsWQKqJ7IpBEBx5xIlSMKACEuBdwTcWQmcwmTqeSO4HMNU+FNAiQumDX+XA+m1lDp8Id
*/