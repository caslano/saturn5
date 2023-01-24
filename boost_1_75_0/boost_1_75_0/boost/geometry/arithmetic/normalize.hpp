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
qiwdrXYJy6iTNAAZv0cEtlRuC3KJyfgqhMm3eNZ6QtrNPwG0t/2kx3fH+9xIj2F/Ati+QiBxc81K76t432qCDS85ObmiztND4sDri/i72lZSKkNu2gJGIWzFYmXeimdye6ds/kIsiEuHABWhP7OpL9Qai6Jdl8fjDhv4l1Fj55JDHgAw7A+K73R4XmI6RKf/ztnDs+junIHTRzO8ZuwvPK0allZQBeC0psaxtrYVC+ZCgbwHm0spN0HlSLYnrdxefVZqlpkBGaeomIS5+Oify6czC/Knhu3RzYsFfxCG67CuoF6E4YSqctxKD32Z1fiyBXIq8dQo9DVXQDoRSc1QeV6gcqiyE9cpmvuwfmzhiVpvLN2G3PhJ6NJJDiPSck5UxMXwowHq6YSSfFCDESwwzACFqPeU08BxfAQvXuaigOhHBToTnyAy//TmtH1yTUO3cudBeUTzY6DRp3PR2C/JKKklugnvnZULoX5k5eLNF/Q85e7hmyzbKMmW77b7KUsRbuI8Rtl9N09UVS1o7xc5b2WTHssMH8sPjndkRr8cFzdFTWg9faPoe/bMlstCLwjusFp4qkwBu3p8GvzZABUnptd7oWWEgKyc2mo+1KrMiR7p+zO787NSTg+8qeJ0RVcZ3yZT7ChEOC2LE9u4PE4eIeUhzdvBhGi6Mks+fO3JdUJy4yHPfqH9sD3kB1kV9SVhyf59DtZImhyrPmZG
*/