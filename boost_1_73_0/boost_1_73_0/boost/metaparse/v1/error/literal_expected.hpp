#ifndef BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP
#define BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <char C>
        struct literal_expected
        {
          typedef literal_expected type;

          static std::string get_value()
          {
            return std::string("Expected: ") + C;
          }
        };
      }
    }
  }
}

#endif



/* literal_expected.hpp
t332HXHkVB/Q1H1lCHAkqajui0tARDR26UGVDA58N/+8uQVPZkyWEhZsNhAxRIi4gQBLjVaIvhAwmb3DI1yl68go9hGVo7TwuhiIGABDPCyIlxxCVNmXkNYhl0H05J0u7ID1OBgEsI5HUkjalzCuSzANQluAUH4gZYACVcaYkrysF8ku9yayGdqyyGgFaypVbsB9gP1UZpVzqgTgUp9cWZd7a3ze9u8M6mQlpdrSBkNE7mjUU1BcjPNKwtfaRFs=
*/