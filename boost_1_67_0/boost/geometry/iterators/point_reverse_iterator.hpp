// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_POINT_REVERSE_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_POINT_REVERSE_ITERATOR_HPP

#include <iterator>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>

namespace boost { namespace geometry
{


// MK:: need to add doc here
template <typename Geometry>
class point_reverse_iterator
    : public std::reverse_iterator<point_iterator<Geometry> >
{
private:
    typedef std::reverse_iterator<point_iterator<Geometry> > base_type;

    template <typename OtherGeometry> friend class point_reverse_iterator;
    template <typename G>
    friend inline point_reverse_iterator<G> points_rbegin(G&);

    template <typename G>
    friend inline point_reverse_iterator<G> points_rend(G&);

    inline point_reverse_iterator(base_type const& base_it)
        : base_type(base_it) {}

public:
    inline point_reverse_iterator() {}

    template <typename OtherGeometry>
    inline
    point_reverse_iterator(point_reverse_iterator<OtherGeometry> const& other)
        : base_type(other.base())
    {
        static const bool is_conv = boost::is_convertible
            <
                std::reverse_iterator<point_iterator<Geometry> >,
                std::reverse_iterator<point_iterator<OtherGeometry> >
            >::value;

        BOOST_MPL_ASSERT_MSG((is_conv),
                             NOT_CONVERTIBLE,
                             (point_reverse_iterator<OtherGeometry>));
    }
};


// MK:: need to add doc here
template <typename Geometry>
inline point_reverse_iterator<Geometry>
points_rbegin(Geometry& geometry)
{
    return std::reverse_iterator
        <
            point_iterator<Geometry>
        >(points_end(geometry));
}


// MK:: need to add doc here
template <typename Geometry>
inline point_reverse_iterator<Geometry>
points_rend(Geometry& geometry)
{
    return std::reverse_iterator
        <
            point_iterator<Geometry>
        >(points_begin(geometry));
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_POINT_REVERSE_ITERATOR_HPP

/* point_reverse_iterator.hpp
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
*/