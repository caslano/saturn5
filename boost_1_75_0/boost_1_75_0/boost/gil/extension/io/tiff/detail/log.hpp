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
ANAguS9wKCP6IA9EGaFoA7YkiFmDOgA0sjWLRmuodx9jQHAuPO8ufYmFgnyxC2Rr8DncEZ/hZeKNDGFLeDXyHxBe4WkUOTDeo/8a4AaIeBEaMU7CgfpvjBrikEO8r+Ej4uH+7owDkh4FAzSgiEa87PDZMAVA8TWXHdL70Mot4BK6KCEE+T2Kp2geQCBJBeZ+xfRSTZEHr91bDMd2cAgHnphEaQ8yBLSELQKq9hsDtG68u21byCHkeQierB6A890bQN7BDdz9jUXJIXfAFm0nYAcFDskntVniRVD8kvgC8CJkiPhAfYEo3JcG6OxP+37/QBtwcb0f4I/PDGiOHAV4RGkE4EQyw70HasGJsi0AzoFaUhMqADpYyqwgBxm7q0T2Phd8zUQhak1PISKkSYFkSz9NNYCoVb0bszqE/O2xZjYPRehFYYn31OEO4JPcMfLTOAd7h8iJaJvxRTpOwPBFeo31p6JWFl/WOXeH/VM3j6KQ1mqVb37OjIn+sUFqq/6hCdckz6bDuXPH9C3JIt8o32hwKpVD0hqb+3P5KlXz/bqo2/PI+GrHqG/5c8d5/M+3Y7zdlN3bUPabmyuFq1VOYtlpue6u+qTXLXw+LlwoTAZ5m79qNhjJJ3Ic/oX+BB6aYYDgmX6GAA3NQYSm0Go7IU7U7aDO/fzF3PGwyfsR3+2x4wsD7VPeuiN9rt1Egi8FlflaAv/jOEnZqnUy
*/