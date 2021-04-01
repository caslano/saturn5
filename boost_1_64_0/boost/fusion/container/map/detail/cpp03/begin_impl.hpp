/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct begin_impl;

    template <>
    struct begin_impl<map_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
                  , typename Seq::category
                  , Seq
                  , 0
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

/* begin_impl.hpp
5XXB9FCUb7a2AE3TlYoLD+WxXo0R6fE9pf13N3sQdoLBrZZBzMTrWRgU8fOveh6xqUoL6j78XveBEli2NXL27HP2gD2MXTbqiL3WzUd4ofinMDLoAOd3aKiEA46630qJWP1mhbTwmY5mTvzMi/Kdytdg2gGUUTAtXbgxDD50l1DdvFmWj7J+BO60uZ1WAG90jl/ZlVYheNFhaZnxuMPC/3dfvkvwbRCpGz+uE/0bLc6/uI+DzYmna4MbFq4dtxbghb1C+reojV0kTRivBz+x8kY/ILdX27bxz7LTXpcYkCtX90X2Yn6CmJ0K4z8KSBgjqyeU6Rc4tDaMHWwMHh4Xeqi9j5XE0XhNYU5K8QMTRp7OMBsK81xFAN9lSJkVTYNzf8b8vOsHrHbQp+pGn1lkSvQfVTmAd0WRpP9H5v6aCIjg3ScWygk9NJ84rQDaYKmZesg8j+di6S4GXrbrsn7plhAh9ODCoOCwslXA8Vy3YXBkRGBfdP1IYvyxTcbaT26rPgjWk0aXVtbNuTdALtSC+KoDssGvcNxeJknlC+ukwXYRd9ToxbJQSVnCwQ==
*/