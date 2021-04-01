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
rg8zK6w/tZOFn2Zk23XbfsYxsjrQ8fNlIG4DbceZm//cC732+JUnuteyNQMPgNOBTuKucm57ANwS9Oz9U9xuZFAinRJESUTxCh3uqqoHFxuE+KZ25YwFdcbA9c/EMbt6AKQoxn675DqUnuMFs72moagKWMirzIvESFmjlA3sURuu6wMV0+wD0m6FJJIrE9Ucr+tlsCMkMrEHVwoKiDfWdD4K4Flg9yiMa/0Dn6N8U/qNRP9uwYA5sLNojSSVSdcJLSXJ0QY/lxufTXLkvUwPy3m8FiAsYUdQMxEe0E+udjcN0sz4+T6Q52J1TadG0c2pUflAqel5fP/iqgqWhuPQfu3QjghIurN4iEh4C6+O4u2iUUEm4kMdhD6t52UkifVUG2N38yv1dEFsOJLx7NMVZhW5yISz7cWx796x+kFhI9g+tJCRRGx1WuOr82MO0YYi19wOYFS8TcLUryfvlXdd7Tn0yG+0TwdFYg0SspUWhrfCKCA1CVsjXZEM+KN1zvDSD05aTU4KfBe9E2PATzAAQBNQCHQwJlph2gYvSMSah5w1y6slnPMRSGnNyw==
*/