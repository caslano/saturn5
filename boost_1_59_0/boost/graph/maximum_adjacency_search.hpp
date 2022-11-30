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
LBWqWSyA4PtA4ZWddVjeWXyq1wvVYjIsoLXKnTydCUs0+bspL3T0DvBhdjfGgOLu9ypVPL0lV8N1smKAQKngHnStOLUxTeF/JhVxgQLTdyKQbKUD1Z7v/074qh44ZAQYdJO8YiD6FnoS6wlEYdrQbXQZ+NBTqPJXh4ywexA2S9m5PXEogFMg3JSqfLYtn8MOQIbANUfL/q6qkQyKfYJJiSnzQp8HYMpb2JRKB84ELu5XcwLZWkDD6hM7RWGnzqZWTBQqJsoqJv5NK8cS0qeKZEIt5o2NZPgAdL0F+prUnA0wMZUPmc4j3YZI17dhw9aDhg1e3F9BN0RMNkAYxQDP2AbU29o/RANsmgG2cQxQ34Bw3cJzgewkjQvCUQfGveaOhfpvYOApuYGXtwia1B4L/QlYkRSBUlc+sSAXG3ErX89s3FQjRDp/Aku5O2xkNo+ZrWfzdXgSbdJSlp1KSwsxNrSgQZOkiM1Hpakg+udwSt6KcFIAmfSUMnh+vJS5JsYBaEYzIYfVnB1whyVccDDecYkD5cCbRsQejwNlAzc+UO5/HfzYI9CvpoE1K1OsQfaF/aRpxMKK5Tttqjff1fOd8Pl+EyRW2+AsPxHIAjiUirmApUTqgqrurD5RlQjnyFRicR01VZKAwbrpjtCrGBS7wXSfvPk4bcwBavChXD+s3D/M2Nei2XHIfBSu5F0xln5tmH7uk9t3Yd0VcZ/cDZWVvLlfdp9WGjEprfT5AnB88CTbhE0AAAqbQ+7UqVrnm0ZyciE/5vvzB3WixjR2xDXqfTPqB8NGnovsiE7eXCBn1yM5s71pin0x9G+4Qz9AHUP3saahU40D6I8VRg28bHu26smgCTERtSw6F3gDqUbWRS5XmG3eGqByMmPdmT1M1sIYnBbyMNE9MBHk80TcuAzMhgpY9qaDibCPG/XyG/+PRpWDUZ+8kZKLjC0ZtJgxpuDMsSjiFdPHoYhAeyBTMIZnAWmFAnRU5vXiASsUNX1jjQ8I44xtgbHGyO5U0seONZ081Wjs6Z9iTY0NI+jRudeMrC8o0LPeP6yq42V9V2h8euR9fQQQBGxav4wOiEBBk33t044OdPMMZ7i2eLGtZSqpFsgXxTcGskukHh7oUvOXC8IN7NmD5PgpByWdFFMDaAGvl5SfxKF1AWZj/msGtC4viCPAngIzafpDtok0pdOZUyDhTWTpiWnJZAlrRlqJZKn5tX+WLG3b/y2RpR93XpwsLTeRJZgi5dTi68/E4CQxjlg8l/54wMyW1k/7NtnSn/GgmP+qiS29hSo3HDCi8EjBuGzpVmuCLRUxtoQVPP34QCpbmnFgLKKgZxStwVyaTbBBPMCyhNWesnsQDYe77gEUG9BSyRCC3yGV+pKZSsMI9b8KjaWe7fyoNEVnJwZboXUvY6LxsOPXF7ttwQUG7hWRGBQ+k0iGdBvP4Y2SJHsAFY+EGCqCCqgEMHv7IXujzybZ+Nf9Y3Ipt01rwV+CkS/ts3IuDx8QU3R9Yli7aCw76ZxQArud4W1duznWBOuymGDqkSYwdSkzlSHJPMPg0wmDDV2FxmGBCrb14IxasZhBQ/tTGh5QimHLKRP7R3cKak1eonLQOdr7rxhA4pid4Gj4/lOco9WdB3owKkf7HwFEl+xPhovTMWnAvox8IN29lqv1BWf6OYhf7OubUZb18Ve9BCx5SbmzDzuoWr29pBRiQYQzDVjEXJ1FRPMZfgYEZaONOqfg00VlSYkm/yW9aTLrpcer88ZRurwDom5OMM8/H41BomhCfECsYy/GTXEPmyyZoVlidJvcw7oaVoZruB6YWIuG/QLsaEhYtrhRumAJHpXuFrhl/jX3p7dCFX+LAAkmRrulu4GYTyS38JhvjuhL8aeEevTqRtv/AapLVBhEr8X2cU+5HhUNySz4T/sMJNo3Wz8P674a/zzcu1djwf+L+73s5RGHH+kKZNSfeRfUppAMnfvagfvWkutcQSEgIP11HWoeMhWxjlAzZuubYBlwXNgqxLBNfGTC7XMhhYZmQiiWsVCU/r0cTq+yCo4+NMPUgSwFMbJEVPaHGCcKps/yiNFcV3dwAukFah4VSD9Ja+LIO6ooe0TgxcCIbzcxYpybp4/NiDPiNLr+rKrK95YCzGzZZyLCV6KZT77E2qeaWp3+Kku9xAKGwX5CqYeVnl2zhsH4dJhNO2op/j/7aPa+kWkKFAq7k0gWs2u9TlWtEbFhrFR5MXenjtF9HHPgJH1gDT/GSOlALzbL4IxN3woJtA2/ERH7zkqVftQCbcgkGU0WRB1TvwyQ48xG8MMvXzSQ4/a5BnKQTeWMbryQzrzCAOSBvwGAlPFe5ox5k3DLGNvIfCmFaNh0ouHsc10IzgVURo6hYfTZpEL3LBS6Z1mhe9kLVq640hbMBGmkGNHjRVUVGpe4BpLD1RXIKy4XYZkz7x2FSvQDldCL4dzUnss/ZE7n85dozv1bxjcnz2ROnLfM22vmLb+bOA5vyUvmLVCfeg2u8vs4V3HBVtC2vfFNMDa4MLRhE6i7di97VC1X9kJwyZXHnR86+5p4uf7kKnnC+U+yHug6/8Gk3mp6aqGVWymX8cVXtmz2F+FjpZwC7MzJ7iNoHgTjksSz9vRZbnyA7QZ7jQfYbqAex4m7F2OF8I9KlScty6Sw4FWDR9DKYxO1AoYsZc39c+6TFpn/ecAmrT/5tRLspwcGVXWJ68pmCbL1+B5zqeRzqsU3tuQAwSC2EMB4BoNxscx1Y3NUbeH1V4Eak567DNGhT1V1nHfKRj4a3+G46NPzraOJoBL2LhsmwzjaDLmB8eVAppbu/tM3tD4wqvXgh8fOXHQmwzLstI5vGZ382cUNA7FfRr+h/f5xXYtNqYtorPp8PI2A+tl4bL7wO4b6GNHRTCICKmLOKkvttHs6O3SiGsJrDIle83wC4tXZeCtZqf/zS/FGLd3yl0vyWtbQJYkdHF9srF5UQjglVWZ+eUlqH/jqksRWnb80n2yMXdJ0yy9cithF3yHNAACbFu8CzOGQ52MzYGVyWxKqNyhGezrwySgjAYyr2x7fPjpr69itMZXPlZ1YeyMPtDf2GTyjFNH+hudYxAHzjvfYnJAbyqZ86lfjfEKPtvBzSb00VlB8/Rsrvs12fW1SGaFUFbLGuOrJS6oj1JYSjbfkk6P0N1jD3v5c0uFcDUnHuOIjOey1jpRuEEBslQ2JNmAudi6uUqotruMtef6TV+l8uwIZpT/OtxuftsYfcTYIZBpwREFptbhWCIF3S6Ru3tXV/JnrwsZJyG+qBJk/EG0gXS6P2Fyu3MNZ8RhaRSKmM2jNNeCrfmd4ZbFHCMws9ogtWTCO2LbJNqkExw2pLYKO93KDIG8RiceGEisE2b5N9dgaTc/VuNCzyG/eeJb5n3VbIxOwapcbeblRkJaKaqTMVsBu2OXGXLkxTynL16jO36cC7bl/u8b8rNprK/Ku3Vqxj287J5otSDrjT9qTezj062n41Jw9a991VmvIfvxsCmeEAuFbDDrT6zBnmsxv5S0b7VW8G7DhqXi017XU99lbcsRTAnNnSxWOEhVu27VmZrSWzLiHCeM7VzbFY8MxBer7pMJho9vRWxUOB9Z/6nvSlrVcoIhUrVUDDpGw/rGnRK+3bm7vu/dQYu73kl64w4qvm94Q1Ns8xmu57IGFLfnxAXPHVlY55cpFSplNyucgGeC27MnVbN5jSXq7o5wnXgztWgztCxjazRbX0Nih3bYbQvscRPTVy0idAMFDJkGcC8oWCz5Q7/NgeH/R/Nlq11+1+K4cxvi24QN1ZYNAH8zGJ3zmaGRocO3TqWgw7wsNDVb9LQUNXnzahAb2UBjRYPAppI6koQQo0WaBtSJvBV+cSmowMHAAt293f9kWDmZpAHFKA4jou+T/aruWmCaiKFpq+UgUBmlMIy4gFqNQIzFsEBcQWyQGkgKKYBVZuUB0gWVlCGgDZngWWJDIpxRLsC5MYEMguiBGEtSwJbrQha6YpCwwlASNZnz3zu9Ny0D5uGvamXfP3HnvvrnnnLYVJ6G3oiAoWFea27eYK6xwEomoHgZtOkmtg0pi73WtC6dfxUxbtY6sZ21RRxT3TuNb2b2TztP0g2Fnkz5hkMO+5iMmvjLtQxn+RDPbkmRBktLDam9rkbleaVNLFj5nQE9sERy/RVEYCOtqm3FUW34CUQdfqlEvndVHbZajztK9SDgRZlhBBzxh38Qz0YvTewyFHVz0PC56SctBqccCKk7qDHRZT+HHh6wFUFVMSarU0w+uYyhAUsWB2uPrh7+4E0uaOK+rxSY/k5OPfPUadLilS958UsHRHjmZb+Qix0sXyRpJaT9UE0mqo0WEI3Q9lHPkNhxs5scFoCnb6btW2qEI3zgsSVcp+vdcnJ3u+kOmfpTprcxuxcvrR5801AK7NAXptd+yN5A+uH4KTvP3YCqCMW/7eyzy6VY+GEUOFdZ05JGvD6960WlvMEmr2SeK3joausjt74MCKJyj9wI+NxOn3VlKi1pbCv24MpIKDky/5TGxdX/1ZpNsfw+k2n2DLIm1VroeKmi0IhxYePaXLj0NglxQ5iE0+I5pyMzuNtikw/idQAZNxKEf2MajV4S22cgeVmkxztAYtOA1QMHLlVnPKppAxqOnt1SvWsHB8rPF7FGgVa8uukQ5Nb55hELnmvcouWLhe4pxxohJ9CgJWleHaGp3kE4UrLIUkGItR28Ngixd8KaTlDrECayC504TWfB8ipemottLU1FFmur8I4p6aUohbssnzMwk0ZHL81HkLc4TxNRi5XvW8P4rATL8qH3VCHny6Dzi0XHihQzdXS/O4hRzrUmufctOzPiCnuF1TuhMbTnw6PAkJGulxQWglUImBwvkyoAznOUUMR/xDrYSmKsrIW3wC+80w6DyyvcGs4HnmkS3kylN620UyK8XKkczU6BUD66QlYnmgT+dExRvzb0foqh5ayZVuejuhrLLSIOgt+Y7yEWXQ/uVi2rHDkguunjfUC5qNvTW7AFwKHBAgPnWnQFf0zNB6PfJG2eZIA/wi4krWM3bK1jTtL0SHowze9UUTKWpoLrLOQpBweqKV7BsOFVCK7Q6ygrW5LKqYOWMx0pInqC0yrv25bWxjibq9xkOxtttvowdBIaBkYT8PrYtANQbAvgPMt7zsVjGlRXrolt5ijRu8/WwGWUoOnqRjpuEy+gPGOZxF7alyuH92ZbmAox/Q0a2MWqEbBdC5fTQnoXKU4GdhcoaQ4y7ESrTh/YuVHaM6oXKgJFQGR5hhcquxIXKACNUZo5qCwEs9+2xG5is3tviPWc2zXOmp/o2FQ6yNcuIElpm+ap/RZP35AM/AIBDS7Q9f3RTVZpJGtIHPJuHphiG6BQpYz2AMhaETsaZVpqkrrQkVFpYpOUcsTIdXAvk0aIUYULH3l6ijgP+2PmxsrucPbt65ujuLFTX9bRUDRwQGIejaDm7jHL0QopUhi1FC9nvu/e95L2XtlRn95+S9979+d3v9/2+j2u4NL0zrjnc16MOB4zz5EYAmPpi5sLtNl0dQA1el8A/dGHoFNewuHIQnWjQBrhT/G7OXnnyZOrD+FNOuxZU9SGCuIa1DeM4Y6+8aA1+R9/Z2Hxs7M2xNTt1+RoA+OwRAED0Ba4NCUcKDxZFqq2TYlVKKhGUMWiZ1HlInZfU+eJbeBREfLGcDhsUXhfN0AkVEC8pdZJlkriRdoj3pL40ESpHBZfUV5D6VSK+Ag0dzQXzW9RkACrPvWDiwL/A9YXgncina+eXgidJJSvujTc30W5YMakvJPVF/v6on9tLoNUq/nfdu7rdew9yiS0DzyV1iv8QWFJ1SjIfhLL/gJpTg4aUHQ0pRoIKqV+NRwUWzCTk1SeMeWNs6gtppnxELBeU1qCPBAtIsJAEi2JVcwBOszBmkQTnkuACEvwhCZbq3tjGgs6f4Dauez5t4pPW06SVkdY+MPGPk9YhQZ2pKh/Y8GpRyZbCjdPjwQKgTX93dAqovU1OWiGRBaTFSVoksvQ0URmp7IO+gnaLB0pa2cbraeA0lV+l9mqw7YN+la3/Iq6eZr1nQV348fOGW9ImVBeeeI4fOr17OzfuQJYlXBhgII4esDiYOcmqWQDn1IekrjQRFIdYV0HqVsFxff6cgU886LTFHpRsoKwNxjeE/Zeid4/osaYhJXMPnFDH00EukJMuvBAGRoP3wPWJheU8X6DHmH5OwzKZ1Pa+mkPudaLdn7pX6jH5Of1BaX1FdW38Ad0P2WPwQx6fArseRD+kK+orCUob82ge90I+WYr9LqTu0p2QP6oHMKygSyV0nV5P87gb0pCPNBom4L39sJjg6yxDTMjZpbkViruAhNBPCQZfSCIhmQSGACVOkGaFhDwk5BWIwR0HQR93/+j6xm1mVQLV3nizkw1cBa30GjrHOzCDCBbRJOC0XSai42us32lYI7pN/u/WuOTbrLF1p2GNcztLEIdv3ykuQAPHSOVxIYUPg7DrSgQOM6sO0wU6TBfXYbY/g71kkQwlrjm7NL4SYFyvq/eyO64IcwovMAf/CL9bj9vi+1AykH2nuZv4uF64eEJKPS5882CaHuNXuU72+S+t8dl4B+Hl7uC+MbqDf512B780zB3E8yi7Xn/W6ANHvV9w40RIxhw5Uq/EQ15hIOaAuR1/eqvF8/1ro+dbtxuF55s7xS1mKfvqq1RKuJva9ayxT5+1CLLM5d6tI13uwQlO4vbvL/gJai7T4gE4ozCehfo2UQ8gb1QPw+mKnFPu6VL7/VfVXLYNRHJyIs2Fw45wyMfVLm0bLDBBC5zsx1NnB8dzwXL3s9YoqMbUmg/WGVxh95sSZFcJT1hsdeEa/KOg4whTz+WtM81JsGswCXYOfJ2bToK9H5Ngw6/M5NmXy3i1JVWmKyVouDYeLVTYYgfPgl2Tokc6TrC90KCjhy6COY2ZsNpJr+n8DaySHeVYKxUP+I9EbwrXxgM7wiwP9kvUobi6g4Vxl7DhHcn7NWACKI/NHAMo7xo3Mii/ksSoXQjPMKvI4aC88ExamHg6r0NmceczaRUKwaN3fxD+aNjNALv7ELtP6XFRizAuilY5TWla5Tz2/fx49AcVCX+psFwlwQxWT8IrZZ6esvYZq7n6ytPoTImHiiwaeqgc9O1IfHE58qR5RjuttjwMr9G1dEKY9hLNQbdfWLkWf3o9vhiIrNDOjesHtJi7jLZ+9GlLDJZsA4pQMVvvB+g9qCrHsSSY8Vwt3eIEC6WAhjBGW/Wi/g/7TQQLbenBaQIdZYYQoVj3IqGqZ9T/gs5liCf/9JTDJsw5STg+ss3i02HNA8I2UYfN6PyTwThgNzAsYoFJg/EggvK4AZTCu+isIVucGqQksfHjdFBsPZZyqHmNKdhBKn8VLn1LYXFXW8q9s4u98VTWFZmMAU219HLbgL7ii8OtOGPjJjpAF1xcjlxW0cxN2XwbcwdCYXccUUFXamlASbg4MXDlJl4FyqwMGkaaGOykbk5JvRIN6Y54emI5WakgMrb1gkapaSsLlaQPtBUetVadlFBpabQBzSgEvjiKe7WRintppQz6Zi77GPADdBouEoBwXodV7ZfTync/Ztdd2qFFq+H66FGNeFP5p/GxeQ73+TW/
*/