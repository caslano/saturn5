// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_COMPARE_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_COMPARE_HPP


#include <type_traits>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/compare.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace compare
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <std::size_t I, typename P>
static inline typename geometry::coordinate_type<P>::type
get(P const& p, std::true_type /*same units*/)
{
    return geometry::get<I>(p);
}

template <std::size_t I, typename P>
static inline typename geometry::coordinate_type<P>::type
get(P const& p, std::false_type /*different units*/)
{
    return geometry::get_as_radian<I>(p);
}

template
<
    typename ComparePolicy,
    typename Point1,
    typename Point2,
    std::size_t DimensionCount
>
struct spherical_latitude
{
    typedef typename geometry::coordinate_type<Point1>::type coordinate1_type;
    typedef typename geometry::detail::cs_angular_units<Point1>::type units1_type;
    typedef typename geometry::coordinate_type<Point2>::type coordinate2_type;
    typedef typename geometry::detail::cs_angular_units<Point2>::type units2_type;
    typedef std::is_same<units1_type, units2_type> same_units_type;

    template <typename T1, typename T2>
    static inline bool apply(Point1 const& left, Point2 const& right,
                             T1 const& l1, T2 const& r1)
    {
        // latitudes equal
        if (math::equals(l1, r1))
        {
            return compare::detail::compare_loop
                <
                    ComparePolicy, 2, DimensionCount
                >::apply(left, right);
        }
        else
        {
            return ComparePolicy::apply(l1, r1);
        }
    }

    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        coordinate1_type const& l1 = compare::detail::get<1>(left, same_units_type());
        coordinate2_type const& r1 = compare::detail::get<1>(right, same_units_type());

        return apply(left, right, l1, r1);
    }
};

template
<
    typename ComparePolicy,
    typename Point1,
    typename Point2
>
struct spherical_latitude<ComparePolicy, Point1, Point2, 1>
{
    template <typename T1, typename T2>
    static inline bool apply(Point1 const& left, Point2 const& right,
                             T1 const& , T2 const& )
    {
        return apply(left, right);
    }

    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        return compare::detail::compare_loop
            <
                ComparePolicy, 1, 1
            >::apply(left, right);
    }
};

template
<
    typename ComparePolicy,
    typename Point1,
    typename Point2,
    std::size_t DimensionCount
>
struct spherical_longitude
{
    typedef typename geometry::coordinate_type<Point1>::type coordinate1_type;
    typedef typename geometry::detail::cs_angular_units<Point1>::type units1_type;
    typedef typename geometry::coordinate_type<Point2>::type coordinate2_type;
    typedef typename geometry::detail::cs_angular_units<Point2>::type units2_type;
    typedef std::is_same<units1_type, units2_type> same_units_type;
    typedef std::conditional_t<same_units_type::value, units1_type, geometry::radian> units_type;

    static const bool is_equatorial = ! std::is_same
                                        <
                                            typename geometry::cs_tag<Point1>::type,
                                            geometry::spherical_polar_tag
                                        >::value;

    static inline bool are_both_at_antimeridian(coordinate1_type const& l0,
                                                coordinate2_type const& r0,
                                                bool & is_left_at,
                                                bool & is_right_at)
    {
        is_left_at = math::is_longitude_antimeridian<units_type>(l0);
        is_right_at = math::is_longitude_antimeridian<units_type>(r0);
        return is_left_at && is_right_at;
    }

    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        // if units are different the coordinates are in radians
        coordinate1_type const& l0 = compare::detail::get<0>(left, same_units_type());
        coordinate2_type const& r0 = compare::detail::get<0>(right, same_units_type());
        coordinate1_type const& l1 = compare::detail::get<1>(left, same_units_type());
        coordinate2_type const& r1 = compare::detail::get<1>(right, same_units_type());

        bool is_left_at_antimeridian = false;
        bool is_right_at_antimeridian = false;
        
            // longitudes equal
        if (math::equals(l0, r0)
               // both at antimeridian
            || are_both_at_antimeridian(l0, r0, is_left_at_antimeridian, is_right_at_antimeridian)
               // both at pole
            || (math::equals(l1, r1)
                && math::is_latitude_pole<units_type, is_equatorial>(l1)))
        {
            return spherical_latitude
                <
                    ComparePolicy, Point1, Point2, DimensionCount
                >::apply(left, right, l1, r1);
        }
        // if left is at antimeridian and right is not at antimeridian
        // then left is greater than right
        else if (is_left_at_antimeridian)
        {
            // less/equal_to -> false, greater -> true
            return ComparePolicy::apply(1, 0);
        }
        // if right is at antimeridian and left is not at antimeridian
        // then left is lesser than right
        else if (is_right_at_antimeridian)
        {
            // less -> true, equal_to/greater -> false
            return ComparePolicy::apply(0, 1);
        }
        else
        {
            return ComparePolicy::apply(l0, r0);
        }
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Compare strategy for spherical coordinates
\ingroup strategies
\tparam Point point-type
\tparam Dimension dimension
*/
template
<
    typename ComparePolicy,
    int Dimension = -1
>
struct spherical
    : cartesian<ComparePolicy, Dimension>
{};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
// all dimensions starting from longitude
template <typename ComparePolicy>
struct spherical<ComparePolicy, -1>
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        return compare::detail::spherical_longitude
            <
                ComparePolicy,
                Point1,
                Point2,
                std::conditional_t
                    <
                        (dimension<Point1>::value < dimension<Point2>::value),
                        std::integral_constant<std::size_t, dimension<Point1>::value>,
                        std::integral_constant<std::size_t, dimension<Point2>::value>
                    >::value
            >::apply(left, right);
    }
};

// only longitudes (and latitudes to check poles)
template <typename ComparePolicy>
struct spherical<ComparePolicy, 0>
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        return compare::detail::spherical_longitude
            <
                ComparePolicy, Point1, Point2, 1
            >::apply(left, right);
    }
};

// only latitudes
template <typename ComparePolicy>
struct spherical<ComparePolicy, 1>
{
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& left, Point2 const& right)
    {
        return compare::detail::spherical_latitude
            <
                ComparePolicy, Point1, Point2, 2
            >::apply(left, right);
    }
};

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace services
{


template <typename ComparePolicy, typename Point1, typename Point2, int Dimension>
struct default_strategy
    <
        ComparePolicy, Point1, Point2, Dimension,
        spherical_tag, spherical_tag
    >
{
    typedef compare::spherical<ComparePolicy, Dimension> type;
};

template <typename ComparePolicy, typename Point1, typename Point2, int Dimension>
struct default_strategy
    <
        ComparePolicy, Point1, Point2, Dimension,
        spherical_polar_tag, spherical_polar_tag
    >
{
    typedef compare::spherical<ComparePolicy, Dimension> type;
};

template <typename ComparePolicy, typename Point1, typename Point2, int Dimension>
struct default_strategy
    <
        ComparePolicy, Point1, Point2, Dimension,
        spherical_equatorial_tag, spherical_equatorial_tag
    >
{
    typedef compare::spherical<ComparePolicy, Dimension> type;
};

template <typename ComparePolicy, typename Point1, typename Point2, int Dimension>
struct default_strategy
    <
        ComparePolicy, Point1, Point2, Dimension,
        geographic_tag, geographic_tag
    >
{
    typedef compare::spherical<ComparePolicy, Dimension> type;
};


} // namespace services


}} // namespace strategy::compare


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_COMPARE_HPP

/* compare.hpp
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
*/