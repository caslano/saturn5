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
sknMoHHt5okl53tCb6nicJ/zc2ZU+sxpOdaVzaiMdH5zxfaEFIAaYJ6fDWHxah9EzDmr/GCG+fU14LeVWjNnSbWf3mg45q0jb5CIs2ExXRMU7pb2gbbbOwL9wWMwwDEnIocT1z0klG3KYlD7M6WsX5NaVhl0io8JmLfcKaf/rJ5yfs/yaIqwgtdEDUPRhnKfrvUwTVSQtk0wTqVBz8gtgjwObQFxi3Jl+Aw1UlkTDnLFR3wswiNheiO3Foj9d9YgZlkWnVf0aVADKLM06FygFKsjbtInydbgnXwN3snY4J2cDd7J2uCdvA3eydzgndwN3sne4J38Dd4FgyM2PFsV5lP8DfbClqpsYYNgGwAq5G3RNL+su93qstGlw/VW4cBcwxUa2rUbahVPtYdooXINTllViEeGuL3hGn7uLqdPAqqZYMGen+y76C1iTY/ewuZuwGX3ZotgcWj0zPp2g6Nx8NxNbin3yTPxtJR96ulLHRe/Ak34nK4LPwu/vlQsAM2q9R65U/nIqm2RNLYPhbt3qHFQhQNXDq48XPm4CnAV4QJ3WJnBo7tzrt2xCh3G867dVvfOTVmoYyakXUclSXqmoOdFDfKCeFys3SP8P5+B6PuUYsrxijMSMNeC6SE3H2LCg1dLv35sLTZIYp03elL8bwT6wzTzLyAOms9EMksj1+hNb+VExmnSFqOxZGSPyKg03DyRUekTW0dloCfg1yMyrkdkTE+khs5ya7biQ2X6w9uzw6uysc4omZOByySb6JtYBFO4N2SYp5SRu6Q4uJvPyDLyoDx4teDYfEr7AZAaf9k2ExEDWHKkxPIYNYW/mGiGQyCZJLlLlOO77Gta2FLt56TQS/yxyQM31y8W+1+TjdGtiCmMrqxvQFCDYJhlqfUcaBY03Ah2oeAuvsON0SxbypD7HbuyFZmCYABLNssFKsK+z5bcdRAP/FUdZGCOJCf5xuWgPppuyZ+tm+rmlA2B6GkSQfHhOWtwI25X9DKW3JiDsrTiWotrI65XcG3DtR3XblwJIGmZkbJW3HpIKxNNb3jw0hOSU+J9ohc3BGRPhERXNPQUHg+CcsREXzS0Fs8G0+Mdj72zOnzRKzbg6WB8nNURvXGj9dSSvQmS19mhdvf7Shaz/406HK1oDdJTst+YtQYxPhjbN+raxdODQZHkZb4M+UGmUfe8fILi+1L51APNKZ96GnV0/pEyZgvVmGWrpgzazhOLjYthyy7yRaUsDmfBbtVZsy/ajyf2UjAjajLay7lc0ZeoWb+VkkbjkjQaDoNUGg06cSmAAXSrddvbiQT8EQJSexOzHaTbhl7if8UfpmG+g7Yhtx0cEltdolm8nCCxC/oEzPNJBi4zn0YyMUT89KYNcQmyjCD6602cNwmKwblgjuqilFyHzsckhq2tktbgwU/Y6lYVHB7ALSZHlyvGKlOfFT8OaVNLfK5llziejSjn+3RRcoPcheP5/r7brkl7bs2NmVpwNEOh06IQrid6SnnQzTNwdJvqMB5eHqexGI5+8oI/7U2oDhjcCMwmgV/8NtJjwCZGgTKhdUEMyhpFGQ02yrhE9DYm5/Jhi7glmtTyERuTaK3hyqsll+JoJM/tVLhv/JsAztYSObIFjvlfoNB8yvpmas2d372e5u75bXIznfWYg4qYOwNV1CImd9UnPVUJ+YyXsfebHfR9B5xVuprluUcKy1JY5ggp2tHqCJM8RWkJ6+4/CnL4GlP0csmHoXEpc/ubpom0HEEUIwBGXfWc2kWTIgUUJZAT3ZEnEJ3ftQyakEYq3CiCBjdyVKlEX7pAr20v4JzldrN5hHRuTaPA+EsnCwdq4UY9ips15RG5Fy9SlkeWkZDoMxE=
*/