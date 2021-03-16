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
O6+isaYasfTiXKhVMzrSIpx2F8xZfKZ8lWd/Z0TBm2pnLfSm+KoaPA0/UpLRBN4UT0N1zZwzrQp8z7YAfrqtGFJnVAq8EWfKU+U7FwWvrZgPVutsJen3oLLCW+PzVp+tMLVY6BCfCznyvgiBZ9TCtJg421IoHd1TV3dO7lUV7mCdaSW8FXNqvD6YWc+2BPo9hv5dMR+WV8GK4TXfX6ji7x/gqxmRrDDuslT+Gkoj69at12u7P9m14w/ZO1dOC+8=
*/