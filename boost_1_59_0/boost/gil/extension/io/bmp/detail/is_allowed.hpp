//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/bmp/tags.hpp>
#include <boost/gil/channel.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< bmp_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    bmp_bits_per_pixel::type src_bits_per_pixel = 0;

    switch( info._bits_per_pixel )
    {
        case 1:
        case 4:
        case 8:
        {
            if(  info._header_size == bmp_header_size::_win32_info_size
              && info._compression != bmp_compression::_rle8
              && info._compression != bmp_compression::_rle4
              )
            {
                src_bits_per_pixel = 32;
            }
            else
            {
                src_bits_per_pixel = 24;
            }

            break;
        }

        case 15:
        case 16:
        {
            src_bits_per_pixel = 24;

            break;
        }

        case 24:
        case 32:
        {
            src_bits_per_pixel = info._bits_per_pixel;

            break;
        }
        default:
        {
            io_error( "Pixel size not supported." );
        }
    }

    using channel_t = typename channel_traits<typename element_type<typename View::value_type>::type>::value_type;
    bmp_bits_per_pixel::type dst_bits_per_pixel = detail::unsigned_integral_num_bits< channel_t >::value
                                                * num_channels< View >::value;

    return ( dst_bits_per_pixel == src_bits_per_pixel );
}

template< typename View >
bool is_allowed( const image_read_info< bmp_tag >& /* info */
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
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
*/