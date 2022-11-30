//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_FILTERED_GRAPH_HPP
#define BOOST_FILTERED_GRAPH_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include <boost/graph/detail/set_adaptor.hpp>
#include <boost/iterator/filter_iterator.hpp>

namespace boost
{

//=========================================================================
// Some predicate classes.

struct keep_all
{
    template < typename T > bool operator()(const T&) const { return true; }
};

// Keep residual edges (used in maximum-flow algorithms).
template < typename ResidualCapacityEdgeMap > struct is_residual_edge
{
    is_residual_edge() {}
    is_residual_edge(ResidualCapacityEdgeMap rcap) : m_rcap(rcap) {}
    template < typename Edge > bool operator()(const Edge& e) const
    {
        return 0 < get(m_rcap, e);
    }
    ResidualCapacityEdgeMap m_rcap;
};

template < typename Set > struct is_in_subset
{
    is_in_subset() : m_s(0) {}
    is_in_subset(const Set& s) : m_s(&s) {}

    template < typename Elt > bool operator()(const Elt& x) const
    {
        return set_contains(*m_s, x);
    }
    const Set* m_s;
};

template < typename Set > struct is_not_in_subset
{
    is_not_in_subset() : m_s(0) {}
    is_not_in_subset(const Set& s) : m_s(&s) {}

    template < typename Elt > bool operator()(const Elt& x) const
    {
        return !set_contains(*m_s, x);
    }
    const Set* m_s;
};

namespace detail
{

    template < typename EdgePredicate, typename VertexPredicate,
        typename Graph >
    struct out_edge_predicate
    {
        out_edge_predicate() {}
        out_edge_predicate(EdgePredicate ep, VertexPredicate vp, const Graph& g)
        : m_edge_pred(ep), m_vertex_pred(vp), m_g(&g)
        {
        }

        template < typename Edge > bool operator()(const Edge& e) const
        {
            return m_edge_pred(e) && m_vertex_pred(target(e, *m_g));
        }
        EdgePredicate m_edge_pred;
        VertexPredicate m_vertex_pred;
        const Graph* m_g;
    };

    template < typename EdgePredicate, typename VertexPredicate,
        typename Graph >
    struct in_edge_predicate
    {
        in_edge_predicate() {}
        in_edge_predicate(EdgePredicate ep, VertexPredicate vp, const Graph& g)
        : m_edge_pred(ep), m_vertex_pred(vp), m_g(&g)
        {
        }

        template < typename Edge > bool operator()(const Edge& e) const
        {
            return m_edge_pred(e) && m_vertex_pred(source(e, *m_g));
        }
        EdgePredicate m_edge_pred;
        VertexPredicate m_vertex_pred;
        const Graph* m_g;
    };

    template < typename EdgePredicate, typename VertexPredicate,
        typename Graph >
    struct edge_predicate
    {
        edge_predicate() {}
        edge_predicate(EdgePredicate ep, VertexPredicate vp, const Graph& g)
        : m_edge_pred(ep), m_vertex_pred(vp), m_g(&g)
        {
        }

        template < typename Edge > bool operator()(const Edge& e) const
        {
            return m_edge_pred(e) && m_vertex_pred(source(e, *m_g))
                && m_vertex_pred(target(e, *m_g));
        }
        EdgePredicate m_edge_pred;
        VertexPredicate m_vertex_pred;
        const Graph* m_g;
    };

} // namespace detail

//===========================================================================
// Filtered Graph

struct filtered_graph_tag
{
};

// This base class is a stupid hack to change overload resolution
// rules for the source and target functions so that they are a
// worse match than the source and target functions defined for
// pairs in graph_traits.hpp. I feel dirty. -JGS
template < class G > struct filtered_graph_base
{
    typedef graph_traits< G > Traits;
    typedef typename Traits::vertex_descriptor vertex_descriptor;
    typedef typename Traits::edge_descriptor edge_descriptor;
    filtered_graph_base(const G& g) : m_g(g) {}
    // protected:
    const G& m_g;
};

template < typename Graph, typename EdgePredicate,
    typename VertexPredicate = keep_all >
class filtered_graph : public filtered_graph_base< Graph >
{
    typedef filtered_graph_base< Graph > Base;
    typedef graph_traits< Graph > Traits;
    typedef filtered_graph self;

public:
    typedef Graph graph_type;
    typedef detail::out_edge_predicate< EdgePredicate, VertexPredicate, self >
        OutEdgePred;
    typedef detail::in_edge_predicate< EdgePredicate, VertexPredicate, self >
        InEdgePred;
    typedef detail::edge_predicate< EdgePredicate, VertexPredicate, self >
        EdgePred;

    // Constructors
    filtered_graph(const Graph& g, EdgePredicate ep) : Base(g), m_edge_pred(ep)
    {
    }

    filtered_graph(const Graph& g, EdgePredicate ep, VertexPredicate vp)
    : Base(g), m_edge_pred(ep), m_vertex_pred(vp)
    {
    }

    // Graph requirements
    typedef typename Traits::vertex_descriptor vertex_descriptor;
    typedef typename Traits::edge_descriptor edge_descriptor;
    typedef typename Traits::directed_category directed_category;
    typedef typename Traits::edge_parallel_category edge_parallel_category;
    typedef typename Traits::traversal_category traversal_category;

    // IncidenceGraph requirements
    typedef filter_iterator< OutEdgePred, typename Traits::out_edge_iterator >
        out_edge_iterator;

    typedef typename Traits::degree_size_type degree_size_type;

    // AdjacencyGraph requirements
    typedef typename adjacency_iterator_generator< self, vertex_descriptor,
        out_edge_iterator >::type adjacency_iterator;

    // BidirectionalGraph requirements
    typedef filter_iterator< InEdgePred, typename Traits::in_edge_iterator >
        in_edge_iterator;

    // VertexListGraph requirements
    typedef filter_iterator< VertexPredicate, typename Traits::vertex_iterator >
        vertex_iterator;
    typedef typename Traits::vertices_size_type vertices_size_type;

    // EdgeListGraph requirements
    typedef filter_iterator< EdgePred, typename Traits::edge_iterator >
        edge_iterator;
    typedef typename Traits::edges_size_type edges_size_type;

    typedef filtered_graph_tag graph_tag;

    // Bundled properties support
    template < typename Descriptor >
    typename graph::detail::bundled_result< Graph, Descriptor >::type&
    operator[](Descriptor x)
    {
        return const_cast< Graph& >(this->m_g)[x];
    }

    template < typename Descriptor >
    typename graph::detail::bundled_result< Graph, Descriptor >::type const&
    operator[](Descriptor x) const
    {
        return this->m_g[x];
    }

    static vertex_descriptor null_vertex() { return Traits::null_vertex(); }

    // private:
    EdgePredicate m_edge_pred;
    VertexPredicate m_vertex_pred;
};

// Do not instantiate these unless needed
template < typename Graph, typename EdgePredicate, typename VertexPredicate >
struct vertex_property_type<
    filtered_graph< Graph, EdgePredicate, VertexPredicate > >
: vertex_property_type< Graph >
{
};

template < typename Graph, typename EdgePredicate, typename VertexPredicate >
struct edge_property_type<
    filtered_graph< Graph, EdgePredicate, VertexPredicate > >
: edge_property_type< Graph >
{
};

template < typename Graph, typename EdgePredicate, typename VertexPredicate >
struct graph_property_type<
    filtered_graph< Graph, EdgePredicate, VertexPredicate > >
: graph_property_type< Graph >
{
};

template < typename Graph, typename EdgePredicate, typename VertexPredicate >
struct vertex_bundle_type<
    filtered_graph< Graph, EdgePredicate, VertexPredicate > >
: vertex_bundle_type< Graph >
{
};

template < typename Graph, typename EdgePredicate, typename VertexPredicate >
struct edge_bundle_type<
    filtered_graph< Graph, EdgePredicate, VertexPredicate > >
: edge_bundle_type< Graph >
{
};

template < typename Graph, typename EdgePredicate, typename VertexPredicate >
struct graph_bundle_type<
    filtered_graph< Graph, EdgePredicate, VertexPredicate > >
: graph_bundle_type< Graph >
{
};

//===========================================================================
// Non-member functions for the Filtered Edge Graph

// Helper functions
template < typename Graph, typename EdgePredicate >
inline filtered_graph< Graph, EdgePredicate > make_filtered_graph(
    Graph& g, EdgePredicate ep)
{
    return filtered_graph< Graph, EdgePredicate >(g, ep);
}
template < typename Graph, typename EdgePredicate, typename VertexPredicate >
inline filtered_graph< Graph, EdgePredicate, VertexPredicate >
make_filtered_graph(Graph& g, EdgePredicate ep, VertexPredicate vp)
{
    return filtered_graph< Graph, EdgePredicate, VertexPredicate >(g, ep, vp);
}

template < typename Graph, typename EdgePredicate >
inline filtered_graph< const Graph, EdgePredicate > make_filtered_graph(
    const Graph& g, EdgePredicate ep)
{
    return filtered_graph< const Graph, EdgePredicate >(g, ep);
}
template < typename Graph, typename EdgePredicate, typename VertexPredicate >
inline filtered_graph< const Graph, EdgePredicate, VertexPredicate >
make_filtered_graph(const Graph& g, EdgePredicate ep, VertexPredicate vp)
{
    return filtered_graph< const Graph, EdgePredicate, VertexPredicate >(
        g, ep, vp);
}

template < typename G, typename EP, typename VP >
std::pair< typename filtered_graph< G, EP, VP >::vertex_iterator,
    typename filtered_graph< G, EP, VP >::vertex_iterator >
vertices(const filtered_graph< G, EP, VP >& g)
{
    typedef filtered_graph< G, EP, VP > Graph;
    typename graph_traits< G >::vertex_iterator f, l;
    boost::tie(f, l) = vertices(g.m_g);
    typedef typename Graph::vertex_iterator iter;
    return std::make_pair(
        iter(g.m_vertex_pred, f, l), iter(g.m_vertex_pred, l, l));
}

template < typename G, typename EP, typename VP >
std::pair< typename filtered_graph< G, EP, VP >::edge_iterator,
    typename filtered_graph< G, EP, VP >::edge_iterator >
edges(const filtered_graph< G, EP, VP >& g)
{
    typedef filtered_graph< G, EP, VP > Graph;
    typename Graph::EdgePred pred(g.m_edge_pred, g.m_vertex_pred, g);
    typename graph_traits< G >::edge_iterator f, l;
    boost::tie(f, l) = edges(g.m_g);
    typedef typename Graph::edge_iterator iter;
    return std::make_pair(iter(pred, f, l), iter(pred, l, l));
}

// An alternative for num_vertices() and num_edges() would be to
// count the number in the filtered graph. This is problematic
// because of the interaction with the vertex indices...  they would
// no longer go from 0 to num_vertices(), which would cause trouble
// for algorithms allocating property storage in an array. We could
// try to create a mapping to new recalibrated indices, but I don't
// see an efficient way to do this.
//
// However, the current solution is still unsatisfactory because
// the following semantic constraints no longer hold:
// boost::tie(vi, viend) = vertices(g);
// assert(std::distance(vi, viend) == num_vertices(g));

template < typename G, typename EP, typename VP >
typename filtered_graph< G, EP, VP >::vertices_size_type num_vertices(
    const filtered_graph< G, EP, VP >& g)
{
    return num_vertices(g.m_g);
}

template < typename G, typename EP, typename VP >
typename filtered_graph< G, EP, VP >::edges_size_type num_edges(
    const filtered_graph< G, EP, VP >& g)
{
    return num_edges(g.m_g);
}

template < typename G >
typename filtered_graph_base< G >::vertex_descriptor source(
    typename filtered_graph_base< G >::edge_descriptor e,
    const filtered_graph_base< G >& g)
{
    return source(e, g.m_g);
}

template < typename G >
typename filtered_graph_base< G >::vertex_descriptor target(
    typename filtered_graph_base< G >::edge_descriptor e,
    const filtered_graph_base< G >& g)
{
    return target(e, g.m_g);
}

template < typename G, typename EP, typename VP >
std::pair< typename filtered_graph< G, EP, VP >::out_edge_iterator,
    typename filtered_graph< G, EP, VP >::out_edge_iterator >
out_edges(typename filtered_graph< G, EP, VP >::vertex_descriptor u,
    const filtered_graph< G, EP, VP >& g)
{
    typedef filtered_graph< G, EP, VP > Graph;
    typename Graph::OutEdgePred pred(g.m_edge_pred, g.m_vertex_pred, g);
    typedef typename Graph::out_edge_iterator iter;
    typename graph_traits< G >::out_edge_iterator f, l;
    boost::tie(f, l) = out_edges(u, g.m_g);
    return std::make_pair(iter(pred, f, l), iter(pred, l, l));
}

template < typename G, typename EP, typename VP >
typename filtered_graph< G, EP, VP >::degree_size_type out_degree(
    typename filtered_graph< G, EP, VP >::vertex_descriptor u,
    const filtered_graph< G, EP, VP >& g)
{
    typename filtered_graph< G, EP, VP >::degree_size_type n = 0;
    typename filtered_graph< G, EP, VP >::out_edge_iterator f, l;
    for (boost::tie(f, l) = out_edges(u, g); f != l; ++f)
        ++n;
    return n;
}

template < typename G, typename EP, typename VP >
std::pair< typename filtered_graph< G, EP, VP >::adjacency_iterator,
    typename filtered_graph< G, EP, VP >::adjacency_iterator >
adjacent_vertices(typename filtered_graph< G, EP, VP >::vertex_descriptor u,
    const filtered_graph< G, EP, VP >& g)
{
    typedef filtered_graph< G, EP, VP > Graph;
    typedef typename Graph::adjacency_iterator adjacency_iterator;
    typename Graph::out_edge_iterator f, l;
    boost::tie(f, l) = out_edges(u, g);
    return std::make_pair(adjacency_iterator(f, const_cast< Graph* >(&g)),
        adjacency_iterator(l, const_cast< Graph* >(&g)));
}

template < typename G, typename EP, typename VP >
std::pair< typename filtered_graph< G, EP, VP >::in_edge_iterator,
    typename filtered_graph< G, EP, VP >::in_edge_iterator >
in_edges(typename filtered_graph< G, EP, VP >::vertex_descriptor u,
    const filtered_graph< G, EP, VP >& g)
{
    typedef filtered_graph< G, EP, VP > Graph;
    typename Graph::InEdgePred pred(g.m_edge_pred, g.m_vertex_pred, g);
    typedef typename Graph::in_edge_iterator iter;
    typename graph_traits< G >::in_edge_iterator f, l;
    boost::tie(f, l) = in_edges(u, g.m_g);
    return std::make_pair(iter(pred, f, l), iter(pred, l, l));
}

template < typename G, typename EP, typename VP >
typename filtered_graph< G, EP, VP >::degree_size_type in_degree(
    typename filtered_graph< G, EP, VP >::vertex_descriptor u,
    const filtered_graph< G, EP, VP >& g)
{
    typename filtered_graph< G, EP, VP >::degree_size_type n = 0;
    typename filtered_graph< G, EP, VP >::in_edge_iterator f, l;
    for (boost::tie(f, l) = in_edges(u, g); f != l; ++f)
        ++n;
    return n;
}

template < typename G, typename EP, typename VP >
typename enable_if< typename is_directed_graph< G >::type,
    typename filtered_graph< G, EP, VP >::degree_size_type >::type
degree(typename filtered_graph< G, EP, VP >::vertex_descriptor u,
    const filtered_graph< G, EP, VP >& g)
{
    return out_degree(u, g) + in_degree(u, g);
}

template < typename G, typename EP, typename VP >
typename disable_if< typename is_directed_graph< G >::type,
    typename filtered_graph< G, EP, VP >::degree_size_type >::type
degree(typename filtered_graph< G, EP, VP >::vertex_descriptor u,
    const filtered_graph< G, EP, VP >& g)
{
    return out_degree(u, g);
}

template < typename G, typename EP, typename VP >
std::pair< typename filtered_graph< G, EP, VP >::edge_descriptor, bool > edge(
    typename filtered_graph< G, EP, VP >::vertex_descriptor u,
    typename filtered_graph< G, EP, VP >::vertex_descriptor v,
    const filtered_graph< G, EP, VP >& g)
{
    typename graph_traits< G >::edge_descriptor e;
    bool exists;
    boost::tie(e, exists) = edge(u, v, g.m_g);
    return std::make_pair(e, exists && g.m_edge_pred(e));
}

template < typename G, typename EP, typename VP >
std::pair< typename filtered_graph< G, EP, VP >::out_edge_iterator,
    typename filtered_graph< G, EP, VP >::out_edge_iterator >
edge_range(typename filtered_graph< G, EP, VP >::vertex_descriptor u,
    typename filtered_graph< G, EP, VP >::vertex_descriptor v,
    const filtered_graph< G, EP, VP >& g)
{
    typedef filtered_graph< G, EP, VP > Graph;
    typename Graph::OutEdgePred pred(g.m_edge_pred, g.m_vertex_pred, g);
    typedef typename Graph::out_edge_iterator iter;
    typename graph_traits< G >::out_edge_iterator f, l;
    boost::tie(f, l) = edge_range(u, v, g.m_g);
    return std::make_pair(iter(pred, f, l), iter(pred, l, l));
}

//===========================================================================
// Property map

template < typename G, typename EP, typename VP, typename Property >
struct property_map< filtered_graph< G, EP, VP >, Property >
: property_map< G, Property >
{
};

template < typename G, typename EP, typename VP, typename Property >
typename property_map< G, Property >::type get(
    Property p, filtered_graph< G, EP, VP >& g)
{
    return get(p, const_cast< G& >(g.m_g));
}

template < typename G, typename EP, typename VP, typename Property >
typename property_map< G, Property >::const_type get(
    Property p, const filtered_graph< G, EP, VP >& g)
{
    return get(p, (const G&)g.m_g);
}

template < typename G, typename EP, typename VP, typename Property,
    typename Key >
typename property_map_value< G, Property >::type get(
    Property p, const filtered_graph< G, EP, VP >& g, const Key& k)
{
    return get(p, (const G&)g.m_g, k);
}

template < typename G, typename EP, typename VP, typename Property,
    typename Key, typename Value >
void put(Property p, const filtered_graph< G, EP, VP >& g, const Key& k,
    const Value& val)
{
    put(p, const_cast< G& >(g.m_g), k, val);
}

//===========================================================================
// Some filtered subgraph specializations

template < typename Graph, typename Set > struct vertex_subset_filter
{
    typedef filtered_graph< Graph, keep_all, is_in_subset< Set > > type;
};
template < typename Graph, typename Set >
inline typename vertex_subset_filter< Graph, Set >::type
make_vertex_subset_filter(Graph& g, const Set& s)
{
    typedef typename vertex_subset_filter< Graph, Set >::type Filter;
    is_in_subset< Set > p(s);
    return Filter(g, keep_all(), p);
}

// This is misspelled, but present for backwards compatibility; new code
// should use the version below that has the correct spelling.
template < typename Graph, typename Set > struct vertex_subset_compliment_filter
{
    typedef filtered_graph< Graph, keep_all, is_not_in_subset< Set > > type;
};
template < typename Graph, typename Set >
inline typename vertex_subset_compliment_filter< Graph, Set >::type
make_vertex_subset_compliment_filter(Graph& g, const Set& s)
{
    typedef typename vertex_subset_compliment_filter< Graph, Set >::type Filter;
    is_not_in_subset< Set > p(s);
    return Filter(g, keep_all(), p);
}

template < typename Graph, typename Set > struct vertex_subset_complement_filter
{
    typedef filtered_graph< Graph, keep_all, is_not_in_subset< Set > > type;
};
template < typename Graph, typename Set >
inline typename vertex_subset_complement_filter< Graph, Set >::type
make_vertex_subset_complement_filter(Graph& g, const Set& s)
{
    typedef typename vertex_subset_complement_filter< Graph, Set >::type Filter;
    is_not_in_subset< Set > p(s);
    return Filter(g, keep_all(), p);
}

// Filter that uses a property map whose value_type is a boolean
template < typename PropertyMap > struct property_map_filter
{

    property_map_filter() {}

    property_map_filter(const PropertyMap& property_map)
    : m_property_map(property_map)
    {
    }

    template < typename Key > bool operator()(const Key& key) const
    {
        return (get(m_property_map, key));
    }

private:
    PropertyMap m_property_map;
};

} // namespace boost

#endif // BOOST_FILTERED_GRAPH_HPP

/* filtered_graph.hpp
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
*/