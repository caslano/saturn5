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