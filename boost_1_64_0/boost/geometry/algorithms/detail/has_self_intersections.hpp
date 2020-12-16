// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017, 2019.
// Modifications copyright (c) 2017, 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_HAS_SELF_INTERSECTIONS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_HAS_SELF_INTERSECTIONS_HPP

#include <deque>

#include <boost/range.hpp>
#include <boost/throw_exception.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/self_turn_points.hpp>

#include <boost/geometry/policies/disjoint_interrupt_policy.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>
#include <boost/geometry/policies/robustness/segment_ratio_type.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_HAS_SELF_INTERSECTIONS
#  include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#  include <boost/geometry/io/dsv/write.hpp>
#endif


namespace boost { namespace geometry
{


#if ! defined(BOOST_GEOMETRY_OVERLAY_NO_THROW)

/*!
\brief Overlay Invalid Input Exception
\ingroup overlay
\details The overlay_invalid_input_exception is thrown at invalid input
 */
class overlay_invalid_input_exception : public geometry::exception
{
public:

    inline overlay_invalid_input_exception() {}

    virtual char const* what() const throw()
    {
        return "Boost.Geometry Overlay invalid input exception";
    }
};

#endif


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template <typename Geometry, typename Strategy, typename RobustPolicy>
inline bool has_self_intersections(Geometry const& geometry,
        Strategy const& strategy,
        RobustPolicy const& robust_policy,
        bool throw_on_self_intersection = true)
{
    typedef typename point_type<Geometry>::type point_type;
    typedef turn_info
    <
        point_type,
        typename segment_ratio_type<point_type, RobustPolicy>::type
    > turn_info;
    std::deque<turn_info> turns;
    detail::disjoint::disjoint_interrupt_policy policy;

    detail::self_get_turn_points::self_turns
        <
            false,
            detail::overlay::assign_null_policy
        >(geometry, strategy, robust_policy, turns, policy, 0, false);

#ifdef BOOST_GEOMETRY_DEBUG_HAS_SELF_INTERSECTIONS
    bool first = true;
#endif
    for(typename std::deque<turn_info>::const_iterator it = boost::begin(turns);
        it != boost::end(turns); ++it)
    {
        turn_info const& info = *it;
        bool const both_union_turn =
            info.operations[0].operation == detail::overlay::operation_union
            && info.operations[1].operation == detail::overlay::operation_union;
        bool const both_intersection_turn =
            info.operations[0].operation == detail::overlay::operation_intersection
            && info.operations[1].operation == detail::overlay::operation_intersection;

        bool const valid = (both_union_turn || both_intersection_turn)
            && (info.method == detail::overlay::method_touch
                || info.method == detail::overlay::method_touch_interior);

        if (! valid)
        {
#ifdef BOOST_GEOMETRY_DEBUG_HAS_SELF_INTERSECTIONS
            if (first)
            {
                std::cout << "turn points: " << std::endl;
                first = false;
            }
            std::cout << method_char(info.method);
            for (int i = 0; i < 2; i++)
            {
                std::cout << " " << operation_char(info.operations[i].operation);
                std::cout << " " << info.operations[i].seg_id;
            }
            std::cout << " " << geometry::dsv(info.point) << std::endl;
#endif

#if ! defined(BOOST_GEOMETRY_OVERLAY_NO_THROW)
            if (throw_on_self_intersection)
            {
                BOOST_THROW_EXCEPTION(overlay_invalid_input_exception());
            }
#endif
            return true;
        }

    }
    return false;
}

// For backward compatibility
template <typename Geometry>
inline bool has_self_intersections(Geometry const& geometry,
                    bool throw_on_self_intersection = true)
{
    typedef typename geometry::point_type<Geometry>::type point_type;
    typedef typename geometry::rescale_policy_type<point_type>::type
        rescale_policy_type;

    typename strategy::intersection::services::default_strategy
        <
            typename cs_tag<Geometry>::type
        >::type strategy;

    rescale_policy_type robust_policy
        = geometry::get_rescale_policy<rescale_policy_type>(geometry, strategy);

    return has_self_intersections(geometry, strategy, robust_policy,
                                  throw_on_self_intersection);
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_HAS_SELF_INTERSECTIONS_HPP


/* has_self_intersections.hpp
cT6T6z89euB3Z4r3RNZ7mVQyan0F9pder/ylkX7zwERmiAd0EiTXv+YF161PtDo8Roie5hlhe3+1WQhlf6bUvePH/EUkf9i7/ibBX73jL6EYFDB1J6iuC+u7+ek4bNPI/nU92pkrE8LwMxCGTnOY9fj0kL7oHZFgvEkn498p2h/lYerX1qlsf5dEgnk2iDxPDKH5nhC/BHwxzfepfMNwPoB2P7ZAjgd4X5r9LouMf6/ycmF7SJ9luSBbvGEVCcr6OLFGQTDw5cogbdZHOR18LG3rdHmQ7uOi33+tsl2fRPi1yh/eL/zeTyu/9zPKZn8WYapn0EQ9Ib/TlW/3BRF/fsTKE+Vy8V8S/J6v+L0a4fMVv+cJfr+m+L1G8ft1lf+Jir9v+vFIq/n7tvQZcHdl+DsAbWe2d3T3NEejtvVxCHb0OvDZGJ7WIne0tCI1hzn99Ui/IDDuzIyYV4Pte67wT74n7Mm0Cej+OvBuLNn/WHy3b1+rbXqCJUZGJazQc0/0+PtG5lo/iGAjxhZ7DJtlYBncXQ/YbAMbAAz5FhlYkjIGvWKCzTMw8/wxYCXWlhKMtkaTvWVYxPIShNUbWJ+DLcYZ6B8E+gDzLIrf7Tl7b+q7BPH3oP/+YSR4ZsXZzuiZfbTTNyij6Jp96biXlU+0m+jGDY5/N/9NAZ8xumF7ymA4Jjhk71kK16uOtag+95P7qJ+wToWVM2rorjgpsazRps0GcddmiL7k0eHjw/Bz8lZg2/BU8Hmr4XNK1o+/LWK+kD2PBDNpIyLtHSijtuP6Ttq7InjLh89HuDsefmT57ed3xH4Rmcw+rY2drR3d3eujCTqKkdyd6LP7udnGtMKPuwHj+3vQh9yrfL4bhM/n+Jji3Q/cX4m5qe+yfXNxBwNzU3j/GH9rPPpUX/Qb0HxA5U98Mq+7MLZ6ELiHFK7t+1W//jvYvl1ecBxIfPBbAPaeOdCSPsYilOXhkLIUFmXL8d6iYFkeBX9/jgTnRzMGX/TLu0LehP4L0j4u5/1UuZ8UfinJxvzmfbOES23YfTUuzL//Os4HmOk9DZp/U/OMUif+gTh+7zKCegmZm34GaZ5FGn7XUujGmGf3xTK9f0fcW6lVRePHu/8BvRVFJg3qQKUpqEY6UQdTqsXbjJ6Lr4XsT0Y+Uu7TqvFufHWwrLuQrjWEt+lIQ7rFZ4PWKj5nVjs+Z1WH83m04pPzy8HnHOR5THX2brEpxkJf+J/ulp7o5tau7vaNHdGOjT3R7tYe7wkb58mozUtdXzvd7tE0dIuIVqovHcUuy6i16meeJEHGtD/Rn82L6K3f+Mpoa0dP19Zoz9bOVj9Hoo08x6NsoXUnP74gJL6zq7WltavHW0W8TQVvxcQb8TE0OkCnUtLJfVEzTe1zGBJh+DTne7Pl7t64qYuchU0dZ3RsPLOD85dxPevphOCWHrKXJCAnsyki3jK+eZlAcTSmSpyNLd2dUeppOte3ro12tXZ3buzobvWsnKehLPMg59RoJtnHhWCI4/4pd8eLqLfm9e1rm3soW0O+Z1M3ixrlCMVBcY2IPZQnDM9BuDzhOO0dFmbpTMuZH+lX+7r21rVOfkdNwBe00VtH8imEfBZAPjQCTcTsETLb4WdSLKqwSFfnjQWu35xbrfYL4+zYDEMZYTtPZnMaikucUs9oE3w74EUAM6gSXu8Z/4w4GB7z/PQNNPcv82gyYZmHfedmsDc1GKWLyT2GNZs9ywYkeGkzMEGr04QFrRIq5xYvq/k+b/MJ/mrP6hPDFhJsmzdOcNYfehHJvpTi/f8GrVww/HY/4WuFrr+kjXSAjUB2/uHYah7X2N8FgJc7OPsiFdXOxpVZPqi/hI2rAl4=
*/