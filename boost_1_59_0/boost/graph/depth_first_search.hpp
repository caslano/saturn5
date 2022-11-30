//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2003 Bruce Barr
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

// Nonrecursive implementation of depth_first_visit_impl submitted by
// Bruce Barr, schmoost <at> yahoo.com, May/June 2003.
#ifndef BOOST_GRAPH_RECURSIVE_DFS_HPP
#define BOOST_GRAPH_RECURSIVE_DFS_HPP

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/detail/mpi_include.hpp>
#include <boost/ref.hpp>
#include <boost/implicit_cast.hpp>
#include <boost/optional.hpp>
#include <boost/parameter.hpp>
#include <boost/concept/assert.hpp>
#include <boost/tti/has_member_function.hpp>

#include <vector>
#include <utility>

namespace boost
{

template < class Visitor, class Graph > class DFSVisitorConcept
{
public:
    void constraints()
    {
        BOOST_CONCEPT_ASSERT((CopyConstructibleConcept< Visitor >));
        vis.initialize_vertex(u, g);
        vis.start_vertex(u, g);
        vis.discover_vertex(u, g);
        vis.examine_edge(e, g);
        vis.tree_edge(e, g);
        vis.back_edge(e, g);
        vis.forward_or_cross_edge(e, g);
        // vis.finish_edge(e, g); // Optional for user
        vis.finish_vertex(u, g);
    }

private:
    Visitor vis;
    Graph g;
    typename graph_traits< Graph >::vertex_descriptor u;
    typename graph_traits< Graph >::edge_descriptor e;
};

namespace detail
{

    struct nontruth2
    {
        template < class T, class T2 >
        bool operator()(const T&, const T2&) const
        {
            return false;
        }
    };

    BOOST_TTI_HAS_MEMBER_FUNCTION(finish_edge)

    template < bool IsCallable > struct do_call_finish_edge
    {
        template < typename E, typename G, typename Vis >
        static void call_finish_edge(Vis& vis, E e, const G& g)
        {
            vis.finish_edge(e, g);
        }
    };

    template <> struct do_call_finish_edge< false >
    {
        template < typename E, typename G, typename Vis >
        static void call_finish_edge(Vis&, E, const G&)
        {
        }
    };

    template < typename E, typename G, typename Vis >
    void call_finish_edge(Vis& vis, E e, const G& g)
    { // Only call if method exists
#if ((defined(__GNUC__) && (__GNUC__ > 4)               \
         || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 9))) \
    || defined(__clang__)                               \
    || (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1200)))
        do_call_finish_edge< has_member_function_finish_edge< Vis, void,
            boost::mpl::vector< E, const G& > >::value >::call_finish_edge(vis,
            e, g);
#else
        do_call_finish_edge< has_member_function_finish_edge< Vis,
            void >::value >::call_finish_edge(vis, e, g);
#endif
    }

// Define BOOST_RECURSIVE_DFS to use older, recursive version.
// It is retained for a while in order to perform performance
// comparison.
#ifndef BOOST_RECURSIVE_DFS

    // If the vertex u and the iterators ei and ei_end are thought of as the
    // context of the algorithm, each push and pop from the stack could
    // be thought of as a context shift.
    // Each pass through "while (ei != ei_end)" may refer to the out-edges of
    // an entirely different vertex, because the context of the algorithm
    // shifts every time a white adjacent vertex is discovered.
    // The corresponding context shift back from the adjacent vertex occurs
    // after all of its out-edges have been examined.
    //
    // See https://lists.boost.org/Archives/boost/2003/06/49265.php for FAQ.

    template < class IncidenceGraph, class DFSVisitor, class ColorMap,
        class TerminatorFunc >
    void depth_first_visit_impl(const IncidenceGraph& g,
        typename graph_traits< IncidenceGraph >::vertex_descriptor u,
        DFSVisitor& vis, ColorMap color, TerminatorFunc func = TerminatorFunc())
    {
        BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< IncidenceGraph >));
        BOOST_CONCEPT_ASSERT((DFSVisitorConcept< DFSVisitor, IncidenceGraph >));
        typedef
            typename graph_traits< IncidenceGraph >::vertex_descriptor Vertex;
        typedef typename graph_traits< IncidenceGraph >::edge_descriptor Edge;
        BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< ColorMap, Vertex >));
        typedef typename property_traits< ColorMap >::value_type ColorValue;
        BOOST_CONCEPT_ASSERT((ColorValueConcept< ColorValue >));
        typedef color_traits< ColorValue > Color;
        typedef typename graph_traits< IncidenceGraph >::out_edge_iterator Iter;
        typedef std::pair< Vertex,
            std::pair< boost::optional< Edge >, std::pair< Iter, Iter > > >
            VertexInfo;

        boost::optional< Edge > src_e;
        Iter ei, ei_end;
        std::vector< VertexInfo > stack;

        // Possible optimization for vector
        // stack.reserve(num_vertices(g));

        put(color, u, Color::gray());
        vis.discover_vertex(u, g);
        boost::tie(ei, ei_end) = out_edges(u, g);
        if (func(u, g))
        {
            // If this vertex terminates the search, we push empty range
            stack.push_back(std::make_pair(u,
                std::make_pair(boost::optional< Edge >(),
                    std::make_pair(ei_end, ei_end))));
        }
        else
        {
            stack.push_back(std::make_pair(u,
                std::make_pair(
                    boost::optional< Edge >(), std::make_pair(ei, ei_end))));
        }
        while (!stack.empty())
        {
            VertexInfo& back = stack.back();
            u = back.first;
            src_e = back.second.first;
            boost::tie(ei, ei_end) = back.second.second;
            stack.pop_back();
            // finish_edge has to be called here, not after the
            // loop. Think of the pop as the return from a recursive call.
            if (src_e)
            {
                call_finish_edge(vis, src_e.get(), g);
            }
            while (ei != ei_end)
            {
                Vertex v = target(*ei, g);
                vis.examine_edge(*ei, g);
                ColorValue v_color = get(color, v);
                if (v_color == Color::white())
                {
                    vis.tree_edge(*ei, g);
                    src_e = *ei;
                    stack.push_back(std::make_pair(u,
                        std::make_pair(src_e, std::make_pair(++ei, ei_end))));
                    u = v;
                    put(color, u, Color::gray());
                    vis.discover_vertex(u, g);
                    boost::tie(ei, ei_end) = out_edges(u, g);
                    if (func(u, g))
                    {
                        ei = ei_end;
                    }
                }
                else
                {
                    if (v_color == Color::gray())
                    {
                        vis.back_edge(*ei, g);
                    }
                    else
                    {
                        vis.forward_or_cross_edge(*ei, g);
                    }
                    call_finish_edge(vis, *ei, g);
                    ++ei;
                }
            }
            put(color, u, Color::black());
            vis.finish_vertex(u, g);
        }
    }

#else // BOOST_RECURSIVE_DFS is defined

    template < class IncidenceGraph, class DFSVisitor, class ColorMap,
        class TerminatorFunc >
    void depth_first_visit_impl(const IncidenceGraph& g,
        typename graph_traits< IncidenceGraph >::vertex_descriptor u,
        DFSVisitor& vis, // pass-by-reference here, important!
        ColorMap color, TerminatorFunc func)
    {
        BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< IncidenceGraph >));
        BOOST_CONCEPT_ASSERT((DFSVisitorConcept< DFSVisitor, IncidenceGraph >));
        typedef
            typename graph_traits< IncidenceGraph >::vertex_descriptor Vertex;
        BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< ColorMap, Vertex >));
        typedef typename property_traits< ColorMap >::value_type ColorValue;
        BOOST_CONCEPT_ASSERT((ColorValueConcept< ColorValue >));
        typedef color_traits< ColorValue > Color;
        typename graph_traits< IncidenceGraph >::out_edge_iterator ei, ei_end;

        put(color, u, Color::gray());
        vis.discover_vertex(u, g);

        if (!func(u, g))
            for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ++ei)
            {
                Vertex v = target(*ei, g);
                vis.examine_edge(*ei, g);
                ColorValue v_color = get(color, v);
                if (v_color == Color::white())
                {
                    vis.tree_edge(*ei, g);
                    depth_first_visit_impl(g, v, vis, color, func);
                }
                else if (v_color == Color::gray())
                    vis.back_edge(*ei, g);
                else
                    vis.forward_or_cross_edge(*ei, g);
                call_finish_edge(vis, *ei, g);
            }
        put(color, u, Color::black());
        vis.finish_vertex(u, g);
    }

#endif

} // namespace detail

template < class VertexListGraph, class DFSVisitor, class ColorMap >
void depth_first_search(const VertexListGraph& g, DFSVisitor vis,
    ColorMap color,
    typename graph_traits< VertexListGraph >::vertex_descriptor start_vertex)
{
    typedef typename graph_traits< VertexListGraph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((DFSVisitorConcept< DFSVisitor, VertexListGraph >));
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;

    typename graph_traits< VertexListGraph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        Vertex u = implicit_cast< Vertex >(*ui);
        put(color, u, Color::white());
        vis.initialize_vertex(u, g);
    }

    if (start_vertex != detail::get_default_starting_vertex(g))
    {
        vis.start_vertex(start_vertex, g);
        detail::depth_first_visit_impl(
            g, start_vertex, vis, color, detail::nontruth2());
    }

    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        Vertex u = implicit_cast< Vertex >(*ui);
        ColorValue u_color = get(color, u);
        if (u_color == Color::white())
        {
            vis.start_vertex(u, g);
            detail::depth_first_visit_impl(
                g, u, vis, color, detail::nontruth2());
        }
    }
}

template < class VertexListGraph, class DFSVisitor, class ColorMap >
void depth_first_search(
    const VertexListGraph& g, DFSVisitor vis, ColorMap color)
{
    typedef typename boost::graph_traits< VertexListGraph >::vertex_iterator vi;
    std::pair< vi, vi > verts = vertices(g);
    if (verts.first == verts.second)
        return;

    depth_first_search(g, vis, color, detail::get_default_starting_vertex(g));
}

template < class Visitors = null_visitor > class dfs_visitor
{
public:
    dfs_visitor() {}
    dfs_visitor(Visitors vis) : m_vis(vis) {}

    template < class Vertex, class Graph >
    void initialize_vertex(Vertex u, const Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_initialize_vertex());
    }
    template < class Vertex, class Graph >
    void start_vertex(Vertex u, const Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_start_vertex());
    }
    template < class Vertex, class Graph >
    void discover_vertex(Vertex u, const Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_discover_vertex());
    }
    template < class Edge, class Graph >
    void examine_edge(Edge u, const Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_examine_edge());
    }
    template < class Edge, class Graph > void tree_edge(Edge u, const Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_tree_edge());
    }
    template < class Edge, class Graph > void back_edge(Edge u, const Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_back_edge());
    }
    template < class Edge, class Graph >
    void forward_or_cross_edge(Edge u, const Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_forward_or_cross_edge());
    }
    template < class Edge, class Graph >
    void finish_edge(Edge u, const Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_finish_edge());
    }
    template < class Vertex, class Graph >
    void finish_vertex(Vertex u, const Graph& g)
    {
        invoke_visitors(m_vis, u, g, ::boost::on_finish_vertex());
    }

    BOOST_GRAPH_EVENT_STUB(on_initialize_vertex, dfs)
    BOOST_GRAPH_EVENT_STUB(on_start_vertex, dfs)
    BOOST_GRAPH_EVENT_STUB(on_discover_vertex, dfs)
    BOOST_GRAPH_EVENT_STUB(on_examine_edge, dfs)
    BOOST_GRAPH_EVENT_STUB(on_tree_edge, dfs)
    BOOST_GRAPH_EVENT_STUB(on_back_edge, dfs)
    BOOST_GRAPH_EVENT_STUB(on_forward_or_cross_edge, dfs)
    BOOST_GRAPH_EVENT_STUB(on_finish_edge, dfs)
    BOOST_GRAPH_EVENT_STUB(on_finish_vertex, dfs)

protected:
    Visitors m_vis;
};
template < class Visitors >
dfs_visitor< Visitors > make_dfs_visitor(Visitors vis)
{
    return dfs_visitor< Visitors >(vis);
}
typedef dfs_visitor<> default_dfs_visitor;

// Boost.Parameter named parameter variant
namespace graph
{
    namespace detail
    {
        template < typename Graph > struct depth_first_search_impl
        {
            typedef void result_type;
            template < typename ArgPack >
            void operator()(const Graph& g, const ArgPack& arg_pack) const
            {
                using namespace boost::graph::keywords;
                boost::depth_first_search(g,
                    arg_pack[_visitor | make_dfs_visitor(null_visitor())],
                    boost::detail::make_color_map_from_arg_pack(g, arg_pack),
                    arg_pack[_root_vertex
                        || boost::detail::get_default_starting_vertex_t<
                            Graph >(g)]);
            }
        };
    }
    BOOST_GRAPH_MAKE_FORWARDING_FUNCTION(depth_first_search, 1, 4)
}

BOOST_GRAPH_MAKE_OLD_STYLE_PARAMETER_FUNCTION(depth_first_search, 1)

template < class IncidenceGraph, class DFSVisitor, class ColorMap >
void depth_first_visit(const IncidenceGraph& g,
    typename graph_traits< IncidenceGraph >::vertex_descriptor u,
    DFSVisitor vis, ColorMap color)
{
    vis.start_vertex(u, g);
    detail::depth_first_visit_impl(g, u, vis, color, detail::nontruth2());
}

template < class IncidenceGraph, class DFSVisitor, class ColorMap,
    class TerminatorFunc >
void depth_first_visit(const IncidenceGraph& g,
    typename graph_traits< IncidenceGraph >::vertex_descriptor u,
    DFSVisitor vis, ColorMap color, TerminatorFunc func = TerminatorFunc())
{
    vis.start_vertex(u, g);
    detail::depth_first_visit_impl(g, u, vis, color, func);
}
} // namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/depth_first_search.hpp>)

#endif

/* depth_first_search.hpp
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
*/