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
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
*/