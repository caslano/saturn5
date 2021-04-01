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
CypBIJuCEXZ+um+uSgVvRlyye2MPjR+3ZZ4s6KZ/pD37iSWb1YJ5KeQdKK4HupfaQsoVz0wGYjHrM9VyYXQwVKdBKFCaEY9Gbx9RczM1z5u6sK+YTQ3Czb3EOA/+hlJvrq6UaJWMwZ8R3cp5znXdxu2R86lrWsmXatzFK8fSJ6oVoXvkzN+LjBxXWHi9Bv8aB3Fv+KU6gi4SaTk+Ma3LBiBmFVNCBOwcNhGplk3vy0TuHRBv9LcJetUAG5ZiJ51fwyevNuLPTbJk6sF2CIg+k9JT9VHmHxK8r2sXhPe5e/PDC3CKg0QRuNqWzY+hVXEnmgPRNVn3xFkFFq0uMIZRgghFodNNNfPqHkQYqOQfVZYdZRVlAtt+E+la9Vm+M3JhlLS7KyGMI+5aWtcHrwX6uFAIT+xPx4Sfiqh/7IYSjTdlo5UsG4xtnQ5FUrEn3GwkwUKV5b9/TGwd+7fXQ2/cADp62UFXB+K7/Xg+sEAe/E1aPq5M0q8JO8RVgQv7TteGUrzWllqn3rPxVwEUz1F6fYqt9CXyqMMYmQktXaDueBG5gALc8szVtFcXVQ==
*/