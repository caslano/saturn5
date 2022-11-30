/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_STD_TUPLE_05292014_0100)
#define BOOST_FUSION_BUILD_STD_TUPLE_05292014_0100

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/index_sequence.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <tuple>
#include <cstddef>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last,
              bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_std_tuple;

    template <typename First, typename Last>
    struct build_std_tuple<First, Last, true>
    {
        typedef std::tuple<> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

    template <typename T, typename Rest>
    struct push_front_std_tuple;

    template <typename T, typename ...Rest>
    struct push_front_std_tuple<T, std::tuple<Rest...> >
    {
        typedef std::tuple<T, Rest...> type;

        template <std::size_t ...I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        indexed_call(T const& first, std::tuple<Rest...> const& rest, index_sequence<I...>)
        {
            return type(first, std::get<I>(rest)...);
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(T const& first, std::tuple<Rest...> const& rest)
        {
            typedef typename make_index_sequence<sizeof...(Rest)>::type gen;
            return indexed_call(first, rest, gen());
        }
    };

    template <typename First, typename Last>
    struct build_std_tuple<First, Last, false>
    {
        typedef
            build_std_tuple<typename result_of::next<First>::type, Last>
        next_build_std_tuple;

        typedef push_front_std_tuple<
            typename result_of::value_of<First>::type
          , typename next_build_std_tuple::type>
        push_front;

        typedef typename push_front::type type;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return push_front::call(
                v, next_build_std_tuple::call(fusion::next(f), l));
        }
    };
}}}

#endif

/* build_std_tuple.hpp
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
*/