// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_TURNS_HPP


#include <boost/geometry/algorithms/detail/overlay/do_reverse.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>

#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>
#include <boost/geometry/policies/robustness/segment_ratio_type.hpp>

#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/distance.hpp>


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

    template <typename Turns, typename InterruptPolicy, typename Strategy>
    static inline void apply(Turns & turns,
                             Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             InterruptPolicy & interrupt_policy,
                             Strategy const& strategy)
    {
        typedef typename robust_policy_type<Strategy>::type robust_policy_t;

        robust_policy_t robust_policy
                = geometry::get_rescale_policy<robust_policy_t>(
                    geometry1, geometry2, strategy);

        apply(turns, geometry1, geometry2, interrupt_policy, strategy, robust_policy);
    }

    template <typename Turns, typename InterruptPolicy, typename Strategy, typename RobustPolicy>
    static inline void apply(Turns & turns,
                             Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             InterruptPolicy & interrupt_policy,
                             Strategy const& strategy,
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
                     strategy, robust_policy,
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