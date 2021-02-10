/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_09242011_1744)
#define BOOST_FUSION_END_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <tuple>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template <>
        struct end_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename remove_const<Sequence>::type seq_type;
                static int const size = std::tuple_size<seq_type>::value;
                typedef std_tuple_iterator<Sequence, size> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
bWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfVVNFUlBXRC4zVVQFAAG2SCRgrVZhc9tEEP2uX7FjPuB0XIVSmEIpDGriEFPF8lhyQwYzmrN0io7IOqGT4mYo/523JymxDTP0A24TOae73bdv3+6eux7Rs//t47hsjv7zE9ufGB88h0OLWv8uk+bfD8TxR+r+4eAaz09wdUpPpz7GJ/RJpz7S2J6Ke19v+Hscf4K7NYPkX6d8eB3zV6x0J/vzZ7p6qNVt3tD47IRefPvtN/ScvvzixasJnYtSyYLCRpYbWd9O6E1qV37MxYcPrpE/TEg2JAr3wGCUK0NGZ81O1JLwvVCJLI1MSRhKpUlqtcEfqqQml5SpQtJZsLiZzX+a0C5XSd7bedAtmVy3RUq5uJdUy0Sq+85MJeqGdAYLsJ8q08Bm2yhdunAvqZH11vRmGIQojCZxL1QhNnAnGsqbpjKvT0+Tti4QyWmqE3OaDFS4ebM9iuoGaLbigXTVUKOpNXJCvH9CW52qjJ+gCItVuymUySdPsOCwTE91TUYWRW8OR5U0XQiSwp6tCe+kCuhVww+jS8PedrneHmwErb2hrK1LuAMt2JdqED+htkxlbfdbIgYvPcuW8v9I2RP2lHQJVDTyQpqFI9oI
*/