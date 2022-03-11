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