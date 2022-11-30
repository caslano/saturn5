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
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
*/