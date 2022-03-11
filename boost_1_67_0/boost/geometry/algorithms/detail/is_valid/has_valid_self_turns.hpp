// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_VALID_SELF_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_VALID_SELF_TURNS_HPP

#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/is_valid/is_acceptable_turn.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/self_turn_points.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/policies/predicate_based_interrupt_policy.hpp>
#include <boost/geometry/policies/robustness/segment_ratio_type.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{


template
<
    typename Geometry,
    typename CSTag
>
class has_valid_self_turns
{
private:
    typedef typename point_type<Geometry>::type point_type;

    typedef typename geometry::rescale_policy_type
        <
            point_type,
            CSTag
        >::type rescale_policy_type;

    typedef detail::overlay::get_turn_info
        <
            detail::overlay::assign_null_policy
        > turn_policy;

public:
    typedef detail::overlay::turn_info
        <
            point_type,
            typename segment_ratio_type
                <
                    point_type,
                    rescale_policy_type
                >::type
        > turn_type;

    // returns true if all turns are valid
    template <typename Turns, typename VisitPolicy, typename Strategy>
    static inline bool apply(Geometry const& geometry,
                             Turns& turns,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        boost::ignore_unused(visitor);

        rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(geometry, strategy);

        detail::overlay::stateless_predicate_based_interrupt_policy
            <
                is_acceptable_turn<Geometry>
            > interrupt_policy;

        // Calculate self-turns, skipping adjacent segments
        detail::self_get_turn_points::self_turns<false, turn_policy>(geometry,
                                          strategy,
                                          robust_policy,
                                          turns,
                                          interrupt_policy,
                                          0, true);

        if (interrupt_policy.has_intersections)
        {
            BOOST_GEOMETRY_ASSERT(! boost::empty(turns));
            return visitor.template apply<failure_self_intersections>(turns);
        }
        else
        {
            return visitor.template apply<no_failure>();
        }
    }

    // returns true if all turns are valid
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Geometry const& geometry, VisitPolicy& visitor, Strategy const& strategy)
    {
        std::vector<turn_type> turns;
        return apply(geometry, turns, visitor, strategy);
    }
};


}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_VALID_SELF_TURNS_HPP

/* has_valid_self_turns.hpp
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
*/