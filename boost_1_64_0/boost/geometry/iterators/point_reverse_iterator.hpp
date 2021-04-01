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
Yg94lgEJSOs8vtjUhOvLKvFbTPaogozfQatk6rbZHEUJqgOeXUtme+tC11+GE8Bh7Cxjs8sYBrNgDoR0NlqdQ1t3xPuEl+tqFQfKZYyVYcHbN311yvL+IqnFYeISo4gb+e2+K3GsUcHkwoFSTWS/Rbrskc/Oo2w0KS93SNrC7opzp8v1knYdTDxB9Iz/RsFF6XYyliejxD/+8noeTrJZNyXstaPtK/qzyFL4zhGPpHqEIVmt2ka5Yse5XxO8fiBV/gdnKlI0yf3GQQoieS1uZ2B0N2DpMyz9BM1bfjjFmlIibghMPOqucHftDI06nJ//bXgrqOvBTfUavDSJaCz/gIxfemRfoag1cIijP3pL3tHRwglpHBJ8z+tjGro+oEITEr8AaByQ/2Z5iq7EStWyKPDPskbfDrY5SOe8hvcxKBqEpupowghzbJKNvlyKQXjKeIF/tA0AYYPQEnKM/Vb9KquloSM0KiHSDgSg68UUUfa+fL4afHtCGLfaZMR0XX2N7JQ4r9k6ey/VQX3lb59QRMB/PT5Hu+F5kKGmwSe3CExgAVdyA6/UJlERdQ==
*/