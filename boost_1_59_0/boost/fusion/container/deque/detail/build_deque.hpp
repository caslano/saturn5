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
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
*/