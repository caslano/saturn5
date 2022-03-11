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