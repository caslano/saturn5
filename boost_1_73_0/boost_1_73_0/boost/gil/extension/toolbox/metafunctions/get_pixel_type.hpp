//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_GET_PIXEL_TYPE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_GET_PIXEL_TYPE_HPP

#include <boost/gil/extension/toolbox/dynamic_images.hpp>
#include <boost/gil/extension/toolbox/metafunctions/is_bit_aligned.hpp>

#include <boost/gil/detail/mp11.hpp>

namespace boost{ namespace gil {

/// get_pixel_type metafunction
/// \brief Depending on Image this function generates either
///        the pixel type or the reference type in case
///        the image is bit_aligned.
template<typename View>
struct get_pixel_type
{
    using type = mp11::mp_if
        <
            is_bit_aligned<typename View::value_type>,
            typename View::reference,
            typename View::value_type
        >;
};

template<typename Views>
struct get_pixel_type<any_image_view<Views>>
{
    using type = any_image_pixel_t;
};

}} // namespace boost::gil

#endif

/* get_pixel_type.hpp
Kk7E4oOz0kKqNh73+cH+vrU/OtiD/xqNRi2FfKSYYBdyegOYrbhHh0BVFFGDPinM3SZ+lRFTFywjtSzp/UzHa9K031NunfvgiCngffx6MoHdBLYlngY+En5fg6/uNWtMCvsx12gj4SGqhM0R1QKYjMDqadSwxqob+gSr+41aMkEMCYOpGS9rZoI53CPE7fXZ7+AuEKcfhyIaH4QDqR6BVw8OEaevdjhS5yFsondEcaNWfs03amzrLeuREpoO4OFOx5K0DiKLmUOJQBw/5TIyshUA6V6fn+NtmXAJE4ozouWH4WRFFxiLhzPpra3gyQenKw/scYfAQ3Ab/PofMDyFtgmHBaflKBlVoxGAQjZy6xOXMJlyVs7DsmkY8H6aFB7QWW/N9daCc0zcogAEVFUejdpJYv/GXrxh62/WVQKTnqjYDaTbjQlAWE0/qu9a8JyRQE4GMrSGabRdkv8DF21RpthH503hBQ2kmCyVYfGpD+aQybGS7KhUZqTlAaL4JpRMJpyx6r1maOcqUaxiOjL1q1JGuX6AOh64g9Qbc1AgGT2qp/YGUW+DKesXa5KIEsqOjJQeIG6D9AIkeut5I9ANb3Y7KZSrTPaEaI/LS7Ygd32+XLM1AOLqS1MWDlIZnuu5FlfK96W5/xUlqpZF
*/