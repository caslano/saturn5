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
lS1uk39ThiyXntdkFQyXsyDNw5eLF+MdIeLR4/iDb5CaxzTunE6dh/Sl1tuYmQPtetWP0STb/pJJ+ly6RVMMu0sExpi1Fn868WRQsjgHSAuPEDS+G0/TpP8LZXcRFUeXhgEYl2AJECBAQ7Dw4+4a3N2Da3B3DxDcggdpnODuGtzdrSFAoLFGGqfp8ZnNyJlFLapOre6izvnuW899zfLCH/CJ5PR+FIhPv1ghEKh5Ym7mF6DVUeyU4oSQXe8QnhcLZZEY8IZHiYFDoKizPyWxjfvSdFqMIEhHnRpVb5xMm38QNP9CI3EKc4lekoinpHOvDACGwxpgr8Tj9eiXv9REEkKRzmdfj0takku9KUvZpByhp+jISLA2fgKzdB9QiulI2esEXaH2sPlI/vDH6pnxESsXikeX3zITljpm3cfUuKOqTeogKCc8Zi1W+dGJB1S7o+wM77hrU/7h/w0msZW4yUYIJ5DYKsshPFY5UC841zZ+c3xe8Fwwf0Xfc11c99dGMZyvnTTIHO6f+L9i0FtKy29lX3SP5pkyv8HIAlxKebOb+1W/qFkmSX7WfBixltWtXSJWgwaACmMFvgq9jtIvjeO81opJgDh4obzRHKRG37O2p12nVK8vqLGBFdaLj8agmhefLVSD2p9oGsZ8+ImJll309AbMzHAiI3hu6y6iGgbcE0EWOoGPX3aCVoHGCkW9XK55EB/WgDnh6ysu
*/