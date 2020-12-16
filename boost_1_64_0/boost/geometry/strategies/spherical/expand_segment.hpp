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
lHJtXcIqnsUvky9u3YHi9pvcvJI2fUtG5pmXZg+/u/Z36X1+mTWoYvHrwljXeSl+3ZYC+622rKNRcJ0X6zoaBdedsa5jUvy6M8Wtk3Kj684Uty6Pdd2TguvCWNepKbguzOrS2vTJg16I/yBghF9oi/sPnzlXi7Tb263L70DYhJBNcG63/i8P+sXB2Vgf56BjuWxZrp7FcvNkuflYCxc4LZcnyzWwWG6CLJeJQThRLcff8ILje1CW+4fEN1UtR5DlGlks9xDz+eLDWBenOy1nk+V6WCw3TuJLxC443mm5fbKcn8VyscznhXES7xin5c7LcnUtllvOfOXxBayDK9Ry8m6PXSyWWyVlYquxI74iy1XxlndveSfXFsqBcvL7wWNSRvsEtse52BUXY19cikPweRyBL+Eiie+2EsSDgfgq1sPXsDXmYhd8HXvjWhyE63AYvoEjcT2Oxw2YhhvxYXwL5+BmfBK34GJ8B1/BPFyH7+I23Ip78T08iNsxH3fgd7gTL+Eu9OT62Y234R6sjB9iAO7FJrgPW+J+7Iof4wA8gMPwU4zAz3AMHsRE/BwfxMM4Hb/AeZiPS/Aovohf4mt4DNfjcdyI3+DHeBqP4Bk8h2fxIn6HWr+O32Mc/oDP4Y+4Ai/g63gRt2PpEmw3lsfyWn+OWAf9sRfWwIEYhCOwPmZgE/wntsCnsQ2uxc74A3bBkpxDXfE27I5VsQc2xH7YFvvjAByAczAcX8WBuAcH4WkcgldwGHqXIgvAQByBbfBe7I/3YSyOxIk4Cifj/fgERuBKjMR3MAo/w9H4LcbizxiHpcgvU9AH07AyZmA9nIDtMRNjcCLOxkn4PE7GnTgFf8UH8U+cineUYedjO5yG/fEhTMGH8Rmcgbk4B9/CbHxPPh/Gufg9zsOSt5C/YhAuwAa4EEPwSeyFizAGn8KH8GmchYvxLXwWz+EyLMm76Er0x1exGa7FzvgGpuJb+DBuwpm4BRfj27gW83A/vov/xq3odSvXH1bA7VgJ38dquAM74E7sjLuwH36AcbgX83Afbsf9uAM/wVN4AEuU4zrD9ngIO+JhvB+/wFTMx0fwCM7BL3EhHscc/AqfxxNS5yCcYH83lT7ZtGsGukm+ep/UORiJ1XAU1sD7cQTG4igcgxGYgLJexzsn76Lu623CfJWxKQZiM5yLwViG+ZvjP7AFXsIQlH7d5F1Rf4dkveZ+3VrLetvIekPxBWyLTVmoHa7H9hjG8h1wF3ZEqSsk73rsO9kfznWFwmT9nbEmdsMOeDd+it3xMPZQ61PvYJzT7uvrLevrI+vrL+sbgDOZPxz/hQNR+vWSdyPyPkmfc79e30udr/PYEX/EHngBI6Xu6XQsjcuwDL6Dt+FZ9MXzntqGFt5nj2W9ioLrVEh9imurSzFkbMnrUp/ietaluJ71KIpbh+IyIdii3kQM+8lUd+J61ZkYW/K61Zu4nnUmXOtL7CPMJK2nUdWVsKwncf3qSJjqR/zNdSMc9SIWs82bCccIHuOoG0HoSYgnzCSsJhwgXCE05kEtnJBGWETYTHD98yIk3ZDyf/svn9p/Q+RX0OtRF6Aq7Z5+0sr6g7TfRFi5/Sf95qxWfZdl/q4FX+l1CBr5ErejHauU488iVCLMIPyirddLz3MHD+4bEjHo7q4DBnXTm7NSPlb0NotlbtfLkfTfjnqafs9nP6Qyn3lcbtNYk9LuyNSGKlgOW7qk1SZp9fB2TSsRkNjU2BuXVuff9DZLukIJlQkhhF9JV457uijNIjwQwYqL3r5Spc00fqtajamcPtTTuk7Iee8bXydkg6d7vYg/iDu4lGXctLsrej2BNJf40yzqhLT0sq4TElnqxtc=
*/