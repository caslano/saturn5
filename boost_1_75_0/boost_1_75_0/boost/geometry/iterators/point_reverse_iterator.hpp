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
VSgQP3Nad1LcPPvDLOwzFvOmLL1FbqbbFV85sHSMhz9xldgAekgYZOvCA2vjZ8Ydfqsbyj28oXhTkewuee+jZ0lvaH+QqVx3uX7naxOtJP0j8w+YWyzHkKbxl9Bwnu/6ijrau1yRe/dfI+5NQ7/pWJcA9iRljPjlFzrhvFzgXZGR4cV17uPKNLZV5tlees/bbcHarWK3GrerAdK/zRaemu/pLGir7ud1sxQ47pG3PREbH36boKeTwXc9l+VI5170P2UQ4zIugRPeQEGOxG2q9hZTTYbfbME+lfeKVTcNyMg6haT1Uw1bMmQn+DMOrnEX8D1LgF63JgPChGe3q0K3e24cNVYZtnHuPgQY6NV+4Clerk1tndK3ZMlz3JXPLqjx+fDJ+Rvzt3wSS7mTisrTlt1HLgJqKnoqU7r9u4FBCWOTjHG/OYrKFt9tnJSZ7fGK1NacPjze46wR2JxbYC2IvK/cQtHxUsonM4R9KozwQ/r+ivqUS+axrd7FSWt9z+JS4qy+QXtR5wENytGlVDmw9AvdwgNUcGS7OmxSLv935imP3qRvs07yAWxG6nSAHaZNa+zlr+WhqGiZJWFo1WqV1XXoWVJ6Tr3q82p/IUmuOC48AZ3+aCzA4/gH1kLqpszm8KXXfFl/8b74iYuTOUX2mRNMGyNmjbAUs7PWIEWunw5PNjnXthW5DXTEE92NvmzjhPySlOaSHb4Ekk1F
*/