// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_HAS_SELF_INTERSECTIONS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_HAS_SELF_INTERSECTIONS_HPP

#include <deque>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
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


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_HAS_SELF_INTERSECTIONS_HPP


/* has_self_intersections.hpp
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
*/