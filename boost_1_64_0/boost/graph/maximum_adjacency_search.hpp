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
zfBkOVumnNn7B1vfTZjudk3yk5Zr9zJnl6pb832DDddVxZs631LCXeqcqS6VLyO4bYGjzhX/i1U19Vp+M8PGleCcrX5pv3Px0XLxq/HZe4wN5825aC5hVjh7VbDa52+vjZCw/jbCs/fGs9o82ijx1vPaDRveazfCn91tG2Fsw+9fdkp9kpNj56TEyu+sct7Ex7uHnmnnBjWV/Vc409VFdm7Qs+LXzT6PKvd51I7DbiT7r3beVg1890LcCM1zT2icaeebiF2Fs085vriKiMm75+txmbY5+tx6z1/m/iMndA8+WOqka9fVuVQV4yf3Qmx5uQvkiw9en0WhxB+v0mlL4kxb0p969DM0ADVEp6OB6Aw0yLQNbWBSgms/WPzcZ7ghcu3/8Wt8qO1oYK/x4W2HLf9u21FDG5FXQ39EcVh/xNH3BLbM2fbD30/RTKfPPtP58jisD2PPCaZdQI3QPWhUE8qv5Gu5HsCfo1vG/Fk5bpptmXd9Tdq8cm/OR5w5/8+Ie6EardrbMnDGCvxwh+4nlMTlXR92SJifq3rePAE7V+572ZekGquO9lol94lypfLKXRPzG+G/2ZVyUg+7K8wzXDm61Nzr3RXrloOlaJH2+wnlQOdzoj0nXp6EPzvPaK5kO4O0dYPx8EMiLpZ0lRfmLqDzkNZ3aoHy5bHrE5bHJkwPe829TdwRjr8++59F1sn+SCfOPnuEfsnL8/vF5pCck/nx8qxc6H92u3OF19/Yv4n3LB3eX9Ip1s3PpSZ/n6IAnhrr/t0VdkG70QT5283v7FhzrY449nN06wh5jpY8HxQRynN/HnnPz6TRPD+HfUellZItx3HnEA6C+wiw8XI5D1I5KfBz5kwtnFHNNdCWwzfEfhz9fk29si9+nU3bxMyKlbiPfU2UMFjae9r94m5RfT+ete9rnxf3ibutU+MztA3Tyz5DfiDujj/6DL3x8p/+DO23XR52/+yfo/Ke2KXQp9/Uu96Fha/whzfXE3s/HGa7ukq6yqhGnm1KmG2lxOO7Tkmb4dWBQ66tU90cxAT2bFtp8t5eE6W42DLRTPaPpLwNs/c4n0qcJzmn4jtP7jG8Omp+3tbjz8U2zvFs7LOjvQf/UmwSnFC/+ZVyvXPZxHC4YQqsgCs8cd378fti3U8lx+qbXzClyrXu3/Ms6933hsqU/76X82n8Km1Ytzz42+G9pjF/C7VFv0X78Yu5Qup/SS7Xu4yRQzL7+MqKY8+VbYON/WnVzlct1GVa9m+S/VHuPKmi2bne/Ndhsv9K+Y0Dpq+pLCe/cGaR1273F5u7cPuft7zyOkD2V8r+T2V/ab6/zR4o+9erHpSV+rqscK0dwXkZidLQKJSORqOtpDHDPD+NSfjx654uI+uvsGXE9C3bPmubX/62d+XJSrb3zXu05+ER/QwSyvviAl/bW2N/g7FvI/VuLO64K7X7Tp5ruqvq+hzkedyG264GkKLq+hnMs4W1SyK+mp5BxlS1+9H+BWy9tvRH+hf8tsur6V+w7WaYbcVP6Evw26/+kb4Ev23lT+hL8NuvP8Y1oJmcr0ye1Lrb8Nlh4Tfittcnt+5QO7zfmxJmv/kY14y8MNut1cRNCGtfHGa//RjXmAVhtjtrvsZInWwtx/7Laq8x8XD+VXp/wLh5qhZ3ck3XDWknWkqcG2vql5G2ooVbR5wa2hu5fiXIb9UPb7Ps/nFm/1m0J03Ms1Yq5TITtTPPTVeirARs0XhzHZoAtxFftth416Rw9THtTsaPtDuSJ2HXpvA+nLwa+nCKa+jDWVDD81l5DX04y6vpw6lQ1byHq6EPp7KaPpz14ddIY7vR91uheDfba5yvbuC/1X89NLbbw2zZI7Y=
*/