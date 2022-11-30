// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_COMPARE_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_COMPARE_TURNS_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>


namespace boost { namespace geometry
{

namespace detail { namespace turns
{

// TURNS SORTING AND SEARCHING

// sort turns by G1 - source_index == 0 by:
// seg_id -> fraction -> other_id -> operation
template
<
    typename IdLess = std::less<signed_size_type>,
    int N = 0, int U = 1, int I = 2, int B = 3, int C = 4, int O = 0,
    std::size_t OpId = 0
>
struct less_seg_fraction_other_op
{
    BOOST_STATIC_ASSERT(OpId < 2);
    static const std::size_t other_op_id = (OpId + 1) % 2;

    template <typename Op>
    static inline int order_op(Op const& op)
    {
        switch (op.operation)
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

    template <typename Op>
    static inline bool use_operation(Op const& left, Op const& right)
    {
        return order_op(left) < order_op(right);
    }

    template <typename Turn>
    static inline bool use_other_id(Turn const& left, Turn const& right)
    {
        segment_identifier const& left_other_seg_id = left.operations[other_op_id].seg_id;
        segment_identifier const& right_other_seg_id = right.operations[other_op_id].seg_id;

        if ( left_other_seg_id.multi_index != right_other_seg_id.multi_index )
        {
            return left_other_seg_id.multi_index < right_other_seg_id.multi_index;
        }
        if ( left_other_seg_id.ring_index != right_other_seg_id.ring_index )
        {
            return left_other_seg_id.ring_index != right_other_seg_id.ring_index;
        }
        if ( left_other_seg_id.segment_index != right_other_seg_id.segment_index )
        {
            return IdLess()(left_other_seg_id.segment_index,
                            right_other_seg_id.segment_index);
        }
        return use_operation(left.operations[OpId], right.operations[OpId]);
    }

    template <typename Turn>
    static inline bool use_fraction(Turn const& left, Turn const& right)
    {
        return
            geometry::math::equals(left.operations[OpId].fraction,
                                   right.operations[OpId].fraction)
            ?
            use_other_id(left, right)
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





}} // namespace detail::turns

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_COMPARE_TURNS_HPP

/* compare_turns.hpp
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
*/