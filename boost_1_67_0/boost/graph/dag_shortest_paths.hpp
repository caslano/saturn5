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