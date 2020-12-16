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
+J/VWCIO2OeuGKwSbpYJv0t7/xPQ3JOd5t4ztHNzP3SHbO5NWPwPVOAiShu0UdpXJR568QQpD4+b1bukCx66KAWlLbrkY1HaNyWoHAnKS1AtQw8E5aC0b158IEpLDTHtX6Eh1vnnLVkX0nF+53ki9fhmhFdLTAsJQHZr7kx189Z28BUErkakQxKRFLS3Ty1z0g8QfABcK3KO9hZfB6LghH4ifjz9Z2IolpsdYNzw8FPs9Uw9CjwLcmtuuQhtqpXINjz+ek8Khji48bOji+TPHsgv2nevyJkZkvOkWEQ9rD7YSwevxqa6qMls6paXI9q1ZOU0UVOtt79wpR/1rP/48154hgeMDBSDPiZFOh+0hRMw/FzuQU26fiTa4BAk9yu8M6BpgeO9nZOm1idP8L9kfYycHgHzOaN39sCk9Sq6OQWbMm1guTCH5ipPNJptgZK2qYXlZmNAbwoUrg5E0wbSUpXHyEkbKAxU2Tgv9JDRCnnIXNye/vSfLM9Pf5osz2aWp7M1ralns0DKkJbHMaTFfRFFW/0JRdO/QNGc/nBPLWR/MGu6x4v25BsLISCXZTWxh8IaLq9nPxv+U+DpaPSpJaqL4cQiB9/LN7/GHMqy2mQmCJCl92atjvYsD7vhl2a4Z98nZeE3m8SQGOxflpxoTdemDV5Nbi1W9p7L5GQbTh5YrwBEpY8vleORYD9hP+DJJc9WnX77J2pX2InZCGIVVr+3LqAEsHAFbB5krYGsopJUyyw3L/P4obV4dLl5EAyENTHhslqRcIM1Cgslk2HBRz4DUk53gsJO+wefR9OZeWp+LiUp80mucGxPWdNoz+bU+SMmZ8oUaj5w/t9t84tFensJUEtPnwtsXUMGdjN+AiYXAFWEHNh/A4lUdq8cQllrvFEU+BPGyxqIoSZBQLE/B+PBdNFSPc3JPeeN9sYrx4sDsEe3AMXgMA5YhVOrz7HR6dtPlVdR6/PGu1QrUSSPFuKkPaZvUwLcsOpP1YSMBUbAChGUJU3GWdefzohLeCTAKMB4MW7HavqZVmv29xANzHhkXzOtJ6STEo01xa7QdqNhx4DmbtOvgZbb7uearAFN8QFHN+3e1Pzlxh8Y+/niEb57s5ncR82mo9fsXuc9ujFLhhlLmo5as2ud96jGniIglTQ47s6UU2OcB0ZgbcqDdb30YC291ihB5kBMOPaEG2vy4qIi4nZG1DYwPIGn6ddSllWqGSy5m6FcCyD9AbbkdK0lc39LRiJymUYP+ZSgz4YKbuEr4E7rL/9RRyJ8R+1j6xrOHyI2sRHZAtU50H15Z8JbQ60ydTZB2jr/xrikjwvD0mGvhWB33gqw/Ghw41eFMSXXPzXId94hGzl2odai7cdetAOc3BY9AfJ3aWQaWqLZTQTUfZ4GprZYwwpb9ebPjIDI9SYmMzG9lwTM1eHGd8IdvY25IMQQvTz7esTdaS6qvaGO7JLnEq9By5IrT9w9f2/Cfm6NJZ9/fnNKeMpzwcLkc+HtyedhKXBeSEmz5048d8YTERXsISLHs4v58PKPRSpGqfMaZYVAdPKL6N237E2o5XPdbPBhUYkncX8Rl4XrfVwuhGXjCn3MlYdrIK4iXBfU6V+AG/PpP3RBuPFtmJea7sXC9ewMtr3XXFQzZY7uKtfXJV6r92luV7M0edFc7/KIv6X863bzL4Lxt1Ttrwu9+G7yx1yjcI3G9W1cF+GagGvinM9XPzl+KhbZ4yfckRs8NNxxeBJtZSfMm68662p0abf8xKxF9tmbDAr5M8svCccPgflIPIfj8MsZjqcHe4bjPYLfoGSTcJ+zLQoFog4t6LMFo/Kl9FrDUfKEZnOPE5X52PFv6HIKTvGD+JI=
*/