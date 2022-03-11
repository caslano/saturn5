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
#ifndef BOOST_GRAPH_UNDIRECTED_DFS_HPP
#define BOOST_GRAPH_UNDIRECTED_DFS_HPP

#include <boost/graph/depth_first_search.hpp>
#include <vector>
#include <boost/concept/assert.hpp>

namespace boost
{

namespace detail
{

// Define BOOST_RECURSIVE_DFS to use older, recursive version.
// It is retained for a while in order to perform performance
// comparison.
#ifndef BOOST_RECURSIVE_DFS

    template < typename IncidenceGraph, typename DFSVisitor,
        typename VertexColorMap, typename EdgeColorMap >
    void undir_dfv_impl(const IncidenceGraph& g,
        typename graph_traits< IncidenceGraph >::vertex_descriptor u,
        DFSVisitor& vis, VertexColorMap vertex_color, EdgeColorMap edge_color)
    {
        BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< IncidenceGraph >));
        BOOST_CONCEPT_ASSERT((DFSVisitorConcept< DFSVisitor, IncidenceGraph >));
        typedef
            typename graph_traits< IncidenceGraph >::vertex_descriptor Vertex;
        typedef typename graph_traits< IncidenceGraph >::edge_descriptor Edge;
        BOOST_CONCEPT_ASSERT(
            (ReadWritePropertyMapConcept< VertexColorMap, Vertex >));
        BOOST_CONCEPT_ASSERT(
            (ReadWritePropertyMapConcept< EdgeColorMap, Edge >));
        typedef
            typename property_traits< VertexColorMap >::value_type ColorValue;
        typedef
            typename property_traits< EdgeColorMap >::value_type EColorValue;
        BOOST_CONCEPT_ASSERT((ColorValueConcept< ColorValue >));
        BOOST_CONCEPT_ASSERT((ColorValueConcept< EColorValue >));
        typedef color_traits< ColorValue > Color;
        typedef color_traits< EColorValue > EColor;
        typedef typename graph_traits< IncidenceGraph >::out_edge_iterator Iter;
        typedef std::pair< Vertex,
            std::pair< boost::optional< Edge >, std::pair< Iter, Iter > > >
            VertexInfo;

        std::vector< VertexInfo > stack;

        put(vertex_color, u, Color::gray());
        vis.discover_vertex(u, g);
        stack.push_back(std::make_pair(
            u, std::make_pair(boost::optional< Edge >(), out_edges(u, g))));
        while (!stack.empty())
        {
            VertexInfo& back = stack.back();
            u = back.first;
            boost::optional< Edge > src_e = back.second.first;
            Iter ei = back.second.second.first,
                 ei_end = back.second.second.second;
            stack.pop_back();
            while (ei != ei_end)
            {
                Vertex v = target(*ei, g);
                vis.examine_edge(*ei, g);
                ColorValue v_color = get(vertex_color, v);
                EColorValue uv_color = get(edge_color, *ei);
                put(edge_color, *ei, EColor::black());
                if (v_color == Color::white())
                {
                    vis.tree_edge(*ei, g);
                    src_e = *ei;
                    stack.push_back(std::make_pair(u,
                        std::make_pair(src_e, std::make_pair(++ei, ei_end))));
                    u = v;
                    put(vertex_color, u, Color::gray());
                    vis.discover_vertex(u, g);
                    boost::tie(ei, ei_end) = out_edges(u, g);
                }
                else if (v_color == Color::gray())
                {
                    if (uv_color == EColor::white())
                        vis.back_edge(*ei, g);
                    call_finish_edge(vis, *ei, g);
                    ++ei;
                }
                else
                { // if (v_color == Color::black())
                    call_finish_edge(vis, *ei, g);
                    ++ei;
                }
            }
            put(vertex_color, u, Color::black());
            vis.finish_vertex(u, g);
            if (src_e)
                call_finish_edge(vis, src_e.get(), g);
        }
    }

#else // BOOST_RECURSIVE_DFS

    template < typename IncidenceGraph, typename DFSVisitor,
        typename VertexColorMap, typename EdgeColorMap >
    void undir_dfv_impl(const IncidenceGraph& g,
        typename graph_traits< IncidenceGraph >::vertex_descriptor u,
        DFSVisitor& vis, // pass-by-reference here, important!
        VertexColorMap vertex_color, EdgeColorMap edge_color)
    {
        BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< IncidenceGraph >));
        BOOST_CONCEPT_ASSERT((DFSVisitorConcept< DFSVisitor, IncidenceGraph >));
        typedef
            typename graph_traits< IncidenceGraph >::vertex_descriptor Vertex;
        typedef typename graph_traits< IncidenceGraph >::edge_descriptor Edge;
        BOOST_CONCEPT_ASSERT(
            (ReadWritePropertyMapConcept< VertexColorMap, Vertex >));
        BOOST_CONCEPT_ASSERT(
            (ReadWritePropertyMapConcept< EdgeColorMap, Edge >));
        typedef
            typename property_traits< VertexColorMap >::value_type ColorValue;
        typedef
            typename property_traits< EdgeColorMap >::value_type EColorValue;
        BOOST_CONCEPT_ASSERT((ColorValueConcept< ColorValue >));
        BOOST_CONCEPT_ASSERT((ColorValueConcept< EColorValue >));
        typedef color_traits< ColorValue > Color;
        typedef color_traits< EColorValue > EColor;
        typename graph_traits< IncidenceGraph >::out_edge_iterator ei, ei_end;

        put(vertex_color, u, Color::gray());
        vis.discover_vertex(u, g);
        for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ++ei)
        {
            Vertex v = target(*ei, g);
            vis.examine_edge(*ei, g);
            ColorValue v_color = get(vertex_color, v);
            EColorValue uv_color = get(edge_color, *ei);
            put(edge_color, *ei, EColor::black());
            if (v_color == Color::white())
            {
                vis.tree_edge(*ei, g);
                undir_dfv_impl(g, v, vis, vertex_color, edge_color);
            }
            else if (v_color == Color::gray() && uv_color == EColor::white())
                vis.back_edge(*ei, g);
            call_finish_edge(vis, *ei, g);
        }
        put(vertex_color, u, Color::black());
        vis.finish_vertex(u, g);
    }

#endif // ! BOOST_RECURSIVE_DFS

} // namespace detail

template < typename Graph, typename DFSVisitor, typename VertexColorMap,
    typename EdgeColorMap, typename Vertex >
void undirected_dfs(const Graph& g, DFSVisitor vis, VertexColorMap vertex_color,
    EdgeColorMap edge_color, Vertex start_vertex)
{
    BOOST_CONCEPT_ASSERT((DFSVisitorConcept< DFSVisitor, Graph >));
    BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< Graph >));

    typedef typename property_traits< VertexColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;

    typename graph_traits< Graph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        put(vertex_color, *ui, Color::white());
        vis.initialize_vertex(*ui, g);
    }
    typename graph_traits< Graph >::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        put(edge_color, *ei, Color::white());

    if (start_vertex != *vertices(g).first)
    {
        vis.start_vertex(start_vertex, g);
        detail::undir_dfv_impl(g, start_vertex, vis, vertex_color, edge_color);
    }

    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        ColorValue u_color = get(vertex_color, *ui);
        if (u_color == Color::white())
        {
            vis.start_vertex(*ui, g);
            detail::undir_dfv_impl(g, *ui, vis, vertex_color, edge_color);
        }
    }
}

template < typename Graph, typename DFSVisitor, typename VertexColorMap,
    typename EdgeColorMap >
void undirected_dfs(const Graph& g, DFSVisitor vis, VertexColorMap vertex_color,
    EdgeColorMap edge_color)
{
    undirected_dfs(g, vis, vertex_color, edge_color, *vertices(g).first);
}

namespace detail
{
    template < typename VertexColorMap > struct udfs_dispatch
    {

        template < typename Graph, typename Vertex, typename DFSVisitor,
            typename EdgeColorMap, typename P, typename T, typename R >
        static void apply(const Graph& g, DFSVisitor vis, Vertex start_vertex,
            const bgl_named_params< P, T, R >&, EdgeColorMap edge_color,
            VertexColorMap vertex_color)
        {
            undirected_dfs(g, vis, vertex_color, edge_color, start_vertex);
        }
    };

    template <> struct udfs_dispatch< param_not_found >
    {
        template < typename Graph, typename Vertex, typename DFSVisitor,
            typename EdgeColorMap, typename P, typename T, typename R >
        static void apply(const Graph& g, DFSVisitor vis, Vertex start_vertex,
            const bgl_named_params< P, T, R >& params, EdgeColorMap edge_color,
            param_not_found)
        {
            std::vector< default_color_type > color_vec(num_vertices(g));
            default_color_type c = white_color; // avoid warning about un-init
            undirected_dfs(g, vis,
                make_iterator_property_map(color_vec.begin(),
                    choose_const_pmap(
                        get_param(params, vertex_index), g, vertex_index),
                    c),
                edge_color, start_vertex);
        }
    };

} // namespace detail

// Named Parameter Variant
template < typename Graph, typename P, typename T, typename R >
void undirected_dfs(const Graph& g, const bgl_named_params< P, T, R >& params)
{
    typedef typename get_param_type< vertex_color_t,
        bgl_named_params< P, T, R > >::type C;
    detail::udfs_dispatch< C >::apply(g,
        choose_param(
            get_param(params, graph_visitor), make_dfs_visitor(null_visitor())),
        choose_param(get_param(params, root_vertex_t()), *vertices(g).first),
        params, get_param(params, edge_color), get_param(params, vertex_color));
}

template < typename IncidenceGraph, typename DFSVisitor,
    typename VertexColorMap, typename EdgeColorMap >
void undirected_depth_first_visit(const IncidenceGraph& g,
    typename graph_traits< IncidenceGraph >::vertex_descriptor u,
    DFSVisitor vis, VertexColorMap vertex_color, EdgeColorMap edge_color)
{
    detail::undir_dfv_impl(g, u, vis, vertex_color, edge_color);
}

} // namespace boost

#endif

/* undirected_dfs.hpp
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
*/