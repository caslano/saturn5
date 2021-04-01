#ifndef BOOST_METAPARSE_V1_FOLDR_HPP
#define BOOST_METAPARSE_V1_FOLDR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/foldr_start_with_parser.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr : foldr_start_with_parser<P, return_<State>, BackwardOp> {};
    }
  }
}

#endif


/* foldr.hpp
4wgrCXibyNcrMQLHnvpWntr9Is/IyVH4pIWMOH4oiNC/tCjy+KcqOxRt/D75Ves2+ciTv/nzo4EBLqJje3ueOnChTiNBi1TlBROMCQDSNm0PFHczQ4fo7onlSA2uOC6FgXfJe/5c6/S6goKxjqZXlOug1tuY9F9bWqwY/cMGgHchOsaMRheC6ETngmeY32O6ag1REl5KyOq8kHzIJEFBdMXnbJ29zGtLAV/Z9M8OoTlCssTNrBarFU9kkreox3iD5N7suarWZh2tZDSa79iK8H9Iwg89TabElypdrkjRq+25JypRGBEo1niICb13u5WJUjlcb9DY8fkZ7Q1slovajs9Qsho7pMA8A0mKIO+YoeoANUtVGuiFaT3uKEnYRlLaUPTTwwlAKFZemuanKsA/nrxr1ueqfTGtmm7cyb369V28TIFHW3YXsgLrABZtVe0kZtxzjKkl6/BC+rY8iLSd3OSGFkHw+BpE0BPi/m95YP0i9F2rQXptkOY33IDUF6wT+8RG0fGh2ct0BL4YL8IZ60bFon5ttTKlliRcKvieEiIsCmzR0MkO6Q03rw==
*/