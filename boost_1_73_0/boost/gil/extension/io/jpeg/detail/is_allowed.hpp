//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< jpeg_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    if( info._color_space == JCS_YCbCr )
    {
        // We read JCS_YCbCr files as rgb.
        return ( is_read_supported< typename View::value_type
                                  , jpeg_tag
                                  >::_color_space == JCS_RGB );
    }

    return ( is_read_supported< typename View::value_type
                              , jpeg_tag
                              >::_color_space == info._color_space );
}

template< typename View >
bool is_allowed( const image_read_info< jpeg_tag >& /* info */
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
cFH+6unh/v59vfj+K4kXHv6K+F62HHF5uw9/5OewteiLeTbkC/m8iLG9ZivMcch1r69DbzEOW+D3A9egHPrjvC7qzS74NL6FuboL7MfdiDNWSr7exRiPJ/HAZFlv1irEsI9DVyTf228svtuXED3EOE+HDO7fM9ivJaMH1vEbnpa/HAw7At3+LZzIXIuWAG3Y5TnwXx2PQZaHoQyJn6fBTiz6ELwvw7je4MO7rgrSOPpvsOl9
*/