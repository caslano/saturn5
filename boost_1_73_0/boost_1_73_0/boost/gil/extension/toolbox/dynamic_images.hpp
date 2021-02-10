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
ylaT/QRx5tQyPhXTVJW2FMY6VAbuF6o1iQiadBap+SLc1mfeWKKdN91z52zQH/fACHv9s8E5tM5V8kfYNmrB55AbOlg1oByFPokBUhOUMg7yUJY5JHJ0unA380kr5MwcKo6XWTbjTEEn6zmQwBS9V82tK4myz2610/ikxbzV1sybt0Oo2ca9UEp5gQNhe6v9NsAMnLN33X6/98F5c9lHFY+2o6KgsO02FtPTVjsfWthgtjGmDoZ7ATFG263x66LHQdPEFDYj2MPE9LeExbrEn0Mxbv1QR6gFQ26l2XJNLIYVRebtZssK2nFMQ6iEqc3mzf1SQdEuiy513jXhveoZm8T49RF+RTRP4/YipxjDS1eNnxfi+ZtiK5c2N9DIyCwM1oZos96y3TRVSIssErDeamrIa5O0BLWlpxXBA/SFwiGEhhLHO82COacisNWuqUb8JGo2GoUCyd7Ni6Ry0Vsuk6wiKjlo7Uwmjd27n8ukkBGYKU13OZtZP5dJpwqPmCjUzg12NzP4i+YFj5sV/C1zggUr3M2sAF+Pb3Hxtbs2V9NUanUfQs6OmmN71Up94665cjf16/9bW/0XNckFxoAQ+NNarkoEbwGw4j3E9ZuIQJLwngH/z+DKOe9ddK8/jBcAYIYO3TmNa8HP3HsH
*/