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