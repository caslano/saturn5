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