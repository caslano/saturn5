// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_VALID_SELF_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_VALID_SELF_TURNS_HPP

#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/range/empty.hpp>

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
    typename CSTag // TODO: remove
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
        detail::self_get_turn_points::self_turns
            <
                false, detail::overlay::assign_null_policy
            >(geometry, strategy, robust_policy, turns, interrupt_policy,
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