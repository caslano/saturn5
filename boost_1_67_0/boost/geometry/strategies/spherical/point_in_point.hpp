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


#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POINT_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POINT_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
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
                boost::is_same
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