// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_REVERSE_DISPATCH_HPP
#define BOOST_GEOMETRY_CORE_REVERSE_DISPATCH_HPP


#include <cstddef>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/integral_constant.hpp>

#include <boost/geometry/core/geometry_id.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Different geometries: reverse_dispatch if second ID < first ID
template <std::size_t GeometryId1, std::size_t GeometryId2>
struct reverse_dispatch : boost::mpl::if_c
    <
        (GeometryId1 > GeometryId2),
        boost::true_type,
        boost::false_type
    >
{};


// Same geometry: never reverse_dispatch
template <std::size_t GeometryId>
struct reverse_dispatch<GeometryId, GeometryId> : boost::false_type {};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template <typename Geometry1, typename Geometry2>
struct reverse_dispatch : detail::reverse_dispatch
    <
        geometry_id<Geometry1>::type::value,
        geometry_id<Geometry2>::type::value
    >
{};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_REVERSE_DISPATCH_HPP

/* reverse_dispatch.hpp
6/yQNDs/vENDUfvs60YrH75egiJdbOzDbdmRm/59+vRR9KF7vL2hi+JheuFHLOOA89vSBfkL8lnIyxuLM99xsRXBE6sxBeWA8btKC0t3Fu7YWbCzYEfBloItCVOLKtq3bUsTIP+dyACj8RcT7FiwI39L4asVRcHtJ05MUAZjfmdBlnMJTYEz5B0FO3bk78gvTCiqqAgO1tFvIerv3JGFE+qlLEXhTsoDUyQUFVU8zB6wvxMLwAkx5VG6cwmXYGd+QkVsVhcaH4iz86wllIFzCZ2DMykKthROXJDfx87iSwsL3U5nOZ2AL6EMkAU+y5b8/LFyLh4ZLHU6l1IZSkuXUCEwReGO/HwZiy/Eaftr5ew40VI6jUdtYJIdBVvzxz6N8eVYQKl7KZ21OykX+qzsUQoYg0D2bFl2uh3dySVaipLQ+f7OwrFtiLucLQzYsxZmubNoGDduXH8MfbhAAl0oNj48/u5kKtpRuHPHzi07+vBVjfmXOhmL0qW0FlDJhTuwpvp74p3s2ZEHezwmGeXiyZ/logyWMgbcIzBmO8c18GeSYyFOTj6UsD+K6Ilf6uKzlbubM0VX1lJXOd2nX55tb9ZWXVncg49rPvpWB2gSrnUFqLsfnRd6ZZpw1aQNj9/DQ6AAGq+sjG8C/NnyzPvFpbWe12r1U1r9lFY/xXc/pait6FBqUfuplOBZx5bpplZPbR9DPOvYsS4cqqe2
*/