//=======================================================================
// Copyright 2000 University of Notre Dame.
// Authors: Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_EDMONDS_KARP_MAX_FLOW_HPP
#define BOOST_GRAPH_EDMONDS_KARP_MAX_FLOW_HPP

#include <boost/config.hpp>
#include <vector>
#include <algorithm> // for std::min and std::max
#include <boost/config.hpp>
#include <boost/pending/queue.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/breadth_first_search.hpp>

namespace boost
{

// The "labeling" algorithm from "Network Flows" by Ahuja, Magnanti,
// Orlin.  I think this is the same as or very similar to the original
// Edmonds-Karp algorithm.  This solves the maximum flow problem.

namespace detail
{

    template < class Graph, class ResCapMap >
    filtered_graph< Graph, is_residual_edge< ResCapMap > > residual_graph(
        Graph& g, ResCapMap residual_capacity)
    {
        return filtered_graph< Graph, is_residual_edge< ResCapMap > >(
            g, is_residual_edge< ResCapMap >(residual_capacity));
    }

    template < class Graph, class PredEdgeMap, class ResCapMap,
        class RevEdgeMap >
    inline void augment(Graph& g,
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

template < class Graph, class CapacityEdgeMap, class ResidualCapacityEdgeMap,
    class ReverseEdgeMap, class ColorMap, class PredEdgeMap >
typename property_traits< CapacityEdgeMap >::value_type edmonds_karp_max_flow(
    Graph& g, typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink, CapacityEdgeMap cap,
    ResidualCapacityEdgeMap res, ReverseEdgeMap rev, ColorMap color,
    PredEdgeMap pred)
{
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;

    typename graph_traits< Graph >::vertex_iterator u_iter, u_end;
    typename graph_traits< Graph >::out_edge_iterator ei, e_end;
    for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end; ++u_iter)
        for (boost::tie(ei, e_end) = out_edges(*u_iter, g); ei != e_end; ++ei)
            put(res, *ei, get(cap, *ei));

    put(color, sink, Color::gray());
    while (get(color, sink) != Color::white())
    {
        boost::queue< vertex_t > Q;
        breadth_first_search(detail::residual_graph(g, res), src, Q,
            make_bfs_visitor(record_edge_predecessors(pred, on_tree_edge())),
            color);
        if (get(color, sink) != Color::white())
            detail::augment(g, src, sink, pred, res, rev);
    } // while

    typename property_traits< CapacityEdgeMap >::value_type flow = 0;
    for (boost::tie(ei, e_end) = out_edges(src, g); ei != e_end; ++ei)
        flow += (get(cap, *ei) - get(res, *ei));
    return flow;
} // edmonds_karp_max_flow()

namespace detail
{
    //-------------------------------------------------------------------------
    // Handle default for color property map

    // use of class here is a VC++ workaround
    template < class ColorMap > struct edmonds_karp_dispatch2
    {
        template < class Graph, class PredMap, class P, class T, class R >
        static typename edge_capacity_value< Graph, P, T, R >::type apply(
            Graph& g, typename graph_traits< Graph >::vertex_descriptor src,
            typename graph_traits< Graph >::vertex_descriptor sink,
            PredMap pred, const bgl_named_params< P, T, R >& params,
            ColorMap color)
        {
            return edmonds_karp_max_flow(g, src, sink,
                choose_const_pmap(
                    get_param(params, edge_capacity), g, edge_capacity),
                choose_pmap(get_param(params, edge_residual_capacity), g,
                    edge_residual_capacity),
                choose_const_pmap(
                    get_param(params, edge_reverse), g, edge_reverse),
                color, pred);
        }
    };
    template <> struct edmonds_karp_dispatch2< param_not_found >
    {
        template < class Graph, class PredMap, class P, class T, class R >
        static typename edge_capacity_value< Graph, P, T, R >::type apply(
            Graph& g, typename graph_traits< Graph >::vertex_descriptor src,
            typename graph_traits< Graph >::vertex_descriptor sink,
            PredMap pred, const bgl_named_params< P, T, R >& params,
            param_not_found)
        {
            typedef
                typename graph_traits< Graph >::vertices_size_type size_type;
            size_type n = is_default_param(get_param(params, vertex_color))
                ? num_vertices(g)
                : 1;
            std::vector< default_color_type > color_vec(n);
            return edmonds_karp_max_flow(g, src, sink,
                choose_const_pmap(
                    get_param(params, edge_capacity), g, edge_capacity),
                choose_pmap(get_param(params, edge_residual_capacity), g,
                    edge_residual_capacity),
                choose_const_pmap(
                    get_param(params, edge_reverse), g, edge_reverse),
                make_iterator_property_map(color_vec.begin(),
                    choose_const_pmap(
                        get_param(params, vertex_index), g, vertex_index),
                    color_vec[0]),
                pred);
        }
    };

    //-------------------------------------------------------------------------
    // Handle default for predecessor property map

    // use of class here is a VC++ workaround
    template < class PredMap > struct edmonds_karp_dispatch1
    {
        template < class Graph, class P, class T, class R >
        static typename edge_capacity_value< Graph, P, T, R >::type apply(
            Graph& g, typename graph_traits< Graph >::vertex_descriptor src,
            typename graph_traits< Graph >::vertex_descriptor sink,
            const bgl_named_params< P, T, R >& params, PredMap pred)
        {
            typedef typename get_param_type< vertex_color_t,
                bgl_named_params< P, T, R > >::type C;
            return edmonds_karp_dispatch2< C >::apply(
                g, src, sink, pred, params, get_param(params, vertex_color));
        }
    };
    template <> struct edmonds_karp_dispatch1< param_not_found >
    {

        template < class Graph, class P, class T, class R >
        static typename edge_capacity_value< Graph, P, T, R >::type apply(
            Graph& g, typename graph_traits< Graph >::vertex_descriptor src,
            typename graph_traits< Graph >::vertex_descriptor sink,
            const bgl_named_params< P, T, R >& params, param_not_found)
        {
            typedef
                typename graph_traits< Graph >::edge_descriptor edge_descriptor;
            typedef
                typename graph_traits< Graph >::vertices_size_type size_type;
            size_type n
                = is_default_param(get_param(params, vertex_predecessor))
                ? num_vertices(g)
                : 1;
            std::vector< edge_descriptor > pred_vec(n);

            typedef typename get_param_type< vertex_color_t,
                bgl_named_params< P, T, R > >::type C;
            return edmonds_karp_dispatch2< C >::apply(g, src, sink,
                make_iterator_property_map(pred_vec.begin(),
                    choose_const_pmap(
                        get_param(params, vertex_index), g, vertex_index),
                    pred_vec[0]),
                params, get_param(params, vertex_color));
        }
    };

} // namespace detail

template < class Graph, class P, class T, class R >
typename detail::edge_capacity_value< Graph, P, T, R >::type
edmonds_karp_max_flow(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink,
    const bgl_named_params< P, T, R >& params)
{
    typedef typename get_param_type< vertex_predecessor_t,
        bgl_named_params< P, T, R > >::type Pred;
    return detail::edmonds_karp_dispatch1< Pred >::apply(
        g, src, sink, params, get_param(params, vertex_predecessor));
}

template < class Graph >
typename property_traits<
    typename property_map< Graph, edge_capacity_t >::const_type >::value_type
edmonds_karp_max_flow(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor src,
    typename graph_traits< Graph >::vertex_descriptor sink)
{
    bgl_named_params< int, buffer_param_t > params(0);
    return edmonds_karp_max_flow(g, src, sink, params);
}

} // namespace boost

#endif // BOOST_GRAPH_EDMONDS_KARP_MAX_FLOW_HPP

/* edmonds_karp_max_flow.hpp
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
*/