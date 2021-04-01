/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_DEQUE_02032013_1921)
#define BOOST_FUSION_BUILD_DEQUE_02032013_1921

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last
      , bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_deque;

    template <typename First, typename Last>
    struct build_deque<First, Last, true>
    {
        typedef deque<> type;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

    template <typename T, typename Rest>
    struct push_front_deque;

    template <typename T, typename ...Rest>
    struct push_front_deque<T, deque<Rest...>>
    {
        typedef deque<T, Rest...> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(T const& first, deque<Rest...> const& rest)
        {
            return type(front_extended_deque<deque<Rest...>, T>(rest, first));
        }
    };

    template <typename First, typename Last>
    struct build_deque<First, Last, false>
    {
        typedef
            build_deque<typename result_of::next<First>::type, Last>
        next_build_deque;

        typedef push_front_deque<
            typename result_of::value_of<First>::type
          , typename next_build_deque::type>
        push_front;

        typedef typename push_front::type type;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return push_front::call(
                v, next_build_deque::call(fusion::next(f), l));
        }
    };
}}}

#endif

/* build_deque.hpp
9qV5bhLWjSbC4xSgj5SFSF5PrcwKVOZ+ajzZ8PkRFCmO2e+uHKOPXoaQQqX1BK03c3EqQ08h9S0Bemwcw/Qo8Iv1o5PNAl/9WeWSt0IDnJKnJD6grGo55GqZhtEgpTTN4s5Hb6VoEC98ToHJ6JCQibMUlPKAy12YQn7AQicaJ+cOkLXwS2TwsCV9wAsArLl7lnV2Id8jwF7Rz7uSq9iUryEX3G6D0aTcEjHWMfTUQDwYG9iJlYWi3g2/PDzBaEOTom0/tw5gHNz15PRAv1t6ow0E4Z0eDJSqGpVoc0krfEZEtloSXPn04LGfbMkTeeSoaNUD5gBhZSwmtBCgpPB9D8Qkv5GweDLeWUh1/x0ZzyP1xLykT4GVUjCLFeoBBzqoGe3omyNqXIj1iLtbi+yuQitCAGS/d3RLPcbsXymIYctSJ3yKy9An8KuYA4tgOtyuQwxTkHlKvZpWDjMFTcTEz6RSDlmj+B+xP+2HmQflKtLWcQ2Eto4S3haCHE75nNs7ge9NOSV+Iw+bI3qae1UsJ3afQuvDbtV/9AIb0N+2osqF2w17/qWx8G2xlA==
*/