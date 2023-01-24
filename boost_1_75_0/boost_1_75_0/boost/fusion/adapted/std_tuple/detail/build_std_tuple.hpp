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
KX+xWFc5OBYFt1XGoydMQStaARy6CbCXEFFjmAQ5iZAzhKNr4mjvGJ2An2xnjtoXyKK4/ogl3FQkj/edE/24Dmgu/sCVQGh6Dz+63nay0bHyI7zvQvi6WVaWogj+oHhejUDkBnTEHRAuuYGAdNOU3bcAPI902ITboE46IvyOM+l0BKAX70fMcpkBaSv+4r02OzWfMjtRHXkEXU+b2mbOZTbeOsbe+hgI14anBZ8mwNzESZvH6Bx4RZSya1e0Ks86SiARyr5XilC/e9mh9MhImo78IgZup3eTcWBksG6Miw8QLWO5KVq5eDJa4y4bUCkUvUKTZ0Th6XWFy1k4AaRrB/WKXrwTPSEmZAnJyguQrByUrBw6kUHZ2nMhyVb7hmXLmxYoW1lStmAO+eqqurKVZcpWVoBsZZmyldWIbF3CspUv+5JgwHkyLHTfAwIWiV4YmVmm3Kgylt0UAdvIApbNAvZWXylguwIE7FsWsBxTwHL+NwG7ta8pYHUmvyxguSBg6yMt79MAfB6J8H98mIn/OYwl7MURJGHPjyAJG0cSVu8ZpAli+exS8wieQCx/c3lPCTHKLHtsphCzmTj/7SPHE0TRc3p/TEt+Ilcv6QKntSV/6MWAmJ7hG5WXmXJ1gl68LITgjlMJgH7E54g2yWCqvvCkPDoVz6J4jVIYRETBbGNl2r+4QKrBLSM8mQklnDnIe7wazrwQDpsSoOEa
*/