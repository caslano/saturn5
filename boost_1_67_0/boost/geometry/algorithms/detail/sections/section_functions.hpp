// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_FUNCTIONS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_FUNCTIONS_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>

// For spherical/geographic longitudes covered_by point/box
#include <boost/geometry/strategies/cartesian/point_in_box.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace section
{

// TODO: This code is CS-specific, should be moved to strategies

template
<
    std::size_t Dimension,
    typename Geometry,
    typename CastedCSTag = typename tag_cast
                            <
                                typename cs_tag<Geometry>::type,
                                spherical_tag
                            >::type
>
struct preceding_check
{
    template <typename Point, typename Box>
    static inline bool apply(int dir, Point const& point, Box const& /*point_box*/, Box const& other_box)
    {
        return (dir == 1  && get<Dimension>(point) < get<min_corner, Dimension>(other_box))
            || (dir == -1 && get<Dimension>(point) > get<max_corner, Dimension>(other_box));
    }
};

template <typename Geometry>
struct preceding_check<0, Geometry, spherical_tag>
{
    template <typename Point, typename Box>
    static inline bool apply(int dir, Point const& point, Box const& point_box, Box const& other_box)
    {
        typedef typename select_coordinate_type
            <
                Point, Box
            >::type calc_t;
        typedef typename coordinate_system<Point>::type::units units_t;

        calc_t const c0 = 0;

        calc_t const value = get<0>(point);
        calc_t const other_min = get<min_corner, 0>(other_box);
        calc_t const other_max = get<max_corner, 0>(other_box);
        
        bool const pt_covered = strategy::within::detail::covered_by_range
                                    <
                                        Point, 0, spherical_tag
                                    >::apply(value,
                                             other_min,
                                             other_max);

        if (pt_covered)
        {
            return false;
        }

        if (dir == 1)
        {
            calc_t const diff_min = math::longitude_distance_signed
                                        <
                                            units_t, calc_t
                                        >(other_min, value);

            calc_t const diff_min_min = math::longitude_distance_signed
                                        <
                                            units_t, calc_t
                                        >(other_min, get<min_corner, 0>(point_box));

            return diff_min < c0 && diff_min_min <= c0 && diff_min_min <= diff_min;
        }
        else if (dir == -1)
        {
            calc_t const diff_max = math::longitude_distance_signed
                                        <
                                            units_t, calc_t
                                        >(other_max, value);

            calc_t const diff_max_max = math::longitude_distance_signed
                                        <
                                            units_t, calc_t
                                        >(other_max, get<max_corner, 0>(point_box));

            return diff_max > c0 && diff_max_max >= c0 && diff_max <= diff_max_max;
        }

        return false;
    }
};


template
<
    std::size_t Dimension,
    typename Point,
    typename RobustBox,
    typename RobustPolicy
>
static inline bool preceding(int dir,
                             Point const& point,
                             RobustBox const& point_robust_box,
                             RobustBox const& other_robust_box,
                             RobustPolicy const& robust_policy)
{
    typename geometry::robust_point_type<Point, RobustPolicy>::type robust_point;
    geometry::recalculate(robust_point, point, robust_policy);
    return preceding_check<Dimension, Point>::apply(dir, robust_point, point_robust_box, other_robust_box);
}

template
<
    std::size_t Dimension,
    typename Point,
    typename RobustBox,
    typename RobustPolicy
>
static inline bool exceeding(int dir,
                             Point const& point,
                             RobustBox const& point_robust_box,
                             RobustBox const& other_robust_box,
                             RobustPolicy const& robust_policy)
{
    return preceding<Dimension>(-dir, point, point_robust_box, other_robust_box, robust_policy);
}


}} // namespace detail::section
#endif


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_FUNCTIONS_HPP

/* section_functions.hpp
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
*/