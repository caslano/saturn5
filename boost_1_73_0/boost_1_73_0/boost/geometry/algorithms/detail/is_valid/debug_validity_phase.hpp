// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP

#ifdef GEOMETRY_TEST_DEBUG
#include <iostream>
#endif

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace is_valid
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct debug_validity_phase
{
    static inline void apply(int)
    {
    }
};

#ifdef BOOST_GEOMETRY_TEST_DEBUG
template <typename Polygon>
struct debug_validity_phase<Polygon, polygon_tag>
{
    static inline void apply(int phase)
    {
        switch (phase)
        {
        case 1:
            std::cout << "checking exterior ring..." << std::endl;
            break;
        case 2:
            std::cout << "checking interior rings..." << std::endl;
            break;
        case 3:
            std::cout << "computing and analyzing turns..." << std::endl;
            break;
        case 4:
            std::cout << "checking if interior rings are inside "
                      << "the exterior ring..." << std::endl;
            break;
        case 5:
            std::cout << "checking connectivity of interior..." << std::endl;
            break;
        }
    }
};
#endif

}} // namespace detail::is_valid

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP

/* debug_validity_phase.hpp
tMFaU9UOwuc16mhDWnG3oBVhpmcSAD/FkYjYcZoGt+A868zw/IIkC+3ZS61iYR3xijOCXyFhMEZBZ9vhGSUhU8Izh5qQeCvSIghOYWeePyrJzlZh68JxWxSJQpJEwV+a+rDUElzx8gUcbc4JCYN7iTvCUTlSVjH4Vh4A4RyBRaoDAvcYdwmMa+U2dSvDeOly/HqZfrJ4oKq0yXewsrpdTjgtJgOI20dYyYSSfM4o1xyTzHHU0eMMJbYY86dqnHni5L1WnqawlrXyvbp+xuMD196b7llewdkzZiVqMsHqM5B21EQ5pooxbDrZlPIWsdmEwrXS6X+Gg9UdYnR/FW4pqFDOnkoaMLrLzd4nWchwremAruBgmgpIsSep28HIlb6hY4mRILqNDGiP3EZHJ9QxE6a5kXQrFx+WuFnwR6vOW+TL7hzSzRM1eQeMj8/q/oi9nlSCVsXxgJ3tlM9zmHS73BcXEqhsmpnUeXGh9AnWGC50joRaaoe5y8HpzzwiYQQNd+dIp3BAhqOWORFMgpq648c+/yL9mXOjj3MjhG44n9TvkMqtZPLJyBampNDFHzEjJodp15wA1pyxZqGt9Ed7ixm0KllLdbg/v83P0fGRvIuzoJBiXsqAM7SrO3Zb2EXvayuZ4xeATwRhVD4Y
*/