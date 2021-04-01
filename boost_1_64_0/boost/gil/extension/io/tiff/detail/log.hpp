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
wkngSvwM6DRO3TbysxZpeZyI7JPSmPY8hKd5XqKiVu9uhvXUR6Z36c3rhIo9u7iFmz7y+73+Vuy+AzgTkZFsSatk8X+rWnPpjnGiAVrJtJTDt+kQMeguZXTAyr8WgJhYoumOdo8amCOsafItP0iwxCMix9CVV2kRcITHhVJPHmp10CxgKR0m5IUhCzj7EF3SgAVuhkTVVFgctonfhA1DMRYLxiR/0rrlU9cGL6rpMwofmUXamoaOJPViPJCipH7eBbkl91v3Jam0ykGJht9auTRqy4xFo0Luj2IS7P6VP5o5WqBRDS2M7ZeWTGukn4j/y1j9QPyqR1zZIlfQtsYHv14eyWAuERIyXomYCHZQCOqC/xPMG7XXie/CGwuzj6eCYKFRF85Vf0R46l6jgoL8GnB4PmwZqyvWhq0sBLBDzOB91ZAtNGq9mBoNT7diWT9ivaO8kpRJARh3v72KA7oabD5G5wck4xoQJoP1yRTgKZGRZ4WFkgI0aV5S66PJ5cNSwey6PEOWyGhnRg0XEO5jDEkVYYppUPQDSyZ3q59ciLuaotC3zcrUuE4UkQ==
*/