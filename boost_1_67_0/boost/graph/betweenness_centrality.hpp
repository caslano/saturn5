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