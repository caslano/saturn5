//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_LOG_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_LOG_HPP

#include <iostream>

extern "C" {
#include "tiffio.h"
}

namespace boost { namespace gil {

class tiff_no_log
{
public:

    tiff_no_log()
    {
        TIFFSetErrorHandler  ( nullptr );
        TIFFSetWarningHandler( nullptr );
    }
};

class console_log
{
public:

    console_log()
    {
        TIFFSetErrorHandler  ( console_log::error   );
        TIFFSetWarningHandler( console_log::warning );
    }

private:

    static void error( const char* /* module */
                     , const char* fmt
                     , va_list ap
                     )
    {
        char buf[1000];
        sprintf(buf, fmt, ap);
        std::cout << "error: " << buf << std::endl;
    }

    static void warning( char const* /* module */
                       , char const* fmt
                       , va_list ap
                       )
    {
        char buf[1000];
        sprintf(buf, fmt, ap);
        std::cout << "warning: " << fmt << std::endl;
    }
};

} // namespace gil
} // namespace boost

#endif

/* log.hpp
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
*/