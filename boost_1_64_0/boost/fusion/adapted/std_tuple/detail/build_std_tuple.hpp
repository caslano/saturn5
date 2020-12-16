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
tjEORT3Eb7t703bOcdgXy+cvx7aymg7h/bqHTe6Hx/P4sa27/+S+BMsDP/w2ZRP44f60jfYDn8cc20ljRN4eSNnEviLb36dt/QqHuB9M2sKvyMdDaRupnEjjw0m72P+0f9i3NX0s7lf1dH7CNHJ63raBR3ybXNoZ9hR7nJbq8H2rVld3vT/qaXR6Pc/fx7rbS/mYx4bcGWCPR7rsy3jCY7jYx87bgw1mxYUV84sui/SnPJ3SQPrTni7xP+PpNg5mzzpGL38ODOyvIUNmaX+xz4rI6Jm/x7p5BHuLfYaE4KxlyzBJS3uKPU3K4N+RLmXwH4+JD56LdCmDDTbWrDhoX+LaMGIS5vM0Q3ZsXXy+x5bTWlUKFXyjBOeQOewXgJeGB5YOlvxx3cYRkzWmm0RMxjCbJpg9o2Uzy5p+Xdvc6X5d28LTxScvdHpc17Z0LK5rWzkW17UXOebXtRc7Pa5rW/uMEwLfbwO2ZDAaU1N8L3Hc9/u2se7q3XYekzUsL/V0WXeyva9P2/XlO4S6+j33Msf8ct3R0921McR2EibjRvjh5Y6F4zzuc3eOeZf8WJlw60R2cTbB2Ax8V5/L88jvbo7rMRnnd3fHMOZCmHs4PRiL4blXOO7PLezpdDf+oTTs5etcSHjH7R0w/SNHj8/2cXbR+Ij4vjHnioXnXxlzrkTg+8Xcu0tk/4j75XBAyIN3+YFJPtPFGZ1FVqlOHBTbFZWK5piMDcV1cGyDgudymBVwU5EpDbMDPe/h677QLvD1nJAHvj4k5IGv54Y88PWhIQ98fVjIA1/Pi3ja14dHdrGvj4ht4GtuX0c6Tv0C1idjf7RjFB5pr3YamVJ5vYY12lih7/F5rdL1u+so6CPzS2rMw8/0K1admizmTSgf8yPdX0s9INyWNemDotPSD5u3kuhF/SPbBUrL1TlrC1mnT7rz+kbMWm/WF0EvlD6CnL8hpbveHmV/dIqp9SjHBJw6IbDFioX3Sy4JGHZ6ZFlb9uIMp23cOpulCR6eoTSSsqmNU/jHJhg9i3o9GnLZtlSsn23Z90o5Zdeaydp0nRfnZSywoXXe5GdO57KA6/XTyxPM3qV3XMBoa7aXSMxjR3axr1ZGNuKr1yUYniV+fMQ7bZ2/ExSX+2c4bScqFt91wzav72ljJk5gU4lt5I4bpOMkZcO/pozhLM5DNcVM621Uc3p2POTcCxOrhYxaL4dbT7LCQ/xsFnE5N3YiZNQIONzJJKNSJ74qxfk+HAq7EXH5Fn1yyNxbhfnqJJdv3VNJ3uhk08ynU5x/BlNZNmMuW2RQ3q3IRrbB2HfTTMrGPyGE+sZTfDu3r66tdDpJt9Jw47JcMQoJekfpvK+F89wN9PB8ozWK82g83td6qrIJz2VdGzN+UYOvS/HWVN0+f5ri+u4nd4ewz01Z8Dv79FhHtLhLOOZcUqa3t/l6o7IJzyw902dRvs6KOPKFdJ+tuN5H8Calc7PCPvBQp/UmzN4SMVlr8taIlWinlZuLjvioeZbZ20NGlZXZOyK2arpaY/bOgM1WaX1XxCSt7w5ZkNb3hJzTyvcHR6wzleMa0rra2/O+wI4qE+rE+2MmXT5sPpC2QZePOeiUDfdxlNYPeTxauVZ8kKPx1Ye1ndGK+nGO0vSZSh+JdVRHzD8rTqNYescw+1jE5B3y8ZDRe4LZJyImfe0nQybvAZ5/TvHgzoFPp2wobczPjTneB9ifneLB/RznJW3QkcDmsymb4Ozq82Mbf492kqMAEc8FyiY+eAxz1Ukb2cd9YU8u94dfFNvIXm98T744aSM30rXMP226L1mPrf1G8oXIxrzX8fylEcujunBZ0kbqwuVJLnXhizGP6sIVsU0=
*/