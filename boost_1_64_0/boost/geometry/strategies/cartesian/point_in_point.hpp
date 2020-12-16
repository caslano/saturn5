// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_POINT_IN_POINT_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_POINT_IN_POINT_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/within.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace within
{


template <std::size_t Dimension, std::size_t DimensionCount>
struct point_point_generic
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& p1, Point2 const& p2)
    {
        if (! geometry::math::equals(get<Dimension>(p1), get<Dimension>(p2)))
        {
            return false;
        }
        return
            point_point_generic<Dimension + 1, DimensionCount>::apply(p1, p2);
    }
};

template <std::size_t DimensionCount>
struct point_point_generic<DimensionCount, DimensionCount>
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const&, Point2 const& )
    {
        return true;
    }
};

}} // namespace detail::within
#endif // DOXYGEN_NO_DETAIL


namespace strategy { namespace within
{

struct cartesian_point_point
{
    typedef cartesian_tag cs_tag;

    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& point1, Point2 const& point2)
    {
        return geometry::detail::within::point_point_generic
            <
                0, dimension<Point1>::type::value
            >::apply(point1, point2);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename PointLike1, typename PointLike2, typename Tag1, typename Tag2>
struct default_strategy<PointLike1, PointLike2, Tag1, Tag2, pointlike_tag, pointlike_tag, cartesian_tag, cartesian_tag>
{
    typedef strategy::within::cartesian_point_point type;
};

} // namespace services
#endif


}} // namespace strategy::within


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace strategy { namespace covered_by { namespace services
{

template <typename PointLike1, typename PointLike2, typename Tag1, typename Tag2>
struct default_strategy<PointLike1, PointLike2, Tag1, Tag2, pointlike_tag, pointlike_tag, cartesian_tag, cartesian_tag>
{
    typedef strategy::within::cartesian_point_point type;
};

}}} // namespace strategy::covered_by::services
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_POINT_IN_POINT_HPP

/* point_in_point.hpp
+77V6w+ecl+z9on3X7x73XWjeiRcN/bvG4O8trgG+6vH9q4trqf+6rFix4vropljeqbljv79neHvTg9j1lXmVazCTjyTCTyLN4T3f4I1+QfWZhrrcA3rhjHozmctXsDLWJ+JbMBebJg51mi4FsrBYbmyjjV6JIzRGxfGsM3Ny5iHbZmPyczPx3gCD7MA/TuuIGvwJLZjIXbgyUxiEYYxYcK1zej2Scs2JkzvMHbWQFZlEmtwEOszme2Ywt5MZV8O5h28kY9xGPfwlqxjCIdrm60lLdvYXz3DGJ69eBZ7sxr7MJ59s4wFujW8z1JJy/bdff4wJuIJrMcCbMSCHMdCnMiTOYlF+SRLcDpL8zmW4QKW4yJWYHRsm3D9MVyXTMs2ts3hsB758uhbzPysx0LsxMLszZM5lkX4GItzMk/hCpbiTpZmkVzmxWIswxIsS8vj+5dwfZEnheXJeOZHXOgbWYpPswGf4aWczrZ8ntdwLntwHhP5AgdxIR/iy5zKJZzGVziXSzmfr/JVLuM7XM73uYKf8DXu4Uoe4ioe5mqmj7HJ/FyXuV7hOiHb57BeXcJYMX1YiX1Zm/1ZnwPZnoM4gMkcypt4G4dzDG/hON7GR3kHX+Hd/IyjuYP3hOW6l/ksz5iwHcayEsfxTN7PGhzPunyAV/DB8Pf2V9fwYtuBCpF6E9Zraxjr9zOeyV2M59dM4AHewIMcwj9zGL/jXSyaN1qvi3EKi3MtS3MTT+WHLMOPWY5fsTyP8DRGlrECi/B0nsqKPIuVWJWV2YhnMJ5V2JZnsQOrsit/w16szgGsySTWYnR/CtfieGYO+9NLYX9eyMpczGQu4XAu5Qwu4xyu4Fq+xre4kt9yFX/mapY2nzWswHWsyPWZY/2G62/sKGkxYxRF+4YWZyNW48Wsw8a8gE3Zjs14FZtnWc9wbcw1s2PX8xzbryyrhfr8G1Zn9dB+NOQVbMareCl7sQVvYDz783IuYutQj9txLa/kBl6VuX+Fa18om8P+VUl5FGMVtmRVtuM5vIoXshMbsTMbswebMJHN2Y+XcABbcDDjOYSteSvbcASv5ihew3v4O45nJz7IznyU1/H37MKp7M5n2COzfQ7XonhKDvXpT6YrxQ/YgB+F5fuEN3FrqFefcjQ/50TuCvPbydX8kpF2YDcLcS9P5j4W5f7M+hSuK/HKHOrTgXC8/TPP4Lesxu/YgIcYzx/Ymj/yAJdJuEbk2lH0fU/x7wXhfRuFMfmbsjmbcyxbcALj+Rgv41y25GZezq1sy31sx0j7diUTeBVvZnuOYAfO59X8M69hIcvSiXV5La9mZ3ZiF3Zh17Ae2pJw7ceyhfWoHGmPwnfsxcNYzyV4Ok/nOazEZjyL7Xg2r2c19mZ1DmFNTmRtPs06nMNzuZjncR3r8QtewO9Znz+yAQtGzuN4Kn/Li9iIbXgRB7AJb2FTjmczTmdzLuWlXM0W/ICX8SAvZ6QvYytWYGueyzZsxCvZlFfxQOjnEK5BOfZEyytSHu1Deb0cnoWwjLW4gk34Gi/nanbmGt7GtbyX67iFr/NTvsG93BDK401GZrqRZfk2q/Ed1uL7bM4PQrl8zD78JJTHNi7gp1zHz7iJ27mFn/NL7mR96/RFWP8v2Ye7OY57OJV7+Rz3cQG/5ms8wLLK5UdW5WG24k/sxiPsx5+ZxFyRMdSZm6OYh9F7WsN1sHB9LC3bPa1Xh3LuzOrsEsq5K59nAl9kIleyJ19nb/6J/RlpPwawMAeyDgexHlN4HVM5iINDOd7IZzmEL3Iol3AYV/Im7uLN3MNbWNiy38riHMGyHMnqvJ2X8h6O572hfMdwJsdxCe/jScrnQZbiQ6F8H+Y=
*/