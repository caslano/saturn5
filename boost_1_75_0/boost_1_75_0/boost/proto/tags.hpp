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
rXPd6sZVjVvFAf6qAX7bFnGAH1LMbayr437WnjpXOXSrWFvbSF1bUXdLyfqNTXXz61g8+qk/IUAc4K8a4McKo/1V6JdoeML5Q/6qSP/SVevddeIAP+W3bXDfznMLEf6qAX5qbpS/KuznpUf7efzChroNkeVzf9UAf6j8kJ/nX+Sua9zq2FC/MVTI4PCqgeEqQFH+qrC/zL3eta5hPeuGJvEK4VXR+RmIg+thoKrhi+tcoe6I9FcN8FNpUX4G3+JVm+oi+4v7Q/1VsnHDhro1rgo2dcPpBoSH0s9d725aG4FvgJLgW1y3xt24zrU1DDeicmS93B8qZ8FG17r6rSVrV224BeEhmNXxWtJU11iyflVTU11TxcaNLkpfUdewftUa3pQofxX3N7k2NkbGq/4qtV+GhHPJhghII/0IqSgtFcsjSAh4ppQtnlK1bsOUEih8ihMo7nq1i6Y4p02ZNiVnau369er4lW2sda+vsy5YdXsdXiUXOBkT5ro3rEEiCaQs6h8evk2ujrOqwTnTpufmXTfj+vyCVavX1NbV127e2FgLJa2t2yJMrQZ+bQ3rpRC+2EptkqMyVJ71ntD604zrTTn3a7g/n/u13L+W+3Xcv4X79Wr+ZuY3cP8uHm/k/sUL51ZWiRW26hKnuHixbbEKx1TJNldc4gwBNndm9S3Trq9euri6qXFN9aamddWujRvXN1XDArJmVQMF3t60
*/