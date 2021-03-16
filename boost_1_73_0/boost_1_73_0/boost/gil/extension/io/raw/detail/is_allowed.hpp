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
GMNnLOPMFPNPL/8pxfRJYpx2VD5jDZ9xjGP1NBuf6D9g+lwO9vIZZ/iMZ5wiMf/z1z/wmj7JjPOag7dsrrL7pDDOaDG/89axfabPBMZJRuuVYvhMZJxEMf/EvqZRpk8q4zSh9Zpo+ExiHNo3U/XBTZXTTZ/JjNOJ1muS4TOFcdLF/M3O7rtNn6mMMwctzxTDJ41zLJ+O1l7TZxpY62UtT5rhk844U8X8rTNvSzd9pjNOAC1PuuGTwTjDxPzKDws=
*/