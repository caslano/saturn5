/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_31122005_1505)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_31122005_1505

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
mf0Bf0vs64juHdiDVpWspakek5OoFkGACkpAUFOwyJvBJcFr1OWAkJcI6iZNPN6tGF466KzHonGuYbOz3AyQuFaRHjrR1qp0DDA7xHJLnN3sOma8pLcCbxyO2rdwIuGvhK4r+B3nlcu9VsmzAldwhpAnBWVQWFV4QoaQFkez5XSSp8s1XlTTYnmUJvP1NUh0OJHFn/cPn/zl14zscFhsvUfrIRjxL1f+YZ/QppTHeGeqx3U1/rW6jXzoE/uxBtxp6HBUuov5AbykadA30+xLv2CtQBSlFa3rD54zJdOVQ81HgIOx6yCxO34Xz+bxy9l8lq8Dr//+buHJv5zmq2UC7+L5ahosucW7m3H5TYv0DQh/TfMCQVrwcTi9rvmNq+RNkp4kRerOdTJCHfLuR9l0CvE8S0ef6Gm6mCa+7uNVMnFWJK4IMdaFujLae0wPwX9QSwMECgAAAAgALWdKUsQzj5EiBAAADgkAADkACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1VOUkVTVFJJQ1RFRF9BVVRILjNVVAUAAbZIJGCtVG1v2zYQ/q5fcfC+2K0qJ8uArGtWTHGURosqGZLczIABgZYoiystGiIVx2j633ek5KRJFiQfKsOieLzX
*/