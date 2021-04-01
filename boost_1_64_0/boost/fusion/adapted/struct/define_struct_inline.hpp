/*=============================================================================
    Copyright (c) 2012 Nathan Ridge

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_INLINE_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_INLINE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct_inline.hpp>

#define BOOST_FUSION_DEFINE_TPL_STRUCT_INLINE(                                  \
    TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES)                                      \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_INLINE_IMPL(                                 \
        TEMPLATE_PARAMS_SEQ,                                                    \
        NAME,                                                                   \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_STRUCT_INLINE(NAME, ATTRIBUTES)                     \
    BOOST_FUSION_DEFINE_STRUCT_INLINE_IMPL(NAME, ATTRIBUTES)                    \

#endif

/* define_struct_inline.hpp
p+CaJVWSWNc7tifi3rnu343dwyrzqFEEPbpWvbbYpiY1dbMJen3sGbMTwPk9xk5GtpF7/4atREGvY1dVMyRJKOhnkw58D3IOAmk4wKXYkMqQjlSeHctITs9X79BbbTDo7LgiyRZEGoDOS6uJK1t8PWsPyjgvVJ5RwLddwl7iZM3AaQautEeDA2OoDul7OuzUy3RGJMszC1zD0Hg7SQ/2aXk4WxIZVfNDO/8Si1rb2+/zVFs7r89hyP7ZsheRF9ee9s0To2JrYY+0zBT6AevfbBuqQqdI398g2vAXJdtxlC1hrhU1nf6AheKc6qhqUU+BLA+winN5CTlXVDFpgSnytSGMsdr/t3zG1b1tIOYuzGqGSGwmdJ2Ld1CyTdqvsFcPfaQ2omsPXW2uHXnaZKJvG0eXdXVVICpa+rlpyAPPVbk5MYdb9WAnpiVSOwiFuj1fb6dmphBOOwEKcb7vE7de68I9j0zqsR7L2/8QEc9dnHFAb0X1wnVysV73loWMYa6ZuTFP+CF//Ft/kQ38jVf/e6+b6tFw9y9gyAAdPvAiMFN5qBxb5fZWx+/ObQ==
*/