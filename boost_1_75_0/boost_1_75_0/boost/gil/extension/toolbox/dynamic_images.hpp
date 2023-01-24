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
SSsns94TRpZRgpAqxHLe1XIC/hkkdopngUaBxI9roQxrAbdRKmsfwPkBmVwK+KU14CSvIZEI5VKZUgScSqSyXATS16jBksiP5HIdSCSSoRMLzA9pOQqFGElBD3csDN0llBBJIHdIlcKCUVmuAJeBM+r/KGhxdY2QUWJlAoaELQ/JgRhKXiaKcV6BVCNglArIxLpIRO6IpWFm7IEZsTuCCyAslgg8aRYTkEZk+RmxerQuFEjeAM2At0sYwsA9MUcifIMwOhEWuGF45nN4LgGQKD80LxU9aSJAaCI6cCX3UZslaDKQopaXRKlTAZ/hY1VA11Gr1CQHywOBOanUCtQvlVpJOB4DnYFiAJbYWoJkC6C3liYArLRgsY0YEa+bRZE2D0YTEC2RcFIZFnG8vgcjS7tDOI/nU6PQwhKr1BKe9moJyysGPImJqFGwcsSl+KSaEjnqDcu6u/PFWF41cYd5xqLuUICTT3NnQaUg6iceXUpklyRTaVyQBoIbggqC3gkswx398Znkch47qhOkPOiWUnSRy+UeEkWFrPZ55TbEMplTeVilLo+gIdIIaYQCqWJQO1Jb1c4aIW6KEo2FxlUi4rOTqQiqlYuMcQAhruIhQAR9hBUnQMWnw4qGEVU6jDKEGkmg0SrLU0wElm++9eKg7VB8NjzimMhYZcMhFstUzqrGcRgGEgBQMlYs5biqSCTvDxnIZ+vgScRAWXd3
*/