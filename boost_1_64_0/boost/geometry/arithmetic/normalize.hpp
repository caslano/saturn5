// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_NORMALIZE_HPP
#define BOOST_GEOMETRY_ARITHMETIC_NORMALIZE_HPP


#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Point>
inline typename coordinate_type<Point>::type vec_length_sqr(Point const& pt)
{
    return dot_product(pt, pt);
}

template <typename Point>
inline typename coordinate_type<Point>::type vec_length(Point const& pt)
{
    // NOTE: hypot() could be used instead of sqrt()
    return math::sqrt(dot_product(pt, pt));
}

template <typename Point>
inline bool vec_normalize(Point & pt, typename coordinate_type<Point>::type & len)
{
    typedef typename coordinate_type<Point>::type coord_t;

    coord_t const c0 = 0;
    len = vec_length(pt);
    
    if (math::equals(len, c0))
    {
        return false;
    }

    divide_value(pt, len);
    return true;
}

template <typename Point>
inline bool vec_normalize(Point & pt)
{
    typedef typename coordinate_type<Point>::type coord_t;
    coord_t len;
    return vec_normalize(pt, len);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ARITHMETIC_NORMALIZE_HPP

/* normalize.hpp
29qxHuxUzvYZ5ip8Fkvfa653MgNWNc89jy4HUGOkCKnxPrJpnEnJWW0eXqj4VomhnbJy8g/oHNOJ7vEH+9DhA2Ua6ioDy9hx8M0uxDj1o5K1lkmLvxN+EsUL4fMb8mfG1AsF6Bq4Hq84/5469Nogwn7yWO18csFL/y6mE7y5+DUZjCYyI4u3htLcCl/efQi8ucCSmDFdsiNtHxXUUbosCEAtPe4ATEk/N56rG8CG9QOWgF+kyYX2w9ieWdeg4NG8MpN2xxBnRGVC5reLxSf6/u6X8TdS0oGx+fYZK+5xR2jo2esJgQIqEb0J+IKKZ16WCrYl4UcwwanvIbtwKeU7Z4EH9ucBsmzJ91HXLIPZxo5xQeqpGCvotPZdG3tvHxo3F/EX/1SjsQnWiMPlysZTAiwR+YtqIqjOw0uJtW/uNS9j5HpYrbDzyVpW8AwZ+LGCER4P9umgQMAlrnjVIgvIRqi1G7tbgtiV7o/lsg1uyxmRVmUb55nT3Le14iGZyK2G6cZAwEwRQD2BG/gQrtr36arG5//dTTGf2x2VCJRFR9MqvI90zU3f08uDwg==
*/