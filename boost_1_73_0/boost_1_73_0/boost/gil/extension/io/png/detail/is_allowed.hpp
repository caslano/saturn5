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
Qq84DEQZpAhODUV3ful3B50YFetANM4vOHJVn3LJxrhHWM57qCryeuvj3jDuoxwJ2ju3Ng2ZbGj0wmv1Imh10u73P8adj5037dPTITpxU07LWdzPd1GJcW/8QBdvWGcXp6MufVOCLN3zwUWPyNIH78mw3+kcc24I72F9nqPz87eEur0n8Pn3/jSIHdcdqnpBFiDPy5aXip+kzE9cT1Acbf4Aa038FqIYnjUQ09EAFQUHQ6Gl/gMEXXbbp93/6BwHz4duzvYZoi2f/WHsUIU1temdC46/Lbymbj8cqOMFVcGtBsq84BZA1kF8Xg0HhJF8+KOR/8tEPLZrEaVYDz3IXr6aRZaO06KSLkahETB97XJbOMm7XmxUfX99gV+ch9079QV2T4zfr9ekvHF/cQ6iINb8Yjkd2rhW6KJsFM96t1fPAqVPWVPAvxukwqowV8PKedOJwpTz6CVVXZ/ViBmvTpBYtvBUOAYtDMc5IZGr3Lhhi/uBcXhe665UeGKaMRZVpFsitlO5AUZhCYbI2Og0qG1kE9l7mipTMU2tDU32Vq0Uduim6mZqaoNltsJYkATFFw/8AHY9HlOkdGDXbev1GWRTt1J7VeCtyK9GlWo0BsOb/M7PcFykpQTaPp70T5TU+8YD2hstc90u6sbF
*/