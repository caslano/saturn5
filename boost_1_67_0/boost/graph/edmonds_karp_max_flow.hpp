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