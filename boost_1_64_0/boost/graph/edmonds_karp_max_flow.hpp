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
gqXxbyUab/FmQ5bFrtsgo811ji8JdkgbxNTRQ8t6p5lwnq53Hk4NuGIDprZxJ1u8pCbj1xSLF+PL2xDC2tvi8Ik79spMDvLmamK5gKRFX3zb6izqvRz7fidZKGZpQKXH8oV7qZLCOq4kkKEWrxE7L8a6qX6JjlxlbC0Le2fEeVbGIzFuGXL29HWOWlnFK3XtKA1BUF8drWGd9udhK0xfjXexPRurN/ydFM4DumNJSmejnpoaIxXd0p0RS0MOvuTP3KoO9zcl+QqNnHkWd3H8Jn9elsm7G2BIJXWtwRJj/XR4e875wRVYncznwTgzsTpDzZrq1oCmuUY4o/qr1rjOudhTDWoOh5DfMmGwgq1+ofngSW33KNGw5oNnxFGo+2M9wVGj12I+hVI9rLV6qqa+mhFZt32HFKXncusMNhse1Ddw628jOCU8U8xFSfoGR7fB4xLHtWULKo9boH/KabllNa1lrdVFcuueYwNNG1egl+aXymmiterccTImq85vcF75Kf17qbNZ1VWqjUmlYpU5QOrq+LXOmzWodPxcIQe/Ct2Z7584uMS9Q6hciozcye8w+e5tbyiKq9W4JKfMg9XzOmRbpSpvch5STyWubDqXcF2c7CvKmxxOO1F/TFwpJb9eNvoKvVbuhM2vk/yekVQi8/D50rM2NdQUO3f0rFVtyWUNNTVRtU3p2BH9mdrlKsmq6pL6qMRkXGFbPSGUXdsqX/fg5Vij25PLa5o31Tf61MA4J15NmzaJdyvqGyWkH3JiUdh4bn1zU+Mmie1p66Q/Wu/E4bM6PVfVtJGcf0v2AlzeZGKhxjnPE/TVm1sl7Pklzg0/ZTHYe5JKWxvy10WdKpXPXZ+/dLgVelps6eZG3UMWuqfh+x3NafXNrZvXNaxp3KLXcG5IXtNYp5OiurBNJsQc5xI6fedCfbK8M646Y3SOqsv89PEodWFicQugqXlpja7+JWwQ2CK6Amc71MaaZo871/F3pXOjGXkk5S4v6VSpbltLapplylqSeoPEVqqKhOKgQCjcLJFipYbskpTXYgrMukTHCpEBghgnZStkQrCoxrHICktXFa7wakiukjm9DXWSAouUTO06V4Wqxc4vffJriaPVO8hOcjg9+5yqKitlFiEqvW+tzPe4KSYuTssvXbPK2fg5f2G267cSl+s2OD1q0/rKWskfJfONG3R1U7OUzFQ4F1ipzaq2pqlW3Kooa0lXK3m5Ppefodzx3n6Ka0ud58RVY5PMOKsaKb1i6ShpJmoaZT6+2gktfhyj9BS3DvEVDt/o/GxU0pjJHoMala8qz15fJ8/LnwRSZ9++qpLQFatKHbYSJUc76pVa5/jQ2iRxOk/V6gtITxWNgy8UH9v0AETWHFSrnEOQWKhLHff63YmqUgJSLS3WBqk40tGdW8sFo2fLkw1NW8R1ZJSblpYN65yVsy2qtrZB39vUrmr1Baf7qXP03RhN8rT7rqvlrdofN/4ShAZ1mJKRgtxVeLb6pH5ug8pWuj+TS5P2V94Frs1K9xiSYkqdq2pJuSOVPmwpSXyBqtWpcLGq1fX/MlXbIg2I2O5yT4lk8OWqlvuuClVlg1apUlWp3a5VTn+7SVvvZ6tK3GUorg7X6zTr5IVbnEUpybvjlBgUFFajqvFbFqUWWi6aZCbemVFzWhun7Pr3jKGppT1QB8s7nS16rbq4zBSkf6hcJ4R1TlzlKemSaqS0m931euZ+gqp0CGchYJOMNnQ6ZSndgxGSWAE9wQ1nqzykTvR/V9Y4uaJfXe6+p9ZNnSR5S7Sy0kkHKd/JLiJVZkho3WdO9mOo5wtZKGtwAk7cAidiU710dp1ql9L+K3OPun71OP0uXeh0SDY=
*/