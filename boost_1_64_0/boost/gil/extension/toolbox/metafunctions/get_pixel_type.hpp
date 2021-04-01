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
gDVFxD64Yv2rheMt14ejYt2k07hCq36sd1XpXTM2cyvBbi8/P24SD7Qst5NbcqWEWJ5Iginmy8zSWJUh86KfNQVtffASf8cIFJwW95baOElb+UVxfyX25usDUKpVOkMG7YrH0RetLBKR2pOi17/UhuY2zSlSSNoDU/1TWCQjFWDp+Jw1uqTPh8G60+QrlfpBiy0Dx7n4OjPb6Qlb4FZpwaZoQ1qrfnHFVnJ/2LqktjsfSNJ/fv6Th86Nu3BiyPiwFY1/Q+gNmQRz4ZpZIbkBJ/cOdTc94cr9oIvAYG6dSBihxwf8i9hEUoAgyy3YbfRcdpvN3PgW3RFaVV4E7Og+bcLvuDmwBE2YtOr/fUbnGeDEkPEJhfFRmcZBOpi2OXu62/vHOX7Gvvf6NL6qAxiY5E0qRufWvsAe/Y5VM/Ttl8vqeOGmKzu920iZbQN8R/X0wEsJ9hjrQq2JBsyBY6NAdwuA3IXyg42i09MhnJjnj9FVo9LTttkDkIhPakqhrE6llMFhlCJ2lG6YnYjgYfz24lsX6G3MacKN3GcHfPXMWt7Q2DSc3JUjGrCODw==
*/