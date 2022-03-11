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