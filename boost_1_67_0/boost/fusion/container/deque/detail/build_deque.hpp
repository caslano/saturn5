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