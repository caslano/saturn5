/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_BEGIN_IMPL_09122006_2034)
#define BOOST_FUSION_DEQUE_BEGIN_IMPL_09122006_2034

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque_iterator.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template<>
        struct begin_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    deque_iterator<Sequence, (Sequence::next_down::value + 1)>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
WVwXZmtWXGe0RcGfUPgTyP7I0z8MY5JmSSeY43mO2UDSZA9kHLl4a27DdPE9DhLfvBWOFeFwm8URYnEMCJXnjqWcBs0aNk3iTcsVvn36e+SfLxL/LD6VlFhldcyPMeLzYYIVb03aQvl3r7vn/zgnfXp3n/GieWsbxovm6OrN2H8L1wWL3rLWH1f1VdO9BQccOyDQcvCAWE9iNfVCX07UOdd7qKn6aYU2IjBBumxJGp1T+CiEME7McA7Iz7MkL4GPyxg68KIwee3BMENdqLzq13BdiMDYCn/CHH6dRm9SoNTvpPeIVd4j2uN7fNutsff4Y43P9yho8B5nv8f3+P0X/XssXOPPe7Tx8h7Z+8V79Nsf7qX+Tzef8Q4d13iPLc1pkGf/1Jf+0M/EqV7r/+wT8L66L9xzTM2gO3zX//nSI83r8+wXndCTfQ+/wF4zxRvZ1+4VYP+8N9xDbSh2R/DrCWqiB08eNGu/oH1mgrrPTEgawxbj9w18n0nska0h77CueRRh/Zrw9kticsUXtPQ4Rb+JXxAN2ruA90uSqWkI+r5Y/zY1HRBDAwgMJELXy3ygO7/wSHNqKBRmRlj5nJoZwV1rXbNHIKQafiELZS+UBBIH8NxR51y6vf5QfZ33J25X7c+YmauWigqrFd6lz6OoxDf7ztCQJrksSdMYtl4MgEcxyTzD+QXtGA5y/7JlnxN6ngsA74Fp9mhTKTwu
*/