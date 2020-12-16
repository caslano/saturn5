/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_AT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_AT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<iterator_range_tag>
        {
            template <typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::begin_type begin_type;
                typedef typename result_of::advance<begin_type,N>::type pos;
                typedef typename result_of::deref<pos>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Seq& s)
                {
                    return * fusion::advance<N>(s.first);
                }
            };
        };
    }
}}

#endif


/* at_impl.hpp
yR3HyOXGqnQruqsahIzOVDwoK+wBWFnz2LWtwreUS1Bw5bl/7+a0Zjyo7q73T/V2N+g2AV01qO4GXjDs/HL6ThwPuG/JR9QoH6tgXwoc1/P6OxiI4Pe0xQNlPO5Ntzlbm6CB94YJvO311VZ8czNtHl2XAg82OYzHx7XfNbDhHuUbzTZ57fL9uclplw/2PIy3V/n2N3i8fGjD14Gnhn4YN94Vtj4Sp5HVwOvLPOBcuh44TYtOdqcDHBnFye1teRnBtKP8S5Nzalj5+9J+Xm/UwOmnf1pdeQDn3I0bnO2TuKuOt3FvwjiqAtk9beD41JnlRjyfuankDZ9RTz2s9LGefK1u7Cf3Zm2chvdd2UngC2Obf/NSJ0nzMLvmOYU5f3i40Z79M9wGe3GK4fxej8LQ1nCYcFeNT3O8Tw/zraoYwKG9anCgCzoi4sBetsmpowHnN/uJw9oA0SC/Zw+0Oap/ahujOcIb9Y+LRIY9xflyGnYSSlfqkmGPUr83ehI2B8h3TeprzrlVcJCnOp4+/Ms22jwMnCiynX/JvuxhrM2x54Rx2MBRLrSHwpvtyvdcOrPgNMtuvJcLDsreTGuwnzi8TTQH7forcCb3qxMHgLf6FdrhmLb5ba9JYWPyfHDMdV0OO5JmO1lZmAf5VfvkmdROi7ydaLHBbDwZLkH4T5nl2BZ9qiWB2TTukxyZahX1CuqdsAPASEriaEZwxBw4lEb98ZF0o23c64FDnxRlWba9a4zz568PHDpQlxM2e4+8keSs9ncqozHE3bkxhbfbHfiojctMIO2DNwHe1Au0+fm3aVtxIumzjY7xZvAjge+pN+dH4EzUm/mG3mSZl7pecNX+YLXewE5lm/l8C5PSCxP6QszTKoQm46bfzw09vx6ZMkeDMiGJ2BO+tOMxBITmP8/kLwSOk4ZhkYhm/ELaj5a3oXnDluSPeqeP0PSzw/2FPtTQU9o1gv5/dIpj/TMKhuyXpoHriNH2958hrNIruuUoPXlur7A7GE18RNf3TD/w+8b49gatvgydvbAfGOWH9Q3If3MOHMKp7Y24f3Z9YOpxY3oWGXF/5QbAjLFVFRuc2YPgGH1GkfAt++BN25yt7f4ZWkWzvIhbSF5dxHqFjXFVYXv3rxO3bON0qRb5/GYbry7VGuueL202/ESkbpEmfiZycvq20pNLR3Uj8cFYO459jP2GyWai8IIsS2NfeR8sd09urK8cW0j69OqLpa1lKR62BkdcB7f4+21hXiSWl1sqrsea7w5t96Rjhjr2Z1DsyBjeFmNxRSLz49jJVEyOvidKxVJTh1aGOuM35U6weBIRRK6bBn6gYloii+veiMyRJ5WOr0fPmPE8tHSDwokoO0eJjP/rxLdxziD3Rfj9R8z19RiQbvL1YhyVTuHoNes8SnRcl2ez8b5KmPpJ6UMCrh03do0l7/wZFXQGS1Z2D26wyW3viziJ/kbdlYbI8VTx2SNxvaPG+4r3rckmq4lXqrurj+qu7i53NzGek9nd2ezoZnfcmY2JeEQREfGIIiLihRciKioiIgqCIn4QCeoHES/UD16IoIiCoK+qu97U656NLn7y/2c3Sb3fe3W9el3Hq1ehHyeHtJ0TfzhSpzRPM+6HaV1C2k/brr/nUmWH0LEc98JnkQZx/SpiHfMFec9oOvU9gWUMYnGN9v6ZqVjwu++N1h3c2dlpOPjyVTj0/+9cJXohgxx0PmdDUGpwL6f3gu7hYs+keZ5GPJIGi+MSfZsa/Sy5iHxfxkxlwcpZvTNwsQv3JM3lBRt7VPsOfRXOQv/8Ss07Bdjt7V+vY+d9Gc40T2wfgMMrrc7aFtrtdAuLNysQ99oDcdSX4e8H4epFCcY=
*/