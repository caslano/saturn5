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
AMJWneXtmbbSE9g3UekiltS5lkwr3pXvvzwK/2vTEgZCqb74Gv2tJqJ7g4kvS8zeQLEtpK7TdcqjQinUX0MX+B3pslOYH+ER5b77IJVTzCwhSkNGUSJUwBTo76JBJermyTUJGEmfK5f5IV/elJG0DzDseDDkxDgXlUT1BdPFt5US6ad8jLGjHcy3VhfBuj86A/55S6udiQo8HTtTfSDy3FaY5eFSRJPsja0XwONvTxjF1vovMlyPyu1DX/djQKrCVJ9sXC6g0mF/Y49jaIuaaJD3N2+iFe8Wwp+nrOBxhZNznHaVl5ZOnnNGaLW0yB2+eb3dR94ndiTpJ0cHX5TDpm6SaXA2qcp9NUhXcOA/HoSog+WGFXKR/DCN3li13ZO+qpGIDPcJlVLBZE5zelWhLO+5lmBb0m4Kw/2KKhWK41jbuZF+bGAQMMClwSVJtaLX9Gs06gkS+bYAL5VLswAFKD5gEu5aBTgFERmMGNpSwHp/fHfYyjCI8yNdBsH9dwdLkAQWC8g8dtT2Js0/sdVjVJO8eMhWGS8xRFvB9+VCE+Kx+3rjxjgRgP2rrQ==
*/