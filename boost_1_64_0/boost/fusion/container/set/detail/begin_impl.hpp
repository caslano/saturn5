/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct begin_impl;

    template <>
    struct begin_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
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
np7NQeZ8EeZfob7XGiY9D5t05lSGb6UHPggKKkGPZhfOjQvVOisvXnmYJrjBkNEratc/exTkR/mJLf/dxOzLUv2xYu/N18xLUKNb2mPKI0ntVgJ0LB1e6ksXFXnPX1wmC/6ixX9oK4lk3QSawV2Q6mMub8pGW7VUm7eqiGiCItHaxg3gWZiSGsQOYl1PC+ptF83gDEjm8ZnHHyi2Sx6uyRdvID1RFgPQXtr3b+RisbFhWjlb7xaefU//0j8Qxg03/qZkbNlGlIg7CyTG6HeIDPRd3au0Mr1ES4uDmFzBf/CUoppDvfRQEW6zszA3FyFCzDQdiY9XrqHG0605pmhi3B0rqaQ46X3SezaFZuRclXj5OMGDaT2D+f0dMVijC6wlnWPM8UVoRgisOLgbltd9mrOlAb5U6HlaS/4OrXblqsQdo5MuEJT2wEbmZg+3oYfMZpC2lYAjdbgqdtdpiyh6clJZIuaFivB2hMOb3tDmnC4Ar2DmKoOHeYwiCvKbsJt9QPi+03SktajxE6n98ruK67pVV0ujCW5LmX3iQN/9xjpGs9aIlwslaBdP3w==
*/