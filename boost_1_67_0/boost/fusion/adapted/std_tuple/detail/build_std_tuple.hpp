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