#ifndef BOOST_METAPARSE_V1_ACCEPT_HPP
#define BOOST_METAPARSE_V1_ACCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/accept.hpp>
#include <boost/metaparse/v1/accept_tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Result, class Remaining, class Pos>
      struct accept
      {
        typedef accept_tag tag;

        typedef
          accept<Result, typename Remaining::type, typename Pos::type>
          type;

        typedef Result result;
        typedef Remaining remaining;
        typedef Pos source_position;
      };
    }
  }
}

#endif


/* accept.hpp
ydASXvigEG0VZT0OHudroQTJnPCZidKiTWodojja6IN48DenjPonqXM3AMJ/XFPGpRvQBkChI3CBih/wTbDdD7mm5sry4AziMW4ZPterODZ9/BdGYnL7hvjC9uKHrIJ4r3hP5oVtv4g8WOyITCGHCwlU3ednhsEXFFAdWOfap+ZaLe+mact9mablCtVwBii+DVcI+/Y+mixI2/OXbd5Lx+4SE5O+eGakQSGXIazlIK1a5TNopQYtPREf0eV3U47CqjGgEZqy+c4zhmdESk3HZ9WGSvav6dIdJaOa2cj5WOyAwtP3IFD+ut+e8Z5W0wQJhTVlGy6YqJNoXMZPgrJPG6tSkpl42YOfU1jGxPOV8PGVFCXKHewbUFUiZrhuV23DBBhv0xlWvtGPAyUmePQMJ7iDwLt/yikVme0ObrFCOoD7ICL+bsjbfS9JPelOOUHHy7cBMf/tS5RogVm9GOBZcydG9jJa6F76ZtaVNGnG2SVl7R9cSsq3iz/bfJKwbVHBzGO3GV+CLxM7pkWMh35N+kkYtzz/tNO1cm5MrF1WHXJki6pqvCvDKnJuMg==
*/