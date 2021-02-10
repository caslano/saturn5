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
ofEYnoPMtm14osTuVf9/1Hp7eXz6KyzoddE7EG0cgnj8WP3y6FCsHq528IG9vt456NAAeGxPngAwbPXkCaLlh/Boi7CBBEFPBMBNuCfwWMoPXViSsBYTe4L8NeY+Jxa7v2utikPuD2Ko+7NnQgwQyABhCWYBLFdwjaYpMBA4x+8CWHLgB96Aa/VI48ooFpV8vHj9htj4pYZnsFwvjk8vClzTTAMeHTB8TXAMsO1J2xwDWjqx+u7d6r6SBhjrI54v3UQNNQzi2B2BXkFtQrSiywauF7d21MDVuPCTTbseBX+0/NGUIeoDBH98LdGzDtKrCXvI8F8GnITQssFRBF8bsbvonc79xEmAviJ4+PE6QmO3HciGpSJG6XgMetGgFWly/VRqMr+on6NIWh9ICDSvugVWzUxaiWssIO6VDx49UYDSoFxdxQeAg4NyXMdfTQSSZzF/Xf/KHCTzFx1v9CWpSwDeiheE4V0Lo4sYOhTGRPKPVGjE9xrwu0iNWH31MwbgAuLhoDtuImfUK2VUJphWhcih2C7iaA3GEs6FA+RH9KOsnvBZQUhxwWSrUL/R2JRmhK/UaiXTHyz1Xxa6XpsYxpIxFODlgqin/ge0+xiB7PV+FO0YjDxEDWJno7ex0xHrceomHBaiQ6o4AYwA
*/