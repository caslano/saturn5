// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DIRECTED_GRAPH_HPP
#define BOOST_GRAPH_DIRECTED_GRAPH_HPP

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/pending/property.hpp>
#include <boost/property_map/transform_value_property_map.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{
struct directed_graph_tag
{
};

/**
 * The directed_graph class template is a simplified version of the BGL
 * adjacency list. This class is provided for ease of use, but may not
 * perform as well as custom-defined adjacency list classes. Instances of
 * this template model the BidirectionalGraph, VertexIndexGraph, and
 * EdgeIndexGraph concepts. The graph is also fully mutable, supporting
 * both insertions and removals of vertices and edges.
 *
 * @note Special care must be taken when removing vertices or edges since
 * those operations can invalidate the numbering of vertices.
 */
template < typename VertexProp = no_property, typename EdgeProp = no_property,
    typename GraphProp = no_property >
class directed_graph
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
    typedef adjacency_list< listS, listS, bidirectionalS,
        internal_vertex_property, internal_edge_property, GraphProp, listS >
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
    typedef directed_graph_tag graph_tag;
    typedef typename graph_type::directed_category directed_category;
    typedef typename graph_type::edge_parallel_category edge_parallel_category;
    typedef typename graph_type::traversal_category traversal_category;

    typedef std::size_t vertex_index_type;
    typedef std::size_t edge_index_type;

    directed_graph(GraphProp const& p = GraphProp())
    : m_graph(p)
    , m_num_vertices(0)
    , m_num_edges(0)
    , m_max_vertex_index(0)
    , m_max_edge_index(0)
    {
    }

    directed_graph(directed_graph const& x)
    : m_graph(x.m_graph)
    , m_num_vertices(x.m_num_vertices)
    , m_num_edges(x.m_num_edges)
    , m_max_vertex_index(x.m_max_vertex_index)
    , m_max_edge_index(x.m_max_edge_index)
    {
    }

    directed_graph(vertices_size_type n, GraphProp const& p = GraphProp())
    : m_graph(n, p)
    , m_num_vertices(n)
    , m_num_edges(0)
    , m_max_vertex_index(n)
    , m_max_edge_index(0)
    {
        renumber_vertex_indices();
    }

    template < typename EdgeIterator >
    directed_graph(EdgeIterator f, EdgeIterator l, vertices_size_type n,
        edges_size_type m = 0, GraphProp const& p = GraphProp())
    : m_graph(f, l, n, m, p)
    , m_num_vertices(n)
    , m_num_edges(0)
    , m_max_vertex_index(n)
    , m_max_edge_index(0)
    {
        // Unfortunately, we have to renumber the entire graph.
        renumber_indices();

        // Can't always guarantee that the number of edges is actually
        // m if distance(f, l) != m (or is undefined).
        m_num_edges = m_max_edge_index = boost::num_edges(m_graph);
    }

    directed_graph& operator=(directed_graph const& g)
    {
        if (&g != this)
        {
            m_graph = g.m_graph;
            m_num_vertices = g.m_num_vertices;
            m_num_edges = g.m_num_edges;
            m_max_vertex_index = g.m_max_vertex_index;
            m_max_edge_index = g.m_max_edge_index;
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
        m_num_edges -= boost::degree(v, m_graph);
        boost::clear_vertex(v, m_graph);
    }

    void remove_vertex(vertex_descriptor v)
    {
        boost::remove_vertex(v, m_graph);
        --m_num_vertices;
    }

    edges_size_type num_edges() const { return m_num_edges; }

private:
    // A helper function for managing edge index attributes.
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
        vertex_iterator i, end;
        boost::tie(i, end) = vertices(m_graph);
        m_max_vertex_index = renumber_vertex_indices(i, end, 0);
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
        edge_iterator j = next(i), end = edges(m_graph).second;
        edge_index_type n = get(edge_index, m_graph, *i);

        // remove the offending edge and renumber everything after
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

    void swap(directed_graph& g)
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

    vertices_size_type renumber_edge_indices(
        edge_iterator i, edge_iterator end, vertices_size_type n)
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

#define DIRECTED_GRAPH_PARAMS typename VP, typename EP, typename GP
#define DIRECTED_GRAPH directed_graph< VP, EP, GP >

// IncidenceGraph concepts
template < DIRECTED_GRAPH_PARAMS >
inline typename DIRECTED_GRAPH::vertex_descriptor source(
    typename DIRECTED_GRAPH::edge_descriptor e, DIRECTED_GRAPH const& g)
{
    return source(e, g.impl());
}

template < DIRECTED_GRAPH_PARAMS >
inline typename DIRECTED_GRAPH::vertex_descriptor target(
    typename DIRECTED_GRAPH::edge_descriptor e, DIRECTED_GRAPH const& g)
{
    return target(e, g.impl());
}

template < DIRECTED_GRAPH_PARAMS >
inline typename DIRECTED_GRAPH::degree_size_type out_degree(
    typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH const& g)
{
    return out_degree(v, g.impl());
}

template < DIRECTED_GRAPH_PARAMS >
inline std::pair< typename DIRECTED_GRAPH::out_edge_iterator,
    typename DIRECTED_GRAPH::out_edge_iterator >
out_edges(typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH const& g)
{
    return out_edges(v, g.impl());
}

// BidirectionalGraph concepts
template < DIRECTED_GRAPH_PARAMS >
inline typename DIRECTED_GRAPH::degree_size_type in_degree(
    typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH const& g)
{
    return in_degree(v, g.impl());
}

template < DIRECTED_GRAPH_PARAMS >
inline std::pair< typename DIRECTED_GRAPH::in_edge_iterator,
    typename DIRECTED_GRAPH::in_edge_iterator >
in_edges(typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH const& g)
{
    return in_edges(v, g.impl());
}

template < DIRECTED_GRAPH_PARAMS >
inline typename DIRECTED_GRAPH::degree_size_type degree(
    typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH const& g)
{
    return degree(v, g.impl());
}

// AdjacencyGraph concepts
template < DIRECTED_GRAPH_PARAMS >
inline std::pair< typename DIRECTED_GRAPH::adjacency_iterator,
    typename DIRECTED_GRAPH::adjacency_iterator >
adjacent_vertices(
    typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH const& g)
{
    return adjacent_vertices(v, g.impl());
}

template < DIRECTED_GRAPH_PARAMS >
typename DIRECTED_GRAPH::vertex_descriptor vertex(
    typename DIRECTED_GRAPH::vertices_size_type n, DIRECTED_GRAPH const& g)
{
    return vertex(n, g.impl());
}

template < DIRECTED_GRAPH_PARAMS >
std::pair< typename DIRECTED_GRAPH::edge_descriptor, bool > edge(
    typename DIRECTED_GRAPH::vertex_descriptor u,
    typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH const& g)
{
    return edge(u, v, g.impl());
}

// VertexListGraph concepts
template < DIRECTED_GRAPH_PARAMS >
inline typename DIRECTED_GRAPH::vertices_size_type num_vertices(
    DIRECTED_GRAPH const& g)
{
    return g.num_vertices();
}

template < DIRECTED_GRAPH_PARAMS >
inline std::pair< typename DIRECTED_GRAPH::vertex_iterator,
    typename DIRECTED_GRAPH::vertex_iterator >
vertices(DIRECTED_GRAPH const& g)
{
    return vertices(g.impl());
}

// EdgeListGraph concepts
template < DIRECTED_GRAPH_PARAMS >
inline typename DIRECTED_GRAPH::edges_size_type num_edges(
    DIRECTED_GRAPH const& g)
{
    return g.num_edges();
}

template < DIRECTED_GRAPH_PARAMS >
inline std::pair< typename DIRECTED_GRAPH::edge_iterator,
    typename DIRECTED_GRAPH::edge_iterator >
edges(DIRECTED_GRAPH const& g)
{
    return edges(g.impl());
}

// MutableGraph concepts
template < DIRECTED_GRAPH_PARAMS >
inline typename DIRECTED_GRAPH::vertex_descriptor add_vertex(DIRECTED_GRAPH& g)
{
    return g.add_vertex();
}

template < DIRECTED_GRAPH_PARAMS >
inline typename DIRECTED_GRAPH::vertex_descriptor add_vertex(
    typename DIRECTED_GRAPH::vertex_property_type const& p, DIRECTED_GRAPH& g)
{
    return g.add_vertex(p);
}

template < DIRECTED_GRAPH_PARAMS >
inline void clear_vertex(
    typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH& g)
{
    return g.clear_vertex(v);
}

template < DIRECTED_GRAPH_PARAMS >
inline void remove_vertex(
    typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH& g)
{
    return g.remove_vertex(v);
}

template < DIRECTED_GRAPH_PARAMS >
inline std::pair< typename DIRECTED_GRAPH::edge_descriptor, bool > add_edge(
    typename DIRECTED_GRAPH::vertex_descriptor u,
    typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH& g)
{
    return g.add_edge(u, v);
}

template < DIRECTED_GRAPH_PARAMS >
inline std::pair< typename DIRECTED_GRAPH::edge_descriptor, bool > add_edge(
    typename DIRECTED_GRAPH::vertex_descriptor u,
    typename DIRECTED_GRAPH::vertex_descriptor v,
    typename DIRECTED_GRAPH::edge_property_type const& p, DIRECTED_GRAPH& g)
{
    return g.add_edge(u, v, p);
}

template < DIRECTED_GRAPH_PARAMS >
inline void remove_edge(typename DIRECTED_GRAPH::vertex_descriptor u,
    typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH& g)
{
    return g.remove_edge(u, v);
}

template < DIRECTED_GRAPH_PARAMS >
inline void remove_edge(
    typename DIRECTED_GRAPH::edge_descriptor e, DIRECTED_GRAPH& g)
{
    return g.remove_edge(e);
}

template < DIRECTED_GRAPH_PARAMS >
inline void remove_edge(
    typename DIRECTED_GRAPH::edge_iterator i, DIRECTED_GRAPH& g)
{
    return g.remove_edge(i);
}

template < DIRECTED_GRAPH_PARAMS, class Predicate >
inline void remove_edge_if(Predicate pred, DIRECTED_GRAPH& g)
{
    return remove_edge_if(pred, g.impl());
}

template < DIRECTED_GRAPH_PARAMS, class Predicate >
inline void remove_out_edge_if(typename DIRECTED_GRAPH::vertex_descriptor v,
    Predicate pred, DIRECTED_GRAPH& g)
{
    return remove_out_edge_if(v, pred, g.impl());
}

template < DIRECTED_GRAPH_PARAMS, class Predicate >
inline void remove_in_edge_if(typename DIRECTED_GRAPH::vertex_descriptor v,
    Predicate pred, DIRECTED_GRAPH& g)
{
    return remove_in_edge_if(v, pred, g.impl());
}

template < DIRECTED_GRAPH_PARAMS, typename Property >
struct property_map< DIRECTED_GRAPH, Property >
: property_map< typename DIRECTED_GRAPH::graph_type, Property >
{
};

template < DIRECTED_GRAPH_PARAMS >
struct property_map< DIRECTED_GRAPH, vertex_all_t >
{
    typedef transform_value_property_map< detail::remove_first_property,
        typename property_map< typename DIRECTED_GRAPH::graph_type,
            vertex_all_t >::const_type >
        const_type;
    typedef transform_value_property_map< detail::remove_first_property,
        typename property_map< typename DIRECTED_GRAPH::graph_type,
            vertex_all_t >::type >
        type;
};

template < DIRECTED_GRAPH_PARAMS >
struct property_map< DIRECTED_GRAPH, edge_all_t >
{
    typedef transform_value_property_map< detail::remove_first_property,
        typename property_map< typename DIRECTED_GRAPH::graph_type,
            edge_all_t >::const_type >
        const_type;
    typedef transform_value_property_map< detail::remove_first_property,
        typename property_map< typename DIRECTED_GRAPH::graph_type,
            edge_all_t >::type >
        type;
};

// PropertyGraph concepts
template < DIRECTED_GRAPH_PARAMS, typename Property >
inline typename property_map< DIRECTED_GRAPH, Property >::type get(
    Property p, DIRECTED_GRAPH& g)
{
    return get(p, g.impl());
}

template < DIRECTED_GRAPH_PARAMS, typename Property >
inline typename property_map< DIRECTED_GRAPH, Property >::const_type get(
    Property p, DIRECTED_GRAPH const& g)
{
    return get(p, g.impl());
}

template < DIRECTED_GRAPH_PARAMS >
inline typename property_map< DIRECTED_GRAPH, vertex_all_t >::type get(
    vertex_all_t, DIRECTED_GRAPH& g)
{
    return typename property_map< DIRECTED_GRAPH, vertex_all_t >::type(
        detail::remove_first_property(), get(vertex_all, g.impl()));
}

template < DIRECTED_GRAPH_PARAMS >
inline typename property_map< DIRECTED_GRAPH, vertex_all_t >::const_type get(
    vertex_all_t, DIRECTED_GRAPH const& g)
{
    return typename property_map< DIRECTED_GRAPH, vertex_all_t >::const_type(
        detail::remove_first_property(), get(vertex_all, g.impl()));
}

template < DIRECTED_GRAPH_PARAMS >
inline typename property_map< DIRECTED_GRAPH, edge_all_t >::type get(
    edge_all_t, DIRECTED_GRAPH& g)
{
    return typename property_map< DIRECTED_GRAPH, edge_all_t >::type(
        detail::remove_first_property(), get(edge_all, g.impl()));
}

template < DIRECTED_GRAPH_PARAMS >
inline typename property_map< DIRECTED_GRAPH, edge_all_t >::const_type get(
    edge_all_t, DIRECTED_GRAPH const& g)
{
    return typename property_map< DIRECTED_GRAPH, edge_all_t >::const_type(
        detail::remove_first_property(), get(edge_all, g.impl()));
}

template < DIRECTED_GRAPH_PARAMS, typename Property, typename Key >
inline typename property_traits< typename property_map<
    typename DIRECTED_GRAPH::graph_type, Property >::const_type >::value_type
get(Property p, DIRECTED_GRAPH const& g, Key const& k)
{
    return get(p, g.impl(), k);
}

template < DIRECTED_GRAPH_PARAMS, typename Key >
inline typename property_traits<
    typename property_map< typename DIRECTED_GRAPH::graph_type,
        vertex_all_t >::const_type >::value_type
get(vertex_all_t, DIRECTED_GRAPH const& g, Key const& k)
{
    return get(vertex_all, g.impl(), k).m_base;
}

template < DIRECTED_GRAPH_PARAMS, typename Key >
inline typename property_traits< typename property_map<
    typename DIRECTED_GRAPH::graph_type, edge_all_t >::const_type >::value_type
get(edge_all_t, DIRECTED_GRAPH const& g, Key const& k)
{
    return get(edge_all, g.impl(), k).m_base;
}

template < DIRECTED_GRAPH_PARAMS, typename Property, typename Key,
    typename Value >
inline void put(Property p, DIRECTED_GRAPH& g, Key const& k, Value const& v)
{
    put(p, g.impl(), k, v);
}

template < DIRECTED_GRAPH_PARAMS, typename Key, typename Value >
inline void put(vertex_all_t, DIRECTED_GRAPH& g, Key const& k, Value const& v)
{
    put(vertex_all, g.impl(), k,
        typename DIRECTED_GRAPH::internal_vertex_property(
            get(vertex_index, g.impl(), k), v));
}

template < DIRECTED_GRAPH_PARAMS, typename Key, typename Value >
inline void put(edge_all_t, DIRECTED_GRAPH& g, Key const& k, Value const& v)
{
    put(edge_all, g.impl(), k,
        typename DIRECTED_GRAPH::internal_vertex_property(
            get(edge_index, g.impl(), k), v));
}

template < DIRECTED_GRAPH_PARAMS, class Property >
typename graph_property< DIRECTED_GRAPH, Property >::type& get_property(
    DIRECTED_GRAPH& g, Property p)
{
    return get_property(g.impl(), p);
}

template < DIRECTED_GRAPH_PARAMS, class Property >
typename graph_property< DIRECTED_GRAPH, Property >::type const& get_property(
    DIRECTED_GRAPH const& g, Property p)
{
    return get_property(g.impl(), p);
}

template < DIRECTED_GRAPH_PARAMS, class Property, class Value >
void set_property(DIRECTED_GRAPH& g, Property p, Value v)
{
    return set_property(g.impl(), p, v);
}

// Vertex index management

template < DIRECTED_GRAPH_PARAMS >
inline typename DIRECTED_GRAPH::vertex_index_type get_vertex_index(
    typename DIRECTED_GRAPH::vertex_descriptor v, DIRECTED_GRAPH const& g)
{
    return get(vertex_index, g, v);
}

template < DIRECTED_GRAPH_PARAMS >
typename DIRECTED_GRAPH::vertex_index_type max_vertex_index(
    DIRECTED_GRAPH const& g)
{
    return g.max_vertex_index();
}

template < DIRECTED_GRAPH_PARAMS >
inline void renumber_vertex_indices(DIRECTED_GRAPH& g)
{
    g.renumber_vertex_indices();
}

template < DIRECTED_GRAPH_PARAMS >
inline void remove_vertex_and_renumber_indices(
    typename DIRECTED_GRAPH::vertex_iterator i, DIRECTED_GRAPH& g)
{
    g.remove_vertex_and_renumber_indices(i);
}

// Edge index management
template < DIRECTED_GRAPH_PARAMS >
inline typename DIRECTED_GRAPH::edge_index_type get_edge_index(
    typename DIRECTED_GRAPH::edge_descriptor v, DIRECTED_GRAPH const& g)
{
    return get(edge_index, g, v);
}

template < DIRECTED_GRAPH_PARAMS >
typename DIRECTED_GRAPH::edge_index_type max_edge_index(DIRECTED_GRAPH const& g)
{
    return g.max_edge_index();
}

template < DIRECTED_GRAPH_PARAMS >
inline void renumber_edge_indices(DIRECTED_GRAPH& g)
{
    g.renumber_edge_indices();
}

template < DIRECTED_GRAPH_PARAMS >
inline void remove_edge_and_renumber_indices(
    typename DIRECTED_GRAPH::edge_iterator i, DIRECTED_GRAPH& g)
{
    g.remove_edge_and_renumber_indices(i);
}

// Index management
template < DIRECTED_GRAPH_PARAMS >
inline void renumber_indices(DIRECTED_GRAPH& g)
{
    g.renumber_indices();
}

// Mutability Traits
template < DIRECTED_GRAPH_PARAMS >
struct graph_mutability_traits< DIRECTED_GRAPH >
{
    typedef mutable_property_graph_tag category;
};

#undef DIRECTED_GRAPH_PARAMS
#undef DIRECTED_GRAPH

} /* namespace boost */

#endif

/* directed_graph.hpp
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
*/