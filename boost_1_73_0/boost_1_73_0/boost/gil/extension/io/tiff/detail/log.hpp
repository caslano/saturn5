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
h+t+3BtNYrgOx+NwGE9h9BXC4dQZ+9Yftin1gsg04F2p0RC5BrEopcC05ny9EXheQxSJrFKEc5e9dQrzC7eewZt120j364YRhV8GHdYaT6/iEQsnce/Ae2wtdTu5DH+w7+Fg0mGDzrAb9559Lc3T99u0W6Nh3BnG/+qfHDffeR4W1QJ+eQDOgzUoHHRH7LJ96m9djTpRtGUn6oVEv3NjN+r0pMl2IutNh/Z+f/Kok67Lge7KrAsK76zm1Nlc+WjkcgGZpjrkkORcSizmSAVvDCdJ2ZgpJaFFKWC8sjlLxRyNZXO0rORC7ydUytYhNRxSkfn1dMllhZsX0qGuYp3D/x3PbR1ikZZWH9ARGjQV2UYCnWjbf4bz9Q9QSwMECgAAAAgALWdKUnk+6d/rEgAAuVMAACMACQBjdXJsLW1hc3Rlci9saWIvdmF1dGgvZGlnZXN0X3NzcGkuY1VUBQABtkgkYO0ca3Mbue27fwXtTm3Jp9hOcrm5xpe0iiwnmrNlV5Iv9SSZndWKsrZZ7W734Ucv+e8FwMdyX3rYTtpO63tYIkEQBEEABEDv7z7ezwbbZUt/LPrPgh/4TSPOo+Dv3EmqoS3rCxP/wKiP8HvZJPssG/LFarLlQ76wBg2x5Cy/4GfLWjbRR6QN/7eP
*/