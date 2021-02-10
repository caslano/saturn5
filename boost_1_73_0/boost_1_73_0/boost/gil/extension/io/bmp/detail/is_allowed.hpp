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
+UDgE0Jnn1Y7m8toiMMlkpqMx+mijPR1AJDbelBkHDShoozTKxq8TotEKyhMMR5vDPnV1ZSYtn2SeZlXcq8eUeIxfWBFpz8D6nmb0hWPWTsrHwbdYMmCX9L1VNUt7RSvaMk8GqHydNaAWFkflEx9FkmFMOJlGKkofi74Y5ieQdiELhSDA5coaKzEXO6eyDQ5iFNyCSsZSQRGwPXhOOb5yCAy8+of9mrIZbIoCQRLsAOOD/sDyZHqHrOaZFUY8qP4iXjGuMxj9DusAwjZymgL7jxEx3oXp6fmgrJRQ4AVNGm92tYeLc+87wo6tYTvkIedFKqzhuhsiA/WYprcG72/kYEnLBTrfInefprnd/NWlOMu3mW06c89bjS59pg+av93UOIkIvxwCRUNPnOTXd+oB9AM5wO+UnNlqqARWBKrVaYxeFcZrDyI8MC1MgspzSqtHljK3YPtAJE3UG5H5w+V11gtFCT8kdxpwTnzcO+Hbu/4/APh3yF0tRWHngLa0w1fHB/KAHinAP04Y2szbe0U5td011p3K7jTndMJd1FmpCqa+cOBjPbm46hDZBvmWVo4ksoCRYd9Gk/lzVH5uTxhrXW0I5ZKYouJCh2KDAfHMlxt0JN9IVcyFaLs0ADy+mcTDLu85/n5QPYE66g3
*/