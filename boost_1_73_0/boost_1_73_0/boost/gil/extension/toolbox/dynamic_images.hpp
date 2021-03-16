//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_DYNAMIC_IMAGES_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_DYNAMIC_IMAGES_HPP

#include <boost/gil/extension/dynamic_image/dynamic_image_all.hpp>

namespace boost { namespace gil {

// need this for various meta functions.
struct any_image_pixel_t       {};
struct any_image_channel_t     {};
struct any_image_color_space_t {};

template<>
struct color_space_type< any_image_pixel_t >
{
    using type = any_image_color_space_t;
};

}} // namespace boost::gil

#endif

/* dynamic_images.hpp
TOlf8laDIWpOUiXL1yVXwgrOJko4PNIo5DyRXL+guhUw2SMSFUQuTCzwa0DtfN8Gs6WkfZvk1AVHWURcEvGFdhFUuxDUGDZWvFXlQvWovr0Dqc+Q+E9XU2L8AUZ1G0qf+9ksBDS0jY85/8UDbwLyqp5wG2GZxJMrbFuhs6uqmQrPeZtgBaxCjNvtdV4TFfSI5RlMOypxN2AWTPa8SWRkhm9yUX+LgLNETjpSWBtFzkQdaYCKeqvHmqgi0WBPaZY=
*/