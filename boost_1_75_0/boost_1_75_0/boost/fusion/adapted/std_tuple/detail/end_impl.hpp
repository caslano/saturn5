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
T5txJ/TYLNwJXYKXSVjIWAunCl764XecupojN/HZ9nYxCIpNgBQv4xXk4uLrKFLe0DhSfiPwBb/Skh/J0Usu1znOq4vOhuwKnbDg26FgogWnCFfHExuVw4FYHZ3RP05AuBvGjYZrIha+pzqDWbPm1i9jWQhTfq8fgvGgHm2OoffyUJ9mM4j1wfwLYbEPL+XZCKkGj/7kW+/EoFpghhzQSHl/SgwB3+cCyUJkZXAuqiSfmuQaV7em0SzRDr6iZ7CgpvEmbcleOYAcuEYOaA9BkWybuVLIpubI3s0rBWtAwydC9BOtN3AwaZfhXYK/IRdSITdUtq2+Me0MjGnb7ZoKRa5wdes1EuwUuXJZXLmIq9u/klztkly5VK5cCleAi46/eYSVz4NOiwVXP8BxcbqdiiTLMDZKq4iA5Mk2yuRs9UQnO1RUjE8QYUCOY86F6y4GH1GALtkJ/IF4GW2qo8zOrUVdGw/rutuqMW5tLTqW5MgC20SBmsuiAHrhDykz0MTUjxLsnTAVaPolHpJSCqo1f7Tgmen+FjhLkR+AZ7vmBxREN/gBa/gDEFGXP2DgfusDnNGsHLTowApiuQI8C5MF460vvacaOhLRSCi1lCwTGo0d2788DkNFDtxg1fNXFD4ayY/WKI/2RlFkybd7Wpj3NvG9Nd9Y91bwvW3J1rtfRqnKhSte+WhmFMmAZn2YJlsuTxYqiqKRAs1f0Qro
*/