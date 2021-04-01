//
// Copyright 2010 Kenneth Riddile
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/targa/tags.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< targa_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    targa_depth::type src_bits_per_pixel = 0;

    switch( info._bits_per_pixel )
    {
        case 24:
        case 32:
        {
            src_bits_per_pixel = info._bits_per_pixel;
            break;
        }
        default:
        {
            io_error( "Pixel size not supported." );
            break;
        }
    }

    using channel_t = typename channel_traits<typename element_type<typename View::value_type>::type>::value_type;
    targa_depth::type dst_bits_per_pixel = detail::unsigned_integral_num_bits< channel_t >::value * num_channels< View >::value;

    return ( dst_bits_per_pixel == src_bits_per_pixel );
}

template< typename View >
bool is_allowed( const image_read_info< targa_tag >& /* info */
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
jn2pnEbigREMibwWh+uajsk2uMdOdTijvjIVzLL4/VgqDyIHYk+v2tTRkOTHuGPJjICdmtKLh2Ufy4UCG0ttx4TYJ6BqTxDPAOOVPAgHPEQ7CDtSFRJgrxoB6Y6bDBg3UtIgZIOqPCeFZA0OnxTxF681lMa6thUYQ+JNKIABffEIyM3VkWnWD3/11Z23OUe/xvn8WNfs4MaeLzJKBTfKzSXxXwteqAYHF9Imn3uMVv0MvHmby7KT97rGJGFVDfd7lpSTHjuwv2KakSpU+0j6DxmkhPZ4GXHz8OTx/2FiSyGZaA5l5ETypmign6A2pDnT7iLLGbOk3OukswsTqbG01bZ3arMXFcA2/VSRYTCMHMDcZofRMTO0E+vbYgAe6wHA1wjtH5o8dc2pf4LZekQZ0U1nOVOAvI2l1qGyqkY5q38/cZ1i2FW7fXLD9NppQjmFkC8WdFqhCM8ARrvUOXRjVV7y6LD4NQzRUsjj/7SgHynouqXiHrB3a4ylJDIhejqRbUshmRfr6YNh3aVqpgDNaqUVhqXAir49xiqVh1V4gASB5sJC+w9uC+xLXg==
*/