/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
                  , typename Seq::category
                  , Seq
                  , Seq::size::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
YW/JL6qq3BeX++XkR51Qn/KMW5RS3zgOvXA8tsE7sS9OwCEYjbMxFv+GcbgBJ2E1Zp6CHXAydsU0jMZ0nIRTcClmYB5OxcOYiScxC7/BbLyGOViLss5EL7wX/XAR9sL7MBQXYzLmYjouxXm4DJ/CB3ALPox78VE8jo/haXwcr+NK/BVXY50qHIexDa7DIZiP4bgBY3EjJuEmzMHNeDduwQfwaXwEn8GN+BzuwG34Mj6P57EAi3AHtmadvIiDcTcOw30Yg/sxEV/BWXgA5+FBXIGH8Al8FQvwMO7CI3gUj+IJfA3fw2P4Mx7H3/F1rFSN4zS2xVPYEQtxML6Fw/AdHIfvYRq+j3l4BlfgWXwBP8Q9eA4/wo/wY7yAv+FFbF2d4wC2x0/xFvwM++HnGI+XMBkv40L8Cu/Dr/EZ/Aafx6v4En6HH+I1vIDX8Uf8CT1rcDzAifgL3oM3cDH+hgfQUoXpawDWcuN6MfpjNbwF3TAc3XEk1sK70QNfRk88j/WwCBthDSU0EXbCJuiPTTEcvdGKzXAatsAl2BKfw1a4HdviIWyHJ7E9voe++BN2wGY12X9gC+yCwdgVY9AP4zAQJ+MtOBVvxdnYAxdiL3wQe+NKDMYnsQ9uxb74AvZDZf9ywSLPa2CC7F+bKOdtFvmBynieOBCbYii2wcHYCYfg7RiGY3EYxmA4ZuJwzMURuBUjcAeOwmM4Gt/CMViEY/Ey3oEelCcK6+N4bI13YmecgP54FwbiRByL0Tge4zAa41HO13jWw/X53yXt+d9q1+d/RZrx8mW8FqXML6aE88mtmvEKSyjfLu15Zwnz264Zz2ONlK+U+R0sYX7HNOPNL2G8fdp6KWG8Q5rxQta4Xt4NmvEiSpjfem35dMvren4FMl4fk/HYF8t4fNbKeCWc3xeQImQ8L9l+6in5yXjJtD9vTMG2OBm7Yir2xnQch1PwbszAxWjFBzELN2I2vo7T8B2cju/jTDyPs/AyzsafcC5WoTzz0APnYwNcgPZyy71R7G9S7h7y+7QX+mFvHI3BOB77YTqG4Dzsj0/hAHwGQ3ErDsI9OAQ/wDD8FYei7fwQm+MwbI0jsCPejj1wJAbjKFkvuyvJvVK5h0q5bddrtlaS+zlS3yulvldJfT+BfXENRuNavBfX4f24Hp/CJ3EXPoUf4Ab8B27CC7gZr+DTeAOfwZrk/Sy2wm3YBZ/HkViAY3EHJuIunIov4jzcjTtwD+7GvbgXX8Z/4D78BA/gt3gQ3VjmQ1gfX8UgPIx98DUciidwAp7EKXgKl+EbWIB/x11YiC/h23gJ38Ev8F38Fc+gG/X8ATbGs9gaP8RAPIc98TyOxQsYgxdxMn6MafgJqvuHDbJdud5v8jtG7oXKPVJlvIH82weVzxT5vZqBLdCKATgVB2ImRmE23oXTMQ9n4OM4E1/GWXgeZ2MRzsVfcQHWIPN7sAveiyNxIY7F+zAK78e5uBSfxGW4GfPwCD6MF/FR/CeuwO/wMbyBj2Ml5fwV2+IqHIpP4Ahcg2m4FvNwHa7AfPwbPoWbcSPuxE24Hzfjq7gFP8OnsaZyPot1cCt2wedwJG7DsViA8bgTn8IX8Ri+hKfwZTyP+/Br3I9eynkt9sUDOBAPYQK+iovwMG7Ho/gevoZn8DiexdfxSzyBv+AbWEU5f0UvfAsD8G3sje/gIDyNQ/FdtF3Hqyz3cOXebgjfB9t/z9o+1+T32ffYAn9AX7yOffEnHIQ3cAz+ikn4O87DSuSzESvj61gF/47V8RzWwK/RDT0phDs2wloYjDdjDNbGRKyLd6MnLsN6WID1cRc2wL3YEI9jK/wAW+MX6INXsS02ZBnbYVPsgH7YCUM=
*/