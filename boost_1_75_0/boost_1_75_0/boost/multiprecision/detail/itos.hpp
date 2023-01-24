///////////////////////////////////////////////////////////////
//  Copyright 2019 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// We used to use lexical_cast internally for quick conversions from integers 
// to strings, but that breaks if the global locale is something other than "C".
// See https://github.com/boostorg/multiprecision/issues/167.
//
#ifndef BOOST_MP_DETAIL_ITOS_HPP
#define BOOST_MP_DETAIL_ITOS_HPP

namespace boost { namespace multiprecision { namespace detail {

   template <class Integer>
   std::string itos(Integer val)
   {
      if (!val)  return "0";
      std::string result;
      bool isneg = false;
      if (val < 0)
      {
         val = -val;
         isneg = true;
      }
      while (val)
      {
         result.insert(result.begin(), char('0' + (val % 10)));
         val /= 10;
      }
      if (isneg)
         result.insert(result.begin(), '-');
      return result;
   }


}}} // namespace boost::multiprecision::detail

#endif

/* itos.hpp
P+YaUqWyVDxUoL5bKooF0Khe1W/kqc/pN4hrHsazakc6Tb/hKfg9vLpEeYgidvdBG64qUWCG54s9V4BkTIL2WEFIZ9HVlTdy6/nOnZptmoaCL5umoYUsUe/vSRK1He1Fut9opU9Df9toTEOvzjamoR1+nobSDG1l7xxzAeYdXJopNFlfzw7FNNdcY+gtq+c0R2/Z+q2ut5DKgvUCbtVnmeNTuE6W0CTfudGkSdZ1Skuc05gWSftAc5pjHOv/LSkGaWMqTHlV8L2DTO+tb1BZVxJeEDU420LfX9Kga1Ao5Sy9des3urpKmqqR1wM01AJYTRTGygHZKQJ5vtLcrnsA1b8KVD/7T0Y1ehPHrmdUv3Ahofpq2tZ0b2vhEDaUwesZ1Wmau2KWQHWaemgByJO/8lMSikbJylnXutY9NPcH8yhbZwqe5ftP9i7qE/R8BrPJlTM7yRtt80F8Y0og13Pv3x25fgKcVEdo7sXwTH7AJvsrrHC6VfZXWvNTLu/heyU/kICEXz9QA6NvGsjT/uXIkJqVoWCROF4xYF7q/eQP/TK5UGvuyFkmkn/sRYZDDi16GQ5PxbJ+ejHBodzpEILxmnUMhxzN/U6xXRcM++fX17y+vachzSs7l0qljKrJDNwRl6ZwfCDSBdV7ShdldTAYLx4r2WOcQ6ZSid7bxBw5Hv85y8zIysF3WIRrKb3rnnt0SslpQit74kBIcTXl
*/