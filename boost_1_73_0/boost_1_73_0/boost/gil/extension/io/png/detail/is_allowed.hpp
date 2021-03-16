//
// Copyright 2008 Christian Henning, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/png/tags.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< png_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    using pixel_t = typename get_pixel_type<View>::type;

    using channel_t = typename channel_traits<typename element_type<pixel_t>::type>::value_type;

    const png_num_channels::type dst_num_channels = num_channels< pixel_t >::value;
    const png_bitdepth::type     dst_bit_depth    = detail::unsigned_integral_num_bits< channel_t >::value;

    return   dst_num_channels == info._num_channels
          && dst_bit_depth    == info._bit_depth;
}

template< typename View >
bool is_allowed( const image_read_info< png_tag >& /* info */
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
r/XoeG7a6nd+eefzb0Q+eqsuuWdm16Ghtc2dsbu3qsrujoVNTU0fvdf1SV5yT9ehkwKv2NceJDfir2uru9dMbQtN3oK/v+mMSDIGNJII1FZ2Ji8MVr6UCCQuDF7f/1h3e1fNtGJlqvFq1Tag/YbgVnIPb8zH+4oCkaR5gcgkeTVBEm/Yie+r8Xrj6D1LjDDPUqb/pBLs/yumBFs6XHsFfKnGWF+6gKMPgRr9VbFXwB8r4Jis1bu1Gy9++HhTf9s=
*/