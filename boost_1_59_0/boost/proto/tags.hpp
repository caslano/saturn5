///////////////////////////////////////////////////////////////////////////////
/// \file tags.hpp
/// Contains the tags for all the overloadable operators in C++
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TAGS_HPP_EAN_04_01_2005
#define BOOST_PROTO_TAGS_HPP_EAN_04_01_2005

#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace tagns_ { namespace tag
{

    /// Tag type for terminals; aka, leaves in the expression tree.
    struct terminal {};

    /// Tag type for the unary + operator.
    struct unary_plus {};

    /// Tag type for the unary - operator.
    struct negate {};

    /// Tag type for the unary * operator.
    struct dereference {};

    /// Tag type for the unary ~ operator.
    struct complement {};

    /// Tag type for the unary & operator.
    struct address_of {};

    /// Tag type for the unary ! operator.
    struct logical_not {};

    /// Tag type for the unary prefix ++ operator.
    struct pre_inc {};

    /// Tag type for the unary prefix -- operator.
    struct pre_dec {};

    /// Tag type for the unary postfix ++ operator.
    struct post_inc {};

    /// Tag type for the unary postfix -- operator.
    struct post_dec {};

    /// Tag type for the binary \<\< operator.
    struct shift_left {};

    /// Tag type for the binary \>\> operator.
    struct shift_right {};

    /// Tag type for the binary * operator.
    struct multiplies {};

    /// Tag type for the binary / operator.
    struct divides {};

    /// Tag type for the binary % operator.
    struct modulus {};

    /// Tag type for the binary + operator.
    struct plus {};

    /// Tag type for the binary - operator.
    struct minus {};

    /// Tag type for the binary \< operator.
    struct less {};

    /// Tag type for the binary \> operator.
    struct greater {};

    /// Tag type for the binary \<= operator.
    struct less_equal {};

    /// Tag type for the binary \>= operator.
    struct greater_equal {};

    /// Tag type for the binary == operator.
    struct equal_to {};

    /// Tag type for the binary != operator.
    struct not_equal_to {};

    /// Tag type for the binary || operator.
    struct logical_or {};

    /// Tag type for the binary && operator.
    struct logical_and {};

    /// Tag type for the binary & operator.
    struct bitwise_and {};

    /// Tag type for the binary | operator.
    struct bitwise_or {};

    /// Tag type for the binary ^ operator.
    struct bitwise_xor {};

    /// Tag type for the binary , operator.
    struct comma {};

    /// Tag type for the binary ->* operator.
    struct mem_ptr {};

    /// Tag type for the binary = operator.
    struct assign {};

    /// Tag type for the binary \<\<= operator.
    struct shift_left_assign {};

    /// Tag type for the binary \>\>= operator.
    struct shift_right_assign {};

    /// Tag type for the binary *= operator.
    struct multiplies_assign {};

    /// Tag type for the binary /= operator.
    struct divides_assign {};

    /// Tag type for the binary %= operator.
    struct modulus_assign {};

    /// Tag type for the binary += operator.
    struct plus_assign {};

    /// Tag type for the binary -= operator.
    struct minus_assign {};

    /// Tag type for the binary &= operator.
    struct bitwise_and_assign {};

    /// Tag type for the binary |= operator.
    struct bitwise_or_assign {};

    /// Tag type for the binary ^= operator.
    struct bitwise_xor_assign {};

    /// Tag type for the binary subscript operator.
    struct subscript {};

    /// Tag type for the binary virtual data members.
    struct member {};

    /// Tag type for the ternary ?: conditional operator.
    struct if_else_ {};

    /// Tag type for the n-ary function call operator.
    struct function {};

}}}}

#endif

/* tags.hpp
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
*/