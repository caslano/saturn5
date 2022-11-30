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
#ifndef BOOST_GRAPH_UTILITY_HPP
#define BOOST_GRAPH_UTILITY_HPP

#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <boost/config.hpp>
#include <boost/tuple/tuple.hpp>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/pending/container_traits.hpp>
#include <boost/graph/depth_first_search.hpp>
// iota moved to detail/algorithm.hpp
#include <boost/detail/algorithm.hpp>

namespace boost
{

// Provide an undirected graph interface alternative to the
// the source() and target() edge functions.
template < class UndirectedGraph >
inline std::pair< typename graph_traits< UndirectedGraph >::vertex_descriptor,
    typename graph_traits< UndirectedGraph >::vertex_descriptor >
incident(typename graph_traits< UndirectedGraph >::edge_descriptor e,
    UndirectedGraph& g)
{
    return std::make_pair(source(e, g), target(e, g));
}

// Provide an undirected graph interface alternative
// to the out_edges() function.
template < class Graph >
inline std::pair< typename graph_traits< Graph >::out_edge_iterator,
    typename graph_traits< Graph >::out_edge_iterator >
incident_edges(typename graph_traits< Graph >::vertex_descriptor u, Graph& g)
{
    return out_edges(u, g);
}

template < class Graph >
inline typename graph_traits< Graph >::vertex_descriptor opposite(
    typename graph_traits< Graph >::edge_descriptor e,
    typename graph_traits< Graph >::vertex_descriptor v, const Graph& g)
{
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;
    if (v == source(e, g))
        return target(e, g);
    else if (v == target(e, g))
        return source(e, g);
    else
        return vertex_descriptor();
}

//===========================================================================
// Some handy predicates

template < typename Vertex, typename Graph > struct incident_from_predicate
{
    incident_from_predicate(Vertex u, const Graph& g) : m_u(u), m_g(g) {}
    template < class Edge > bool operator()(const Edge& e) const
    {
        return source(e, m_g) == m_u;
    }
    Vertex m_u;
    const Graph& m_g;
};
template < typename Vertex, typename Graph >
inline incident_from_predicate< Vertex, Graph > incident_from(
    Vertex u, const Graph& g)
{
    return incident_from_predicate< Vertex, Graph >(u, g);
}

template < typename Vertex, typename Graph > struct incident_to_predicate
{
    incident_to_predicate(Vertex u, const Graph& g) : m_u(u), m_g(g) {}
    template < class Edge > bool operator()(const Edge& e) const
    {
        return target(e, m_g) == m_u;
    }
    Vertex m_u;
    const Graph& m_g;
};
template < typename Vertex, typename Graph >
inline incident_to_predicate< Vertex, Graph > incident_to(
    Vertex u, const Graph& g)
{
    return incident_to_predicate< Vertex, Graph >(u, g);
}

template < typename Vertex, typename Graph > struct incident_on_predicate
{
    incident_on_predicate(Vertex u, const Graph& g) : m_u(u), m_g(g) {}
    template < class Edge > bool operator()(const Edge& e) const
    {
        return source(e, m_g) == m_u || target(e, m_g) == m_u;
    }
    Vertex m_u;
    const Graph& m_g;
};
template < typename Vertex, typename Graph >
inline incident_on_predicate< Vertex, Graph > incident_on(
    Vertex u, const Graph& g)
{
    return incident_on_predicate< Vertex, Graph >(u, g);
}

template < typename Vertex, typename Graph > struct connects_predicate
{
    connects_predicate(Vertex u, Vertex v, const Graph& g)
    : m_u(u), m_v(v), m_g(g)
    {
    }
    template < class Edge > bool operator()(const Edge& e) const
    {
        if (is_directed(m_g))
            return source(e, m_g) == m_u && target(e, m_g) == m_v;
        else
            return (source(e, m_g) == m_u && target(e, m_g) == m_v)
                || (source(e, m_g) == m_v && target(e, m_g) == m_u);
    }
    Vertex m_u, m_v;
    const Graph& m_g;
};
template < typename Vertex, typename Graph >
inline connects_predicate< Vertex, Graph > connects(
    Vertex u, Vertex v, const Graph& g)
{
    return connects_predicate< Vertex, Graph >(u, v, g);
}

// Need to convert all of these printing functions to take an ostream object
// -JGS

template < class IncidenceGraph, class Name >
void print_in_edges(
    const IncidenceGraph& G, Name name, std::ostream& os = std::cout)
{
    typename graph_traits< IncidenceGraph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(G); ui != ui_end; ++ui)
    {
        os << get(name, *ui) << " <-- ";
        typename graph_traits< IncidenceGraph >::in_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = in_edges(*ui, G); ei != ei_end; ++ei)
            os << get(name, source(*ei, G)) << " ";
        os << '\n';
    }
}

template < class IncidenceGraph, class Name >
void print_graph_dispatch(const IncidenceGraph& G, Name name, directed_tag,
    std::ostream& os = std::cout)
{
    typename graph_traits< IncidenceGraph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(G); ui != ui_end; ++ui)
    {
        os << get(name, *ui) << " --> ";
        typename graph_traits< IncidenceGraph >::out_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = out_edges(*ui, G); ei != ei_end; ++ei)
            os << get(name, target(*ei, G)) << " ";
        os << '\n';
    }
}
template < class IncidenceGraph, class Name >
void print_graph_dispatch(const IncidenceGraph& G, Name name, undirected_tag,
    std::ostream& os = std::cout)
{
    typename graph_traits< IncidenceGraph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(G); ui != ui_end; ++ui)
    {
        os << get(name, *ui) << " <--> ";
        typename graph_traits< IncidenceGraph >::out_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = out_edges(*ui, G); ei != ei_end; ++ei)
            os << get(name, target(*ei, G)) << " ";
        os << '\n';
    }
}
template < class IncidenceGraph, class Name >
void print_graph(
    const IncidenceGraph& G, Name name, std::ostream& os = std::cout)
{
    typedef typename graph_traits< IncidenceGraph >::directed_category Cat;
    print_graph_dispatch(G, name, Cat(), os);
}
template < class IncidenceGraph >
void print_graph(const IncidenceGraph& G, std::ostream& os = std::cout)
{
    print_graph(G, get(vertex_index, G), os);
}

template < class EdgeListGraph, class Name >
void print_edges(
    const EdgeListGraph& G, Name name, std::ostream& os = std::cout)
{
    typename graph_traits< EdgeListGraph >::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei)
        os << "(" << get(name, source(*ei, G)) << ","
           << get(name, target(*ei, G)) << ") ";
    os << '\n';
}

template < class EdgeListGraph, class VertexName, class EdgeName >
void print_edges2(const EdgeListGraph& G, VertexName vname, EdgeName ename,
    std::ostream& os = std::cout)
{
    typename graph_traits< EdgeListGraph >::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei)
        os << get(ename, *ei) << "(" << get(vname, source(*ei, G)) << ","
           << get(vname, target(*ei, G)) << ") ";
    os << '\n';
}

template < class VertexListGraph, class Name >
void print_vertices(
    const VertexListGraph& G, Name name, std::ostream& os = std::cout)
{
    typename graph_traits< VertexListGraph >::vertex_iterator vi, vi_end;
    for (boost::tie(vi, vi_end) = vertices(G); vi != vi_end; ++vi)
        os << get(name, *vi) << " ";
    os << '\n';
}

template < class Graph, class Vertex >
bool is_adj_dispatch(Graph& g, Vertex a, Vertex b, bidirectional_tag)
{
    typename graph_traits< Graph >::adjacency_iterator vi, viend, adj_found;
    boost::tie(vi, viend) = adjacent_vertices(a, g);
    adj_found = std::find(vi, viend, b);
    if (adj_found == viend)
        return false;

    typename graph_traits< Graph >::out_edge_iterator oi, oiend, out_found;
    boost::tie(oi, oiend) = out_edges(a, g);
    out_found = std::find_if(oi, oiend, incident_to(b, g));
    if (out_found == oiend)
        return false;

    typename graph_traits< Graph >::in_edge_iterator ii, iiend, in_found;
    boost::tie(ii, iiend) = in_edges(b, g);
    in_found = std::find_if(ii, iiend, incident_from(a, g));
    if (in_found == iiend)
        return false;

    return true;
}
template < class Graph, class Vertex >
bool is_adj_dispatch(Graph& g, Vertex a, Vertex b, directed_tag)
{
    typename graph_traits< Graph >::adjacency_iterator vi, viend, found;
    boost::tie(vi, viend) = adjacent_vertices(a, g);
    found = std::find(vi, viend, b);
    if (found == viend)
        return false;

    typename graph_traits< Graph >::out_edge_iterator oi, oiend, out_found;
    boost::tie(oi, oiend) = out_edges(a, g);

    out_found = std::find_if(oi, oiend, incident_to(b, g));
    if (out_found == oiend)
        return false;
    return true;
}
template < class Graph, class Vertex >
bool is_adj_dispatch(Graph& g, Vertex a, Vertex b, undirected_tag)
{
    return is_adj_dispatch(g, a, b, directed_tag());
}

template < class Graph, class Vertex >
bool is_adjacent(Graph& g, Vertex a, Vertex b)
{
    typedef typename graph_traits< Graph >::directed_category Cat;
    return is_adj_dispatch(g, a, b, Cat());
}

template < class Graph, class Edge > bool in_edge_set(Graph& g, Edge e)
{
    typename Graph::edge_iterator ei, ei_end, found;
    boost::tie(ei, ei_end) = edges(g);
    found = std::find(ei, ei_end, e);
    return found != ei_end;
}

template < class Graph, class Vertex > bool in_vertex_set(Graph& g, Vertex v)
{
    typename Graph::vertex_iterator vi, vi_end, found;
    boost::tie(vi, vi_end) = vertices(g);
    found = std::find(vi, vi_end, v);
    return found != vi_end;
}

template < class Graph, class Vertex >
bool in_edge_set(Graph& g, Vertex u, Vertex v)
{
    typename Graph::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        if (source(*ei, g) == u && target(*ei, g) == v)
            return true;
    return false;
}

// is x a descendant of y?
template < typename ParentMap >
inline bool is_descendant(typename property_traits< ParentMap >::value_type x,
    typename property_traits< ParentMap >::value_type y, ParentMap parent)
{
    if (get(parent, x) == x) // x is the root of the tree
        return false;
    else if (get(parent, x) == y)
        return true;
    else
        return is_descendant(get(parent, x), y, parent);
}

// is y reachable from x?
template < typename IncidenceGraph, typename VertexColorMap >
inline bool is_reachable(
    typename graph_traits< IncidenceGraph >::vertex_descriptor x,
    typename graph_traits< IncidenceGraph >::vertex_descriptor y,
    const IncidenceGraph& g,
    VertexColorMap color) // should start out white for every vertex
{
    typedef typename property_traits< VertexColorMap >::value_type ColorValue;
    dfs_visitor<> vis;
    depth_first_visit(g, x, vis, color);
    return get(color, y) != color_traits< ColorValue >::white();
}

// Is the undirected graph connected?
// Is the directed graph strongly connected?
template < typename VertexListGraph, typename VertexColorMap >
inline bool is_connected(const VertexListGraph& g, VertexColorMap color)
{
    typedef typename property_traits< VertexColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;
    typename graph_traits< VertexListGraph >::vertex_iterator ui, ui_end, vi,
        vi_end, ci, ci_end;
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
            if (*ui != *vi)
            {
                for (boost::tie(ci, ci_end) = vertices(g); ci != ci_end; ++ci)
                    put(color, *ci, Color::white());
                if (!is_reachable(*ui, *vi, g, color))
                    return false;
            }
    return true;
}

template < typename Graph >
bool is_self_loop(
    typename graph_traits< Graph >::edge_descriptor e, const Graph& g)
{
    return source(e, g) == target(e, g);
}

template < class T1, class T2 >
std::pair< T1, T2 > make_list(const T1& t1, const T2& t2)
{
    return std::make_pair(t1, t2);
}

template < class T1, class T2, class T3 >
std::pair< T1, std::pair< T2, T3 > > make_list(
    const T1& t1, const T2& t2, const T3& t3)
{
    return std::make_pair(t1, std::make_pair(t2, t3));
}

template < class T1, class T2, class T3, class T4 >
std::pair< T1, std::pair< T2, std::pair< T3, T4 > > > make_list(
    const T1& t1, const T2& t2, const T3& t3, const T4& t4)
{
    return std::make_pair(t1, std::make_pair(t2, std::make_pair(t3, t4)));
}

template < class T1, class T2, class T3, class T4, class T5 >
std::pair< T1, std::pair< T2, std::pair< T3, std::pair< T4, T5 > > > >
make_list(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5)
{
    return std::make_pair(
        t1, std::make_pair(t2, std::make_pair(t3, std::make_pair(t4, t5))));
}

namespace graph
{

    // Functor for remove_parallel_edges: edge property of the removed edge is
    // added to the remaining
    template < typename EdgeProperty > struct add_removed_edge_property
    {
        add_removed_edge_property(EdgeProperty ep) : ep(ep) {}

        template < typename Edge > void operator()(Edge stay, Edge away)
        {
            put(ep, stay, get(ep, stay) + get(ep, away));
        }
        EdgeProperty ep;
    };

    // Same as above: edge property is capacity here
    template < typename Graph >
    struct add_removed_edge_capacity
    : add_removed_edge_property<
          typename property_map< Graph, edge_capacity_t >::type >
    {
        typedef add_removed_edge_property<
            typename property_map< Graph, edge_capacity_t >::type >
            base;
        add_removed_edge_capacity(Graph& g) : base(get(edge_capacity, g)) {}
    };

    template < typename Graph > bool has_no_vertices(const Graph& g)
    {
        typedef typename boost::graph_traits< Graph >::vertex_iterator vi;
        std::pair< vi, vi > p = vertices(g);
        return (p.first == p.second);
    }

    template < typename Graph > bool has_no_edges(const Graph& g)
    {
        typedef typename boost::graph_traits< Graph >::edge_iterator ei;
        std::pair< ei, ei > p = edges(g);
        return (p.first == p.second);
    }

    template < typename Graph >
    bool has_no_out_edges(
        const typename boost::graph_traits< Graph >::vertex_descriptor& v,
        const Graph& g)
    {
        typedef typename boost::graph_traits< Graph >::out_edge_iterator ei;
        std::pair< ei, ei > p = out_edges(v, g);
        return (p.first == p.second);
    }

} // namespace graph

#include <boost/graph/iteration_macros.hpp>

template < class PropertyIn, class PropertyOut, class Graph >
void copy_vertex_property(PropertyIn p_in, PropertyOut p_out, Graph& g)
{
    BGL_FORALL_VERTICES_T(u, g, Graph)
    put(p_out, u, get(p_in, g));
}

template < class PropertyIn, class PropertyOut, class Graph >
void copy_edge_property(PropertyIn p_in, PropertyOut p_out, Graph& g)
{
    BGL_FORALL_EDGES_T(e, g, Graph)
    put(p_out, e, get(p_in, g));
}

// Return true if property_map1 and property_map2 differ
// for any of the vertices in graph.
template < typename PropertyMapFirst, typename PropertyMapSecond,
    typename Graph >
bool are_property_maps_different(const PropertyMapFirst property_map1,
    const PropertyMapSecond property_map2, const Graph& graph)
{

    BGL_FORALL_VERTICES_T(vertex, graph, Graph)
    {
        if (get(property_map1, vertex) != get(property_map2, vertex))
        {

            return (true);
        }
    }

    return (false);
}

} /* namespace boost */

#endif /* BOOST_GRAPH_UTILITY_HPP*/

/* graph_utility.hpp
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
*/