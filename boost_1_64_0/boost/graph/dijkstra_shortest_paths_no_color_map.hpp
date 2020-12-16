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
71CzDo5BHURbkkDqDVBOXy1RBx72qwt4jsAe2wJRz/gx8pZ+edRON5QVwdxpWOzKJiv2BFnWdhT5j+DQzom/8KvrcCd63QG/Vp/BonLwpOW3reY7u92JHVutx6oFagLK0AT0vTzzQewvjMacdbZ+Zw3q7oIM+TZ57Ri1ZMebfJXdb/bNqQ3mzPFNzMn6XpPg/5pitQZtzkqs6T0L8mwxyus8lFdZd1qoy+8YlF+Ej/kK5K+Z3zRrIgmrHQ0pylP0QcKFOeoNeEKflXd1qWWOFm3VhINWTOifWXcIF+Sod+Lpplun2hvmMkeYpaNy1Bo899OdURt3o836jQkP8vEI7PwQzyW6s9XMX7TtoeIcFcOz7JTYcarpd5kad8HyG9XfuBuEnbwS486lzpq2HN85+oLsi6A9QvrlF+VwrVQ51bQf0P0itvdF0oc48pRfPYTnDN041JwzZt9xfqGafxXxuTwabktkrWfwH371VzzDdOtUO8MYuuZX+X8zYdhqj70D0Dtp2zNqY++yZW/4SdTTv/tV+LTYc6jd/q2EfteTxj+qM/07Dre/sP1zqN324tf96v3XjT2n2vQPKQ/j6fnYENKjA89UurHVnrmaZrpBWCvzc1QnHobjVLNMTECZwJwh+qgYI9h9VOlXjkK/EowUoV+J/mXzxCHTD1F6rjLH9EOcal9XkeqCfzPuk77LYNEAZvu4xiB9tUk56kt4LjFOthpuXx5QL0df9YX6PbpzsEfDqn+TL45RF7tLMB6ag/HQbDUHe0XmYAxsRkTs7zyg2J7dNQrys1i1oZ27dwLixvknh5qybqKa5pkDtdYOKiDrpmftyz1m9o8UuNYb47swl4JHz22JHHbrYQ3Xr+cfzHzckVfnqLN4rjJuDjXaZ58aW5+ef7LWYYK7c1QdnuAZse9UY602X5WjzJSjzJTXjDd7To7D/Kd4wnTjVFvjzwNZx5/xXO5D8O1X9sy8bd5m5i+q0Oed600njl1HI69KkFf43WznlLW2OYZrWvbapsQHcwbe+HDOgHOsxSjj1v4MymT2eyDXEBbmTLRsw5xXEfTeAr03Q+9NiOOdqtSsfet1koCajXH1bMRjduKW4QmD4wbGxkvbfDMCWDvF2j7CmFEjcxAD0uedjDlx1K/JkYCeJxmy8sXad6SO5qhn4jn+BUljp5rpgCeixxCYn6lxpIOYlWQ1S5eR8Gdy1DY8nJ91qrn34QUqvWYi67+6n4o2YubVCPrJL1EDsNt4Mkc1nGX7cvmloj6N5yVnxU+v2uFGz+uVrKlIlanZaF+CaEenrr7loMxVDuqVE6XYhnD+bw/q5Pbsc4w56XwqQ56MlTkz1DuMXyFXsGYx6wLenOVA5l7rYd/vk3UR2S6Zi3nNMp63Voj1Dm1e5FNFHaDOC7RpgQTW3vU4PGHNzRVpNzMxXwA97e6T/0R9Ubl6z6JQ/A/Tb+1fPtqSGszp6T4i8qMkkR8u0muOaAPGIJ/HQK6m/Rrvz1ULcnLV0SKLdBv2lRWqsgge1MOyMo6XJuShD3Ia/a1TSuqG+F+kSmrQrxL/C+A/qPvCWfbDNmPvnvOsuXVQN+r9fXgGL+Wo20GVPnEXu8xxukZ4TZO+UmNVPK4vl9b7wn5l74f9xN/yVNtizC8/ZOvFn5ev1mGeIPwVW28P9O6CLNV7As0+2qZ82eM5yWHvGvTCsDdwztZ7qDlfXcOcyTWHvUehF4JeqcNefgvCLYNbh72KFriFf4cceuugNwi9I1+19fqg9zDk8AMOewegNwR7cYfeSeg9AD3leN+HobcM7zvs8O9J6FVA7zGH2ylod4OI30h/C2/Nt9KvyeJt5EpyITmJ3Pc8i4fJo+Q=
*/