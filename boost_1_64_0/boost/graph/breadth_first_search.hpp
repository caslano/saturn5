//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_BREADTH_FIRST_SEARCH_HPP
#define BOOST_GRAPH_BREADTH_FIRST_SEARCH_HPP

/*
  Breadth First Search Algorithm (Cormen, Leiserson, and Rivest p. 470)
*/
#include <boost/config.hpp>
#include <vector>
#include <boost/pending/queue.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/two_bit_color_map.hpp>
#include <boost/graph/detail/mpi_include.hpp>
#include <boost/concept/assert.hpp>

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / concepts.hpp >)

namespace boost
{

template < class Visitor, class Graph > struct BFSVisitorConcept
{
    void constraints()
    {
        BOOST_CONCEPT_ASSERT((CopyConstructibleConcept< Visitor >));
        vis.initialize_vertex(u, g);
        vis.discover_vertex(u, g);
        vis.examine_vertex(u, g);
        vis.examine_edge(e, g);
        vis.tree_edge(e, g);
        vis.non_tree_edge(e, g);
        vis.gray_target(e, g);
        vis.black_target(e, g);
        vis.finish_vertex(u, g);
    }
    Visitor vis;
    Graph g;
    typename graph_traits< Graph >::vertex_descriptor u;
    typename graph_traits< Graph >::edge_descriptor e;
};

// Multiple-source version
template < class IncidenceGraph, class Buffer, class BFSVisitor, class ColorMap,
    class SourceIterator >
void breadth_first_visit(const IncidenceGraph& g, SourceIterator sources_begin,
    SourceIterator sources_end, Buffer& Q, BFSVisitor vis, ColorMap color)
{
    BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< IncidenceGraph >));
    typedef graph_traits< IncidenceGraph > GTraits;
    typedef typename GTraits::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((BFSVisitorConcept< BFSVisitor, IncidenceGraph >));
    BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< ColorMap, Vertex >));
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;
    typename GTraits::out_edge_iterator ei, ei_end;

    for (; sources_begin != sources_end; ++sources_begin)
    {
        Vertex s = *sources_begin;
        put(color, s, Color::gray());
        vis.discover_vertex(s, g);
        Q.push(s);
    }
    while (!Q.empty())
    {
        Vertex u = Q.top();
        Q.pop();
        vis.examine_vertex(u, g);
        for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ++ei)
        {
            Vertex v = target(*ei, g);
            vis.examine_edge(*ei, g);
            ColorValue v_color = get(color, v);
            if (v_color == Color::white())
            {
                vis.tree_edge(*ei, g);
                put(color, v, Color::gray());
                vis.discover_vertex(v, g);
                Q.push(v);
            }
            else
            {
                vis.non_tree_edge(*ei, g);
                if (v_color == Color::gray())
                    vis.gray_target(*ei, g);
                else
                    vis.black_target(*ei, g);
            }
        } // end for
        put(color, u, Color::black());
        vis.finish_vertex(u, g);
    } // end while
} // breadth_first_visit

// Single-source version
template < class IncidenceGraph, class Buffer, class BFSVisitor,
    class ColorMap >
void breadth_first_visit(const IncidenceGraph& g,
    typename graph_traits< IncidenceGraph >::vertex_descriptor s, Buffer& Q,
    BFSVisitor vis, ColorMap color)
{
    typename graph_traits< IncidenceGraph >::vertex_descriptor sources[1]
        = { s };
    breadth_first_visit(g, sources, sources + 1, Q, vis, color);
}

template < class VertexListGraph, class SourceIterator, class Buffer,
    class BFSVisitor, class ColorMap >
void breadth_first_search(const VertexListGraph& g,
    SourceIterator sources_begin, SourceIterator sources_end, Buffer& Q,
    BFSVisitor vis, ColorMap color)
{
    // Initialization
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;
    typename boost::graph_traits< VertexListGraph >::vertex_iterator i, i_end;
    for (boost::tie(i, i_end) = vertices(g); i != i_end; ++i)
    {
        vis.initialize_vertex(*i, g);
        put(color, *i, Color::white());
    }
    breadth_first_visit(g, sources_begin, sources_end, Q, vis, color);
}

template < class VertexListGraph, class Buffer, class BFSVisitor,
    class ColorMap >
void breadth_first_search(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s, Buffer& Q,
    BFSVisitor vis, ColorMap color)
{
    typename graph_traits< VertexListGraph >::vertex_descriptor sources[1]
        = { s };
    breadth_first_search(g, sources, sources + 1, Q, vis, color);
}

namespace graph
{
    struct bfs_visitor_event_not_overridden
    {
    };
}

template < class Visitors = null_visitor > class bfs_visitor
{
public:
    bfs_visitor() {}
    bfs_visitor(Visitors vis) : m_vis(vis) {}

    template < class Vertex, class Graph >
    graph::bfs_visitor_event_not_overridden initialize_vertex(
        Vertex u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_initialize_vertex());
        return graph::bfs_visitor_event_not_overridden();
    }

    template < class Vertex, class Graph >
    graph::bfs_visitor_event_not_overridden discover_vertex(Vertex u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_discover_vertex());
        return graph::bfs_visitor_event_not_overridden();
    }

    template < class Vertex, class Graph >
    graph::bfs_visitor_event_not_overridden examine_vertex(Vertex u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_examine_vertex());
        return graph::bfs_visitor_event_not_overridden();
    }

    template < class Edge, class Graph >
    graph::bfs_visitor_event_not_overridden examine_edge(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, ::boost::on_examine_edge());
        return graph::bfs_visitor_event_not_overridden();
    }

    template < class Edge, class Graph >
    graph::bfs_visitor_event_not_overridden tree_edge(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, ::boost::on_tree_edge());
        return graph::bfs_visitor_event_not_overridden();
    }

    template < class Edge, class Graph >
    graph::bfs_visitor_event_not_overridden non_tree_edge(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, ::boost::on_non_tree_edge());
        return graph::bfs_visitor_event_not_overridden();
    }

    template < class Edge, class Graph >
    graph::bfs_visitor_event_not_overridden gray_target(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, ::boost::on_gray_target());
        return graph::bfs_visitor_event_not_overridden();
    }

    template < class Edge, class Graph >
    graph::bfs_visitor_event_not_overridden black_target(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, ::boost::on_black_target());
        return graph::bfs_visitor_event_not_overridden();
    }

    template < class Vertex, class Graph >
    graph::bfs_visitor_event_not_overridden finish_vertex(Vertex u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_finish_vertex());
        return graph::bfs_visitor_event_not_overridden();
    }

    BOOST_GRAPH_EVENT_STUB(on_initialize_vertex, bfs)
    BOOST_GRAPH_EVENT_STUB(on_discover_vertex, bfs)
    BOOST_GRAPH_EVENT_STUB(on_examine_vertex, bfs)
    BOOST_GRAPH_EVENT_STUB(on_examine_edge, bfs)
    BOOST_GRAPH_EVENT_STUB(on_tree_edge, bfs)
    BOOST_GRAPH_EVENT_STUB(on_non_tree_edge, bfs)
    BOOST_GRAPH_EVENT_STUB(on_gray_target, bfs)
    BOOST_GRAPH_EVENT_STUB(on_black_target, bfs)
    BOOST_GRAPH_EVENT_STUB(on_finish_vertex, bfs)

protected:
    Visitors m_vis;
};
template < class Visitors >
bfs_visitor< Visitors > make_bfs_visitor(Visitors vis)
{
    return bfs_visitor< Visitors >(vis);
}
typedef bfs_visitor<> default_bfs_visitor;

namespace detail
{

    template < class VertexListGraph, class ColorMap, class BFSVisitor, class P,
        class T, class R >
    void bfs_helper(VertexListGraph& g,
        typename graph_traits< VertexListGraph >::vertex_descriptor s,
        ColorMap color, BFSVisitor vis,
        const bgl_named_params< P, T, R >& params, boost::mpl::false_)
    {
        typedef graph_traits< VertexListGraph > Traits;
        // Buffer default
        typedef typename Traits::vertex_descriptor Vertex;
        typedef boost::queue< Vertex > queue_t;
        queue_t Q;
        breadth_first_search(g, s,
            choose_param(get_param(params, buffer_param_t()), boost::ref(Q))
                .get(),
            vis, color);
    }

#ifdef BOOST_GRAPH_USE_MPI
    template < class DistributedGraph, class ColorMap, class BFSVisitor,
        class P, class T, class R >
    void bfs_helper(DistributedGraph& g,
        typename graph_traits< DistributedGraph >::vertex_descriptor s,
        ColorMap color, BFSVisitor vis,
        const bgl_named_params< P, T, R >& params, boost::mpl::true_);
#endif // BOOST_GRAPH_USE_MPI

    //-------------------------------------------------------------------------
    // Choose between default color and color parameters. Using
    // function dispatching so that we don't require vertex index if
    // the color default is not being used.

    template < class ColorMap > struct bfs_dispatch
    {
        template < class VertexListGraph, class P, class T, class R >
        static void apply(VertexListGraph& g,
            typename graph_traits< VertexListGraph >::vertex_descriptor s,
            const bgl_named_params< P, T, R >& params, ColorMap color)
        {
            bfs_helper(g, s, color,
                choose_param(get_param(params, graph_visitor),
                    make_bfs_visitor(null_visitor())),
                params,
                boost::mpl::bool_<
                    boost::is_base_and_derived< distributed_graph_tag,
                        typename graph_traits<
                            VertexListGraph >::traversal_category >::value >());
        }
    };

    template <> struct bfs_dispatch< param_not_found >
    {
        template < class VertexListGraph, class P, class T, class R >
        static void apply(VertexListGraph& g,
            typename graph_traits< VertexListGraph >::vertex_descriptor s,
            const bgl_named_params< P, T, R >& params, param_not_found)
        {
            null_visitor null_vis;

            bfs_helper(g, s,
                make_two_bit_color_map(num_vertices(g),
                    choose_const_pmap(
                        get_param(params, vertex_index), g, vertex_index)),
                choose_param(get_param(params, graph_visitor),
                    make_bfs_visitor(null_vis)),
                params,
                boost::mpl::bool_<
                    boost::is_base_and_derived< distributed_graph_tag,
                        typename graph_traits<
                            VertexListGraph >::traversal_category >::value >());
        }
    };

} // namespace detail

#if 1
// Named Parameter Variant
template < class VertexListGraph, class P, class T, class R >
void breadth_first_search(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    const bgl_named_params< P, T, R >& params)
{
    // The graph is passed by *const* reference so that graph adaptors
    // (temporaries) can be passed into this function. However, the
    // graph is not really const since we may write to property maps
    // of the graph.
    VertexListGraph& ng = const_cast< VertexListGraph& >(g);
    typedef typename get_param_type< vertex_color_t,
        bgl_named_params< P, T, R > >::type C;
    detail::bfs_dispatch< C >::apply(
        ng, s, params, get_param(params, vertex_color));
}
#endif

// This version does not initialize colors, user has to.

template < class IncidenceGraph, class P, class T, class R >
void breadth_first_visit(const IncidenceGraph& g,
    typename graph_traits< IncidenceGraph >::vertex_descriptor s,
    const bgl_named_params< P, T, R >& params)
{
    // The graph is passed by *const* reference so that graph adaptors
    // (temporaries) can be passed into this function. However, the
    // graph is not really const since we may write to property maps
    // of the graph.
    IncidenceGraph& ng = const_cast< IncidenceGraph& >(g);

    typedef graph_traits< IncidenceGraph > Traits;
    // Buffer default
    typedef typename Traits::vertex_descriptor vertex_descriptor;
    typedef boost::queue< vertex_descriptor > queue_t;
    queue_t Q;

    breadth_first_visit(ng, s,
        choose_param(get_param(params, buffer_param_t()), boost::ref(Q)).get(),
        choose_param(
            get_param(params, graph_visitor), make_bfs_visitor(null_visitor())),
        choose_pmap(get_param(params, vertex_color), ng, vertex_color));
}

namespace graph
{
    namespace detail
    {
        template < typename Graph, typename Source >
        struct breadth_first_search_impl
        {
            typedef void result_type;
            template < typename ArgPack >
            void operator()(
                const Graph& g, const Source& source, const ArgPack& arg_pack)
            {
                using namespace boost::graph::keywords;
                typename boost::graph_traits< Graph >::vertex_descriptor
                    sources[1]
                    = { source };
                boost::queue<
                    typename boost::graph_traits< Graph >::vertex_descriptor >
                    Q;
                boost::breadth_first_search(g, &sources[0], &sources[1],
                    boost::unwrap_ref(arg_pack[_buffer | boost::ref(Q)]),
                    arg_pack[_visitor | make_bfs_visitor(null_visitor())],
                    boost::detail::make_color_map_from_arg_pack(g, arg_pack));
            }
        };
    }
    BOOST_GRAPH_MAKE_FORWARDING_FUNCTION(breadth_first_search, 2, 4)
}

#if 0
  // Named Parameter Variant
  BOOST_GRAPH_MAKE_OLD_STYLE_PARAMETER_FUNCTION(breadth_first_search, 2)
#endif

} // namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / breadth_first_search.hpp >)

#endif // BOOST_GRAPH_BREADTH_FIRST_SEARCH_HPP

/* breadth_first_search.hpp
Z4/vcZQe7G8Tr2QxWuRGdiiKbEnZzp5DLDgb5oou4Z3RSOnwoIZWqyH+2UTwbOPDI1Aa/Eb65W9w7447SRW9cNayZO+IJdEztyoU2JZVApJAfxO2XQzvfvEKIOXxUm/jQnr3R++8uJNev8/TuNeIc9t92itW4CQugiOf1KLYneELKVA+MzGQ+eMAfDbK0lSmB5Zx9NEhVSM/gfmGKyOYqsgaZKvA8uetq1B0y0hZo30wxNNIfwQMaSEIxrP8sRrZlLtN12H0ylHqvYGAWZnqbFUz8yA4M06s0LWisx1KrYvTMHNklE6zrsTIxsNpCFdTIvt43by/kc3DZBFpeiMbeYLH+3BaE0s08unS6NnnJxEiXL7XO+ev9j9Yq+ZPfoKLqCKHaEvgqo8TyZvJvQFUn2MyMim5Ay4+Mee+1nM0ho9fkvO94jlgOE+Ay78kPuX/trUpEegmSvejsMGRn41vHh0ftT9UO9OvjW4J6OeSAHAelWEFt/OmxF/UI+FXfnI8g+3qo37FDyGLRP5i7AOOAyYzcg/yl6UA44nb9HH+SqC0t1jPfrEonHxEzeRKq9TErpi9kRYcGwv8oAig45a61b2db/D2vCzgYlskcY088heTWvRW6zl92y++ylNegSC+rv+Cb4pCemJgOuWGmvT688cfK4gcM/4UfJ8BfFEhTArbSCoTdQwcpgHSNQl/IzhtN3TdcCLSZCSZVeFwpWyWL+ZiYcRucuU0FSjtLlHhwFkmbhrmKuscfUe7VBq6/Z19ubkLhQf7nV4adOYLLnjfXDQ4XEC4DrMoVfHE86me51IE8/OQ94OiY5I78EieiBHz47hi2zEFg8GIv7znXrP4eAj6o1fA6QOdSpTxaHR3sOR9SkTpOAUUqAtoKxEy/xXTolVdvhp620wdx7x4tbMXXWCG4wjNkP7JWs8PTjrxAnh13esbHRxsgrEKmhFDawkY05Eg9zt1LcaNtdlw9B55rzUAZ/pbBTRtRKC+DS8tc+8DeLf37Q6vpyOEd0aFU0y7BN6+FLVDixFCwI0fnh1wdRFjtWhnmM97k/FM7JMHo/5ienGd+IfDPhBdntk1NF2EaewH/lQzILZRNJxfWCpXuKbVH9aLnWCfRBv684k07HmySYz2UcRfJvv59Y6nEcygun5hC3U7t/WvuDueDQo6Eb+zSkabqWgeWaun9vdL8O+9dzK4LObeb+Kp7gjLRZ4EON/Rhlx54/3G83S/8aa8ZwiDWYtnLzFW1z5M5uyLLp+W7DDUsvlZpuOm/NVI+frFqHepXF0FyeG8+GllnVxPlkmuk0sAqIuM7AZxgf6FHxjk66HMpmtiFYznzpTqRRGcpu/F8jAMojS8pf8L7Ts8EhnrVkb7Ze+AmZLZB3fifbAUD7yv6AEj6n8/4qV+nZ2A5nrp2gxWii8aDU/0uvee3qCzvvoIGGszJejNhqjYdASsAxT+oeEpKFz4kAecRLMGmP8KYFPf6ivJaQnhg2+oR7BYjWgTxr8I78VStKJ3kTvcdd9suDkJ/9jy3+WE7n7mPVzbBxoN0Kr2rWkzVNNfxMmN7++cHqm9XjZ1vcUboazQ8vReUPaIzi8TuKhp6uFoQ9eM0n9xT7qvGKZVzciLy4X0tGyGYOWLGoim7GbJvmH251SPhrCkRRXelPN4l440Pj+8UDuN7EV7R3hCd/9F90Xz82YX800yzMeDq42rD5ufVxdlF82mK88Xhft3B1ePBqtrzV9r3OBqKv8oSQT3FxR2cCW+74S63HNbXftGU2LpVlCTpt3z8br+uJQf32giVU57VxXpWabXR9Y0Dn+zXPj7GJHfaDr6joDQ3z3qitizdT5e1ahHarc7/FUujIo=
*/