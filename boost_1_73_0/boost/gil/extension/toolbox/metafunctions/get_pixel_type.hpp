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
TZojNWaLPTzMqRpz8sYe5nQwz+KddhIe5myd5vX1Pcy5GpMyuc4HM2Yoo8nkulCnuc7UfjmYP20kxCiT5kqdJmJ4vtor2XB4jcaUGfks15i/mzQ3a0x/U84tGtNqOLxDY94yue7WmBaT6yGNCUlMDtaDLM/s6b0vnkr3C1rBfwTO9EBpTlp7Px7zrBejTBol7xEH2wI+YVnJFGZSK3/m9k/o8VSkvj3C/qBEY64ikli9u2Mj
*/