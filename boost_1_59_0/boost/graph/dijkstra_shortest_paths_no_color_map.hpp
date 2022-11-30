//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2009 Trustees of Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Michael Hansen
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_DIJKSTRA_NO_COLOR_MAP_HPP
#define BOOST_GRAPH_DIJKSTRA_NO_COLOR_MAP_HPP

#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/relax.hpp>
#include <boost/graph/detail/d_ary_heap.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/iteration_macros.hpp>

namespace boost
{

// No init version
template < typename Graph, typename DijkstraVisitor, typename PredecessorMap,
    typename DistanceMap, typename WeightMap, typename VertexIndexMap,
    typename DistanceCompare, typename DistanceWeightCombine,
    typename DistanceInfinity, typename DistanceZero >
void dijkstra_shortest_paths_no_color_map_no_init(const Graph& graph,
    typename graph_traits< Graph >::vertex_descriptor start_vertex,
    PredecessorMap predecessor_map, DistanceMap distance_map,
    WeightMap weight_map, VertexIndexMap index_map,
    DistanceCompare distance_compare,
    DistanceWeightCombine distance_weight_combine,
    DistanceInfinity distance_infinity, DistanceZero distance_zero,
    DijkstraVisitor visitor)
{
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename property_traits< DistanceMap >::value_type Distance;

    typedef indirect_cmp< DistanceMap, DistanceCompare >
        DistanceIndirectCompare;
    DistanceIndirectCompare distance_indirect_compare(
        distance_map, distance_compare);

    // Default - use d-ary heap (d = 4)
    typedef detail::vertex_property_map_generator< Graph, VertexIndexMap,
        std::size_t >
        IndexInHeapMapHelper;
    typedef typename IndexInHeapMapHelper::type IndexInHeapMap;
    typedef d_ary_heap_indirect< Vertex, 4, IndexInHeapMap, DistanceMap,
        DistanceCompare >
        VertexQueue;

    boost::scoped_array< std::size_t > index_in_heap_map_holder;
    IndexInHeapMap index_in_heap = IndexInHeapMapHelper::build(
        graph, index_map, index_in_heap_map_holder);
    VertexQueue vertex_queue(distance_map, index_in_heap, distance_compare);

    // Add vertex to the queue
    vertex_queue.push(start_vertex);

    // Starting vertex will always be the first discovered vertex
    visitor.discover_vertex(start_vertex, graph);

    while (!vertex_queue.empty())
    {
        Vertex min_vertex = vertex_queue.top();
        vertex_queue.pop();

        visitor.examine_vertex(min_vertex, graph);

        // Check if any other vertices can be reached
        Distance min_vertex_distance = get(distance_map, min_vertex);

        if (!distance_compare(min_vertex_distance, distance_infinity))
        {
            // This is the minimum vertex, so all other vertices are unreachable
            return;
        }

        // Examine neighbors of min_vertex
        BGL_FORALL_OUTEDGES_T(min_vertex, current_edge, graph, Graph)
        {
            visitor.examine_edge(current_edge, graph);

            // Check if the edge has a negative weight
            if (distance_compare(get(weight_map, current_edge), distance_zero))
            {
                boost::throw_exception(negative_edge());
            }

            // Extract the neighboring vertex and get its distance
            Vertex neighbor_vertex = target(current_edge, graph);
            Distance neighbor_vertex_distance
                = get(distance_map, neighbor_vertex);
            bool is_neighbor_undiscovered = !distance_compare(
                neighbor_vertex_distance, distance_infinity);

            // Attempt to relax the edge
            bool was_edge_relaxed
                = relax_target(current_edge, graph, weight_map, predecessor_map,
                    distance_map, distance_weight_combine, distance_compare);

            if (was_edge_relaxed)
            {
                visitor.edge_relaxed(current_edge, graph);
                if (is_neighbor_undiscovered)
                {
                    visitor.discover_vertex(neighbor_vertex, graph);
                    vertex_queue.push(neighbor_vertex);
                }
                else
                {
                    vertex_queue.update(neighbor_vertex);
                }
            }
            else
            {
                visitor.edge_not_relaxed(current_edge, graph);
            }

        } // end out edge iteration

        visitor.finish_vertex(min_vertex, graph);
    } // end while queue not empty
}

// Full init version
template < typename Graph, typename DijkstraVisitor, typename PredecessorMap,
    typename DistanceMap, typename WeightMap, typename VertexIndexMap,
    typename DistanceCompare, typename DistanceWeightCombine,
    typename DistanceInfinity, typename DistanceZero >
void dijkstra_shortest_paths_no_color_map(const Graph& graph,
    typename graph_traits< Graph >::vertex_descriptor start_vertex,
    PredecessorMap predecessor_map, DistanceMap distance_map,
    WeightMap weight_map, VertexIndexMap index_map,
    DistanceCompare distance_compare,
    DistanceWeightCombine distance_weight_combine,
    DistanceInfinity distance_infinity, DistanceZero distance_zero,
    DijkstraVisitor visitor)
{
    // Initialize vertices
    BGL_FORALL_VERTICES_T(current_vertex, graph, Graph)
    {
        visitor.initialize_vertex(current_vertex, graph);

        // Default all distances to infinity
        put(distance_map, current_vertex, distance_infinity);

        // Default all vertex predecessors to the vertex itself
        put(predecessor_map, current_vertex, current_vertex);
    }

    // Set distance for start_vertex to zero
    put(distance_map, start_vertex, distance_zero);

    // Pass everything on to the no_init version
    dijkstra_shortest_paths_no_color_map_no_init(graph, start_vertex,
        predecessor_map, distance_map, weight_map, index_map, distance_compare,
        distance_weight_combine, distance_infinity, distance_zero, visitor);
}

namespace detail
{

    // Handle defaults for PredecessorMap, DistanceCompare,
    // DistanceWeightCombine, DistanceInfinity and DistanceZero
    template < typename Graph, typename DistanceMap, typename WeightMap,
        typename VertexIndexMap, typename Params >
    inline void dijkstra_no_color_map_dispatch2(const Graph& graph,
        typename graph_traits< Graph >::vertex_descriptor start_vertex,
        DistanceMap distance_map, WeightMap weight_map,
        VertexIndexMap index_map, const Params& params)
    {
        // Default for predecessor map
        dummy_property_map predecessor_map;

        typedef
            typename property_traits< DistanceMap >::value_type DistanceType;
        DistanceType inf = choose_param(get_param(params, distance_inf_t()),
            (std::numeric_limits< DistanceType >::max)());
        dijkstra_shortest_paths_no_color_map(graph, start_vertex,
            choose_param(
                get_param(params, vertex_predecessor), predecessor_map),
            distance_map, weight_map, index_map,
            choose_param(get_param(params, distance_compare_t()),
                std::less< DistanceType >()),
            choose_param(get_param(params, distance_combine_t()),
                std::plus< DistanceType >()),
            inf,
            choose_param(get_param(params, distance_zero_t()), DistanceType()),
            choose_param(get_param(params, graph_visitor),
                make_dijkstra_visitor(null_visitor())));
    }

    template < typename Graph, typename DistanceMap, typename WeightMap,
        typename IndexMap, typename Params >
    inline void dijkstra_no_color_map_dispatch1(const Graph& graph,
        typename graph_traits< Graph >::vertex_descriptor start_vertex,
        DistanceMap distance_map, WeightMap weight_map, IndexMap index_map,
        const Params& params)
    {
        // Default for distance map
        typedef typename property_traits< WeightMap >::value_type DistanceType;
        typename std::vector< DistanceType >::size_type vertex_count
            = is_default_param(distance_map) ? num_vertices(graph) : 1;

        std::vector< DistanceType > default_distance_map(vertex_count);

        detail::dijkstra_no_color_map_dispatch2(graph, start_vertex,
            choose_param(distance_map,
                make_iterator_property_map(default_distance_map.begin(),
                    index_map, default_distance_map[0])),
            weight_map, index_map, params);
    }
} // namespace detail

// Named parameter version
template < typename Graph, typename Param, typename Tag, typename Rest >
inline void dijkstra_shortest_paths_no_color_map(const Graph& graph,
    typename graph_traits< Graph >::vertex_descriptor start_vertex,
    const bgl_named_params< Param, Tag, Rest >& params)
{
    // Default for edge weight and vertex index map is to ask for them
    // from the graph. Default for the visitor is null_visitor.
    detail::dijkstra_no_color_map_dispatch1(graph, start_vertex,
        get_param(params, vertex_distance),
        choose_const_pmap(get_param(params, edge_weight), graph, edge_weight),
        choose_const_pmap(get_param(params, vertex_index), graph, vertex_index),
        params);
}

} // namespace boost

#endif // BOOST_GRAPH_DIJKSTRA_NO_COLOR_MAP_HPP

/* dijkstra_shortest_paths_no_color_map.hpp
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
*/