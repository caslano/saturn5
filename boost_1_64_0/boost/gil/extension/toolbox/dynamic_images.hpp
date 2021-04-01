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
2ejrAeMY7+bQ6FoEZFZQ7yPBhcc1A/FwMDpMzW99lbh34ZDmFICy2SV3NISK32pxs3lPbeCsq181+rZPGuIyMEcUKYHxFCKiXmUK791unFDVLYqREZs3a6kVtPW6A1jqzixntZJNt77n3OWrDicV6ykEAduFUK8NVfTna/436QlVAYyuOTYP5mvG+qC337AoVEC46xnsAobQKKYeS8Rtt4+Xrwg2CbuB/v5PrqNKJPWgk1OvyVsXFvdgcmPjN4owxgKGCCyjCdk2hO7NwyoOAqhMyHFLtF41wqHq1nEoQ/Op5aKt1YNtJp22J4aO3L4cCgt+YleAN0C6KBDThB9zynJm6fdcaGJYCUNwTV2LoBm5PObXD7kjsZykPnQSbB6bsrU7LWf/RB/HvfXPJd8g9KYhdC4mGGCbSP2k5kDUQL1Eu3AQel7955zzDzWs62qHTRwMwFOMLNwEJvrbLlb9h15//v4faJj/aJwUhiqpwIUyEdGkc2sf0cCQnD+3E591vx07TZNenS7Ymvy1wEAPSt6vl0LlqKmJawuuDmHKvarrZnEkXMbC+hQutg==
*/