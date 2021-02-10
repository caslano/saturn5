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
RVJOQU1FLjNVVAUAAbZIJGCtVlFv2zYQftevOHgPswtFXtYNWbauqJo4jRfHMiy5rgEDAi1RERdZFEQqrrHuv++OohPbWdE81IEjmeLdfXf33Ud5yw68+m4fxyN38M1PbL4xfvC6M5rU8m+e6P83iOMv0P6h4RKvLwjVhyerL3EPXmT1BbrGKrax3tB9HL8g3JJA0r8+GS9jusWV1tLaX8hqW4u7XEP3ogen5+e/wQn8/NPpmQuXrBS8gFDzcsXrOxfepGblXc4+f/YUf+sC18AK78BhlAsFSmZ6w2oOeF+IhJeKp8AUpFwltVjhD1GCzjlkouBwEUwWw/EHFza5SHLrZysbULlsihRy9sCh5gkXD62bitUaZIYe0H8qlEafjRay9DA8B83rtbJuCAQrlAT2wETBVhiOaci1rtTv/X7S1AVm0k9lovrJrhRertdHWS0QzZptQVYatIRGcRdovwtrmYqMrlgiXKyaVSFU7j7BwoBl2pc1KF4U1h2aCq7aFDiEtlou7YQK0QtNFyVLRdE2uVwfbMSyWkdZU5cYDsuC+1KJhXehKVNem/2mELsotsqm5N9o2RP2FGSJqKDjhzAMO7BiSigX5sPoOphFMPenU38cLSC4An+8sP5uhuNL5IbAqDXwz1XNFaKo
*/