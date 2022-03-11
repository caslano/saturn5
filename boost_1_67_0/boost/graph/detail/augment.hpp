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
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
*/