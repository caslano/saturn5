/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09222005_1104)
#define FUSION_CONVERT_IMPL_09222005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/as_vector.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename detail::as_vector<result_of::size<Sequence>::value> gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
TGcw+/1xMsr2R3r5zWk+Nyv5DJOYh/ciWeQiT8Qykw2BLRtinoyjCf4GgMDDxXI4i7Jpw84GhorH+0kqMjmbYV/wXiQznrYUfQWeBjYTC5hxlOOvLIkzHOp2msy9hgBH7GWyTGMYCOAAjcYJgLkhlvFYptSYVq6HUDAlAK/cGjvfsUhimIzYavVFp78lhmEWZQ3xqTP4tXc1EJ9al5et7uCz6J2JVvczdvZbp3sKWx/BYKmQd4tUZjB4KqL5YhbJsRrzx/3sb2z8FMWj2XIsxRbuXpDJfLloTrfwi8lYTsSvrY/toNsedOC/oNMNfrVv/BLLPIL/9qO4OX0j9nftk3y0wEe407FEzMwFDPaTjGGPvZ77n/vBld9rdp/tL3WPE9zvZPQlHI/TYBmv6OW80736PRicXHgdzaJ4eaemAm/NognQygTmN655q6L36hXrMq9WTrvTOxmcl2YeJaN8tuItGOz0XRGC4+GK1mcn3UL/k1G8su/W5UUroOW4b4TpItzHtThv4Wui5kGCl3LW6XXfdXp1sb1tAAUdAp626/XCMoEEoqQ8FdV84yekoAkwpIA2Lt/4iTu0T4DGsugahhCzJL4udBMEHz/0nREJwbzPxRVpJAYcHod5iBhsH2bQbOI/iibPo0WhVZ7K
*/