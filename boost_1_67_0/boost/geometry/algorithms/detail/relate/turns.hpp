// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_TURNS_HPP

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/algorithms/detail/overlay/do_reverse.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>

#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>
#include <boost/geometry/policies/robustness/segment_ratio_type.hpp>

#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>

#include <boost/type_traits/is_base_of.hpp>


namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate { namespace turns {

template <bool IncludeDegenerate = false>
struct assign_policy
    : overlay::assign_null_policy
{
    static bool const include_degenerate = IncludeDegenerate;
};

// GET_TURNS

template
<
    typename Geometry1,
    typename Geometry2,
    typename GetTurnPolicy = detail::get_turns::get_turn_info_type
        <
            Geometry1, Geometry2, assign_policy<>
        >
>
struct get_turns
{
    typedef typename geometry::point_type<Geometry1>::type point1_type;

    template <typename Strategy>
    struct robust_policy_type
        : geometry::rescale_overlay_policy_type
            <
                Geometry1,
                Geometry2,
                typename Strategy::cs_tag
            >
    {};

    template
    <
        typename Strategy,
        typename RobustPolicy = typename robust_policy_type<Strategy>::type
    >
    struct turn_info_type
    {
        typedef typename segment_ratio_type<point1_type, RobustPolicy>::type ratio_type;
        typedef overlay::turn_info
            <
                point1_type,
                ratio_type,
                typename detail::get_turns::turn_operation_type
                    <
                        Geometry1, Geometry2, ratio_type
                    >::type
            > type;
    };

    template <typename Turns>
    static inline void apply(Turns & turns,
                             Geometry1 const& geometry1,
                             Geometry2 const& geometry2)
    {
        detail::get_turns::no_interrupt_policy interrupt_policy;

        typename strategy::intersection::services::default_strategy
            <
                typename cs_tag<Geometry1>::type
            >::type intersection_strategy;

        apply(turns, geometry1, geometry2, interrupt_policy, intersection_strategy);
    }

    template <typename Turns, typename InterruptPolicy, typename IntersectionStrategy>
    static inline void apply(Turns & turns,
                             Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             InterruptPolicy & interrupt_policy,
                             IntersectionStrategy const& intersection_strategy)
    {
        typedef typename robust_policy_type<IntersectionStrategy>::type robust_policy_t;

        robust_policy_t robust_policy
                = geometry::get_rescale_policy<robust_policy_t>(
                    geometry1, geometry2, intersection_strategy);

        apply(turns, geometry1, geometry2, interrupt_policy, intersection_strategy, robust_policy);
    }

    template <typename Turns, typename InterruptPolicy, typename IntersectionStrategy, typename RobustPolicy>
    static inline void apply(Turns & turns,
                             Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             InterruptPolicy & interrupt_policy,
                             IntersectionStrategy const& intersection_strategy,
                             RobustPolicy const& robust_policy)
    {
        static const bool reverse1 = detail::overlay::do_reverse
            <
                geometry::point_order<Geometry1>::value
            >::value;

        static const bool reverse2 = detail::overlay::do_reverse
            <
                geometry::point_order<Geometry2>::value
            >::value;

        dispatch::get_turns
            <
                typename geometry::tag<Geometry1>::type,
                typename geometry::tag<Geometry2>::type,
                Geometry1,
                Geometry2,
                reverse1,
                reverse2,
                GetTurnPolicy
            >::apply(0, geometry1, 1, geometry2,
                     intersection_strategy, robust_policy,
                     turns, interrupt_policy);
    }
};

// TURNS SORTING AND SEARCHING

template <int N = 0, int U = 1, int I = 2, int B = 3, int C = 4, int O = 0>
struct op_to_int
{
    template <typename Operation>
    inline int operator()(Operation const& op) const
    {
        switch(op.operation)
        {
        case detail::overlay::operation_none : return N;
        case detail::overlay::operation_union : return U;
        case detail::overlay::operation_intersection : return I;
        case detail::overlay::operation_blocked : return B;
        case detail::overlay::operation_continue : return C;
        case detail::overlay::operation_opposite : return O;
        }
        return -1;
    }
};

template <std::size_t OpId, typename OpToInt>
struct less_op_xxx_linear
{
    template <typename Turn>
    inline bool operator()(Turn const& left, Turn const& right) const
    {
        static OpToInt op_to_int;
        return op_to_int(left.operations[OpId]) < op_to_int(right.operations[OpId]);
    }
};

template <std::size_t OpId>
struct less_op_linear_linear
    : less_op_xxx_linear< OpId, op_to_int<0,2,3,1,4,0> >
{};

template <std::size_t OpId>
struct less_op_linear_areal_single
{
    template <typename Turn>
    inline bool operator()(Turn const& left, Turn const& right) const
    {
        static const std::size_t other_op_id = (OpId + 1) % 2;
        static turns::op_to_int<0,2,3,1,4,0> op_to_int_xuic;
        static turns::op_to_int<0,3,2,1,4,0> op_to_int_xiuc;

        segment_identifier const& left_other_seg_id = left.operations[other_op_id].seg_id;
        segment_identifier const& right_other_seg_id = right.operations[other_op_id].seg_id;

        typedef typename Turn::turn_operation_type operation_type;
        operation_type const& left_operation = left.operations[OpId];
        operation_type const& right_operation = right.operations[OpId];

        if ( left_other_seg_id.ring_index == right_other_seg_id.ring_index )
        {
            return op_to_int_xuic(left_operation)
                 < op_to_int_xuic(right_operation);
        }
        else
        {
            return op_to_int_xiuc(left_operation)
                 < op_to_int_xiuc(right_operation);
        }
    }
};

template <std::size_t OpId>
struct less_op_areal_linear
    : less_op_xxx_linear< OpId, op_to_int<0,1,0,0,2,0> >
{};

template <std::size_t OpId>
struct less_op_areal_areal
{
    template <typename Turn>
    inline bool operator()(Turn const& left, Turn const& right) const
    {
        static const std::size_t other_op_id = (OpId + 1) % 2;
        static op_to_int<0, 1, 2, 3, 4, 0> op_to_int_uixc;
        static op_to_int<0, 2, 1, 3, 4, 0> op_to_int_iuxc;

        segment_identifier const& left_other_seg_id = left.operations[other_op_id].seg_id;
        segment_identifier const& right_other_seg_id = right.operations[other_op_id].seg_id;

        typedef typename Turn::turn_operation_type operation_type;
        operation_type const& left_operation = left.operations[OpId];
        operation_type const& right_operation = right.operations[OpId];

        if ( left_other_seg_id.multi_index == right_other_seg_id.multi_index )
        {
            if ( left_other_seg_id.ring_index == right_other_seg_id.ring_index )
            {
                return op_to_int_uixc(left_operation) < op_to_int_uixc(right_operation);
            }
            else
            {
                if ( left_other_seg_id.ring_index == -1 )
                {
                    if ( left_operation.operation == overlay::operation_union )
                        return false;
                    else if ( left_operation.operation == overlay::operation_intersection )
                        return true;
                }
                else if ( right_other_seg_id.ring_index == -1 )
                {
                    if ( right_operation.operation == overlay::operation_union )
                        return true;
                    else if ( right_operation.operation == overlay::operation_intersection )
                        return false;
                }
                
                return op_to_int_iuxc(left_operation) < op_to_int_iuxc(right_operation);
            }
        }
        else
        {
            return op_to_int_uixc(left_operation) < op_to_int_uixc(right_operation);
        }
    }
};

template <std::size_t OpId>
struct less_other_multi_index
{
    static const std::size_t other_op_id = (OpId + 1) % 2;

    template <typename Turn>
    inline bool operator()(Turn const& left, Turn const& right) const
    {
        return left.operations[other_op_id].seg_id.multi_index
             < right.operations[other_op_id].seg_id.multi_index;
    }
};

// sort turns by G1 - source_index == 0 by:
// seg_id -> distance and coordinates -> operation
template <std::size_t OpId, typename LessOp, typename CSTag>
struct less
{
    BOOST_STATIC_ASSERT(OpId < 2);

    template <typename Turn>
    static inline bool use_fraction(Turn const& left, Turn const& right)
    {
        typedef typename geometry::strategy::within::services::default_strategy
            <
                typename Turn::point_type, typename Turn::point_type,
                point_tag, point_tag,
                pointlike_tag, pointlike_tag,
                typename tag_cast<CSTag, spherical_tag>::type,
                typename tag_cast<CSTag, spherical_tag>::type
            >::type eq_pp_strategy_type;

        static LessOp less_op;

        // NOTE: Assuming fraction is more permissive and faster than
        //       comparison of points with strategy.
        return geometry::math::equals(left.operations[OpId].fraction,
                                      right.operations[OpId].fraction)
                && eq_pp_strategy_type::apply(left.point, right.point)
             ?
             less_op(left, right)
             :
             (left.operations[OpId].fraction < right.operations[OpId].fraction)
             ;
    }

    template <typename Turn>
    inline bool operator()(Turn const& left, Turn const& right) const
    {
        segment_identifier const& sl = left.operations[OpId].seg_id;
        segment_identifier const& sr = right.operations[OpId].seg_id;

        return sl < sr || ( sl == sr && use_fraction(left, right) );
    }
};

}}} // namespace detail::relate::turns
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_TURNS_HPP

/* turns.hpp
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
*/