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
eY1nAV2Wz3PxlZPO0c+xcHScC8hP2aSxIzepgSbhsMhGnJoPphNPMwWIg84QlV1cKQ0xX4WdTeojq/LxbPWOPUAaWHz4n0rP/09l5w8GJovAUWUyd9kOdpBIrzRbkvvZdyVj8K5pqubQHVqGyVXM2Yl25YTbzOKXgg0kb9bDoy9qQqPmj67mWkhm2fTeiNUm5XRmkuVpX9MKJd5ww+4fN2PM8/ku3NLZT1g10+6KqdjYMB7O/WCWr8OXkFOxjVfTZMnSbDImqgf3ozHRryJVjq2PE2dc9/zyRH1JBB09D4bHhj1h9OWm7+zXuiGcwfMk1m6EegqOdGjocXzRPvU9hyNnSrVz5/6Q0NwhL5pgHZ2eDzvto1H3vOf5EOMswPaK26mCgWZElaBQArQvNdK8alpMo9ldCGkqjUDAVQCn9+ywYaVgY7deptckAiqa5HS4koVXzCV8CuWz2LsEOotuh2OYjJO/eY1g2A3x75qmG3znTCiUw1/iOsxz82PvEB829TRxXGHlNhtzYs4i2XvWtAXdwen50c/q59x4FEbwrjNux2K1s5K+ilU2kV5aIhTnT00b1Ot0jof9D8fGE1lPFV/WxKZrVBbrChciNeQ4e5K9l36YpiWWhWoaxTkhjH+/6Aw+8jheV2dE+Haz
*/