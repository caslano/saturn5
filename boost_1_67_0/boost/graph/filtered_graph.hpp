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