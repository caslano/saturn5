// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_COMPARE_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_COMPARE_HPP


#include <boost/mpl/if.hpp>
#include <boost/mpl/min.hpp>

#include <boost/type_traits/is_same.hpp>

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
get(P const& p, boost::true_type /*same units*/)
{
    return geometry::get<I>(p);
}

template <std::size_t I, typename P>
static inline typename geometry::coordinate_type<P>::type
get(P const& p, boost::false_type /*different units*/)
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
    typedef typename boost::is_same<units1_type, units2_type>::type same_units_type;

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
    typedef typename boost::is_same<units1_type, units2_type>::type same_units_type;
    typedef typename boost::mpl::if_<same_units_type, units1_type, geometry::radian>::type units_type;

    static const bool is_equatorial = ! boost::is_same
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
                boost::mpl::min
                    <
                        geometry::dimension<Point1>,
                        geometry::dimension<Point2>
                    >::type::value
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