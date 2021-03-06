// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_POINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_POINT_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/normalize.hpp>

#include <boost/geometry/algorithms/detail/envelope/transform_units.hpp>

#include <boost/geometry/strategies/cartesian/envelope_point.hpp>

#include <boost/geometry/strategies/envelope.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

struct spherical_point
{
    template<typename Point, typename Box>
    static inline void apply(Point const& point, Box& mbr)
    {
        Point normalized_point;
        strategy::normalize::spherical_point::apply(point, normalized_point);

        typename point_type<Box>::type box_point;

        // transform units of input point to units of a box point
        geometry::detail::envelope::transform_units(normalized_point, box_point);

        geometry::set<min_corner, 0>(mbr, geometry::get<0>(box_point));
        geometry::set<min_corner, 1>(mbr, geometry::get<1>(box_point));

        geometry::set<max_corner, 0>(mbr, geometry::get<0>(box_point));
        geometry::set<max_corner, 1>(mbr, geometry::get<1>(box_point));

        typedef geometry::detail::envelope::envelope_one_point
            <
                2, dimension<Point>::value
            > per_corner;
        per_corner::template apply<min_corner>(normalized_point, mbr);
        per_corner::template apply<max_corner>(normalized_point, mbr);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<point_tag, spherical_equatorial_tag, CalculationType>
{
    typedef strategy::envelope::spherical_point type;
};

template <typename CalculationType>
struct default_strategy<point_tag, spherical_polar_tag, CalculationType>
{
    typedef strategy::envelope::spherical_point type;
};

template <typename CalculationType>
struct default_strategy<point_tag, geographic_tag, CalculationType>
{
    typedef strategy::envelope::spherical_point type;
};


}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_POINT_HPP

/* envelope_point.hpp
JR/2Y0U8bs7EPAemeeysIR0jAGPL3VvGaCjz8589sdY6hIYVhcqg90ofLdILBVYavQMIOJgdXth/RwVcHq8OCq8wkHqB+n2meyvP1TO2yLOiFahSo+bFKhJcULr1eVqUNowt4Fo1x5Aeh+0nHpjhENOfcRrRxxlCp0P9776UgYQTSpfHW+MuAvG2JXrUlc50Ik0p1QNT4cExoFA0tVntVraC9p9qFAGCWy1Yng8O5ZpwJTQ5N6xPr7WMZaCDDo3dA3NnXEwXCoNZ9oX6dXsFIZM7IkmZIGLQI2cT0GSOin9ptOaNuUdqtYqKuuPJ0HVulCk4kQaMPoGArJUxJtX6qeqjeUBhotvMdWQnh1OkmhmdKUZbdOcMSbxX5JkGFe5tsP0+/2k0ryAN6++P21zJNnaci5lMZWxfOuvFxAd+u0Ah6W33Fb0pv2vDz+E2LVGAdNObb3WNkXahVyw2Eyy+c4k9NZuSbmcRyIX/XokAK4EpaBsBfO7sd9VNX2Zc++cY+yF+m/M+p4jfwl9REx3n9+Ishyt6dIN/PNo+Z5pSCc6oDfCXaeORiUGPwg==
*/