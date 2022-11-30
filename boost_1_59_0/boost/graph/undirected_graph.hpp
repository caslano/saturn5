// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_UNDIRECTED_GRAPH_HPP
#define BOOST_GRAPH_UNDIRECTED_GRAPH_HPP

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/pending/property.hpp>
#include <boost/property_map/transform_value_property_map.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{
struct undirected_graph_tag
{
};

/**
 * The undirected_graph class template is a simplified version of the BGL
 * adjacency list. This class is provided for ease of use, but may not
 * perform as well as custom-defined adjacency list classes. Instances of
 * this template model the VertexIndexGraph, and EdgeIndexGraph concepts. The
 * graph is also fully mutable, supporting both insertions and removals of
 * vertices and edges.
 *
 * @note Special care must be taken when removing vertices or edges since
 * those operations can invalidate the numbering of vertices.
 */
template < typename VertexProp = no_property, typename EdgeProp = no_property,
    typename GraphProp = no_property >
class undirected_graph
{
public:
    typedef GraphProp graph_property_type;
    typedef VertexProp vertex_property_type;
    typedef EdgeProp edge_property_type;
    typedef typename lookup_one_property< GraphProp, graph_bundle_t >::type
        graph_bundled;
    typedef typename lookup_one_property< VertexProp, vertex_bundle_t >::type
        vertex_bundled;
    typedef typename lookup_one_property< EdgeProp, edge_bundle_t >::type
        edge_bundled;

public:
    // Embed indices into the vertex type.
    typedef property< vertex_index_t, unsigned, vertex_property_type >
        internal_vertex_property;
    typedef property< edge_index_t, unsigned, edge_property_type >
        internal_edge_property;

public:
    typedef adjacency_list< listS, listS, undirectedS, internal_vertex_property,
        internal_edge_property, GraphProp, listS >
        graph_type;

private:
    // storage selectors
    typedef typename graph_type::vertex_list_selector vertex_list_selector;
    typedef typename graph_type::edge_list_selector edge_list_selector;
    typedef typename graph_type::out_edge_list_selector out_edge_list_selector;
    typedef typename graph_type::directed_selector directed_selector;

public:
    // more commonly used graph types
    typedef typename graph_type::stored_vertex stored_vertex;
    typedef typename graph_type::vertices_size_type vertices_size_type;
    typedef typename graph_type::edges_size_type edges_size_type;
    typedef typename graph_type::degree_size_type degree_size_type;
    typedef typename graph_type::vertex_descriptor vertex_descriptor;
    typedef typename graph_type::edge_descriptor edge_descriptor;

    // iterator types
    typedef typename graph_type::vertex_iterator vertex_iterator;
    typedef typename graph_type::edge_iterator edge_iterator;
    typedef typename graph_type::out_edge_iterator out_edge_iterator;
    typedef typename graph_type::in_edge_iterator in_edge_iterator;
    typedef typename graph_type::adjacency_iterator adjacency_iterator;

    // miscellaneous types
    typedef undirected_graph_tag graph_tag;
    typedef typename graph_type::directed_category directed_category;
    typedef typename graph_type::edge_parallel_category edge_parallel_category;
    typedef typename graph_type::traversal_category traversal_category;

    typedef std::size_t vertex_index_type;
    typedef std::size_t edge_index_type;

    inline undirected_graph(GraphProp const& p = GraphProp())
    : m_graph(p)
    , m_num_vertices(0)
    , m_num_edges(0)
    , m_max_vertex_index(0)
    , m_max_edge_index(0)
    {
    }

    inline undirected_graph(undirected_graph const& x)
    : m_graph(x.m_graph)
    , m_num_vertices(x.m_num_vertices)
    , m_num_edges(x.m_num_edges)
    , m_max_vertex_index(x.m_max_vertex_index)
    , m_max_edge_index(x.m_max_edge_index)
    {
    }

    inline undirected_graph(
        vertices_size_type n, GraphProp const& p = GraphProp())
    : m_graph(n, p)
    , m_num_vertices(n)
    , m_num_edges(0)
    , m_max_vertex_index(n)
    , m_max_edge_index(0)
    {
        renumber_vertex_indices();
    }

    template < typename EdgeIterator >
    inline undirected_graph(EdgeIterator f, EdgeIterator l,
        vertices_size_type n, edges_size_type m = 0,
        GraphProp const& p = GraphProp())
    : m_graph(f, l, n, m, p)
    , m_num_vertices(n)
    , m_num_edges(0)
    , m_max_vertex_index(n)
    , m_max_edge_index(0)
    {
        // Unfortunately, we have to renumber to ensure correct indexing.
        renumber_indices();

        // Can't always guarantee that the number of edges is actually
        // m if distance(f, l) != m (or is undefined).
        m_num_edges = m_max_edge_index = boost::num_edges(m_graph);
    }

    undirected_graph& operator=(undirected_graph const& g)
    {
        if (&g != this)
        {
            m_graph = g.m_graph;
            m_num_vertices = g.m_num_vertices;
            m_num_edges = g.m_num_edges;
            m_max_vertex_index = g.m_max_vertex_index;
        }
        return *this;
    }

    // The impl_() methods are not part of the public interface.
    graph_type& impl() { return m_graph; }

    graph_type const& impl() const { return m_graph; }

    // The following methods are not part of the public interface
    vertices_size_type num_vertices() const { return m_num_vertices; }

private:
    // This helper function manages the attribution of vertex indices.
    vertex_descriptor make_index(vertex_descriptor v)
    {
        boost::put(vertex_index, m_graph, v, m_max_vertex_index);
        m_num_vertices++;
        m_max_vertex_index++;
        return v;
    }

public:
    vertex_descriptor add_vertex()
    {
        return make_index(boost::add_vertex(m_graph));
    }

    vertex_descriptor add_vertex(vertex_property_type const& p)
    {
        return make_index(
            boost::add_vertex(internal_vertex_property(0u, p), m_graph));
    }

    void clear_vertex(vertex_descriptor v)
    {
        std::pair< out_edge_iterator, out_edge_iterator > p
            = boost::out_edges(v, m_graph);
        m_num_edges -= std::distance(p.first, p.second);
        boost::clear_vertex(v, m_graph);
    }

    void remove_vertex(vertex_descriptor v)
    {
        boost::remove_vertex(v, m_graph);
        --m_num_vertices;
    }

    edges_size_type num_edges() const { return m_num_edges; }

private:
    // A helper fucntion for managing edge index attributes.
    std::pair< edge_descriptor, bool > const& make_index(
        std::pair< edge_descriptor, bool > const& x)
    {
        if (x.second)
        {
            boost::put(edge_index, m_graph, x.first, m_max_edge_index);
            ++m_num_edges;
            ++m_max_edge_index;
        }
        return x;
    }

public:
    std::pair< edge_descriptor, bool > add_edge(
        vertex_descriptor u, vertex_descriptor v)
    {
        return make_index(boost::add_edge(u, v, m_graph));
    }

    std::pair< edge_descriptor, bool > add_edge(
        vertex_descriptor u, vertex_descriptor v, edge_property_type const& p)
    {
        return make_index(
            boost::add_edge(u, v, internal_edge_property(0u, p), m_graph));
    }

    void remove_edge(vertex_descriptor u, vertex_descriptor v)
    {
        // find all edges, (u, v)
        std::vector< edge_descriptor > edges;
        out_edge_iterator i, i_end;
        for (boost::tie(i, i_end) = boost::out_edges(u, m_graph); i != i_end;
             ++i)
        {
            if (boost::target(*i, m_graph) == v)
            {
                edges.push_back(*i);
            }
        }
        // remove all edges, (u, v)
        typename std::vector< edge_descriptor >::iterator j = edges.begin(),
                                                          j_end = edges.end();
        for (; j != j_end; ++j)
        {
            remove_edge(*j);
        }
    }

    void remove_edge(edge_iterator i) { remove_edge(*i); }

    void remove_edge(edge_descriptor e)
    {
        boost::remove_edge(e, m_graph);
        --m_num_edges;
    }

    vertex_index_type max_vertex_index() const { return m_max_vertex_index; }

    void renumber_vertex_indices()
    {
        vertex_iterator i, i_end;
        boost::tie(i, i_end) = vertices(m_graph);
        m_max_vertex_index = renumber_vertex_indices(i, i_end, 0);
    }

    void remove_vertex_and_renumber_indices(vertex_iterator i)
    {
        vertex_iterator j = next(i), end = vertices(m_graph).second;
        vertex_index_type n = get(vertex_index, m_graph, *i);

        // remove the offending vertex and renumber everything after
        remove_vertex(*i);
        m_max_vertex_index = renumber_vertex_indices(j, end, n);
    }

    edge_index_type max_edge_index() const { return m_max_edge_index; }

    void renumber_edge_indices()
    {
        edge_iterator i, end;
        boost::tie(i, end) = edges(m_graph);
        m_max_edge_index = renumber_edge_indices(i, end, 0);
    }

    void remove_edge_and_renumber_indices(edge_iterator i)
    {
        edge_iterator j = next(i), end = edges(m_graph.second);
        edge_index_type n = get(edge_index, m_graph, *i);

        // remove the edge and renumber everything after it
        remove_edge(*i);
        m_max_edge_index = renumber_edge_indices(j, end, n);
    }

    void renumber_indices()
    {
        renumber_vertex_indices();
        renumber_edge_indices();
    }

    // bundled property support
#ifndef BOOST_GRAPH_NO_BUNDLED_PROPERTIES
    vertex_bundled& operator[](vertex_descriptor v) { return m_graph[v]; }

    vertex_bundled const& operator[](vertex_descriptor v) const
    {
        return m_graph[v];
    }

    edge_bundled& operator[](edge_descriptor e) { return m_graph[e]; }

    edge_bundled const& operator[](edge_descriptor e) const
    {
        return m_graph[e];
    }

    graph_bundled& operator[](graph_bundle_t) { return get_property(*this); }

    graph_bundled const& operator[](graph_bundle_t) const
    {
        return get_property(*this);
    }
#endif

    // Graph concepts
    static vertex_descriptor null_vertex() { return graph_type::null_vertex(); }

    void clear()
    {
        m_graph.clear();
        m_num_vertices = m_max_vertex_index = 0;
        m_num_edges = m_max_edge_index = 0;
    }

    void swap(undirected_graph& g)
    {
        m_graph.swap(g.m_graph);
        std::swap(m_num_vertices, g.m_num_vertices);
        std::swap(m_max_vertex_index, g.m_max_vertex_index);
        std::swap(m_num_edges, g.m_num_edges);
        std::swap(m_max_edge_index, g.m_max_edge_index);
    }

private:
    vertices_size_type renumber_vertex_indices(
        vertex_iterator i, vertex_iterator end, vertices_size_type n)
    {
        typedef
            typename property_map< graph_type, vertex_index_t >::type IndexMap;
        IndexMap indices = get(vertex_index, m_graph);
        for (; i != end; ++i)
        {
            indices[*i] = n++;
        }
        return n;
    }

    edges_size_type renumber_edge_indices(
        edge_iterator i, edge_iterator end, edges_size_type n)
    {
        typedef
            typename property_map< graph_type, edge_index_t >::type IndexMap;
        IndexMap indices = get(edge_index, m_graph);
        for (; i != end; ++i)
        {
            indices[*i] = n++;
        }
        return n;
    }

    graph_type m_graph;
    vertices_size_type m_num_vertices;
    edges_size_type m_num_edges;
    vertex_index_type m_max_vertex_index;
    edge_index_type m_max_edge_index;
};

#define UNDIRECTED_GRAPH_PARAMS typename VP, typename EP, typename GP
#define UNDIRECTED_GRAPH undirected_graph< VP, EP, GP >

// IncidenceGraph concepts
template < UNDIRECTED_GRAPH_PARAMS >
inline typename UNDIRECTED_GRAPH::vertex_descriptor source(
    typename UNDIRECTED_GRAPH::edge_descriptor e, UNDIRECTED_GRAPH const& g)
{
    return source(e, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS >
inline typename UNDIRECTED_GRAPH::vertex_descriptor target(
    typename UNDIRECTED_GRAPH::edge_descriptor e, UNDIRECTED_GRAPH const& g)
{
    return target(e, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS >
inline typename UNDIRECTED_GRAPH::degree_size_type out_degree(
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH const& g)
{
    return out_degree(v, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS >
inline std::pair< typename UNDIRECTED_GRAPH::out_edge_iterator,
    typename UNDIRECTED_GRAPH::out_edge_iterator >
out_edges(
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH const& g)
{
    return out_edges(v, g.impl());
}

// BidirectionalGraph concepts
template < UNDIRECTED_GRAPH_PARAMS >
inline typename UNDIRECTED_GRAPH::degree_size_type in_degree(
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH const& g)
{
    return in_degree(v, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS >
inline std::pair< typename UNDIRECTED_GRAPH::in_edge_iterator,
    typename UNDIRECTED_GRAPH::in_edge_iterator >
in_edges(
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH const& g)
{
    return in_edges(v, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS >
inline std::pair< typename UNDIRECTED_GRAPH::out_edge_iterator,
    typename UNDIRECTED_GRAPH::out_edge_iterator >
incident_edges(
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH const& g)
{
    return out_edges(v, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS >
inline typename UNDIRECTED_GRAPH::degree_size_type degree(
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH const& g)
{
    return degree(v, g.impl());
}

// AdjacencyGraph concepts
template < UNDIRECTED_GRAPH_PARAMS >
inline std::pair< typename UNDIRECTED_GRAPH::adjacency_iterator,
    typename UNDIRECTED_GRAPH::adjacency_iterator >
adjacent_vertices(
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH const& g)
{
    return adjacent_vertices(v, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS >
typename UNDIRECTED_GRAPH::vertex_descriptor vertex(
    typename UNDIRECTED_GRAPH::vertices_size_type n, UNDIRECTED_GRAPH const& g)
{
    return vertex(n, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS >
std::pair< typename UNDIRECTED_GRAPH::edge_descriptor, bool > edge(
    typename UNDIRECTED_GRAPH::vertex_descriptor u,
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH const& g)
{
    return edge(u, v, g.impl());
}

// VertexListGraph concepts
template < UNDIRECTED_GRAPH_PARAMS >
inline typename UNDIRECTED_GRAPH::vertices_size_type num_vertices(
    UNDIRECTED_GRAPH const& g)
{
    return g.num_vertices();
}

template < UNDIRECTED_GRAPH_PARAMS >
inline std::pair< typename UNDIRECTED_GRAPH::vertex_iterator,
    typename UNDIRECTED_GRAPH::vertex_iterator >
vertices(UNDIRECTED_GRAPH const& g)
{
    return vertices(g.impl());
}

// EdgeListGraph concepts
template < UNDIRECTED_GRAPH_PARAMS >
inline typename UNDIRECTED_GRAPH::edges_size_type num_edges(
    UNDIRECTED_GRAPH const& g)
{
    return g.num_edges();
}

template < UNDIRECTED_GRAPH_PARAMS >
inline std::pair< typename UNDIRECTED_GRAPH::edge_iterator,
    typename UNDIRECTED_GRAPH::edge_iterator >
edges(UNDIRECTED_GRAPH const& g)
{
    return edges(g.impl());
}

// MutableGraph concepts
template < UNDIRECTED_GRAPH_PARAMS >
inline typename UNDIRECTED_GRAPH::vertex_descriptor add_vertex(
    UNDIRECTED_GRAPH& g)
{
    return g.add_vertex();
}

template < UNDIRECTED_GRAPH_PARAMS >
inline typename UNDIRECTED_GRAPH::vertex_descriptor add_vertex(
    typename UNDIRECTED_GRAPH::vertex_property_type const& p,
    UNDIRECTED_GRAPH& g)
{
    return g.add_vertex(p);
}

template < UNDIRECTED_GRAPH_PARAMS >
inline void clear_vertex(
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH& g)
{
    return g.clear_vertex(v);
}

template < UNDIRECTED_GRAPH_PARAMS >
inline void remove_vertex(
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH& g)
{
    return g.remove_vertex(v);
}

template < UNDIRECTED_GRAPH_PARAMS >
inline std::pair< typename UNDIRECTED_GRAPH::edge_descriptor, bool > add_edge(
    typename UNDIRECTED_GRAPH::vertex_descriptor u,
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH& g)
{
    return g.add_edge(u, v);
}

template < UNDIRECTED_GRAPH_PARAMS >
inline std::pair< typename UNDIRECTED_GRAPH::edge_descriptor, bool > add_edge(
    typename UNDIRECTED_GRAPH::vertex_descriptor u,
    typename UNDIRECTED_GRAPH::vertex_descriptor v,
    typename UNDIRECTED_GRAPH::edge_property_type const& p, UNDIRECTED_GRAPH& g)
{
    return g.add_edge(u, v, p);
}

template < UNDIRECTED_GRAPH_PARAMS >
inline void remove_edge(typename UNDIRECTED_GRAPH::vertex_descriptor u,
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH& g)
{
    return g.remove_edge(u, v);
}

template < UNDIRECTED_GRAPH_PARAMS >
inline void remove_edge(
    typename UNDIRECTED_GRAPH::edge_descriptor e, UNDIRECTED_GRAPH& g)
{
    return g.remove_edge(e);
}

template < UNDIRECTED_GRAPH_PARAMS >
inline void remove_edge(
    typename UNDIRECTED_GRAPH::edge_iterator i, UNDIRECTED_GRAPH& g)
{
    return g.remove_edge(i);
}

template < UNDIRECTED_GRAPH_PARAMS, class Predicate >
inline void remove_edge_if(Predicate pred, UNDIRECTED_GRAPH& g)
{
    return remove_edge_if(pred, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS, class Predicate >
inline void remove_incident_edge_if(
    typename UNDIRECTED_GRAPH::vertex_descriptor v, Predicate pred,
    UNDIRECTED_GRAPH& g)
{
    return remove_out_edge_if(v, pred, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS, class Predicate >
inline void remove_out_edge_if(typename UNDIRECTED_GRAPH::vertex_descriptor v,
    Predicate pred, UNDIRECTED_GRAPH& g)
{
    return remove_out_edge_if(v, pred, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS, class Predicate >
inline void remove_in_edge_if(typename UNDIRECTED_GRAPH::vertex_descriptor v,
    Predicate pred, UNDIRECTED_GRAPH& g)
{
    return remove_in_edge_if(v, pred, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS, typename Property >
struct property_map< UNDIRECTED_GRAPH, Property >
: property_map< typename UNDIRECTED_GRAPH::graph_type, Property >
{
};

template < UNDIRECTED_GRAPH_PARAMS >
struct property_map< UNDIRECTED_GRAPH, vertex_all_t >
{
    typedef transform_value_property_map< detail::remove_first_property,
        typename property_map< typename UNDIRECTED_GRAPH::graph_type,
            vertex_all_t >::const_type >
        const_type;
    typedef transform_value_property_map< detail::remove_first_property,
        typename property_map< typename UNDIRECTED_GRAPH::graph_type,
            vertex_all_t >::type >
        type;
};

template < UNDIRECTED_GRAPH_PARAMS >
struct property_map< UNDIRECTED_GRAPH, edge_all_t >
{
    typedef transform_value_property_map< detail::remove_first_property,
        typename property_map< typename UNDIRECTED_GRAPH::graph_type,
            edge_all_t >::const_type >
        const_type;
    typedef transform_value_property_map< detail::remove_first_property,
        typename property_map< typename UNDIRECTED_GRAPH::graph_type,
            edge_all_t >::type >
        type;
};

// PropertyGraph concepts
template < UNDIRECTED_GRAPH_PARAMS, typename Property >
inline typename property_map< UNDIRECTED_GRAPH, Property >::type get(
    Property p, UNDIRECTED_GRAPH& g)
{
    return get(p, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS, typename Property >
inline typename property_map< UNDIRECTED_GRAPH, Property >::const_type get(
    Property p, UNDIRECTED_GRAPH const& g)
{
    return get(p, g.impl());
}

template < UNDIRECTED_GRAPH_PARAMS >
inline typename property_map< UNDIRECTED_GRAPH, vertex_all_t >::type get(
    vertex_all_t, UNDIRECTED_GRAPH& g)
{
    return typename property_map< UNDIRECTED_GRAPH, vertex_all_t >::type(
        detail::remove_first_property(), get(vertex_all, g.impl()));
}

template < UNDIRECTED_GRAPH_PARAMS >
inline typename property_map< UNDIRECTED_GRAPH, vertex_all_t >::const_type get(
    vertex_all_t, UNDIRECTED_GRAPH const& g)
{
    return typename property_map< UNDIRECTED_GRAPH, vertex_all_t >::const_type(
        detail::remove_first_property(), get(vertex_all, g.impl()));
}

template < UNDIRECTED_GRAPH_PARAMS >
inline typename property_map< UNDIRECTED_GRAPH, edge_all_t >::type get(
    edge_all_t, UNDIRECTED_GRAPH& g)
{
    return typename property_map< UNDIRECTED_GRAPH, edge_all_t >::type(
        detail::remove_first_property(), get(edge_all, g.impl()));
}

template < UNDIRECTED_GRAPH_PARAMS >
inline typename property_map< UNDIRECTED_GRAPH, edge_all_t >::const_type get(
    edge_all_t, UNDIRECTED_GRAPH const& g)
{
    return typename property_map< UNDIRECTED_GRAPH, edge_all_t >::const_type(
        detail::remove_first_property(), get(edge_all, g.impl()));
}

template < UNDIRECTED_GRAPH_PARAMS, typename Property, typename Key >
inline typename property_traits< typename property_map<
    typename UNDIRECTED_GRAPH::graph_type, Property >::const_type >::value_type
get(Property p, UNDIRECTED_GRAPH const& g, Key const& k)
{
    return get(p, g.impl(), k);
}

template < UNDIRECTED_GRAPH_PARAMS, typename Key >
inline typename property_traits<
    typename property_map< typename UNDIRECTED_GRAPH::graph_type,
        vertex_all_t >::const_type >::value_type
get(vertex_all_t, UNDIRECTED_GRAPH const& g, Key const& k)
{
    return get(vertex_all, g.impl(), k).m_base;
}

template < UNDIRECTED_GRAPH_PARAMS, typename Key >
inline typename property_traits<
    typename property_map< typename UNDIRECTED_GRAPH::graph_type,
        edge_all_t >::const_type >::value_type
get(edge_all_t, UNDIRECTED_GRAPH const& g, Key const& k)
{
    return get(edge_all, g.impl(), k).m_base;
}

template < UNDIRECTED_GRAPH_PARAMS, typename Property, typename Key,
    typename Value >
inline void put(Property p, UNDIRECTED_GRAPH& g, Key const& k, Value const& v)
{
    put(p, g.impl(), k, v);
}

template < UNDIRECTED_GRAPH_PARAMS, typename Key, typename Value >
inline void put(vertex_all_t, UNDIRECTED_GRAPH& g, Key const& k, Value const& v)
{
    put(vertex_all, g.impl(), k,
        typename UNDIRECTED_GRAPH::internal_vertex_property(
            get(vertex_index, g.impl(), k), v));
}

template < UNDIRECTED_GRAPH_PARAMS, typename Key, typename Value >
inline void put(edge_all_t, UNDIRECTED_GRAPH& g, Key const& k, Value const& v)
{
    put(edge_all, g.impl(), k,
        typename UNDIRECTED_GRAPH::internal_vertex_property(
            get(edge_index, g.impl(), k), v));
}

template < UNDIRECTED_GRAPH_PARAMS, class Property >
inline typename graph_property< UNDIRECTED_GRAPH, Property >::type&
get_property(UNDIRECTED_GRAPH& g, Property p)
{
    return get_property(g.impl(), p);
}

template < UNDIRECTED_GRAPH_PARAMS, class Property >
inline typename graph_property< UNDIRECTED_GRAPH, Property >::type const&
get_property(UNDIRECTED_GRAPH const& g, Property p)
{
    return get_property(g.impl(), p);
}

template < UNDIRECTED_GRAPH_PARAMS, class Property, class Value >
inline void set_property(UNDIRECTED_GRAPH& g, Property p, Value v)
{
    return set_property(g.impl(), p, v);
}

// Indexed Vertex graph

template < UNDIRECTED_GRAPH_PARAMS >
inline typename UNDIRECTED_GRAPH::vertex_index_type get_vertex_index(
    typename UNDIRECTED_GRAPH::vertex_descriptor v, UNDIRECTED_GRAPH const& g)
{
    return get(vertex_index, g, v);
}

template < UNDIRECTED_GRAPH_PARAMS >
typename UNDIRECTED_GRAPH::vertex_index_type max_vertex_index(
    UNDIRECTED_GRAPH const& g)
{
    return g.max_vertex_index();
}

template < UNDIRECTED_GRAPH_PARAMS >
inline void renumber_vertex_indices(UNDIRECTED_GRAPH& g)
{
    g.renumber_vertex_indices();
}

template < UNDIRECTED_GRAPH_PARAMS >
inline void remove_vertex_and_renumber_indices(
    typename UNDIRECTED_GRAPH::vertex_iterator i, UNDIRECTED_GRAPH& g)
{
    g.remove_vertex_and_renumber_indices(i);
}

// Edge index management

template < UNDIRECTED_GRAPH_PARAMS >
inline typename UNDIRECTED_GRAPH::edge_index_type get_edge_index(
    typename UNDIRECTED_GRAPH::edge_descriptor v, UNDIRECTED_GRAPH const& g)
{
    return get(edge_index, g, v);
}

template < UNDIRECTED_GRAPH_PARAMS >
typename UNDIRECTED_GRAPH::edge_index_type max_edge_index(
    UNDIRECTED_GRAPH const& g)
{
    return g.max_edge_index();
}

template < UNDIRECTED_GRAPH_PARAMS >
inline void renumber_edge_indices(UNDIRECTED_GRAPH& g)
{
    g.renumber_edge_indices();
}

template < UNDIRECTED_GRAPH_PARAMS >
inline void remove_edge_and_renumber_indices(
    typename UNDIRECTED_GRAPH::edge_iterator i, UNDIRECTED_GRAPH& g)
{
    g.remove_edge_and_renumber_indices(i);
}

// Index management
template < UNDIRECTED_GRAPH_PARAMS >
inline void renumber_indices(UNDIRECTED_GRAPH& g)
{
    g.renumber_indices();
}

// Mutability Traits
template < UNDIRECTED_GRAPH_PARAMS >
struct graph_mutability_traits< UNDIRECTED_GRAPH >
{
    typedef mutable_property_graph_tag category;
};

#undef UNDIRECTED_GRAPH_PARAMS
#undef UNDIRECTED_GRAPH

} /* namespace boost */

#endif

/* undirected_graph.hpp
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
*/