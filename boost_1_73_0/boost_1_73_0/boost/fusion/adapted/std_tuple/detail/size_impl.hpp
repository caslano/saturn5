/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_09242011_1744)
#define BOOST_FUSION_SIZE_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template <>
        struct size_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply :
                mpl::int_<std::tuple_size<
                    typename remove_const<Sequence>::type>::value
                >
            {};
        };
    }
}}

#endif

/* size_impl.hpp
3vbehkXOoeZx8flhqjvx+WwUcS8QITiLHxEAZ7C8qJFvOUQX01pTYY4mU6EQqVCIVChEKki2EuzHYOfALoC5SYVnbKnAZck5HsiaCud6KMqpMLmojP0zeYuaGqjHTbb06qVRhbv8raoMM1UJtFOq8JLMh5IZYG7u9le2u+WHJ85n+9a7/STxbhsWimxmDiZNzGbWRqm7PGQOe1ygxcdt5Fs2TadKR6jSUSgwGexusA1gG8HcKPV8m5T6a4JSVCo=
*/