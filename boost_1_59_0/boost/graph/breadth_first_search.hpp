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

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/concepts.hpp>)

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

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/breadth_first_search.hpp>)

#endif // BOOST_GRAPH_BREADTH_FIRST_SEARCH_HPP

/* breadth_first_search.hpp
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
*/