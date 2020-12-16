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
tdXMgVVvdPbeXaqxPsSgjR7nuL6s57m+NG04u6ZVP6y+ZRh3xuNYjfX5GteZutD4DKH2px1rqq5W90i751spvSA3X0YEuTM1R8sTzjk4qaeCyhzUrLdwzJf1WrvUqZvSyvLL3akfnapMC5i1g685eurPU2llpSVe3WqUY/+VG1d5txyUB2x9Z2X1DB0PeYoTr2tMaWuukZaC+qLUd/wUaalr2txQ7erVbIc3Z683OedOROM0ZTXq8zrvXPvRjfs3NeO2Ak0bWiTWk+25C3NS8Y9OHDjbuqXafXq35k5bkscczx98TO/0O5/RL5GGTvuh1ExT7vUASq9cTLe52nWb6hu2qgyL1VHWw/l9bV7fGLKhqUHtY/NUNLFNbV7H4GMOZ6zi6/001cHvCpRDsR404poFdbhGeuZWt+tXum5Nytfa+3vMzscFsXbuGO2djHQl0Na9Ek+5PDsgBwNIO2Xv20Muz57J50AMadTDYHsP4i5YryX8Jdhr7X5t7cvUOvVQYPcmlLonlWN9ptv8iNQfcwGFekWvEdQ3OiOPlwKraLJuHZgNUCoS3B/MhMGkIGcmDEbc52rsncR/hw0+/1c4+/m77XU72oYem6WNuC3M6sp5CjMWC1U+vzYsUGq1/i0XEkqFnn9CtrrQbs2razY6Pv6YNdVY67/fC+5gsM7M3envNahx9ktudk5O6nNzpaKRnTaQruuPCieLe5Saj4O88vAp3btZp3JYp5mjNdoiM4c1b9NjK3st5lLHHb5/Rn77fn8oyX/v4qTgWxe6GrMH5Dgfu+db0sqK8qS9vcuReq/Xfc6v4+dLyk7Ta6Tuavseme85fVW+O+/ZWqfXkv8Op2/N2Bz1aPVX+LV5xeV+Tr9us+T0GzbL2l+DtJfVLbJu6r21RTr/qL5STL0DJx2ATCKd1bRe3eTMX5mi36VR44b1gVHI1zTHXvcA/wPNt7jLfmJJ6z5DYjtJ5QV8nCLIdcWDOunSHNZ4laRR0PN0zUg1M8xViflS3hpkAst7peSj4eyQfSVlZcHxqlX3834aNmvsp95WF5vaeJ6LqYdbXKRroOw0SF9bVFy6omT16hXqkLTS/IUmfpkOMkE62EHqIPn/AsPtq1EwgJ9KKS4ozPPbm4s1HpVI6nzN23H7YVpZoT7ngpubNbbdTB23ZKnvIk2QrY8I47+9NSE/r6zcd9+osf3ER7yef+OGTXKaQSfoihAnHsicQH6IXSeFenmIa66RQt8iNxCFz9ypn8Q4aSaB0CfNfh7S+QeXpEW3dYxl7rVZ6vjPbFbHZVD3/Zw01dW/Xpr7ZzQbnOjfuEqpb/mnW/WzJzGP7A7l/xHadyo7lsIzyGqPP/vC+Pvo9PIy/8zbgSB2YurWTDPYhJ/X/XWQ2cd5YmXZssrilfosJCtMYVb7t9xhzbLYMoO0Uj1Ln9raJC+Q/8qZcdmlQ4Fb/dIvEgqfWSt+SW7mla8p00+5oSgLs/pFH08PeM+75wk32qI9PfS81rI4OJsnzFWf9ZtYwZoRijvXsG1sUjPDGp5Vam7AN9Y99IzBnCDPGu+xcOaSWb3KfAwsNrTOm5Umhf2Au5bBKksjy+EurYoNv9Hh5VyijFBszrjN8XjT0B0fZEjZXIuTtzGo8na+L7H04XDOD2r1IK5WRuViZhGGQvReDTLrkmq10TD1ZDSnhjREU31SeNaBTIwusDni9IkAS7hYS2sPaVrMebaLRmtMkbl4tI6LCM+zNGUmy1tUNvlNdfGfVitM/PyiELXKvM//M014c0Qdr9UejyXH15kD62npaALTQkolBlmWV6XhOrdeimt6UEfe6/eocUENr54Uy7VuZyfG0lCGkoyOcZq5n2g=
*/