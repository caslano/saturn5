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
Pdc19NyhJg0MfX0cE+qWAWkaGeqy8nCvoS76jtII/Xs8GfploJ8J/dLOz0O6TaQXId0u0suhX354a+iXFH4z9Av+vh26hX5lk7DfivRB6BcR3gFppUg7Id0h0ieQfifSZ6FfRPmr0C+MjAdzC0an034554K0X6K5MO0Xhi5O+6uImzxldRXlnGJdy2vDlw/JX16303k2ZwjYni/oPWp5ESfXD+9ReTixUTpneV0lzh+qlm2NdoMWP1k1cR2buQ0=
*/