// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_SEGMENT_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/algorithms/detail/envelope/box.hpp>
#include <boost/geometry/algorithms/detail/envelope/range_of_boxes.hpp>
#include <boost/geometry/algorithms/detail/envelope/segment.hpp>

#include <boost/geometry/strategies/expand.hpp>
#include <boost/geometry/strategies/spherical/envelope_segment.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct segment_on_spheroid
{
    template <typename Box, typename Segment, typename EnvelopeStrategy>
    static inline void apply(Box& box, Segment const& segment, EnvelopeStrategy const& strategy)
    {
        Box mbrs[2];

        // compute the envelope of the segment
        typename point_type<Segment>::type p[2];
        geometry::detail::assign_point_from_index<0>(segment, p[0]);
        geometry::detail::assign_point_from_index<1>(segment, p[1]);
        geometry::detail::envelope::envelope_segment
            <
                dimension<Segment>::value
            >::apply(p[0], p[1], mbrs[0], strategy);

        // normalize the box
        strategy::envelope::spherical_box::apply(box, mbrs[1]);

        // compute the envelope of the two boxes
        geometry::detail::envelope::envelope_range_of_boxes::apply(mbrs, box);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template
<
    typename CalculationType = void
>
class spherical_segment
{
public:
    template <typename Box, typename Segment>
    static inline void apply(Box& box, Segment const& segment)
    {
        detail::segment_on_spheroid::apply(box, segment,
            strategy::envelope::spherical_segment<CalculationType>());
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, spherical_equatorial_tag, CalculationType>
{
    typedef spherical_segment<CalculationType> type;
};

template <typename CalculationType>
struct default_strategy<segment_tag, spherical_polar_tag, CalculationType>
{
    typedef spherical_segment<CalculationType> type;
};

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_SEGMENT_HPP

/* expand_segment.hpp
+fwEWd5lVabmcuZ+G+ooQyeZCsRVzEzACdxZ8zpHoXS3n24qPjstdwtfjcFpzG34LsMUTb3OPpOuP1PlOLppQnWjApSxLQV7TRJT4Srdkmmp4AR2ySWZVJGJKJcp1lDb8Cgrqlh1GN5pu383rUAXat9ftvc7KoyzpoSjxATIwcj+3lGf231dpELpRiGtNldKYVidu+6NmyT3VyZUpXoOl/0PrdFpUQ6OevMLjiRXLGPEAfUBTvbrfL5johWlSdeDJZbDphRn8vL67wWyAJPyLs2OvIB4iS2cY/2CE54jqxiQ/YKzix9596tWHbaZD7UHKykA+8PdN3bmA9zYFpPkVykc0r5KiVleBv1KGJM/Wt9brMgZ3iO3SH7x9qzXHokThQx8HXZbFfoUnJdXeN5XCTbxdqmqri4HVEFttke++heIUjpcYNBQn9pc2NiTECrq4Gg7Gpic0/Xz5AhSE9BDvWgfN+Pu73FGsI7LRh1b3NTzoXm+Oe7DN+Zopbe+zkk31pROEVwUTnTef97JhTmuNWE9FncGw7KK+kl6SI9whpzpLgZba8R+k+L94qsDB/qZDbz3fUW1OyNodaMQnuqWwjukPpmDWdlY9vPk/N27m6TULwLnH5lCfYYFhn0+9pctfdL1XJpta4BWq/0802XDa+/4wF1u+naqyB/kiN2K3cpMMDQu7fzHcaVu7V9BMKLwGtWJr/2drdlyHaPT
*/