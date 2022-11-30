// Copyright 2004 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_BRANDES_BETWEENNESS_CENTRALITY_HPP
#define BOOST_GRAPH_BRANDES_BETWEENNESS_CENTRALITY_HPP

#include <stack>
#include <vector>
#include <boost/graph/overloading.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/relax.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/if.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>
#include <algorithm>

namespace boost
{

namespace detail
{
    namespace graph
    {

        /**
         * Customized visitor passed to Dijkstra's algorithm by Brandes'
         * betweenness centrality algorithm. This visitor is responsible for
         * keeping track of the order in which vertices are discovered, the
         * predecessors on the shortest path(s) to a vertex, and the number
         * of shortest paths.
         */
        template < typename Graph, typename WeightMap, typename IncomingMap,
            typename DistanceMap, typename PathCountMap >
        struct brandes_dijkstra_visitor : public bfs_visitor<>
        {
            typedef typename graph_traits< Graph >::vertex_descriptor
                vertex_descriptor;
            typedef
                typename graph_traits< Graph >::edge_descriptor edge_descriptor;

            brandes_dijkstra_visitor(
                std::stack< vertex_descriptor >& ordered_vertices,
                WeightMap weight, IncomingMap incoming, DistanceMap distance,
                PathCountMap path_count)
            : ordered_vertices(ordered_vertices)
            , weight(weight)
            , incoming(incoming)
            , distance(distance)
            , path_count(path_count)
            {
            }

            /**
             * Whenever an edge e = (v, w) is relaxed, the incoming edge list
             * for w is set to {(v, w)} and the shortest path count of w is set
             * to the number of paths that reach {v}.
             */
            void edge_relaxed(edge_descriptor e, const Graph& g)
            {
                vertex_descriptor v = source(e, g), w = target(e, g);
                incoming[w].clear();
                incoming[w].push_back(e);
                put(path_count, w, get(path_count, v));
            }

            /**
             * If an edge e = (v, w) was not relaxed, it may still be the case
             * that we've found more equally-short paths, so include {(v, w)} in
             * the incoming edges of w and add all of the shortest paths to v to
             * the shortest path count of w.
             */
            void edge_not_relaxed(edge_descriptor e, const Graph& g)
            {
                typedef typename property_traits< WeightMap >::value_type
                    weight_type;
                typedef typename property_traits< DistanceMap >::value_type
                    distance_type;
                vertex_descriptor v = source(e, g), w = target(e, g);
                distance_type d_v = get(distance, v), d_w = get(distance, w);
                weight_type w_e = get(weight, e);

                closed_plus< distance_type > combine;
                if (d_w == combine(d_v, w_e))
                {
                    put(path_count, w, get(path_count, w) + get(path_count, v));
                    incoming[w].push_back(e);
                }
            }

            /// Keep track of vertices as they are reached
            void examine_vertex(vertex_descriptor w, const Graph&)
            {
                ordered_vertices.push(w);
            }

        private:
            std::stack< vertex_descriptor >& ordered_vertices;
            WeightMap weight;
            IncomingMap incoming;
            DistanceMap distance;
            PathCountMap path_count;
        };

        /**
         * Function object that calls Dijkstra's shortest paths algorithm
         * using the Dijkstra visitor for the Brandes betweenness centrality
         * algorithm.
         */
        template < typename WeightMap > struct brandes_dijkstra_shortest_paths
        {
            brandes_dijkstra_shortest_paths(WeightMap weight_map)
            : weight_map(weight_map)
            {
            }

            template < typename Graph, typename IncomingMap,
                typename DistanceMap, typename PathCountMap,
                typename VertexIndexMap >
            void operator()(Graph& g,
                typename graph_traits< Graph >::vertex_descriptor s,
                std::stack< typename graph_traits< Graph >::vertex_descriptor >&
                    ov,
                IncomingMap incoming, DistanceMap distance,
                PathCountMap path_count, VertexIndexMap vertex_index)
            {
                typedef brandes_dijkstra_visitor< Graph, WeightMap, IncomingMap,
                    DistanceMap, PathCountMap >
                    visitor_type;
                visitor_type visitor(
                    ov, weight_map, incoming, distance, path_count);

                dijkstra_shortest_paths(g, s,
                    boost::weight_map(weight_map)
                        .vertex_index_map(vertex_index)
                        .distance_map(distance)
                        .visitor(visitor));
            }

        private:
            WeightMap weight_map;
        };

        /**
         * Function object that invokes breadth-first search for the
         * unweighted form of the Brandes betweenness centrality algorithm.
         */
        struct brandes_unweighted_shortest_paths
        {
            /**
             * Customized visitor passed to breadth-first search, which
             * records predecessor and the number of shortest paths to each
             * vertex.
             */
            template < typename Graph, typename IncomingMap,
                typename DistanceMap, typename PathCountMap >
            struct visitor_type : public bfs_visitor<>
            {
                typedef typename graph_traits< Graph >::edge_descriptor
                    edge_descriptor;
                typedef typename graph_traits< Graph >::vertex_descriptor
                    vertex_descriptor;

                visitor_type(IncomingMap incoming, DistanceMap distance,
                    PathCountMap path_count,
                    std::stack< vertex_descriptor >& ordered_vertices)
                : incoming(incoming)
                , distance(distance)
                , path_count(path_count)
                , ordered_vertices(ordered_vertices)
                {
                }

                /// Keep track of vertices as they are reached
                void examine_vertex(vertex_descriptor v, Graph&)
                {
                    ordered_vertices.push(v);
                }

                /**
                 * Whenever an edge e = (v, w) is labelled a tree edge, the
                 * incoming edge list for w is set to {(v, w)} and the shortest
                 * path count of w is set to the number of paths that reach {v}.
                 */
                void tree_edge(edge_descriptor e, Graph& g)
                {
                    vertex_descriptor v = source(e, g);
                    vertex_descriptor w = target(e, g);
                    put(distance, w, get(distance, v) + 1);

                    put(path_count, w, get(path_count, v));
                    incoming[w].push_back(e);
                }

                /**
                 * If an edge e = (v, w) is not a tree edge, it may still be the
                 * case that we've found more equally-short paths, so include
                 * (v, w) in the incoming edge list of w and add all of the
                 * shortest paths to v to the shortest path count of w.
                 */
                void non_tree_edge(edge_descriptor e, Graph& g)
                {
                    vertex_descriptor v = source(e, g);
                    vertex_descriptor w = target(e, g);
                    if (get(distance, w) == get(distance, v) + 1)
                    {
                        put(path_count, w,
                            get(path_count, w) + get(path_count, v));
                        incoming[w].push_back(e);
                    }
                }

            private:
                IncomingMap incoming;
                DistanceMap distance;
                PathCountMap path_count;
                std::stack< vertex_descriptor >& ordered_vertices;
            };

            template < typename Graph, typename IncomingMap,
                typename DistanceMap, typename PathCountMap,
                typename VertexIndexMap >
            void operator()(Graph& g,
                typename graph_traits< Graph >::vertex_descriptor s,
                std::stack< typename graph_traits< Graph >::vertex_descriptor >&
                    ov,
                IncomingMap incoming, DistanceMap distance,
                PathCountMap path_count, VertexIndexMap vertex_index)
            {
                typedef typename graph_traits< Graph >::vertex_descriptor
                    vertex_descriptor;

                visitor_type< Graph, IncomingMap, DistanceMap, PathCountMap >
                    visitor(incoming, distance, path_count, ov);

                std::vector< default_color_type > colors(num_vertices(g),
                    color_traits< default_color_type >::white());
                boost::queue< vertex_descriptor > Q;
                breadth_first_visit(g, s, Q, visitor,
                    make_iterator_property_map(colors.begin(), vertex_index));
            }
        };

        // When the edge centrality map is a dummy property map, no
        // initialization is needed.
        template < typename Iter >
        inline void init_centrality_map(
            std::pair< Iter, Iter >, dummy_property_map)
        {
        }

        // When we have a real edge centrality map, initialize all of the
        // centralities to zero.
        template < typename Iter, typename Centrality >
        void init_centrality_map(
            std::pair< Iter, Iter > keys, Centrality centrality_map)
        {
            typedef typename property_traits< Centrality >::value_type
                centrality_type;
            while (keys.first != keys.second)
            {
                put(centrality_map, *keys.first, centrality_type(0));
                ++keys.first;
            }
        }

        // When the edge centrality map is a dummy property map, no update
        // is performed.
        template < typename Key, typename T >
        inline void update_centrality(dummy_property_map, const Key&, const T&)
        {
        }

        // When we have a real edge centrality map, add the value to the map
        template < typename CentralityMap, typename Key, typename T >
        inline void update_centrality(
            CentralityMap centrality_map, Key k, const T& x)
        {
            put(centrality_map, k, get(centrality_map, k) + x);
        }

        template < typename Iter >
        inline void divide_centrality_by_two(
            std::pair< Iter, Iter >, dummy_property_map)
        {
        }

        template < typename Iter, typename CentralityMap >
        inline void divide_centrality_by_two(
            std::pair< Iter, Iter > keys, CentralityMap centrality_map)
        {
            typename property_traits< CentralityMap >::value_type two(2);
            while (keys.first != keys.second)
            {
                put(centrality_map, *keys.first,
                    get(centrality_map, *keys.first) / two);
                ++keys.first;
            }
        }

        template < typename Graph, typename CentralityMap,
            typename EdgeCentralityMap, typename IncomingMap,
            typename DistanceMap, typename DependencyMap, typename PathCountMap,
            typename VertexIndexMap, typename ShortestPaths >
        void brandes_betweenness_centrality_impl(const Graph& g,
            CentralityMap centrality, // C_B
            EdgeCentralityMap edge_centrality_map,
            IncomingMap incoming, // P
            DistanceMap distance, // d
            DependencyMap dependency, // delta
            PathCountMap path_count, // sigma
            VertexIndexMap vertex_index, ShortestPaths shortest_paths)
        {
            typedef
                typename graph_traits< Graph >::vertex_iterator vertex_iterator;
            typedef typename graph_traits< Graph >::vertex_descriptor
                vertex_descriptor;

            // Initialize centrality
            init_centrality_map(vertices(g), centrality);
            init_centrality_map(edges(g), edge_centrality_map);

            std::stack< vertex_descriptor > ordered_vertices;
            vertex_iterator s, s_end;
            for (boost::tie(s, s_end) = vertices(g); s != s_end; ++s)
            {
                // Initialize for this iteration
                vertex_iterator w, w_end;
                for (boost::tie(w, w_end) = vertices(g); w != w_end; ++w)
                {
                    incoming[*w].clear();
                    put(path_count, *w, 0);
                    put(dependency, *w, 0);
                }
                put(path_count, *s, 1);

                // Execute the shortest paths algorithm. This will be either
                // Dijkstra's algorithm or a customized breadth-first search,
                // depending on whether the graph is weighted or unweighted.
                shortest_paths(g, *s, ordered_vertices, incoming, distance,
                    path_count, vertex_index);

                while (!ordered_vertices.empty())
                {
                    vertex_descriptor w = ordered_vertices.top();
                    ordered_vertices.pop();

                    typedef typename property_traits< IncomingMap >::value_type
                        incoming_type;
                    typedef typename incoming_type::iterator incoming_iterator;
                    typedef
                        typename property_traits< DependencyMap >::value_type
                            dependency_type;

                    for (incoming_iterator vw = incoming[w].begin();
                         vw != incoming[w].end(); ++vw)
                    {
                        vertex_descriptor v = source(*vw, g);
                        dependency_type factor
                            = dependency_type(get(path_count, v))
                            / dependency_type(get(path_count, w));
                        factor *= (dependency_type(1) + get(dependency, w));
                        put(dependency, v, get(dependency, v) + factor);
                        update_centrality(edge_centrality_map, *vw, factor);
                    }

                    if (w != *s)
                    {
                        update_centrality(centrality, w, get(dependency, w));
                    }
                }
            }

            typedef typename graph_traits< Graph >::directed_category
                directed_category;
            const bool is_undirected
                = is_convertible< directed_category*, undirected_tag* >::value;
            if (is_undirected)
            {
                divide_centrality_by_two(vertices(g), centrality);
                divide_centrality_by_two(edges(g), edge_centrality_map);
            }
        }

    }
} // end namespace detail::graph

template < typename Graph, typename CentralityMap, typename EdgeCentralityMap,
    typename IncomingMap, typename DistanceMap, typename DependencyMap,
    typename PathCountMap, typename VertexIndexMap >
void brandes_betweenness_centrality(const Graph& g,
    CentralityMap centrality, // C_B
    EdgeCentralityMap edge_centrality_map,
    IncomingMap incoming, // P
    DistanceMap distance, // d
    DependencyMap dependency, // delta
    PathCountMap path_count, // sigma
    VertexIndexMap vertex_index BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    detail::graph::brandes_unweighted_shortest_paths shortest_paths;

    detail::graph::brandes_betweenness_centrality_impl(g, centrality,
        edge_centrality_map, incoming, distance, dependency, path_count,
        vertex_index, shortest_paths);
}

template < typename Graph, typename CentralityMap, typename EdgeCentralityMap,
    typename IncomingMap, typename DistanceMap, typename DependencyMap,
    typename PathCountMap, typename VertexIndexMap, typename WeightMap >
void brandes_betweenness_centrality(const Graph& g,
    CentralityMap centrality, // C_B
    EdgeCentralityMap edge_centrality_map,
    IncomingMap incoming, // P
    DistanceMap distance, // d
    DependencyMap dependency, // delta
    PathCountMap path_count, // sigma
    VertexIndexMap vertex_index,
    WeightMap weight_map BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    detail::graph::brandes_dijkstra_shortest_paths< WeightMap > shortest_paths(
        weight_map);

    detail::graph::brandes_betweenness_centrality_impl(g, centrality,
        edge_centrality_map, incoming, distance, dependency, path_count,
        vertex_index, shortest_paths);
}

namespace detail
{
    namespace graph
    {
        template < typename Graph, typename CentralityMap,
            typename EdgeCentralityMap, typename WeightMap,
            typename VertexIndexMap >
        void brandes_betweenness_centrality_dispatch2(const Graph& g,
            CentralityMap centrality, EdgeCentralityMap edge_centrality_map,
            WeightMap weight_map, VertexIndexMap vertex_index)
        {
            typedef typename graph_traits< Graph >::degree_size_type
                degree_size_type;
            typedef
                typename graph_traits< Graph >::edge_descriptor edge_descriptor;
            typedef typename mpl::if_c<
                (is_same< CentralityMap, dummy_property_map >::value),
                EdgeCentralityMap, CentralityMap >::type a_centrality_map;
            typedef typename property_traits< a_centrality_map >::value_type
                centrality_type;

            typename graph_traits< Graph >::vertices_size_type V
                = num_vertices(g);

            std::vector< std::vector< edge_descriptor > > incoming(V);
            std::vector< centrality_type > distance(V);
            std::vector< centrality_type > dependency(V);
            std::vector< degree_size_type > path_count(V);

            brandes_betweenness_centrality(g, centrality, edge_centrality_map,
                make_iterator_property_map(incoming.begin(), vertex_index),
                make_iterator_property_map(distance.begin(), vertex_index),
                make_iterator_property_map(dependency.begin(), vertex_index),
                make_iterator_property_map(path_count.begin(), vertex_index),
                vertex_index, weight_map);
        }

        template < typename Graph, typename CentralityMap,
            typename EdgeCentralityMap, typename VertexIndexMap >
        void brandes_betweenness_centrality_dispatch2(const Graph& g,
            CentralityMap centrality, EdgeCentralityMap edge_centrality_map,
            VertexIndexMap vertex_index)
        {
            typedef typename graph_traits< Graph >::degree_size_type
                degree_size_type;
            typedef
                typename graph_traits< Graph >::edge_descriptor edge_descriptor;
            typedef typename mpl::if_c<
                (is_same< CentralityMap, dummy_property_map >::value),
                EdgeCentralityMap, CentralityMap >::type a_centrality_map;
            typedef typename property_traits< a_centrality_map >::value_type
                centrality_type;

            typename graph_traits< Graph >::vertices_size_type V
                = num_vertices(g);

            std::vector< std::vector< edge_descriptor > > incoming(V);
            std::vector< centrality_type > distance(V);
            std::vector< centrality_type > dependency(V);
            std::vector< degree_size_type > path_count(V);

            brandes_betweenness_centrality(g, centrality, edge_centrality_map,
                make_iterator_property_map(incoming.begin(), vertex_index),
                make_iterator_property_map(distance.begin(), vertex_index),
                make_iterator_property_map(dependency.begin(), vertex_index),
                make_iterator_property_map(path_count.begin(), vertex_index),
                vertex_index);
        }

        template < typename WeightMap >
        struct brandes_betweenness_centrality_dispatch1
        {
            template < typename Graph, typename CentralityMap,
                typename EdgeCentralityMap, typename VertexIndexMap >
            static void run(const Graph& g, CentralityMap centrality,
                EdgeCentralityMap edge_centrality_map,
                VertexIndexMap vertex_index, WeightMap weight_map)
            {
                brandes_betweenness_centrality_dispatch2(g, centrality,
                    edge_centrality_map, weight_map, vertex_index);
            }
        };

        template <>
        struct brandes_betweenness_centrality_dispatch1< param_not_found >
        {
            template < typename Graph, typename CentralityMap,
                typename EdgeCentralityMap, typename VertexIndexMap >
            static void run(const Graph& g, CentralityMap centrality,
                EdgeCentralityMap edge_centrality_map,
                VertexIndexMap vertex_index, param_not_found)
            {
                brandes_betweenness_centrality_dispatch2(
                    g, centrality, edge_centrality_map, vertex_index);
            }
        };

        template < typename T > struct is_bgl_named_params
        {
            BOOST_STATIC_CONSTANT(bool, value = false);
        };

        template < typename Param, typename Tag, typename Rest >
        struct is_bgl_named_params< bgl_named_params< Param, Tag, Rest > >
        {
            BOOST_STATIC_CONSTANT(bool, value = true);
        };

    }
} // end namespace detail::graph

template < typename Graph, typename Param, typename Tag, typename Rest >
void brandes_betweenness_centrality(const Graph& g,
    const bgl_named_params< Param, Tag, Rest >& params
        BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, vertex_list_graph_tag))
{
    typedef bgl_named_params< Param, Tag, Rest > named_params;

    typedef typename get_param_type< edge_weight_t, named_params >::type ew;
    detail::graph::brandes_betweenness_centrality_dispatch1< ew >::run(g,
        choose_param(
            get_param(params, vertex_centrality), dummy_property_map()),
        choose_param(get_param(params, edge_centrality), dummy_property_map()),
        choose_const_pmap(get_param(params, vertex_index), g, vertex_index),
        get_param(params, edge_weight));
}

// disable_if is required to work around problem with MSVC 7.1 (it seems to not
// get partial ordering getween this overload and the previous one correct)
template < typename Graph, typename CentralityMap >
typename disable_if< detail::graph::is_bgl_named_params< CentralityMap >,
    void >::type
brandes_betweenness_centrality(const Graph& g,
    CentralityMap centrality BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    detail::graph::brandes_betweenness_centrality_dispatch2(
        g, centrality, dummy_property_map(), get(vertex_index, g));
}

template < typename Graph, typename CentralityMap, typename EdgeCentralityMap >
void brandes_betweenness_centrality(const Graph& g, CentralityMap centrality,
    EdgeCentralityMap edge_centrality_map BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    detail::graph::brandes_betweenness_centrality_dispatch2(
        g, centrality, edge_centrality_map, get(vertex_index, g));
}

/**
 * Converts "absolute" betweenness centrality (as computed by the
 * brandes_betweenness_centrality algorithm) in the centrality map
 * into "relative" centrality. The result is placed back into the
 * given centrality map.
 */
template < typename Graph, typename CentralityMap >
void relative_betweenness_centrality(const Graph& g, CentralityMap centrality)
{
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator;
    typedef
        typename property_traits< CentralityMap >::value_type centrality_type;

    typename graph_traits< Graph >::vertices_size_type n = num_vertices(g);
    centrality_type factor
        = centrality_type(2) / centrality_type(n * n - 3 * n + 2);
    vertex_iterator v, v_end;
    for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v)
    {
        put(centrality, *v, factor * get(centrality, *v));
    }
}

// Compute the central point dominance of a graph.
template < typename Graph, typename CentralityMap >
typename property_traits< CentralityMap >::value_type central_point_dominance(
    const Graph& g,
    CentralityMap centrality BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    using std::max;

    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator;
    typedef
        typename property_traits< CentralityMap >::value_type centrality_type;

    typename graph_traits< Graph >::vertices_size_type n = num_vertices(g);

    // Find max centrality
    centrality_type max_centrality(0);
    vertex_iterator v, v_end;
    for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v)
    {
        max_centrality = (max)(max_centrality, get(centrality, *v));
    }

    // Compute central point dominance
    centrality_type sum(0);
    for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v)
    {
        sum += (max_centrality - get(centrality, *v));
    }
    return sum / (n - 1);
}

} // end namespace boost

#endif // BOOST_GRAPH_BRANDES_BETWEENNESS_CENTRALITY_HPP

/* betweenness_centrality.hpp
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
*/