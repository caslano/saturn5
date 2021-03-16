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
vH6Ifl2Et34QP8rbPUS/fYR3cAh+R4bo9x7hfT4Ev/AtoA2h/EYQ3ljBlX62/aGJ5FNo+BUXkx1huitzBviFsFZwXERnlV3B75/v6fW1ueWt9K29ns52cUN9xlp/TlZ2gZzXl5+XQc+Te9oyfG6y1+93WwzbLjr8P2vXAt9UleZPH2B5SJ9g5SG1FiggTEtpBWUdb5NLE5rXJOkD7Xg3TVOItE1I0vKUEUpVfgHU8TXqOO4sMKLg7oz6U0dHZUA=
*/