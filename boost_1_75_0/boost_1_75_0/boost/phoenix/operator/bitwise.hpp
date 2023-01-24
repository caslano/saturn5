/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_BITWISE_HPP
#define BOOST_PHOENIX_OPERATOR_BITWISE_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_UNARY_OPERATORS(
        (complement)
    )
    
    BOOST_PHOENIX_BINARY_OPERATORS(
        (bitwise_and_assign)
        (bitwise_or_assign)
        (bitwise_xor_assign)
        (shift_left_assign)
        (shift_right_assign)
        (bitwise_and)
        (bitwise_or)
        (bitwise_xor)
        (shift_left)
        (shift_right)
    )

    using proto::exprns_::operator~;
    using proto::exprns_::operator&=;
    using proto::exprns_::operator|=;
    using proto::exprns_::operator^=;
    using proto::exprns_::operator<<=;
    using proto::exprns_::operator>>=;
    using proto::exprns_::operator&;
    using proto::exprns_::operator|;
    using proto::exprns_::operator^;
    using proto::exprns_::operator<<;
    using proto::exprns_::operator>>;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* bitwise.hpp
ACP4OCDZToE1gMn50TiU1JWcMsS5v8ZFhGwUH2oYdVApHn3+GunC8aV58YZKFCOxn9gHIW+k5Z0NgpAXajxYt4v0zA7BMgqRGDB2QXlGMfhL8KA/5OJFckXn620bZ+LzGxnebcb4s6LrMz9xpPLYmmdiHOrsWPsNB3Gk9bhPu96IdFtc5CW3+HWaKy/bwckWtxEg+fYVhyGoLDAG9R2ELhHsyitWW7I6rjTdsm5eg6Nub1k5fjeXEldxbOjdLXp1ybjm4tqpkVU6pWHFupjWMSFliSWCcb+mIyrpu5tIFNmHpoizOmyXulxvQAyHnh1HpGmreTFxqRCrhla198sttxFNjc+uT9WVmbGx1aqKPKKOtb2IAa3IzDGG6ZcxZB4WzDkTtB3Ud0kj0GtBMg2TePz6CqP0EuYQ9MuNJ73L+Bn9Hix9L3VuVnxX94HTCUV/s01421OctxLWK/fim9iHv+ecdZcdmhD++N1/LgkAQSOTuCRvxo7TeLeCO0hXy4ClHDMAu4qesXGhsIjD9ENqGNon2NanO9lzX5r4pDv0u199qEPitIezBn1zQabLbzMAYbYiCAznUuCb7xijtrHJGMDxbe6l8r5IFOZdXHZbdCOx+unFDLpz9tx4KQ6UBPmCAn3XTUkSAO+IMv63ckdAnN4M6uD08+Km+e2TCW+kH8TDz6u0F9OyY/RqvXcSl+C+MRjHP0AarHFue4MF
*/