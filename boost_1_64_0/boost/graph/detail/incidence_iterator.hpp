//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_DETAIL_INCIDENCE_ITERATOR_HPP
#define BOOST_GRAPH_DETAIL_INCIDENCE_ITERATOR_HPP

#include <utility>
#include <iterator>

// OBSOLETE

namespace boost
{

namespace detail
{
    // EdgeDir tags
    struct in_edge_tag
    {
    };
    struct out_edge_tag
    {
    };

    template < class Vertex, class Edge, class Iterator1D, class EdgeDir >
    struct bidir_incidence_iterator
    {
        typedef bidir_incidence_iterator self;
        typedef Edge edge_type;
        typedef typename Edge::property_type EdgeProperty;

    public:
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;
        typedef edge_type reference;
        typedef edge_type value_type;
        typedef value_type* pointer;
        inline bidir_incidence_iterator() {}
        inline bidir_incidence_iterator(Iterator1D ii, Vertex src)
        : i(ii), _src(src)
        {
        }

        inline self& operator++()
        {
            ++i;
            return *this;
        }
        inline self operator++(int)
        {
            self tmp = *this;
            ++(*this);
            return tmp;
        }

        inline reference operator*() const { return deref_helper(EdgeDir()); }
        inline self* operator->() { return this; }

        Iterator1D& iter() { return i; }
        const Iterator1D& iter() const { return i; }

        Iterator1D i;
        Vertex _src;

    protected:
        inline reference deref_helper(out_edge_tag) const
        {
            return edge_type(_src, (*i).get_target(), &(*i).get_property());
        }
        inline reference deref_helper(in_edge_tag) const
        {
            return edge_type((*i).get_target(), _src, &(*i).get_property());
        }
    };

    template < class V, class E, class Iter, class Dir >
    inline bool operator==(const bidir_incidence_iterator< V, E, Iter, Dir >& x,
        const bidir_incidence_iterator< V, E, Iter, Dir >& y)
    {
        return x.i == y.i;
    }
    template < class V, class E, class Iter, class Dir >
    inline bool operator!=(const bidir_incidence_iterator< V, E, Iter, Dir >& x,
        const bidir_incidence_iterator< V, E, Iter, Dir >& y)
    {
        return x.i != y.i;
    }

}
}
#endif

/* incidence_iterator.hpp
HAU/vO31qGQJIJwz6C8+5Ft10BwpdpY7ub7OXCrwRJwiOIh9GngoHdKfX5t46rAeEzBKch3CGevavmQ9bgbPj/AjDji0RBEHa8n6wQn9MzpJHVkj6lHQQOTuMxoL8Dn45Ptd/iyLC17oDpOEBYqDhSmQb1Zthg4LeIQMRQWNO7C37pSSIlzD+A7ARQPu/06+PxTl3aMq7tCc1NIPwoBqGGvAJwqXgCdgP/ORTGl3v2XjLQXuFebK0g2l1f6QeDcVPQbetmQU+P1MWSwBr+q21BmeXF89qBIW4WjIaj+hZ35EFdx1m2E2/2zYGFaNC2QlMCGijprCpjGHSv4iQ8C03V3nI9F0wsdg5eldeKBYfFwJAPPWhH4Yoie7lqL6BW7Ux38bozyRGf3HKXUHJIF/++O8AQFk52GFRPVwlWTRNcx/364Fd9w8O959cuCxDAjupl+tC8moE2jaOKlNTtNkaIIHxaLI6V3ZbIVvsBeXG7Ig1vv+eBbcIX3g+frx93tvSbpffYSUrsErQx4LobhfV0Ea7EUJH6aatK9L4ZVxEcl4BeTlof8uydWjjQ==
*/