//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef BOOST_GRAPH_EDGE_LIST_HPP
#define BOOST_GRAPH_EDGE_LIST_HPP

#include <iterator>
#include <boost/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/range/irange.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>

namespace boost
{

//
// The edge_list class is an EdgeListGraph module that is constructed
// from a pair of iterators whose value type is a pair of vertex
// descriptors.
//
// For example:
//
//  typedef std::pair<int,int> E;
//  list<E> elist;
//  ...
//  typedef edge_list<list<E>::iterator> Graph;
//  Graph g(elist.begin(), elist.end());
//
// If the iterators are random access, then Graph::edge_descriptor
// is of Integral type, otherwise it is a struct, though it is
// convertible to an Integral type.
//

struct edge_list_tag
{
};

// The implementation class for edge_list.
template < class G, class EdgeIter, class T, class D > class edge_list_impl
{
public:
    typedef D edge_id;
    typedef T Vpair;
    typedef typename Vpair::first_type V;
    typedef V vertex_descriptor;
    typedef edge_list_tag graph_tag;
    typedef void edge_property_type;

    struct edge_descriptor
    {
        edge_descriptor() {}
        edge_descriptor(EdgeIter p, edge_id id) : _ptr(p), _id(id) {}
        operator edge_id() { return _id; }
        EdgeIter _ptr;
        edge_id _id;
    };
    typedef edge_descriptor E;

    struct edge_iterator
    {
        typedef edge_iterator self;
        typedef E value_type;
        typedef E& reference;
        typedef E* pointer;
        typedef std::ptrdiff_t difference_type;
        typedef std::input_iterator_tag iterator_category;
        edge_iterator() {}
        edge_iterator(EdgeIter iter) : _iter(iter), _i(0) {}
        E operator*() { return E(_iter, _i); }
        self& operator++()
        {
            ++_iter;
            ++_i;
            return *this;
        }
        self operator++(int)
        {
            self t = *this;
            ++(*this);
            return t;
        }
        bool operator==(const self& x) { return _iter == x._iter; }
        bool operator!=(const self& x) { return _iter != x._iter; }
        EdgeIter _iter;
        edge_id _i;
    };
    typedef void out_edge_iterator;
    typedef void in_edge_iterator;
    typedef void adjacency_iterator;
    typedef void vertex_iterator;
};

template < class G, class EI, class T, class D >
std::pair< typename edge_list_impl< G, EI, T, D >::edge_iterator,
    typename edge_list_impl< G, EI, T, D >::edge_iterator >
edges(const edge_list_impl< G, EI, T, D >& g_)
{
    const G& g = static_cast< const G& >(g_);
    typedef typename edge_list_impl< G, EI, T, D >::edge_iterator edge_iterator;
    return std::make_pair(edge_iterator(g._first), edge_iterator(g._last));
}
template < class G, class EI, class T, class D >
typename edge_list_impl< G, EI, T, D >::vertex_descriptor source(
    typename edge_list_impl< G, EI, T, D >::edge_descriptor e,
    const edge_list_impl< G, EI, T, D >&)
{
    return (*e._ptr).first;
}
template < class G, class EI, class T, class D >
typename edge_list_impl< G, EI, T, D >::vertex_descriptor target(
    typename edge_list_impl< G, EI, T, D >::edge_descriptor e,
    const edge_list_impl< G, EI, T, D >&)
{
    return (*e._ptr).second;
}

template < class D, class E >
class el_edge_property_map
: public put_get_helper< D, el_edge_property_map< D, E > >
{
public:
    typedef E key_type;
    typedef D value_type;
    typedef D reference;
    typedef readable_property_map_tag category;

    value_type operator[](key_type e) const { return e._i; }
};
struct edge_list_edge_property_selector
{
    template < class Graph, class Property, class Tag > struct bind_
    {
        typedef el_edge_property_map< typename Graph::edge_id,
            typename Graph::edge_descriptor >
            type;
        typedef type const_type;
    };
};
template <> struct edge_property_selector< edge_list_tag >
{
    typedef edge_list_edge_property_selector type;
};

template < class G, class EI, class T, class D >
typename property_map< edge_list_impl< G, EI, T, D >, edge_index_t >::type get(
    edge_index_t, const edge_list_impl< G, EI, T, D >&)
{
    typedef typename property_map< edge_list_impl< G, EI, T, D >,
        edge_index_t >::type EdgeIndexMap;
    return EdgeIndexMap();
}

template < class G, class EI, class T, class D >
inline D get(edge_index_t, const edge_list_impl< G, EI, T, D >&,
    typename edge_list_impl< G, EI, T, D >::edge_descriptor e)
{
    return e._i;
}

// A specialized implementation for when the iterators are random access.

struct edge_list_ra_tag
{
};

template < class G, class EdgeIter, class T, class D > class edge_list_impl_ra
{
public:
    typedef D edge_id;
    typedef T Vpair;
    typedef typename Vpair::first_type V;
    typedef edge_list_ra_tag graph_tag;
    typedef void edge_property_type;

    typedef edge_id edge_descriptor;
    typedef V vertex_descriptor;
    typedef typename boost::integer_range< edge_id >::iterator edge_iterator;
    typedef void out_edge_iterator;
    typedef void in_edge_iterator;
    typedef void adjacency_iterator;
    typedef void vertex_iterator;
};

template < class G, class EI, class T, class D >
std::pair< typename edge_list_impl_ra< G, EI, T, D >::edge_iterator,
    typename edge_list_impl_ra< G, EI, T, D >::edge_iterator >
edges(const edge_list_impl_ra< G, EI, T, D >& g_)
{
    const G& g = static_cast< const G& >(g_);
    typedef
        typename edge_list_impl_ra< G, EI, T, D >::edge_iterator edge_iterator;
    return std::make_pair(edge_iterator(0), edge_iterator(g._last - g._first));
}
template < class G, class EI, class T, class D >
typename edge_list_impl_ra< G, EI, T, D >::vertex_descriptor source(
    typename edge_list_impl_ra< G, EI, T, D >::edge_descriptor e,
    const edge_list_impl_ra< G, EI, T, D >& g_)
{
    const G& g = static_cast< const G& >(g_);
    return g._first[e].first;
}
template < class G, class EI, class T, class D >
typename edge_list_impl_ra< G, EI, T, D >::vertex_descriptor target(
    typename edge_list_impl_ra< G, EI, T, D >::edge_descriptor e,
    const edge_list_impl_ra< G, EI, T, D >& g_)
{
    const G& g = static_cast< const G& >(g_);
    return g._first[e].second;
}
template < class E >
class el_ra_edge_property_map
: public put_get_helper< E, el_ra_edge_property_map< E > >
{
public:
    typedef E key_type;
    typedef E value_type;
    typedef E reference;
    typedef readable_property_map_tag category;

    value_type operator[](key_type e) const { return e; }
};
struct edge_list_ra_edge_property_selector
{
    template < class Graph, class Property, class Tag > struct bind_
    {
        typedef el_ra_edge_property_map< typename Graph::edge_descriptor > type;
        typedef type const_type;
    };
};
template <> struct edge_property_selector< edge_list_ra_tag >
{
    typedef edge_list_ra_edge_property_selector type;
};
template < class G, class EI, class T, class D >
inline typename property_map< edge_list_impl_ra< G, EI, T, D >,
    edge_index_t >::type
get(edge_index_t, const edge_list_impl_ra< G, EI, T, D >&)
{
    typedef typename property_map< edge_list_impl_ra< G, EI, T, D >,
        edge_index_t >::type EdgeIndexMap;
    return EdgeIndexMap();
}

template < class G, class EI, class T, class D >
inline D get(edge_index_t, const edge_list_impl_ra< G, EI, T, D >&,
    typename edge_list_impl_ra< G, EI, T, D >::edge_descriptor e)
{
    return e;
}

// Some helper classes for determining if the iterators are random access
template < class Cat > struct is_random
{
    enum
    {
        RET = false
    };
    typedef mpl::false_ type;
};
template <> struct is_random< std::random_access_iterator_tag >
{
    enum
    {
        RET = true
    };
    typedef mpl::true_ type;
};

// The edge_list class conditionally inherits from one of the
// above two classes.

template < class EdgeIter,
#if !defined BOOST_NO_STD_ITERATOR_TRAITS
    class T = typename std::iterator_traits< EdgeIter >::value_type,
    class D = typename std::iterator_traits< EdgeIter >::difference_type,
    class Cat = typename std::iterator_traits< EdgeIter >::iterator_category >
#else
    class T, class D, class Cat >
#endif
class edge_list
: public mpl::if_< typename is_random< Cat >::type,
      edge_list_impl_ra< edge_list< EdgeIter, T, D, Cat >, EdgeIter, T, D >,
      edge_list_impl< edge_list< EdgeIter, T, D, Cat >, EdgeIter, T, D > >::type
{
public:
    typedef directed_tag directed_category;
    typedef allow_parallel_edge_tag edge_parallel_category;
    typedef edge_list_graph_tag traversal_category;
    typedef std::size_t edges_size_type;
    typedef std::size_t vertices_size_type;
    typedef std::size_t degree_size_type;
    edge_list(EdgeIter first, EdgeIter last) : _first(first), _last(last)
    {
        m_num_edges = std::distance(first, last);
    }
    edge_list(EdgeIter first, EdgeIter last, edges_size_type E)
    : _first(first), _last(last), m_num_edges(E)
    {
    }

    EdgeIter _first, _last;
    edges_size_type m_num_edges;
};

template < class EdgeIter, class T, class D, class Cat >
std::size_t num_edges(const edge_list< EdgeIter, T, D, Cat >& el)
{
    return el.m_num_edges;
}

#ifndef BOOST_NO_STD_ITERATOR_TRAITS
template < class EdgeIter >
inline edge_list< EdgeIter > make_edge_list(EdgeIter first, EdgeIter last)
{
    return edge_list< EdgeIter >(first, last);
}
#endif

} /* namespace boost */

#endif /* BOOST_GRAPH_EDGE_LIST_HPP */

/* edge_list.hpp
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
*/