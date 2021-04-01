/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADAPT_VALUE_TRAITS_05062005_0859)
#define FUSION_ADAPT_VALUE_TRAITS_05062005_0859

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct adapt_value_traits
    {
        template <typename Iterator>
        struct apply
        {
            typedef typename
                result_of::value_of<typename Iterator::first_type>::type
            type;
        };
    };
}}}

#endif



/* adapt_value_traits.hpp
cxJ+iFjvmjVKsIEM5awytlaEZDUbesplYDoWAE+GWckJsyKrdVXPvnZOK+Gmn0KW6nK2RZxXz9PG7fBwylLnCZENfEBMIbZ0KNIBIEQ0FYQXyqrhlZ8s7vy+XQlB8Vvyib4JQYmHrZeC6f0uFnmyudHWNZVSjMWXVkV1yWpQliWmCXaR2XvX/iI3KEufArfqsPwWsOv8MHv2p+Q6vmufrJYP7QEtD2f1qL2x9aDG138iy4vCbJdUbJJiqQXDkl14qCzoyrictzvk1uZlP0AqWxzJ2PZp7A3siKtDUnrRDy9C70Sqopdb84wjIp5j5BlaQk8DGmUvfF0821Wr3WbEfM4YLpjyFeQEuJYK4DdY5kCxwqFgFBElvwCwY58nDBPlMPx/1kxZMKyTr3LTfzq3ecKf+b9FEhDbZKVRTBQk2xjQKYMWkCM1HowGD9qeRqI2GHQC0PGIHzObzygBcbrYpVq/L/iVdN1OaaJed0bhejZYo8MQkWtqBt5yGV/tdYfskWSaQGEmqmLo4TbU93JuN9xEssCfJD2KZ2QzREC6w0BP/Nzx0G6KNwEOhQ==
*/