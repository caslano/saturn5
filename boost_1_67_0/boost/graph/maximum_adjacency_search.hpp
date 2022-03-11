//
//=======================================================================
// Copyright 2012 Fernando Vilas
//           2010 Daniel Trebbien
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

// The maximum adjacency search algorithm was originally part of the
// Stoer-Wagner min cut implementation by Daniel Trebbien. It has been
// broken out into its own file to be a public search algorithm, with
// visitor concepts.
#ifndef BOOST_GRAPH_MAXIMUM_ADJACENCY_SEARCH_H
#define BOOST_GRAPH_MAXIMUM_ADJACENCY_SEARCH_H

/**
 * This is an implementation of the maximum adjacency search on an
 * undirected graph. It allows a visitor object to perform some
 * operation on each vertex as that vertex is visited.
 *
 * The algorithm runs as follows:
 *
 * Initialize all nodes to be unvisited (reach count = 0)
 *   and call vis.initialize_vertex
 * For i = number of nodes in graph downto 1
 *   Select the unvisited node with the highest reach count
 *     The user provides the starting node to break the first tie,
 *     but future ties are broken arbitrarily
 *   Visit the node by calling vis.start_vertex
 *   Increment the reach count for all unvisited neighbors
 *     and call vis.examine_edge for each of these edges
 *   Mark the node as visited and call vis.finish_vertex
 *
 */

#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#include <boost/graph/buffer_concepts.hpp>
#include <boost/graph/exception.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/tuple/tuple.hpp>

#include <set>

namespace boost
{
template < class Visitor, class Graph > struct MASVisitorConcept
{
    void constraints()
    {
        boost::function_requires<
            boost::CopyConstructibleConcept< Visitor > >();
        vis.initialize_vertex(u, g);
        vis.start_vertex(u, g);
        vis.examine_edge(e, g);
        vis.finish_vertex(u, g);
    }
    Visitor vis;
    Graph g;
    typename boost::graph_traits< Graph >::vertex_descriptor u;
    typename boost::graph_traits< Graph >::edge_descriptor e;
};

template < class Visitors = null_visitor > class mas_visitor
{
public:
    mas_visitor() {}
    mas_visitor(Visitors vis) : m_vis(vis) {}

    template < class Vertex, class Graph >
    void initialize_vertex(Vertex u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_initialize_vertex());
    }

    template < class Vertex, class Graph > void start_vertex(Vertex u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_start_vertex());
    }

    template < class Edge, class Graph > void examine_edge(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, ::boost::on_examine_edge());
    }

    template < class Vertex, class Graph >
    void finish_vertex(Vertex u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_finish_vertex());
    }

    BOOST_GRAPH_EVENT_STUB(on_initialize_vertex, mas)
    BOOST_GRAPH_EVENT_STUB(on_start_vertex, mas)
    BOOST_GRAPH_EVENT_STUB(on_examine_edge, mas)
    BOOST_GRAPH_EVENT_STUB(on_finish_vertex, mas)

protected:
    Visitors m_vis;
};
template < class Visitors >
mas_visitor< Visitors > make_mas_visitor(Visitors vis)
{
    return mas_visitor< Visitors >(vis);
}
typedef mas_visitor<> default_mas_visitor;

namespace detail
{
    template < class Graph, class WeightMap, class MASVisitor,
        class VertexAssignmentMap, class KeyedUpdatablePriorityQueue >
    void maximum_adjacency_search(const Graph& g, WeightMap weights,
        MASVisitor vis,
        const typename boost::graph_traits< Graph >::vertex_descriptor start,
        VertexAssignmentMap assignments, KeyedUpdatablePriorityQueue pq)
    {
        typedef typename boost::graph_traits< Graph >::vertex_descriptor
            vertex_descriptor;
        typedef typename boost::property_traits< WeightMap >::value_type
            weight_type;

        std::set< vertex_descriptor > assignedVertices;

        // initialize `assignments` (all vertices are initially
        // assigned to themselves)
        BGL_FORALL_VERTICES_T(v, g, Graph) { put(assignments, v, v); }

        typename KeyedUpdatablePriorityQueue::key_map keys = pq.keys();

        // set number of visited neighbors for all vertices to 0
        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            if (v == get(assignments, v))
            { // foreach u \in V do
                put(keys, v, weight_type(0));
                vis.initialize_vertex(v, g);

                pq.push(v);
            }
        }
        BOOST_ASSERT(pq.size() >= 2);

        // Give the starting vertex high priority
        put(keys, start, get(keys, start) + num_vertices(g) + 1);
        pq.update(start);

        // start traversing the graph
        // vertex_descriptor s, t;
        // weight_type w;
        while (!pq.empty())
        { // while PQ \neq {} do
            const vertex_descriptor u = pq.top(); // u = extractmax(PQ)
            /* weight_type w = */ get(keys, u);
            vis.start_vertex(u, g);
            pq.pop(); //            vis.start_vertex(u, g);

            BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
            { // foreach (u, v) \in E do
                vis.examine_edge(e, g);

                const vertex_descriptor v = get(assignments, target(e, g));

                if (pq.contains(v))
                { // if v \in PQ then
                    put(keys, v,
                        get(keys, v)
                            + get(weights,
                                e)); // increasekey(PQ, v, wA(v) + w(u, v))
                    pq.update(v);
                }
            }

            typename std::set< vertex_descriptor >::const_iterator
                assignedVertexIt,
                assignedVertexEnd = assignedVertices.end();
            for (assignedVertexIt = assignedVertices.begin();
                 assignedVertexIt != assignedVertexEnd; ++assignedVertexIt)
            {
                const vertex_descriptor uPrime = *assignedVertexIt;

                if (get(assignments, uPrime) == u)
                {
                    BGL_FORALL_OUTEDGES_T(uPrime, e, g, Graph)
                    { // foreach (u, v) \in E do
                        vis.examine_edge(e, g);

                        const vertex_descriptor v
                            = get(assignments, target(e, g));

                        if (pq.contains(v))
                        { // if v \in PQ then
                            put(keys, v,
                                get(keys, v)
                                    + get(weights, e)); // increasekey(PQ, v,
                                                        // wA(v) + w(u, v))
                            pq.update(v);
                        }
                    }
                }
            }
            vis.finish_vertex(u, g);
        }
    }
} // end namespace detail

template < class Graph, class WeightMap, class MASVisitor,
    class VertexAssignmentMap, class KeyedUpdatablePriorityQueue >
void maximum_adjacency_search(const Graph& g, WeightMap weights, MASVisitor vis,
    const typename boost::graph_traits< Graph >::vertex_descriptor start,
    VertexAssignmentMap assignments, KeyedUpdatablePriorityQueue pq)
{
    BOOST_CONCEPT_ASSERT((boost::IncidenceGraphConcept< Graph >));
    BOOST_CONCEPT_ASSERT((boost::VertexListGraphConcept< Graph >));
    typedef typename boost::graph_traits< Graph >::vertex_descriptor
        vertex_descriptor;
    typedef typename boost::graph_traits< Graph >::vertices_size_type
        vertices_size_type;
    typedef
        typename boost::graph_traits< Graph >::edge_descriptor edge_descriptor;
    BOOST_CONCEPT_ASSERT((boost::Convertible<
        typename boost::graph_traits< Graph >::directed_category,
        boost::undirected_tag >));
    BOOST_CONCEPT_ASSERT(
        (boost::ReadablePropertyMapConcept< WeightMap, edge_descriptor >));
    // typedef typename boost::property_traits<WeightMap>::value_type
    // weight_type;
    boost::function_requires< MASVisitorConcept< MASVisitor, Graph > >();
    BOOST_CONCEPT_ASSERT(
        (boost::ReadWritePropertyMapConcept< VertexAssignmentMap,
            vertex_descriptor >));
    BOOST_CONCEPT_ASSERT((boost::Convertible< vertex_descriptor,
        typename boost::property_traits< VertexAssignmentMap >::value_type >));
    BOOST_CONCEPT_ASSERT(
        (boost::KeyedUpdatableQueueConcept< KeyedUpdatablePriorityQueue >));

    vertices_size_type n = num_vertices(g);
    if (n < 2)
        throw boost::bad_graph(
            "the input graph must have at least two vertices.");
    else if (!pq.empty())
        throw std::invalid_argument(
            "the max-priority queue must be empty initially.");

    detail::maximum_adjacency_search(g, weights, vis, start, assignments, pq);
}

namespace graph
{
    namespace detail
    {
        template < typename WeightMap > struct mas_dispatch
        {
            typedef void result_type;
            template < typename Graph, typename ArgPack >
            static result_type apply(const Graph& g,
                // const bgl_named_params<P,T,R>& params,
                const ArgPack& params, WeightMap w)
            {

                using namespace boost::graph::keywords;
                typedef typename boost::graph_traits< Graph >::vertex_descriptor
                    vertex_descriptor;
                typedef typename WeightMap::value_type weight_type;

                typedef boost::detail::make_priority_queue_from_arg_pack_gen<
                    boost::graph::keywords::tag::max_priority_queue,
                    weight_type, vertex_descriptor,
                    std::greater< weight_type > >
                    default_pq_gen_type;

                default_pq_gen_type pq_gen(
                    choose_param(get_param(params, boost::distance_zero_t()),
                        weight_type(0)));

                typename boost::result_of< default_pq_gen_type(
                    const Graph&, const ArgPack&) >::type pq
                    = pq_gen(g, params);

                boost::null_visitor null_vis;
                boost::mas_visitor< boost::null_visitor > default_visitor(
                    null_vis);
                vertex_descriptor v = vertex_descriptor();
                boost::detail::make_property_map_from_arg_pack_gen<
                    boost::graph::keywords::tag::vertex_assignment_map,
                    vertex_descriptor >
                    map_gen(v);
                typename boost::detail::map_maker< Graph, ArgPack,
                    boost::graph::keywords::tag::vertex_assignment_map,
                    vertex_descriptor >::map_type default_map
                    = map_gen(g, params);
                boost::maximum_adjacency_search(g, w,
                    params[_visitor | default_visitor],
                    params[_root_vertex | *vertices(g).first],
                    params[_vertex_assignment_map | default_map], pq);
            }
        };

        template <> struct mas_dispatch< boost::param_not_found >
        {
            typedef void result_type;

            template < typename Graph, typename ArgPack >
            static result_type apply(
                const Graph& g, const ArgPack& params, param_not_found)
            {

                using namespace boost::graph::keywords;
                typedef typename boost::graph_traits< Graph >::vertex_descriptor
                    vertex_descriptor;

                // get edge_weight_t as the weight type
                typedef typename boost::property_map< Graph, edge_weight_t >
                    WeightMap;
                typedef typename WeightMap::value_type weight_type;

                typedef boost::detail::make_priority_queue_from_arg_pack_gen<
                    boost::graph::keywords::tag::max_priority_queue,
                    weight_type, vertex_descriptor,
                    std::greater< weight_type > >
                    default_pq_gen_type;

                default_pq_gen_type pq_gen(
                    choose_param(get_param(params, boost::distance_zero_t()),
                        weight_type(0)));

                typename boost::result_of< default_pq_gen_type(
                    const Graph&, const ArgPack&) >::type pq
                    = pq_gen(g, params);

                boost::null_visitor null_vis;
                boost::mas_visitor< boost::null_visitor > default_visitor(
                    null_vis);
                vertex_descriptor v = vertex_descriptor();
                boost::detail::make_property_map_from_arg_pack_gen<
                    boost::graph::keywords::tag::vertex_assignment_map,
                    vertex_descriptor >
                    map_gen(v);
                typename boost::detail::map_maker< Graph, ArgPack,
                    boost::graph::keywords::tag::vertex_assignment_map,
                    vertex_descriptor >::map_type default_map
                    = map_gen(g, params);
                boost::maximum_adjacency_search(g, get(edge_weight, g),
                    params[_visitor | default_visitor],
                    params[_root_vertex | *vertices(g).first],
                    params[_vertex_assignment_map | default_map], pq);
            }
        };
    } // end namespace detail
} // end namespace graph

// Named parameter interface
// BOOST_GRAPH_MAKE_OLD_STYLE_PARAMETER_FUNCTION(maximum_adjacency_search, 1)
template < typename Graph, typename P, typename T, typename R >
void maximum_adjacency_search(
    const Graph& g, const bgl_named_params< P, T, R >& params)
{

    typedef bgl_named_params< P, T, R > params_type;
    BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(params_type, params)

    // do the dispatch based on WeightMap
    typedef typename get_param_type< edge_weight_t,
        bgl_named_params< P, T, R > >::type W;
    graph::detail::mas_dispatch< W >::apply(
        g, arg_pack, get_param(params, edge_weight));
}

namespace graph
{
    namespace detail
    {
        template < typename Graph > struct maximum_adjacency_search_impl
        {
            typedef void result_type;

            template < typename ArgPack >
            void operator()(const Graph& g, const ArgPack& arg_pack) const
            {
                // call the function that does the dispatching
                typedef
                    typename get_param_type< edge_weight_t, ArgPack >::type W;
                graph::detail::mas_dispatch< W >::apply(
                    g, arg_pack, get_param(arg_pack, edge_weight));
            }
        };
    } // end namespace detail
    BOOST_GRAPH_MAKE_FORWARDING_FUNCTION(maximum_adjacency_search, 1, 5)
} // end namespace graph

} // end namespace boost

#include <boost/graph/iteration_macros_undef.hpp>

#endif // BOOST_GRAPH_MAXIMUM_ADJACENCY_SEARCH_H

/* maximum_adjacency_search.hpp
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
*/