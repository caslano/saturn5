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
XC/g4V6izrzOC1RlVuGMDe/v1uI/LWsxaLvUvGRb1eNeloprq2oF4Jm9z8GgByoVRDwODtEk2zYvvsGAKIvgcg0NzEwGkL4IbBQyfCjUCkMLhRx2CaymoSN+aMD87v0T2cQw3cqGSS8koT+wg3iqyXh8V49MoiLMjdT9YQ2mJc8Eq3hPoVCWp4tJmRIJjMXyyfpYpuDRihe95CPjkZeOYTx5p/UFlCKQsi+duj+WLx0dWrLFQNg+hk4eRmetCBhwH4i0j08AMot8iSVUuyvh4XxeDgk7+c6/41QcCYr4OH33k22KuRBT2Mjk+g6xCPHYnbm8ImCggMMbJa/uTihryS+vCSK8qRI5GtMSyQILuPkW78x1kTozbrEhM+T2U/Y3Sp7zYkVG9DoWP1HBe3z39iYPAc3fk7ccswex5YUntGCatGZfIs+CMiFHj5HZPoffLewV2GEExjI+H0oJSQe2txSYelk/96NLFOZuJ0xs7cdGwt7jeGjdcmqSxSJEvVGaLWI9rzStrK2mkp2hjTGFpUgifk9A1V00QHgWqpVA7cmF+YvAO1S5Cl+4dLle84mESGMlOKogq/70H7i8ZP4KECzv003prB7iMHoJWsORaak+I/TIZ0gvWIdrUmVfMBouYh9KAGYwhTK0QoaP9VftV81PABCCrY6cNL/arNMftTeaf/ILSCmP81+WzT/5CYqG4Ucuj+TolhMew/ad
*/