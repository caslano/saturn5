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