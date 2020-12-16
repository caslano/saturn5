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
fMDj/BBUQL3QjT7Brm2g4jDW0/hPFeNRX42/kjoI+Aam52Yyo6NUGWfhqRodYyfsBug5uJT8BEN15L0nnTbTN0/f05ZXnLU0492D/E5Y35I21/i9Dl49ExVULzIN1QPb+ZdOMF9FkRaskmf+iD94PMZ1iUdKUPn3QEm/ycPDcAY+bBRyiikcDQIp+U09Xcmo1f0bzaXDxhk+X38GoUFEaC4R+uWSl1AACLkd+U3DXMm0RgKNuk08FgqZ+5iMo8mk8dMy0LiGaLwDGrTuBLY7hsqPoMVFV1w8drfLbxrrSiFyBAoHe/HkkSqL3FRgAKT736S90caHy92dCJwWMqeLZKUP4nY0OP2cDKsF1O3jGQHIOeay6QY+lbuu6xK5tFDABurpZUvO87anLRhaSY2zuQdqeN2S8yG8GTL3PJSiUUqH/PPY7XRBXgEu5GnyuHloELCMZbc9aQqndsF3f8CD6LOszcASNpEH+Dqk8IJwj3oXUbrAY6rVqzQm8CPr0XaorkTDxTTY7y8dJYyiSaWyh/8PuD/UnnWpPaj9hUC9oYj7/AoW45L7Q/TfgwxSVneVyasRKXTwmYPq1Ur1+MgPk0ZVMN01nM94qVb7QdWGa1loCfBayiSgqI5SVKFR13kgqO+Wsf78Uk76njRwEwm+DnDvHrMVRo7xceBmT9laWk02qz4EbUMet7vhLTZOtpnmNZA7UZJ+JyghPoDioxFHw+e9O990U5011mz4TG715gi63/AWW4HmX+yVG4q/8a7Rdlj+IWM3rBHlkhcrmtS7T4jhRZapcn5GVDP3/CDmyCmxUJhO/jTXymtL0R9fDZhtSxArCzBYcDkxrkw5d34KidolCEgaLjPQiVYOqecW4DTCWjg6hIf3fcXMqnPEqv4xcv8PINjb0ak0hhvoRbPU10jRn4EhJ6h3ob41PgfXNvj8G0W4/wpwN1cUQPkfeQi6jKCFgGLgCwhko/VE7RId4uZYN51ua9fqMPr25inSdMpL+npUszahkRYfWzuL0Q8t1/l+FOwOVAWA4sr6MxpIusj5flIC3ey5M4pOyM+6Q0gR0d5BlasnSf2+u0+Df1uAdINuxMw9SCA7UIp/Bj6LJ11h6hqk4aiIpv3J8Wx5QNCz3XkA9P7aIWTG2IEtulLcFON0vLMYADlZA84NQv5AHQk8z4zEqLIAx0ZpZC5OllQL2UKInok4YcPT59DruIw18SiUK/8VXxBZtBoBpzLiN3usrXK63OM9/J6oy9/vFCRHMKnal5ztVpy1MV2j5n09+Ieao6G4AOLR/iuNMjoDGWJCjfRdm/u6oZnoG/kCLuip/sBj83hUhSRKX8tDQ+TSP4X6JiutmSVH5OZNVAduJlluursGsPQ52RB+dRobwifSubYKAmEiqF3i0iESeuZFzjTMNYFqeAfP6KKlsJiD3wvRkgvxNKzvYdUFgk1M8PFuPtNOOhYkGondCP07XFn6iUaDS7zS+xuiKGaslVUQmLJTciOXLMrjcSIYotoGTSUyizpHkfaJDd76dvOJbu4taI5MirQ2ZG4Fl+5QvEBFvjOooTZ+pwpszXqHUmOau5HsHx/j7pe4gSy0o2X+J1ALLs5Cgt71rMeDelghkuUJjTSE/rWj9BEnXSP0+edh96vUXZZ0lD0NXK2CFdAwqHmAkL/R9cbEa1yHGTyZ501hV3+aqHjZH/LkuiALJj3IgCGUe2hWFLkMzeY8RSAt99pkue40brd0/K1eCbI5RiuBTXZuqdyuvv75Dmh4++e0rr7+mRQm/bOUCzEZmNuB+b1P3QpUSr4XybwJGh4tJts1jibiiPoDhi/im4P9s6EHFaGrTuogXXXvJW9XdQeTPIk=
*/