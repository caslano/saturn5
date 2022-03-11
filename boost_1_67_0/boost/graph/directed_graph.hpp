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