//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_TYPEDEFS_HPP
#define BOOST_GIL_IO_TYPEDEFS_HPP

#ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
#include <boost/gil/extension/toolbox/color_spaces/gray_alpha.hpp>
#endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA

#include <boost/gil/image.hpp>
#include <boost/gil/point.hpp>
#include <boost/gil/utilities.hpp>

#include <type_traits>
#include <vector>

namespace boost { namespace gil {

struct double_zero { static double apply() { return 0.0; } };
struct double_one  { static double apply() { return 1.0; } };

using byte_t = unsigned char;
using byte_vector_t = std::vector<byte_t>;

}} // namespace boost::gil

namespace boost {

template<> struct is_floating_point<gil::float32_t> : std::true_type {};
template<> struct is_floating_point<gil::float64_t> : std::true_type {};

} // namespace boost

namespace boost { namespace gil {

///@todo We should use boost::preprocessor here.
/// TODO: NO! Please do not use preprocessor here! --mloskot

using gray1_image_t = bit_aligned_image1_type<1, gray_layout_t>::type;
using gray2_image_t = bit_aligned_image1_type<2, gray_layout_t>::type;
using gray4_image_t = bit_aligned_image1_type<4, gray_layout_t>::type;
using gray6_image_t = bit_aligned_image1_type<6, gray_layout_t>::type;
using gray10_image_t = bit_aligned_image1_type<10, gray_layout_t>::type;
using gray12_image_t = bit_aligned_image1_type<12, gray_layout_t>::type;
using gray14_image_t = bit_aligned_image1_type<14, gray_layout_t>::type;
using gray24_image_t = bit_aligned_image1_type<24, gray_layout_t>::type;

using gray64f_pixel_t = pixel<double, gray_layout_t>;

#ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
using gray_alpha8_pixel_t = pixel<uint8_t, gray_alpha_layout_t>;
using gray_alpha16_pixel_t = pixel<uint16_t, gray_alpha_layout_t>;
using gray_alpha64f_pixel_t = pixel<double, gray_alpha_layout_t>;
#endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA

using rgb64f_pixel_t = pixel<double, rgb_layout_t>;
using rgba64f_pixel_t = pixel<double, rgba_layout_t>;
using gray64f_image_t = image<gray64f_pixel_t, false>;

#ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
using gray_alpha8_image_t = image<gray_alpha8_pixel_t, false>;
using gray_alpha16_image_t = image<gray_alpha16_pixel_t, false>;
using gray_alpha32f_image_t = image<gray_alpha32f_pixel_t, false>;
using gray_alpha32f_planar_image_t = image<gray_alpha32f_pixel_t, true>;
using gray_alpha64f_image_t = image<gray_alpha64f_pixel_t, false>;
using gray_alpha64f_planar_image_t = image<gray_alpha64f_pixel_t, true>;

#endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA

using rgb64f_image_t = image<rgb64f_pixel_t, false>;
using rgb64f_planar_image_t = image<rgb64f_pixel_t, true>;
using rgba64f_image_t = image<rgba64f_pixel_t, false>;
using rgba64f_planar_image_t = image<rgba64f_pixel_t, true>;

}} // namespace boost::gil

#endif

/* typedefs.hpp
GaSQXpYqU6fL6It9vub8wu0CqrlaasJR9bhl6l8JFeJ+yPbuijgeiCKIHAWOrmIz8Z/XW54cZBXtmIxUN5ubuZanSjSR58R+dpJIBRlRZgOQoKB3fZIszp7GV10CUdqfomgSWrVbuqh9pEx4Tg6M9Ed5S3lmYrssys0ROTJO883EG3/3yxrEIU/B4072WbssMKf7acZxvjaV10N4VYtJsUPgpIHgA3xdZEWaYv0usH5LrN9Yp/46rN8yC16qv9JaU/E7y/qdZ/1Od+rvFOt3Dul7AsqRJS2MnKFtFiUDg97w1w1ygVoTfj0flv6XlBj9+/kw5lxE3KVzk81DzoVh5PdHTR6P6oXI+PiGHwXX8gMWELllzdzT2uNDLTsXRSw7F/zEhJVIwUYIN59ViNAoGMXouWHs+j0iJCsLlsqOBHFg4/ALP4bgA31QcCc/MiSkjAmQmsFNBCZbSS4iZDEggWVCmOAb+j6P73OJWV+ir2RcSj0jTdET7EQUqgVZEtP8UZNcwNB7NZS0DGbo+3RiphJz1Y9qj9GBHx9Z0UqI2oaQ+RYklhEaElJgQRyEOAl50oKUMdZRcuxvFqSUkJ8I6W9BTEK+IiTNguwn5DNCkixIPFNeSMhjR8Q+xFugEmPeBD5z5PmMNQlKUP420Gup3lgCjRR7G99niLCYa9JEEQ16+FxYdSpz8SiCZQ9S/iOXTEgWs8VtanTBOaKxAQs7ic6qZhecpzFdD7TMb4dZlKw5dIShHGFcYYd56GBEAvMnYRouEpLno8FLZlArcFtYwDHu/PZ0pKmdSPb1xk6UttlD5wTnD/Wlqi+893OxqKyH8Wm27EbQSsilqth5f9FwomsAKKQX7ZtFvZszs3XLNlgetkkgGeeNVtmt784znPJ2iTt/EbHYD83X2xbceb8yA7zkg3FqJXGG/PpFD3N9809QvNk+MinmAbkX4Yqh/AFhrrPX97j/qUXfeU6MZs0RXQnF0lPB4FgqyZ+STga9kjXo1MaalzQGGXj+SS/P6/CjLKSY13RlswOKFD2/TKolAquq4XcAxIBKjb112PJMtlJ0s05YntQkD/6Azmx3F6S3BUziQnFN7mNdEWog9XwFQD9r/ryGQurOKw33M+EibIdh/o0xJGe87jRVT/YIwZQPH/X31/bgoNQ+3JwnbVWGBj85eWgnvyjFPWdDsPt53XbMv/K8cCKrgRSBFq5WnFBT8YdWfs6GsGZH+anq04cSLrLaRzwzweTUoCaV11GUYR3LyN4GVTMLwqmmtml2Lxk+FN3rZ9H7sD6q0O0Rz5LKI56NmhhHPNpz6IinBzak7WqBlVqtnueU0rVI4vxOWol5urBWrfyaEUtQudAdSW/aGSoh2XKUkHP+rJTj6bNi/1vzTZc803EFzi7csvLQ69gbwzMTz2t4PsTzOZ4SPAfw/IHnDJ5LgNsKzy14PG8ovh+/g/CMxjMJzywL/jp+l+HZgOcQHmMNuumLzx+5Hmp13Nba8G33SLdNg8pDtLFeICtcRgjOac/6jf3mR51JCV3MmqECzRGs1Dqrtpmlk8xQrNn5LntY/6A1HqadN6lJ+sKCC7mTY0pdfrTlB8mq5zG5TGXO/AMM0tlAAnNaaeWEftZ8GFmEYjHKMofgDYXCmbzdaEN1pkCphbPq4Tt1OL7PTsZ5kqY868nQI/ii/6v36P+qs3plrN9Zh1s/eXT681gvHUZegnRlpZDDL13P5OqyZ5hqYKWrPRXHLEfnkGcyhIgcfx3i+GvVbZIsPMWY/0BOFLVfLfvbFE6PvDKloWbY1Vn9f77r4gjY81lz11M0QIrA7wac644vIJPFHeW0vVlHp2zoxU3HHfKKrSYHCo4=
*/