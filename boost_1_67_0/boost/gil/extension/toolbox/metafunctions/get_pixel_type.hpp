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
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
*/