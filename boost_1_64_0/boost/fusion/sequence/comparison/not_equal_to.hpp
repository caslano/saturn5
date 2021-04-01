/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NOT_EQUAL_TO_05052005_0431)
#define FUSION_NOT_EQUAL_TO_05052005_0431

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/not_equal_to.hpp>
#else
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    not_equal_to(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return result_of::size<Seq1>::value != result_of::size<Seq2>::value
            || detail::sequence_not_equal_to<
            Seq1 const, Seq2 const
            , result_of::size<Seq1>::value == result_of::size<Seq2>::value>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(a == b);
#endif
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_equality<Seq1, Seq2>
              , bool
            >::type
        operator!=(Seq1 const& a, Seq2 const& b)
        {
            return fusion::not_equal_to(a, b);
        }
    }
    using operators::operator!=;
}}

#endif

/* not_equal_to.hpp
LB9Jzo9jmdEI8srZEAVjwpLEsauOExQQ4TmRNRPchCfxPk35rioT64ZiBS0MZTuwTxV4W4RfLBNvubZTpqcL6CLKulo5ZcawyvuxWr0GZJSEOIgCqAmz5mWvPMqBzA9DjY10VBlMM5oUxLRIFJc7eER1YLdAtt7Sd5tpHwHbcq+9qx1+p5nAuaEibO+rXgr1EU75BgueDtZe8LBZmlqjh191rXhY4+3WDoA4n+rXiwgosr9WOcLn7q9OGjbtS2vwvhfueBF2HDouNi0gd+2yxNIR5tgplM0dh9W3KmflRP+A6uPoYOr7fJduPjbXvgWCL4EerGMt0X/ZG66IUFNXddF0blGy0yi3OVzk22sDlB1RjQ+Pz3bG6c0IDZiPY84Lk/HD+b2/lYyKe1Qw/MMWVi3+LGUg6Mykd3WX5kD+UQTNPW6AiXdLTlHpoyW/ezgIMyBR0DDk5Ph712C99zPO9Q0s61dmlz946L29s8DQzh4VkX8ib5S0r2BrntMLnVx0Hj0yKgOEnGMR4P3CTaOKGZqzFlh9LROPeBHP750Woco4LKRLUE9nKIkpZQ==
*/