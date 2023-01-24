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
6ZV4J0tm6Ofql9HLfbHqbaMcgpA4B/S0YpKJK3mLiPAe9Evokium2+7lT7pRTUwBKK+5/KnEXl6yi5TYJ3BWZSf2cLRb/tGE+psUTnz9nRu12MZr/W5ZHYhro1Pk9MJVmya806SZGbtKCqfzPT5ILgE/xtbSg3iztxP0+bU0ssQdtqu3Ym4yyDrg1wFpKk8ATLWqpkXerLqGZrJROdqa71cPd9aofqs5kpIw0JB0+t7XrJ4ec/BqOg2nQ2IEFO4guC7y638iz0wkj4Sks8LD39zP8aodCSZjuWm38D95kNXQSeXFFrjQaHpPKY5/PewtONk2L2zHlBBzBNmoLbpN9ihhu0kTTgj1T2h7NlgQ+5T2oPvVC4BmT4wrerZieLuxmeUw6GDY+rVdkTH1ohVEhI+OTa2ONW60vnxeFlJrTQtFifSQmuHim1LLgeBMjT0A8CqDhXfn/qtNtUeXFkbpPMeJXfkW0CMz2MaTfnMoumxQIHZvpOipUBMjqD6VNPmZ3o0BT//uuCyXyMs7Wq06AJxd+ettnVYOXOvkbIpVqAlr26oFHLfovcir9bEkOa7tvDQcskPl3bMqaGHOxVfz21LgdO8oEaC9kRZ2VJpgYBAyFHujyy1kabT835RcV1gTURZeFUQERFBpAlGQKkVCrzGgsHTpEBGkd6kKhBKlCEgJCAhIlY6UgIAUKYr0GnqvoYcWCDUh2dmX3W8f
*/