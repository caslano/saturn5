/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_IMPL_07162005_0132)
#define FUSION_VALUE_IMPL_07162005_0132

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_value_traits.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<joint_view_iterator_tag>
            : detail::adapt_value_traits {};
    }
}}

#endif



/* value_of_impl.hpp
NetZIWsJLeaveQrIzn2O7Ss7DNLaI7KczoDuUFc4zdVqBjCrSIpY7n/ced8ZrtAf+CwY9UTJS52/pJ6+dUxNy8B96zRkhe8Ur7vU91UNuND8kogUrmPl0WnGdlfOzuOqREXC/MWQM+5+lPHlz+vPZd+QWXhIrjvgh309bQzieBmIx51++2iYiJsasM4yYPkCSSHQ+TJA8TzH8XnnvJgFwVK09o4+toeFMEdLsbX9P52jtnH0odUvBHy5AuDfIUEr5u7xUpB7vTxax9bEhGm/KpAtYX8K24sNqtiXxIc7szmhcu6QaRDNPRpxA70hx/j28vDJvlma5csUwcz6bdJD4xwO4uRo6lee+tc39XAYDCBQjqq6kL+Um1M6uTsF00UaoGQjsCkVVxKnbuIzL9GQRnT7i2jzlnUOIp2iNHZYNkKXCnAbzcVDR/IWXCKG052HA82BjHTioVCiamroFN4z3R7f92GIbpI+ccwrugPJTL570js5bb036JJTtOtaBIQzLC115Y7OgYpjfJ6d7Ka12zIOgZ1YLuiD8xt2kDnTMzphuFyAZ53LzuYYbu00LkVJZh6nNihaFa/hjaK1O12WlHR/yeyrLrvDPPFom5VkNzt1/XNkeiohMfoLZnNEM53LCpHNduZJ8tiyO7hX
*/