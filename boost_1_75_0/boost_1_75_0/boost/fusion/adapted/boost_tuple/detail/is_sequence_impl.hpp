/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_tuple_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
JH8EZqCJ3vWCeHw7msKJpM3dKAWcVadUAVEJRFQeI2oDdEAzOlJsMWiiKcdWM1OnKaWqVKN1vlg3nGd8gyfAVc2JAHHXYjFKEykC6MLspLJL8KKqDb2kmeiq/dlq+Qjpuh1yaDDoaiC6NswQdDWwjPYQXWJwDzG+4XTZwKkHgfXOB6FC0YtPcKJOcKIa4ED0ja7Ao4CcsDCL3AqRM4Y6rs//SFcSJTgFppFkKrpMs53/M0oB1r5pBHwMXkKYACng6XHCsf3yk1Vn6JQ9vADyEiJut69gHzQBg8GFcQ7Hwq63cCxsXMjauwZ6GMFFerwRobuQwEz/hguoNdhAR6WS3sjeejLjbuW7GD2CthPi+89ZxLrpFqPqbL13ADZrVUWJ+WmJRT1lX064Pon+FB9vaZaDtVKXn4K30pwYcytV7Te3EjgcK/WYylb7rwVrDfddbCr6SuVTUXqM3/wG0xvMboglBpObeb3c0QTHhgHr9+WOygejSfpibe7qT9J3J8r3uJtEid9Hn77EsNOUKHuOa0UXsVzjRK4LovUplaRdJkCc0AWnPqsGKAT4HRJyTQNxLAq83M18Nqo7LUD85x+tukg1gyezqDQeRaygT+IIiYNyWyoZdRz2B1ZICKFNFx8HfR2OLlyKEMzPcdHuDxktgFM2kDIyCDSraRZik0eVmDxw6ngv0m/qsIbR1tFqnjVu3EezxrjIwFkDZwt0
*/