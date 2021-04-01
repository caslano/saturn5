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
UOdHk2R87U3CQP1C4Qt1okVQnNIYgAeg4HSjhcArFD0JF4m89+OzdNMHLeAbJsQUvJbm6HTxEShgZY5k4M88a9UKqLOf90/x9FUMqD09fzkkmjGfUz+J6fRPi+gtxwMj4Y0IBranYA9YXRzPf0TP6/ii4D7zC1ZL/bi1ERBERjeN6kSlTCA0wZs4I6N5vyLSzCMUTXpu64u67BiET+g43g1VUyfzGKUzwESDN791fbNj0WrHoZOKFLlUYnuxc8fG/pMpcfS/3Rc4M9vker7FyLXz04eYof+3ML3onzd4OXc6NIRc3NS9d4gqa8qyvWLb/6oq8ZRu6FW17nOo5nOT0x7G6wCaBVPofZygKmjPTAZyGJJvUE9IbrYi0V8hMsDoSPOARN4dNQST2OyiViRKU49wfLctIzW6LggMSkqKADxsolI+5Q4+2puvOc4GC0iEg6lvjO7N3QllbbhzR+ZhEHY5xYcy9u9ipA/2FJQaOZvOyLe066KtC9HCeRWzy7uQG5hEajHh5mWkflMiSg1xEm5APLu0IOSrexFkIanonUfO+nLiCQUwb2CROg==
*/