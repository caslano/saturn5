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
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
*/