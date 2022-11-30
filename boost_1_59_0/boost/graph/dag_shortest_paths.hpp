//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_DAG_SHORTEST_PATHS_HPP
#define BOOST_GRAPH_DAG_SHORTEST_PATHS_HPP

#include <boost/graph/topological_sort.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

// single-source shortest paths for a Directed Acyclic Graph (DAG)

namespace boost
{

// Initalize distances and call depth first search
template < class VertexListGraph, class DijkstraVisitor, class DistanceMap,
    class WeightMap, class ColorMap, class PredecessorMap, class Compare,
    class Combine, class DistInf, class DistZero >
inline void dag_shortest_paths(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    DistanceMap distance, WeightMap weight, ColorMap color, PredecessorMap pred,
    DijkstraVisitor vis, Compare compare, Combine combine, DistInf inf,
    DistZero zero)
{
    typedef typename graph_traits< VertexListGraph >::vertex_descriptor Vertex;
    std::vector< Vertex > rev_topo_order;
    rev_topo_order.reserve(num_vertices(g));

    // Call 'depth_first_visit', not 'topological_sort', because we don't
    // want to traverse the entire graph, only vertices reachable from 's',
    // and 'topological_sort' will traverse everything. The logic below
    // is the same as for 'topological_sort', only we call 'depth_first_visit'
    // and 'topological_sort' calls 'depth_first_search'.
    topo_sort_visitor< std::back_insert_iterator< std::vector< Vertex > > >
        topo_visitor(std::back_inserter(rev_topo_order));
    depth_first_visit(g, s, topo_visitor, color);

    typename graph_traits< VertexListGraph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        put(distance, *ui, inf);
        put(pred, *ui, *ui);
    }

    put(distance, s, zero);
    vis.discover_vertex(s, g);
    typename std::vector< Vertex >::reverse_iterator i;
    for (i = rev_topo_order.rbegin(); i != rev_topo_order.rend(); ++i)
    {
        Vertex u = *i;
        vis.examine_vertex(u, g);
        typename graph_traits< VertexListGraph >::out_edge_iterator e, e_end;
        for (boost::tie(e, e_end) = out_edges(u, g); e != e_end; ++e)
        {
            vis.discover_vertex(target(*e, g), g);
            bool decreased
                = relax(*e, g, weight, pred, distance, combine, compare);
            if (decreased)
                vis.edge_relaxed(*e, g);
            else
                vis.edge_not_relaxed(*e, g);
        }
        vis.finish_vertex(u, g);
    }
}

namespace detail
{

    // Defaults are the same as Dijkstra's algorithm

    // Handle Distance Compare, Combine, Inf and Zero defaults
    template < class VertexListGraph, class DijkstraVisitor, class DistanceMap,
        class WeightMap, class ColorMap, class IndexMap, class Params >
    inline void dag_sp_dispatch2(const VertexListGraph& g,
        typename graph_traits< VertexListGraph >::vertex_descriptor s,
        DistanceMap distance, WeightMap weight, ColorMap color, IndexMap /*id*/,
        DijkstraVisitor vis, const Params& params)
    {
        typedef typename property_traits< DistanceMap >::value_type D;
        dummy_property_map p_map;
        D inf = choose_param(get_param(params, distance_inf_t()),
            (std::numeric_limits< D >::max)());
        dag_shortest_paths(g, s, distance, weight, color,
            choose_param(get_param(params, vertex_predecessor), p_map), vis,
            choose_param(
                get_param(params, distance_compare_t()), std::less< D >()),
            choose_param(
                get_param(params, distance_combine_t()), closed_plus< D >(inf)),
            inf, choose_param(get_param(params, distance_zero_t()), D()));
    }

    // Handle DistanceMap and ColorMap defaults
    template < class VertexListGraph, class DijkstraVisitor, class DistanceMap,
        class WeightMap, class ColorMap, class IndexMap, class Params >
    inline void dag_sp_dispatch1(const VertexListGraph& g,
        typename graph_traits< VertexListGraph >::vertex_descriptor s,
        DistanceMap distance, WeightMap weight, ColorMap color, IndexMap id,
        DijkstraVisitor vis, const Params& params)
    {
        typedef typename property_traits< WeightMap >::value_type T;
        typename std::vector< T >::size_type n;
        n = is_default_param(distance) ? num_vertices(g) : 1;
        std::vector< T > distance_map(n);
        n = is_default_param(color) ? num_vertices(g) : 1;
        std::vector< default_color_type > color_map(n);

        dag_sp_dispatch2(g, s,
            choose_param(distance,
                make_iterator_property_map(
                    distance_map.begin(), id, distance_map[0])),
            weight,
            choose_param(color,
                make_iterator_property_map(
                    color_map.begin(), id, color_map[0])),
            id, vis, params);
    }

} // namespace detail

template < class VertexListGraph, class Param, class Tag, class Rest >
inline void dag_shortest_paths(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    const bgl_named_params< Param, Tag, Rest >& params)
{
    // assert that the graph is directed...
    null_visitor null_vis;
    detail::dag_sp_dispatch1(g, s, get_param(params, vertex_distance),
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        get_param(params, vertex_color),
        choose_const_pmap(get_param(params, vertex_index), g, vertex_index),
        choose_param(
            get_param(params, graph_visitor), make_dijkstra_visitor(null_vis)),
        params);
}

} // namespace boost

#endif // BOOST_GRAPH_DAG_SHORTEST_PATHS_HPP

/* dag_shortest_paths.hpp
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
*/