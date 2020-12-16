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
F/UTW5xKVA6d4ZkQ83HdfYcPxWU1oVVUCDm4beGyXLlPReUyHHrkNYbZux2X+xIvd6TtJIWWKsQFqDpq49cifiqDUlPXiu5soY3erpaX7SD+50PWF4kpfMLIQE5M8PcjTjPfJEPd57ie761tbK7Zr73j2vyHqM2kREtJobi+c8oU9DF27jrGbXS3cm+kN+980qPvlgilqzSrVGL9+aZnzPoNXf08Ng+MA7dXTq0hOXG44APssEb8Z2M6BVRdMoMDZN4FvgmbPk4T57Vsyxoz/+VH7Y5EAWf4CiNfmzq3e10np0Q8cPXZRFwCNw/m4jhCiELk8142ycN/fl68nucBx7pY22vhRz1asYpDc6cc9uqlH2twmQelx7gAaxS9fOcwjoQQK+aKpgw95xigqxGOOGAvX30mn67Uo3Hbjuv7Q0J8Hkz2gLP7uEf5dMLRxV2aPlrIf2YcG2fE0EXy2nUdhrvN1xQSY2t1dY7FsXiVy3No4yzvdVEevQGFvB+ed3nozjKdD3Nbrh9f2/Z5xG/dpb/R86NATyHmxNt8+pktQr7dZm14j8/b2T29fsHenVksi/KJrF/bO5AMQczwkh9g8tV98faPd0nTSjYuD98d800APMJbXg8xQp4W5VHfAw7wvMHpXj28PsUL91i+uIx7HG1oiy4kIcLP8eF+IW9lHfPRYfxejd78PbbwuBeP0Osm7sUpj+X7d9CHNe8wq3dd/oee5GIHWcxrY1e769buJ0w+Dobl0aFhFOTc06AJK+7H4XO+rEUix/jf0c3LMwfFBsBd1p3XODdd+Sef+ScxdkJkGz8ezzqzbwwcU3434FU/N47BYwo5OEYWJ+eeG/vFybFtZoDPrvyL4/rx6OrLnsUF/QxmG42Hb++rD4qTs0wX3Lkzbkzf58thqRow8ICpvblfXI+A73/Jzf1jjiyTSgPl3By9aozvbzT9o0gW4iRcO5Th+Q9zPG4Y8sNLBUaBx+66eVwmxBpgGN+H4rbsHhTbY362HBdh5w7bcqc39ivnvg0Q2sO3TOYdxv/+vI1ezTygBirsTX6PYeNtacik+1EuX8/ma8p347Oz6eMo2Ab6GB4XuPnw+MDDoQ74MXkK5z8be2PFrelXbu4fc2jrzPaOnUPLruxr9y+LjXdlFNJ5nJLXh7JknhIiD2GmujJfisbWTiNsX7zM130ZZGC/tqVWeZnvRu06ZCY3LD52UcaNx4/juqic2ShthCZX7itP8pj649PU8nhxWr5QT2LOvGuKh793Ztuaj6/4Mt8O2Otuxqyu7cHnbm4ldXLYp0kOu9dyb4SfRTQGSk4Bt7h7/RMZSYgT4kTQ//wmukOmnW7TLE0F26Q4dvpW7u4FnE4qIQuly7JOhb5PC+W51Z2s7o/vdSj4wg2cT5aKqlFFOeSFWPinHLjHfHT3v3HO71MEhFJVWgpT2HRiWHDvXrzutBdtpgjAYhCnIEdhG+e1Ml+6CMl9fhIj/Q9Rf3KRQlual7L9d7HIaczJNzt1/flt/K6m27zs2kaGNh6MRV67+3LEoxcKypUKF80ZMHLzwWfByJnu7OSUV62SMmnbGI909jia4qeci/ikou+VrAudTjHEGbDCjrft4LRHWpkPVUmIanfRNAZUOtw5n4Gy/L6W5l2jMwGmd7nQleY4Es/m5XFlwe2uLFTPsc2hX7C3bfKn21kz92CnJREhDuuXOC80MJPtUGbtQax21h4+Sg8BlJG9p/8h4kX3/6TJs8GNl1VWBec1PgaX51jQx8tm6IeuYdom9w5+T3d3es3kLVcVpGDp7Td2r2ReQzb1I7026ovw3Id0wMIaxHAwWra9vR7huvu7g0/kU5bpTOJEEMENBH4=
*/