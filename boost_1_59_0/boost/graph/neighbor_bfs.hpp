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
#ifndef BOOST_GRAPH_NEIGHBOR_BREADTH_FIRST_SEARCH_HPP
#define BOOST_GRAPH_NEIGHBOR_BREADTH_FIRST_SEARCH_HPP

/*
  Neighbor Breadth First Search
  Like BFS, but traverses in-edges as well as out-edges.
  (for directed graphs only. use normal BFS for undirected graphs)
*/
#include <boost/config.hpp>
#include <boost/ref.hpp>
#include <vector>
#include <boost/pending/queue.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{

template < class Visitor, class Graph > struct NeighborBFSVisitorConcept
{
    void constraints()
    {
        BOOST_CONCEPT_ASSERT((CopyConstructibleConcept< Visitor >));
        vis.initialize_vertex(u, g);
        vis.discover_vertex(u, g);
        vis.examine_vertex(u, g);
        vis.examine_out_edge(e, g);
        vis.examine_in_edge(e, g);
        vis.tree_out_edge(e, g);
        vis.tree_in_edge(e, g);
        vis.non_tree_out_edge(e, g);
        vis.non_tree_in_edge(e, g);
        vis.gray_target(e, g);
        vis.black_target(e, g);
        vis.gray_source(e, g);
        vis.black_source(e, g);
        vis.finish_vertex(u, g);
    }
    Visitor vis;
    Graph g;
    typename graph_traits< Graph >::vertex_descriptor u;
    typename graph_traits< Graph >::edge_descriptor e;
};

template < class Visitors = null_visitor > class neighbor_bfs_visitor
{
public:
    neighbor_bfs_visitor(Visitors vis = Visitors()) : m_vis(vis) {}

    template < class Vertex, class Graph >
    void initialize_vertex(Vertex u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_initialize_vertex());
    }
    template < class Vertex, class Graph >
    void discover_vertex(Vertex u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_discover_vertex());
    }
    template < class Vertex, class Graph >
    void examine_vertex(Vertex u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_examine_vertex());
    }
    template < class Edge, class Graph > void examine_out_edge(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, on_examine_edge());
    }
    template < class Edge, class Graph > void tree_out_edge(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, on_tree_edge());
    }
    template < class Edge, class Graph >
    void non_tree_out_edge(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, on_non_tree_edge());
    }
    template < class Edge, class Graph > void gray_target(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, on_gray_target());
    }
    template < class Edge, class Graph > void black_target(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, on_black_target());
    }
    template < class Edge, class Graph > void examine_in_edge(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, on_examine_edge());
    }
    template < class Edge, class Graph > void tree_in_edge(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, on_tree_edge());
    }
    template < class Edge, class Graph > void non_tree_in_edge(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, on_non_tree_edge());
    }
    template < class Edge, class Graph > void gray_source(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, on_gray_target());
    }
    template < class Edge, class Graph > void black_source(Edge e, Graph& g)
    {
        invoke_visitors(m_vis, e, g, on_black_target());
    }
    template < class Vertex, class Graph >
    void finish_vertex(Vertex u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_finish_vertex());
    }

protected:
    Visitors m_vis;
};

template < class Visitors >
neighbor_bfs_visitor< Visitors > make_neighbor_bfs_visitor(Visitors vis)
{
    return neighbor_bfs_visitor< Visitors >(vis);
}

namespace detail
{

    template < class BidirectionalGraph, class Buffer, class BFSVisitor,
        class ColorMap >
    void neighbor_bfs_impl(const BidirectionalGraph& g,
        typename graph_traits< BidirectionalGraph >::vertex_descriptor s,
        Buffer& Q, BFSVisitor vis, ColorMap color)

    {
        BOOST_CONCEPT_ASSERT((BidirectionalGraphConcept< BidirectionalGraph >));
        typedef graph_traits< BidirectionalGraph > GTraits;
        typedef typename GTraits::vertex_descriptor Vertex;
        typedef typename GTraits::edge_descriptor Edge;
        BOOST_CONCEPT_ASSERT(
            (NeighborBFSVisitorConcept< BFSVisitor, BidirectionalGraph >));
        BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< ColorMap, Vertex >));
        typedef typename property_traits< ColorMap >::value_type ColorValue;
        typedef color_traits< ColorValue > Color;

        put(color, s, Color::gray());
        vis.discover_vertex(s, g);
        Q.push(s);
        while (!Q.empty())
        {
            Vertex u = Q.top();
            Q.pop(); // pop before push to avoid problem if Q is priority_queue.
            vis.examine_vertex(u, g);

            typename GTraits::out_edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ++ei)
            {
                Edge e = *ei;
                vis.examine_out_edge(e, g);
                Vertex v = target(e, g);
                ColorValue v_color = get(color, v);
                if (v_color == Color::white())
                {
                    vis.tree_out_edge(e, g);
                    put(color, v, Color::gray());
                    vis.discover_vertex(v, g);
                    Q.push(v);
                }
                else
                {
                    vis.non_tree_out_edge(e, g);
                    if (v_color == Color::gray())
                        vis.gray_target(e, g);
                    else
                        vis.black_target(e, g);
                }
            } // for out-edges

            typename GTraits::in_edge_iterator in_ei, in_ei_end;
            for (boost::tie(in_ei, in_ei_end) = in_edges(u, g);
                 in_ei != in_ei_end; ++in_ei)
            {
                Edge e = *in_ei;
                vis.examine_in_edge(e, g);
                Vertex v = source(e, g);
                ColorValue v_color = get(color, v);
                if (v_color == Color::white())
                {
                    vis.tree_in_edge(e, g);
                    put(color, v, Color::gray());
                    vis.discover_vertex(v, g);
                    Q.push(v);
                }
                else
                {
                    vis.non_tree_in_edge(e, g);
                    if (v_color == Color::gray())
                        vis.gray_source(e, g);
                    else
                        vis.black_source(e, g);
                }
            } // for in-edges

            put(color, u, Color::black());
            vis.finish_vertex(u, g);
        } // while
    }

    template < class VertexListGraph, class ColorMap, class BFSVisitor, class P,
        class T, class R >
    void neighbor_bfs_helper(VertexListGraph& g,
        typename graph_traits< VertexListGraph >::vertex_descriptor s,
        ColorMap color, BFSVisitor vis,
        const bgl_named_params< P, T, R >& params)
    {
        typedef graph_traits< VertexListGraph > Traits;
        // Buffer default
        typedef typename Traits::vertex_descriptor Vertex;
        typedef boost::queue< Vertex > queue_t;
        queue_t Q;
        // Initialization
        typedef typename property_traits< ColorMap >::value_type ColorValue;
        typedef color_traits< ColorValue > Color;
        typename boost::graph_traits< VertexListGraph >::vertex_iterator i,
            i_end;
        for (boost::tie(i, i_end) = vertices(g); i != i_end; ++i)
        {
            put(color, *i, Color::white());
            vis.initialize_vertex(*i, g);
        }
        neighbor_bfs_impl(g, s,
            choose_param(get_param(params, buffer_param_t()), boost::ref(Q))
                .get(),
            vis, color);
    }

    //-------------------------------------------------------------------------
    // Choose between default color and color parameters. Using
    // function dispatching so that we don't require vertex index if
    // the color default is not being used.

    template < class ColorMap > struct neighbor_bfs_dispatch
    {
        template < class VertexListGraph, class P, class T, class R >
        static void apply(VertexListGraph& g,
            typename graph_traits< VertexListGraph >::vertex_descriptor s,
            const bgl_named_params< P, T, R >& params, ColorMap color)
        {
            neighbor_bfs_helper(g, s, color,
                choose_param(get_param(params, graph_visitor),
                    make_neighbor_bfs_visitor(null_visitor())),
                params);
        }
    };

    template <> struct neighbor_bfs_dispatch< param_not_found >
    {
        template < class VertexListGraph, class P, class T, class R >
        static void apply(VertexListGraph& g,
            typename graph_traits< VertexListGraph >::vertex_descriptor s,
            const bgl_named_params< P, T, R >& params, param_not_found)
        {
            std::vector< default_color_type > color_vec(num_vertices(g));
            null_visitor null_vis;

            neighbor_bfs_helper(g, s,
                make_iterator_property_map(color_vec.begin(),
                    choose_const_pmap(
                        get_param(params, vertex_index), g, vertex_index),
                    color_vec[0]),
                choose_param(get_param(params, graph_visitor),
                    make_neighbor_bfs_visitor(null_vis)),
                params);
        }
    };

} // namespace detail

// Named Parameter Variant
template < class VertexListGraph, class P, class T, class R >
void neighbor_breadth_first_search(const VertexListGraph& g,
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
    detail::neighbor_bfs_dispatch< C >::apply(
        ng, s, params, get_param(params, vertex_color));
}

// This version does not initialize colors, user has to.

template < class IncidenceGraph, class P, class T, class R >
void neighbor_breadth_first_visit(IncidenceGraph& g,
    typename graph_traits< IncidenceGraph >::vertex_descriptor s,
    const bgl_named_params< P, T, R >& params)
{
    typedef graph_traits< IncidenceGraph > Traits;
    // Buffer default
    typedef boost::queue< typename Traits::vertex_descriptor > queue_t;
    queue_t Q;

    detail::neighbor_bfs_impl(g, s,
        choose_param(get_param(params, buffer_param_t()), boost::ref(Q)).get(),
        choose_param(get_param(params, graph_visitor),
            make_neighbor_bfs_visitor(null_visitor())),
        choose_pmap(get_param(params, vertex_color), g, vertex_color));
}

} // namespace boost

#endif // BOOST_GRAPH_NEIGHBOR_BREADTH_FIRST_SEARCH_HPP

/* neighbor_bfs.hpp
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
*/