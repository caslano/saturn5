// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_FOR_EACH_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_FOR_EACH_COORDINATE_HPP

#include <boost/concept/requires.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/util/add_const_if_c.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Point, int Dimension, int DimensionCount, bool IsConst>
struct coordinates_scanner
{
    template <typename Op>
    static inline Op apply(typename add_const_if_c
        <
            IsConst,
            Point
        >::type& point, Op operation)
    {
        operation.template apply<Point, Dimension>(point);
        return coordinates_scanner
            <
                Point,
                Dimension+1,
                DimensionCount,
                IsConst
            >::apply(point, operation);
    }
};

template <typename Point, int DimensionCount, bool IsConst>
struct coordinates_scanner<Point, DimensionCount, DimensionCount, IsConst>
{
    template <typename Op>
    static inline Op apply(typename add_const_if_c
        <
            IsConst,
            Point
        >::type& , Op operation)
    {
        return operation;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point, typename Op>
inline void for_each_coordinate(Point& point, Op operation)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    typedef typename detail::coordinates_scanner
        <
            Point, 0, dimension<Point>::type::value, false
        > scanner;

    scanner::apply(point, operation);
}

template <typename Point, typename Op>
inline Op for_each_coordinate(Point const& point, Op operation)
{
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point>) );

    typedef typename detail::coordinates_scanner
        <
            Point, 0, dimension<Point>::type::value, true
        > scanner;

    return scanner::apply(point, operation);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_FOR_EACH_COORDINATE_HPP

/* for_each_coordinate.hpp
vwWG+U2yoO7aPAgmxr5ELzXV6LzONH+PLfNcDuvjISaFMZJcHuYRlIG8zwQthjs2ArcAB3BJfQiL3qRteeIzsHcSqCngkOOm+FBADDF/t1KK0g/s5knX8KmmW7yBxhBGjveGydE/oYRuOHEtyK/XQ6KF7GT9QUAVpcPclEOWxv7LHEhJq6LeEmplHSUtWDsa9ZAtlwTnwzjtF6N5jMNH/ZXr7Gss3oDDd90LO7XWY9Wlf4y06uq8JWv9onQukPjYqK4wilRK2k5kKY7ls10EAOgiVngKvhPdeDRket3A6wnbLamgxRCXb4APINWpdrqY0TU03x3R9pzA5et0L40T2qAXXSyA+eAzCFa0jaTWDyndkawcHC2/9NfVhh8gqDf5nW8Tz5jbPssnWlsPUAyfsjZjiCPWeHqmtU+Xa8k2HqoXLVlM6MAtfzbnSuAO76pDez9j2eny4QmQWrkV2MoCnecMi8rXeKf9vJZGFezZmO2elbPmMNvqZoTZ2+RmonsVCff0VoQwXbj3MTaAEsm/5ITMRSWHH53Fmgc+dByEFYCRnbqvwgfexXGXMQ==
*/