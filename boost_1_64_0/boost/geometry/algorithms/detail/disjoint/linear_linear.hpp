// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2017.
// Modifications copyright (c) 2013-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_LINEAR_HPP

#include <cstddef>
#include <deque>

#include <boost/range.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/do_reverse.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_as_subrange.hpp>

#include <boost/geometry/policies/disjoint_interrupt_policy.hpp>
#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{

template <typename Segment1, typename Segment2>
struct disjoint_segment
{
    template <typename Strategy>
    static inline bool apply(Segment1 const& segment1, Segment2 const& segment2,
                             Strategy const& strategy)
    {
        typedef typename point_type<Segment1>::type point_type;

        typedef segment_intersection_points<point_type> intersection_return_type;

        typedef policies::relate::segments_intersection_points
            <
                intersection_return_type
            > intersection_policy;

        detail::segment_as_subrange<Segment1> sub_range1(segment1);
        detail::segment_as_subrange<Segment2> sub_range2(segment2);
        intersection_return_type is = strategy.apply(sub_range1, sub_range2,
                                                     intersection_policy());

        return is.count == 0;
    }
};


struct assign_disjoint_policy
{
    // We want to include all points:
    static bool const include_no_turn = true;
    static bool const include_degenerate = true;
    static bool const include_opposite = true;
};


template <typename Geometry1, typename Geometry2>
struct disjoint_linear
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        typedef typename geometry::point_type<Geometry1>::type point_type;
        typedef geometry::segment_ratio
            <
                typename coordinate_type<point_type>::type
            > ratio_type;
        typedef overlay::turn_info
            <
                point_type,
                ratio_type,
                typename detail::get_turns::turn_operation_type
                        <
                            Geometry1, Geometry2, ratio_type
                        >::type
            > turn_info_type;

        std::deque<turn_info_type> turns;

        // Specify two policies:
        // 1) Stop at any intersection
        // 2) In assignment, include also degenerate points (which are normally skipped)
        disjoint_interrupt_policy interrupt_policy;
        dispatch::get_turns
            <
                typename geometry::tag<Geometry1>::type,
                typename geometry::tag<Geometry2>::type,
                Geometry1,
                Geometry2,
                overlay::do_reverse<geometry::point_order<Geometry1>::value>::value, // should be false
                overlay::do_reverse<geometry::point_order<Geometry2>::value>::value, // should be false
                detail::get_turns::get_turn_info_type
                    <
                        Geometry1, Geometry2, assign_disjoint_policy
                    >
            >::apply(0, geometry1, 1, geometry2,
                     strategy, detail::no_rescale_policy(), turns, interrupt_policy);

        return !interrupt_policy.has_intersections;
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Linear1, typename Linear2>
struct disjoint<Linear1, Linear2, 2, linear_tag, linear_tag, false>
    : detail::disjoint::disjoint_linear<Linear1, Linear2>
{};


template <typename Segment1, typename Segment2>
struct disjoint<Segment1, Segment2, 2, segment_tag, segment_tag, false>
    : detail::disjoint::disjoint_segment<Segment1, Segment2>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_LINEAR_HPP

/* linear_linear.hpp
nnVh/1/t7c5tXzHbtVwhr26MwrAD5u1cdT6wx/5eNhwnJ4/GwvZm8TAMBgyYE4mhWLhktnuQVkfh7udi4SYY155Pds3z7IKzovDeFDWaDcelweczovDolHiY/Swbq5u3OmbvQ+Z4s9+NZFPjHxVXk2HOWddG4S5YN+SlEK6Xm788CV/Ugg5Z1TZjz/at/OTPpNby7fwopLHhtI6x8Iq83zJazibDdLXxVzjyam7P5hkTD8/Cr97qyNnydKnP6ifFQyvvj89aHr5dxH/HfKdqLCzLzX6P+hmG11FnNt4P69XM/pXpiU3ioQWcKgCPLx8oHvGXvnvkeKsQGl4UhdRX4qFcO7E/3DjnhfDLxfYJXuYZ+4mxpcbD3iO+/7yY3ivG3pKnY71jbE0ULhXzVcTwwIej0HGlPLsaLrzpGcVws/hxuPlGFH47y31VxaNwxZJIfYUH471Hq1kUHmSjT/CN12uoe0vxlsnmgC/thZlXbpcv49l2Dh8tt+cur/omnl/52VO+isfDXdeH0FrN+u5sz4tQIx9jy6nPwwnz/u0Z+TCTwCqP+6gTl0+Pwi9V4H02NeSRWMhXQh7LwV/vxFUywdKeantH4splURglp4d/4VmnsL98VfYohKe53oEZamx+9aWmOiNPYlXZurK5XkGHKQ0bfsYZ4ECE4xRVnw/jB/3YcvQY9oaVTWN0Z9ctUcBTgOFdtc6ei7RfzMY9V28CriKne77G7wdht/9/e8I5i8KW7bFQ23HXw9yfn4cbas+OO2HFy7GQX+1+cE0Itz1jfyB+umpe4r3V8fC+WHgTn7zv+Sh0XR4Pb1YXn+vYeIt5Pm6P+wee8fo0Gxzwnuyf5BU7N/9Kfb7WM4Hh4zNiuu8+HO829aOPPLjMvUB9/VUHBt4chWXwYMm+KDyJm6UWjoX1kfhUV2+/Tb73lCtwaoRcyfoVX7wWhbPOFU842zez3CvwNkyZxgbD2HU+PHSezutj4bVeMdzHMyXUjxsKRuHCjT5viruxWcpKmHK5+mhejWDQ/rvg+JWxcM2V8XDkKtd5E/9+VX2+UOzI4Xrq2BzXzjxenJSIheCz8T/ANFz9fdxlhhxZkYbfqpszPmTvafa13ACH1NbP4WOuyQkckHcd4TNe8csSvAQfGpgSc9NaFL7Bj7r8hqPllDNPRWHGte4PhIdHq4hn3HfbAjXnlii8nkMdkNd71IM2xll1XRTOV4saj/Y+irXGyhZjYeBgfO/q9rCsFxzKDjf0CtM7eK/zp/HQju2vm6t+NlJjKkThnn7yjZ3SPsVT5P/MmmLgRflcFgdVU/vy/5Sm7rVZpBdoEcKiCrEwXG3P+6xngZeJQm/Yln1rPFRTkzukqv1t42GIvHipQSwc3GwMD0Xhun5qEE5ydL6YGoRTVsXx1PKH2erjzx3PFkV+xA2vUTvViHvw9k+K6DO+Nf7D3q8wBqaKuy8z4bhV/LwZj31EzcC5JuLXHRbZK4gfdb4MHqodPWby4W7xXMrur/VqiFitrdbm/hrmiPW9atdFw+XvJhyCn36E4es7hHCZOlOebSrc4udPcPXheJM4+VlOfQAv3xrq/s1zYI1cT9MnbRKbT+lH8sH/mV/EwjM9Q8gOOz68Hj9T3+rJhwnF+HwKbjubr/PoD1LgLSy4BV5O9p0dmdV+9WkD7EjKBWeKiKPG+opiAeeOwho1Y9EAfZBrTpcvqTB5kHEeyxwPu216feAN+IWjablClTz2OfF3sYOwXF+UHy5ceI4eo7L4rKZm54I16tgDr8bDeDZ8vBd8eFot1G/uSxGfvfVxeopOfePhnbfjYefrsK5MLDzLrq/Lx+sfcl02ffMO9fVwPJxzGCa8CHc=
*/