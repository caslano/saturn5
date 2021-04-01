/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05052005_1128)
#define FUSION_VALUE_OF_IMPL_05052005_1128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef typename value_at_impl<vector_tag>::template apply<vector, index>::type type;
            };
        };
    }
}}

#endif

/* value_of_impl.hpp
oZvkvvw1a9ZFzDFs3sbiuE5JNcBfxsjRHUoNoCgPXMe+ex7A0Lnagt1B1Ce+4CPIOKRAmpCJgvzedxCjX3gc5ss5D5DhbR1nUw/PVXJt914MV1aTlO5+hvzdKqZm07VOrTJwXYWxD2cgRUU9ZCdpDsmfH+lgfzW4stMNz/bz5EXl9lkC3quZ0W0SiX2NfXowqek6jIcZ00uVHccN0ICY6gqL9ZaO97dRsIe3PUkbe6n5LZNl/cR0LhNk/uAdCzilv3+hBKcThgq2NJEfpORBgmIaNKQQxMHFA/9OiuWEdWq4J7gkoaqd3daE4JnbSePKVS7cfsf4LRcUcR62/i0fBn4yJ7sDpyWm7F1KwjM4oxtrqDZRlKTWzTHlHirsUybvFUWXdlPAjsWxNrwa0tQwuTYeyBn+ZeXRLHg7QrQt6Iop1dtIMvoyyjQ+iapAlwFGMVuPpOhhU734sTpfShJK1HJtAkgiLiOxwujWdPNeIfusd9kT1il5d6HPtYWJHMuQT5q6h4NoNjNgXUZhi2yByyA4xBaJeIVVo/xWoO1bg+FW8BEn22J6i+iw5w==
*/