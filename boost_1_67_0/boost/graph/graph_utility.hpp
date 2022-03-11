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