//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2010 Thomas Claveirole
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Thomas Claveirole
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_ADJACENCY_LIST_HPP
#define BOOST_GRAPH_ADJACENCY_LIST_HPP

#include <boost/config.hpp>

#include <vector>
#include <list>
#include <set>

#include <boost/unordered_set.hpp>

#include <boost/scoped_ptr.hpp>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_mutability_traits.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/graph/detail/edge.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/named_graph.hpp>

namespace boost
{

//===========================================================================
// Selectors for the VertexList and EdgeList template parameters of
// adjacency_list, and the container_gen traits class which is used
// to map the selectors to the container type used to implement the
// graph.

struct vecS
{
};
struct listS
{
};
struct setS
{
};
struct mapS
{
};
struct multisetS
{
};
struct multimapS
{
};
struct hash_setS
{
};
struct hash_mapS
{
};
struct hash_multisetS
{
};
struct hash_multimapS
{
};

template < class Selector, class ValueType > struct container_gen
{
};

template < class ValueType > struct container_gen< listS, ValueType >
{
    typedef std::list< ValueType > type;
};

template < class ValueType > struct container_gen< vecS, ValueType >
{
    typedef std::vector< ValueType > type;
};

template < class ValueType > struct container_gen< mapS, ValueType >
{
    typedef std::set< ValueType > type;
};

template < class ValueType > struct container_gen< setS, ValueType >
{
    typedef std::set< ValueType > type;
};

template < class ValueType > struct container_gen< multisetS, ValueType >
{
    typedef std::multiset< ValueType > type;
};

template < class ValueType > struct container_gen< multimapS, ValueType >
{
    typedef std::multiset< ValueType > type;
};

template < class ValueType > struct container_gen< hash_setS, ValueType >
{
    typedef boost::unordered_set< ValueType > type;
};

template < class ValueType > struct container_gen< hash_mapS, ValueType >
{
    typedef boost::unordered_set< ValueType > type;
};

template < class ValueType > struct container_gen< hash_multisetS, ValueType >
{
    typedef boost::unordered_multiset< ValueType > type;
};

template < class ValueType > struct container_gen< hash_multimapS, ValueType >
{
    typedef boost::unordered_multiset< ValueType > type;
};

template < class StorageSelector > struct parallel_edge_traits
{
};

template <> struct parallel_edge_traits< vecS >
{
    typedef allow_parallel_edge_tag type;
};

template <> struct parallel_edge_traits< listS >
{
    typedef allow_parallel_edge_tag type;
};

template <> struct parallel_edge_traits< setS >
{
    typedef disallow_parallel_edge_tag type;
};

template <> struct parallel_edge_traits< multisetS >
{
    typedef allow_parallel_edge_tag type;
};

template <> struct parallel_edge_traits< hash_setS >
{
    typedef disallow_parallel_edge_tag type;
};

// mapS is obsolete, replaced with setS
template <> struct parallel_edge_traits< mapS >
{
    typedef disallow_parallel_edge_tag type;
};

template <> struct parallel_edge_traits< hash_mapS >
{
    typedef disallow_parallel_edge_tag type;
};

template <> struct parallel_edge_traits< hash_multisetS >
{
    typedef allow_parallel_edge_tag type;
};

template <> struct parallel_edge_traits< hash_multimapS >
{
    typedef allow_parallel_edge_tag type;
};

namespace detail
{
    template < class Directed > struct is_random_access
    {
        enum
        {
            value = false
        };
        typedef mpl::false_ type;
    };
    template <> struct is_random_access< vecS >
    {
        enum
        {
            value = true
        };
        typedef mpl::true_ type;
    };

} // namespace detail

template < typename Selector > struct is_distributed_selector : mpl::false_
{
};

//===========================================================================
// The adjacency_list_traits class, which provides a way to access
// some of the associated types of an adjacency_list type without
// having to first create the adjacency_list type. This is useful
// when trying to create interior vertex or edge properties who's
// value type is a vertex or edge descriptor.

template < class OutEdgeListS = vecS, class VertexListS = vecS,
    class DirectedS = directedS, class EdgeListS = listS >
struct adjacency_list_traits
{
    typedef
        typename detail::is_random_access< VertexListS >::type is_rand_access;
    typedef typename DirectedS::is_bidir_t is_bidir;
    typedef typename DirectedS::is_directed_t is_directed;

    typedef typename mpl::if_< is_bidir, bidirectional_tag,
        typename mpl::if_< is_directed, directed_tag,
            undirected_tag >::type >::type directed_category;

    typedef typename parallel_edge_traits< OutEdgeListS >::type
        edge_parallel_category;

    typedef std::size_t vertices_size_type;
    typedef void* vertex_ptr;
    typedef typename mpl::if_< is_rand_access, vertices_size_type,
        vertex_ptr >::type vertex_descriptor;
    typedef detail::edge_desc_impl< directed_category, vertex_descriptor >
        edge_descriptor;

private:
    // Logic to figure out the edges_size_type
    struct dummy
    {
    };
    typedef typename container_gen< EdgeListS, dummy >::type EdgeContainer;
    typedef typename DirectedS::is_bidir_t BidirectionalT;
    typedef typename DirectedS::is_directed_t DirectedT;
    typedef typename mpl::and_< DirectedT,
        typename mpl::not_< BidirectionalT >::type >::type on_edge_storage;

public:
    typedef typename mpl::if_< on_edge_storage, std::size_t,
        typename EdgeContainer::size_type >::type edges_size_type;
};

} // namespace boost

#include <boost/graph/detail/adjacency_list.hpp>

namespace boost
{

//===========================================================================
// The adjacency_list class.
//

template < class OutEdgeListS = vecS, // a Sequence or an AssociativeContainer
    class VertexListS = vecS, // a Sequence or a RandomAccessContainer
    class DirectedS = directedS, class VertexProperty = no_property,
    class EdgeProperty = no_property, class GraphProperty = no_property,
    class EdgeListS = listS >
class adjacency_list
: public detail::adj_list_gen<
      adjacency_list< OutEdgeListS, VertexListS, DirectedS, VertexProperty,
          EdgeProperty, GraphProperty, EdgeListS >,
      VertexListS, OutEdgeListS, DirectedS, VertexProperty, EdgeProperty,
      GraphProperty, EdgeListS >::type,
  // Support for named vertices
  public graph::maybe_named_graph<
      adjacency_list< OutEdgeListS, VertexListS, DirectedS, VertexProperty,
          EdgeProperty, GraphProperty, EdgeListS >,
      typename adjacency_list_traits< OutEdgeListS, VertexListS, DirectedS,
          EdgeListS >::vertex_descriptor,
      VertexProperty >
{
public:
    typedef GraphProperty graph_property_type;
    typedef typename lookup_one_property< GraphProperty, graph_bundle_t >::type
        graph_bundled;

    typedef VertexProperty vertex_property_type;
    typedef
        typename lookup_one_property< VertexProperty, vertex_bundle_t >::type
            vertex_bundled;

    typedef EdgeProperty edge_property_type;
    typedef typename lookup_one_property< EdgeProperty, edge_bundle_t >::type
        edge_bundled;

private:
    typedef adjacency_list self;
    typedef typename detail::adj_list_gen< self, VertexListS, OutEdgeListS,
        DirectedS, vertex_property_type, edge_property_type, GraphProperty,
        EdgeListS >::type Base;

public:
    typedef typename Base::stored_vertex stored_vertex;
    typedef typename Base::vertices_size_type vertices_size_type;
    typedef typename Base::edges_size_type edges_size_type;
    typedef typename Base::degree_size_type degree_size_type;
    typedef typename Base::vertex_descriptor vertex_descriptor;
    typedef typename Base::edge_descriptor edge_descriptor;
    typedef OutEdgeListS out_edge_list_selector;
    typedef VertexListS vertex_list_selector;
    typedef DirectedS directed_selector;
    typedef EdgeListS edge_list_selector;

    adjacency_list(const GraphProperty& p = GraphProperty())
    : m_property(new graph_property_type(p))
    {
    }

    adjacency_list(const adjacency_list& x)
    : Base(x), m_property(new graph_property_type(*x.m_property))
    {
    }

    adjacency_list& operator=(const adjacency_list& x)
    {
        // TBD: probably should give the strong guarantee
        if (&x != this)
        {
            Base::operator=(x);

            // Copy/swap the ptr since we can't just assign it...
            property_ptr p(new graph_property_type(*x.m_property));
            m_property.swap(p);
        }
        return *this;
    }

    // Required by Mutable Graph
    adjacency_list(vertices_size_type num_vertices,
        const GraphProperty& p = GraphProperty())
    : Base(num_vertices), m_property(new graph_property_type(p))
    {
    }

    // Required by Iterator Constructible Graph
    template < class EdgeIterator >
    adjacency_list(EdgeIterator first, EdgeIterator last, vertices_size_type n,
        edges_size_type = 0, const GraphProperty& p = GraphProperty())
    : Base(n, first, last), m_property(new graph_property_type(p))
    {
    }

    template < class EdgeIterator, class EdgePropertyIterator >
    adjacency_list(EdgeIterator first, EdgeIterator last,
        EdgePropertyIterator ep_iter, vertices_size_type n, edges_size_type = 0,
        const GraphProperty& p = GraphProperty())
    : Base(n, first, last, ep_iter), m_property(new graph_property_type(p))
    {
    }

    void swap(adjacency_list& x)
    {
        // Is there a more efficient way to do this?
        adjacency_list tmp(x);
        x = *this;
        *this = tmp;
    }

    void clear()
    {
        this->clearing_graph();
        Base::clear();
    }

#ifndef BOOST_GRAPH_NO_BUNDLED_PROPERTIES
    // Directly access a vertex or edge bundle
    vertex_bundled& operator[](vertex_descriptor v)
    {
        return get(vertex_bundle, *this)[v];
    }

    const vertex_bundled& operator[](vertex_descriptor v) const
    {
        return get(vertex_bundle, *this)[v];
    }

    edge_bundled& operator[](edge_descriptor e)
    {
        return get(edge_bundle, *this)[e];
    }

    const edge_bundled& operator[](edge_descriptor e) const
    {
        return get(edge_bundle, *this)[e];
    }

    graph_bundled& operator[](graph_bundle_t) { return get_property(*this); }

    graph_bundled const& operator[](graph_bundle_t) const
    {
        return get_property(*this);
    }
#endif

    //  protected:  (would be protected if friends were more portable)
    typedef scoped_ptr< graph_property_type > property_ptr;
    property_ptr m_property;
};

#define ADJLIST_PARAMS                                               \
    typename OEL, typename VL, typename D, typename VP, typename EP, \
        typename GP, typename EL
#define ADJLIST adjacency_list< OEL, VL, D, VP, EP, GP, EL >

template < ADJLIST_PARAMS, typename Tag, typename Value >
inline void set_property(ADJLIST& g, Tag tag, Value const& value)
{
    get_property_value(*g.m_property, tag) = value;
}

template < ADJLIST_PARAMS, typename Tag >
inline typename graph_property< ADJLIST, Tag >::type& get_property(
    ADJLIST& g, Tag tag)
{
    return get_property_value(*g.m_property, tag);
}

template < ADJLIST_PARAMS, typename Tag >
inline typename graph_property< ADJLIST, Tag >::type const& get_property(
    ADJLIST const& g, Tag tag)
{
    return get_property_value(*g.m_property, tag);
}

// dwa 09/25/00 - needed to be more explicit so reverse_graph would work.
template < class Directed, class Vertex, class OutEdgeListS, class VertexListS,
    class DirectedS, class VertexProperty, class EdgeProperty,
    class GraphProperty, class EdgeListS >
inline Vertex source(const detail::edge_base< Directed, Vertex >& e,
    const adjacency_list< OutEdgeListS, VertexListS, DirectedS, VertexProperty,
        EdgeProperty, GraphProperty, EdgeListS >&)
{
    return e.m_source;
}

template < class Directed, class Vertex, class OutEdgeListS, class VertexListS,
    class DirectedS, class VertexProperty, class EdgeProperty,
    class GraphProperty, class EdgeListS >
inline Vertex target(const detail::edge_base< Directed, Vertex >& e,
    const adjacency_list< OutEdgeListS, VertexListS, DirectedS, VertexProperty,
        EdgeProperty, GraphProperty, EdgeListS >&)
{
    return e.m_target;
}

// Mutability Traits
template < ADJLIST_PARAMS > struct graph_mutability_traits< ADJLIST >
{
    typedef mutable_property_graph_tag category;
};

// Can't remove vertices from adjacency lists with VL==vecS
template < typename OEL, typename D, typename VP, typename EP, typename GP,
    typename EL >
struct graph_mutability_traits< adjacency_list< OEL, vecS, D, VP, EP, GP, EL > >
{
    typedef add_only_property_graph_tag category;
};
#undef ADJLIST_PARAMS
#undef ADJLIST

} // namespace boost

#endif // BOOST_GRAPH_ADJACENCY_LIST_HPP

/* adjacency_list.hpp
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
*/