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
3QHRjQsXa635q/Nn04ZQHi53ihAEY0jfDOcqpWj5MaFM9CdMcFSv9EOHtdeZSVNcveMQ9/v4Xdpb07cwhlhMO8Ll2BGlHXu4tk+BzLTaJ/AaiLt9YY8oEnvnjLfRj0DqIaAlHootD2qIJHT9Uu0eAGxbLZMkL498uZTjWP3V2ZvNCrU5669G9gpfmvLCi1Xywk5/mOjrX0d73WEqO2J466ajIKYtx6QdWoZfDuGbEU/+bVfYVlVlab4Sm4+xstcuRdf9vOLW55r2PwTQTDKSBmJFZvw2N597n/UEQve/EHvmbuIh32sgpP+CuXdBWNyFP/6NVgWGPxZD4AXD21JGEF/CtBYOoHmH1UAnfFl99HIHLBq40Y0MHqvhXJ1PtpkdZNltTHXb5OoaGEdbZYom6PVY+VZUpXkHsVqiS/zu29FLy21lidmyEDzEmKL21cfoHvIYJ8+Svm7a6liNm5LNLt8aqd6J8Sz4mT/mL8SAuH5HF1r1or5A6uZfzbWfxNa2ZmqPyZzxS/M07lEKg3lpt1K9BYT18rdwzVNNpJNE9qg+CRR0L+aHj0epfgUUdB/mB/OAUmGF0lKOqI5OwkFREZsuiuyM0ZsqUslravW1afZF392TDSzRMfZV3/5t01O9rqPX6yPnKJaxHh/jow6CG2ewlbtdvbInS1QWzfVENufvTDy3sgt6qma4zCwoHeTXFjgTLRjVxdsPv4H0
*/