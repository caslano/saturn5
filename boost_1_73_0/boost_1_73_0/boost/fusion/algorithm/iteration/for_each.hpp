/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOR_EACH_20070527_0943)
#define BOOST_FUSION_FOR_EACH_20070527_0943

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/detail/for_each.hpp>
#include <boost/fusion/algorithm/iteration/detail/segmented_for_each.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct for_each
        {
            typedef void type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence& seq, F f)
    {
        detail::for_each(seq, f, typename traits::is_segmented<Sequence>::type());
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence const& seq, F f)
    {
        detail::for_each(seq, f, typename traits::is_segmented<Sequence>::type());
    }
}}

#endif

/* for_each.hpp
07h1aR2GunUKQ4q5WlPA8Ho6IQ0wPJQmMGwMjGXK7MExaf3bHP69ulGMKtmjWBfa6PerC5h95WIUq9NqvuxL55WhtawpYC5ie5jPY9K6i4noQbkJbJitOuZN8pMPZt7YoGiEiXs0PtNhLqsrPWMgnzhX7tFidZ2ZSLocxcHUMdiM1/xLUpK9fifXdraqa0flUlQXOF7bnVWPR+4wzZ52W/Uc7WM9VnZxscOZAPM8Mgydc3KsORlpxdHyB2bKALJh47qnith5IyHtKqb4njRMhrSPYDykXcdc8F7blMkk5uYG3TYZVkVVZ0b/wF9MWa85JjQmt5vj5q2MedCHNpmRFhsZ2xTr3xVhJwG8CmLD8dLItuMedhIVYOqBtVbgTy2IjzRHh2lBfByrVtJLwSZVj/V+/czsBml4GlOsr3XAUK3viewGFABptFCTZcI72gsQETDfLUDeBvteAUy1/24BXKH/XgFik+jOyq4X0PDzh+8WwDXS66tQHduw6XJvxZxg9qHpkkVwMHeNxVyIcKcNWg2yPcUrbthbDP5Km004CqLHtNkkMBvVaHOuJqX15paTimLYeU2H0g+busC4mhowzgh3rnCnbEgTcsXWYzgIQ+q1niKKZuWeN5EB/kJY/34afelBUExHHqekB1uE
*/