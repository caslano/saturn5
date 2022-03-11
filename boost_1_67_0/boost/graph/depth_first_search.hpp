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

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / depth_first_search.hpp >)

#endif

/* depth_first_search.hpp
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
*/