#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_EMPTY_STRING_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_EMPTY_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ignore = int>
        struct empty_string
        {
          typedef empty_string type;

          static constexpr char value[1] = {0};
        };

        template <class Ignore>
        constexpr char empty_string<Ignore>::value[1];
      }
    }
  }
}

#endif


/* empty_string.hpp
0ZDbNncpVUffWHz32NLvYK5fNA5yXZFwl7cyT1iRyzENkLciAYM/tt8Y1KsYh8lSaS4prnNy/L3JfuHC/HK5Av0y3idnZChU3AC+cnTtO3ciuY1hhzbJAbbEPKD1CrA9IrtnRxijvVD3ARGt/64dK1k5mytksVRXRYB3m1P/2SazbureWo5W7+5+lwK4N4DqbxYrbcz82Y6IF7aZCC7iK0j1XtuTptd7few/nGV1mbhVfgKuCw/OwhVTtGiY63MwmMUZa72hoWVeg1RzE8Fz9w9k3fmjO2MplxK1q7Eka4Nkk8t5MKj7JvmsFYQ4E+T16jxi2gDVksBvK+BMDOCwq0CzJ6ZInruE/VeaPeo5ktKShbdPAB2EqdStc5P3bovsYPIQF9rzOjHQpCXrxeVjMvH/mFJdPuzNaKEjM/Gy85F8VkRPBFYJstD/lyFHhOJT2ES3aux5qyrrcl8RhBWKW3YrnE8oQ7uIH1AJtDiKiBemGNgRIevuFs/dmsIpShJz9yRbyojts8rDcKiQIJ0BjvP38ko2qHRIp7piI5WUNpm6m4TgPweqKk7D/Q==
*/