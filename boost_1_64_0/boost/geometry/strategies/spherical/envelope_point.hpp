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
PczHBngJG+Kv2Bi9byEvw6HYEmdiKC7FDrgP78JL2AXrliWfwH7YC+/F3piFfXAG9sUc7IcrsT++jwPwGA7E0zgIvW8lv8AaOAyb4HBsiSMwEkfiFIzAlTgaD2IsXsI45Bh4xGMQJmAzHIvdcRyGYxIOw2QcgSkYiRn4FE7AHMzE53EibsFJeBQn4yl8GH/F6XhLea5/DMRHMQhnYHuciT1xDvbFbLygP+9JHR18X+4fVfj/Hrl/LC3PcwI+j0NwBSbgSkzCVTgVV+N0fA0XYC4+jWtxFa7HXNyEu3AzHsYtmI/v4E+Yh6VIx1Ysg+9hTdyOLXAHtsQP8G78EHvgXuyD+zEcP0Zt+/Z5St0ZqUvD9tEumfVKff/XtP2FuRiF6zAJ38AJ+CZOxfW4DDfgy/gWbsRN+C5uxlO4Bc/hOxhApO9iGG7F3rgNh+B2TMT3cTruwNn4Eb6Oe3Ejfowf4yeYj4fwFH6B5zEf/dmmI1gNv8QmeAxb4XEcgV9hJJ7EJDyF6fg1TsFvcA1+jzvxB/wQL+JhvIRf4S94Fi/jRfwVtfvMbxiEv2Mj/ANb4Z84FD3KEw964vNYGpdjGdyOZfEslsfbvMiH8A6shI3xDuyMVbE73omjsDqOwZo4DWvho1gHc7AuvoAN8T1shKewMV7GJuhJ/t0Uy2AzbIrBOAib4wgMwfnYEjdgK3wH2+B72BYPY3v8ETvgz9gJK5Yi38LGGIbNsSt2x27YB3vhQuyPO3Ew/oJDsVpp8h/shyMxDSMwB0fjZozF0xiPlclPE7EBjscBmISpmIyTMAWfxlR8G9NwO2bgbpyIX+MkvIX8dgrWxgexPmZhV5yGQ/EhvA8fwVh8FB/GmbgEH8eXcBbuwNl4DJ/AEuS/c9ETF2BNXISd8Bnsgs9iD3wO1RiwedJngMV7EXl8luYH6I170DFW7jFZ7kPJ75zHyv2T+fzw39gAPW7lfICSGIreGI6lcAyWxqlYBhfirfgGlsPDWB79iKcCtsHbsDP6YBz64uPojwuwEm7AyrgTq6C8Z0tdGM45i/fsA6TXCz9FH/wMW+IhbI2fo+p3V9YzWdbj/P7/eXnSi0exN36Jg/AYJuFxTMWvUPpucNRFoY6Ke98NSRU4HzEZa6AN62EqdsQ0HI/pOB0z8SmchGvxQczDf+AHOBVPYBb+jtPwduJ9CANwBrbEx7Av/gtjcC4m4zycgQtxLj6JL+NzuB6X4FbMwcO4DI/icrSfd1J3BetanHffyPlzGmviGZT3camDwjZavI+fk+V+kON1HkPxR+yFl3AY/oQj8Bcci5fxAfwNU/F3lHRSt6Tg62OvXB/70Bv3Oy0XKMu1t1iu4m3sZ6yErbEyXsBIgk2Wy5LlbsEhstwpLV/C01gDz2BDPItt8VvsiOdwJH6HGfgDTsbzqLZL6hyEWqTPR9LniyHoJ+mbSYiU5arKeeo8tvmFChwv/An1fu2xE/6CPfEy3o+/YjZewdXoxfo3oTd+h2XwV7wFf8ey6Et85bAilpf0DPeQug/YT7ajDPaV9FRlPm+shr4YgFWwOjbBGtgca2IPrIV9sTbK2OlS34FzR9bvPHZ6Xebzw3pYFRvI/mqME7AFTsMQfBJb4hZshSewNX6LbfEHbKe2S+o34G6L7crnPKuGR7AxHsUu+CUuwWO4Bo9jHp7A7XgS5Tg66iOQx7gfxxe1fABXYjt8CXvjy3gvrsIoXI2J+Ara8FWch6/h85iLK3ANvouv48e4Fg/iOryAOz2kHgKGy3lVif9vlvSsZz4/fBsb4TvYBvOwM27DcHwPo3E7puNufAw/wPm4B1/Fj3Ab7sXd+Cnuw88kfQfxOH6BZbXnQ7w=
*/