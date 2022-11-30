// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POINT_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POINT_HPP


#include <cstddef>
#include <type_traits>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/dispatch/disjoint.hpp>
#include <boost/geometry/algorithms/transform.hpp>

#include <boost/geometry/geometries/helper_geometry.hpp>

#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/strategy_transform.hpp>
#include <boost/geometry/strategies/within.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace within
{

class point_point_on_spheroid
{
public:
    typedef spherical_tag cs_tag;

private:
    template <typename Point1, typename Point2, bool SameUnits>
    struct are_same_points
    {
        static inline bool apply(Point1 const& point1, Point2 const& point2)
        {
            typedef typename helper_geometry<Point1>::type helper_point_type1;
            typedef typename helper_geometry<Point2>::type helper_point_type2;

            helper_point_type1 point1_normalized;
            strategy::normalize::spherical_point::apply(point1, point1_normalized);
            helper_point_type2 point2_normalized;            
            strategy::normalize::spherical_point::apply(point2, point2_normalized);

            return point_point_generic
                <
                    0, dimension<Point1>::value
                >::apply(point1_normalized, point2_normalized);
        }
    };

    template <typename Point1, typename Point2>
    struct are_same_points<Point1, Point2, false> // points have different units
    {
        static inline bool apply(Point1 const& point1, Point2 const& point2)
        {
            typedef typename geometry::select_most_precise
                <
                    typename fp_coordinate_type<Point1>::type,
                    typename fp_coordinate_type<Point2>::type
                >::type calculation_type;

            typename helper_geometry
                <
                    Point1, calculation_type, radian
                >::type helper_point1, helper_point2;

            Point1 point1_normalized;
            strategy::normalize::spherical_point::apply(point1, point1_normalized);
            Point2 point2_normalized;
            strategy::normalize::spherical_point::apply(point2, point2_normalized);

            geometry::transform(point1_normalized, helper_point1);
            geometry::transform(point2_normalized, helper_point2);

            return point_point_generic
                <
                    0, dimension<Point1>::value
                >::apply(helper_point1, helper_point2);
        }
    };

public:
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& point1, Point2 const& point2)
    {
        return are_same_points
            <
                Point1,
                Point2,
                std::is_same
                    <
                        typename detail::cs_angular_units<Point1>::type,
                        typename detail::cs_angular_units<Point2>::type
                    >::value
            >::apply(point1, point2);
    }
};

}} // namespace detail::within
#endif // DOXYGEN_NO_DETAIL


namespace strategy { namespace within
{

struct spherical_point_point
    : geometry::detail::within::point_point_on_spheroid
{};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename PointLike1, typename PointLike2, typename Tag1, typename Tag2>
struct default_strategy<PointLike1, PointLike2, Tag1, Tag2, pointlike_tag, pointlike_tag, spherical_tag, spherical_tag>
{
    typedef strategy::within::spherical_point_point type;
};

} // namespace services
#endif


}} // namespace strategy::within


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace strategy { namespace covered_by { namespace services
{

template <typename PointLike1, typename PointLike2, typename Tag1, typename Tag2>
struct default_strategy<PointLike1, PointLike2, Tag1, Tag2, pointlike_tag, pointlike_tag, spherical_tag, spherical_tag>
{
    typedef strategy::within::spherical_point_point type;
};

}}} // namespace strategy::covered_by::services
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POINT_HPP

/* point_in_point.hpp
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
*/