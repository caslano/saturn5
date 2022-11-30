// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_FUNCTIONS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_FUNCTIONS_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
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
    typename Box,
    typename RobustPolicy
>
static inline bool preceding(int dir,
                             Point const& point,
                             Box const& point_box,
                             Box const& other_box,
                             RobustPolicy const& robust_policy)
{
    typename geometry::robust_point_type<Point, RobustPolicy>::type robust_point;
    geometry::recalculate(robust_point, point, robust_policy);

    // After recalculate() to prevent warning: 'robust_point' may be used uninitialized
    assert_coordinate_type_equal(robust_point, point_box);

    return preceding_check<Dimension, Box>::apply(dir, robust_point,
                                                    point_box,
                                                    other_box);
}

template
<
    std::size_t Dimension,
    typename Point,
    typename Box,
    typename RobustPolicy
>
static inline bool exceeding(int dir,
                             Point const& point,
                             Box const& point_box,
                             Box const& other_box,
                             RobustPolicy const& robust_policy)
{
    return preceding<Dimension>(-dir, point, point_box, other_box, robust_policy);
}


}} // namespace detail::section
#endif


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_FUNCTIONS_HPP

/* section_functions.hpp
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
*/