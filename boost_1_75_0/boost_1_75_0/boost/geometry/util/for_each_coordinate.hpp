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
RKkspaYyuv5dcc9J388JBuz2t0r7IKwfpgb106OQQeACIZiWsK15zESk5Yg6w7CWoCtR2DvWT/cESbqy86Sab19S8vh5xAWSC4OHeVJepSKnoqSuS1ULKHTwazpHGcaDnjBKy5d91tk01XRnAQcK8zNaXD4VDjCOaf1hRGWDThd7h4YzUTWiVZ1IC6S+kltX2npKK1EZaMC6H6P+FGoLDAdsRnMbR1ATJRwW/zHSViSPwpqfEixpVTlXndfaOR0dVGlVWmkN6crIyrV9IRbqp+t4utTopyS/1rtbe1Qe1qKgEhb1xdZzH0v8S793ckE/MDVgWE9IVV4rprLn9oc+6yO4h2a82GOJ5TH7ACjmUEkvkCqAJCDMfblhQGuu7VyRyDtu3u1UWkggVGVgWjynEf6aaiYRxX0TCUfEgRcdDbMHBUcKKVbwsuVX7Owwg0E2qsREn99+bybOG/16RRvfMoNSQ4vU6RHtpWS35M4RIxvO0YXNCnu77nTALzFlx4PfkIznplMsKHaHxIkH0zmtAJWUL9HjJbG3wOkOf4f54jZ25qr7DO2xJBxfZ4rl8cnuWMqOpMEDt3MR4s7ZGRsDBqo8WeloUQy5Ae6o0hDaVsisU9M8KrYhfTgTcEkYPjztJfkFuxxOqOaX+SftiqKGOHojkKohgXO/PS8b9G4QWNr2i7MqW5XJ561xGYNmUEfgn0j2twpNH/QSDDYT
*/