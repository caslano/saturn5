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
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
*/