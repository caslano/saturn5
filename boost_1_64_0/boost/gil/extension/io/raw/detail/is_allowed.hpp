//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_RAW_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_RAW_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/raw/tags.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< raw_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    using pixel_t = typename get_pixel_type<View>::type;
    using num_channel_t = typename num_channels<pixel_t>::value_type;
    using channel_t = typename channel_traits<typename element_type<typename View::value_type>::type>::value_type;

    constexpr num_channel_t dst_samples_per_pixel = num_channels<pixel_t>::value;
    constexpr unsigned int dst_bits_per_pixel = detail::unsigned_integral_num_bits<channel_t>::value;
    constexpr bool is_type_signed = std::is_signed<channel_t>::value;

    return (dst_samples_per_pixel == info._samples_per_pixel &&
            dst_bits_per_pixel == static_cast<unsigned int>(info._bits_per_pixel) &&
            !is_type_signed);
}

template< typename View >
bool is_allowed( const image_read_info< raw_tag >& /* info */
               , std::false_type  // is read_and_convert
               )
{
    return true;
}

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* is_allowed.hpp
ShP1b9+az8m5aA1z2wlO8iBn0Z3IhAKcFLpuD8REINHKFCZ3yd/UYLBoy+IsRNaUyqwqflt9uHivtzXR+AcygR7dOwhm+vxiwAtPGHwIRGMPAAKE/831xgqffpdN4+dwPztBx2qWzw0ezc0U0N3OiZ1P5rbyP/KrR2HlRAhXEguPrZkeow/oYiKMBkoBmT1AhjTKSvb1H30YjOczs1F1+QSxZIx8SboXkLL8qKXsAPi5vppdt8mwkdxJLfGZgsgHSxXgfPpAPJqGxSHlfI/dUZlP8fwXJRg+qsUi2ab6n50kqOWaxZCC7jkpsvyN2+p/aJEmg1v0+nf4FAr5hIOj7t48gHNqLFBwE0SC+5dI4rgU32KJHNr1UzXxeuXlZzPwcBH76Zr9Vv0ec7nUYuktWF8HCgvWGob41aaIDQ5l8atFL/3EMuw9zjvqieY8mpewSote+g5gcXpCQHol68j3IGoyMfgxI1ZgIz37u+BAH6V+7Z98c6X7olE5NDvWVzyoh0sETjOTxgstA3cYD7C8nCbpG0JlexYyCi6YsqxG5pJz0YuZd7TPTKafGA==
*/