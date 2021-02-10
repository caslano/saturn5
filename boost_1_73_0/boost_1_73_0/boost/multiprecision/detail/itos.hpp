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
Q/OCrtHbaXazbtqcUCjk6vK0y/Kr6W/EdSn6ytTCc8krmNxO2GYeYWWtFElVq38Dh7PcyxKo0qbYeoUaJu9soWLY10WRzVeWx5+fRMmbRBrQqYav0rL3LT0tC7pp9EnEKIOhwo284DjEBYzX1eGaRcglXBCXOhovyDC/H478m6w9VH+XkQKVX3yOGMgOJlmCQXeurRm6s2q8e6KrfePVEz1s0XjTfGrfF1B7EGJrgFeqpM33+xjc+xsvJP2ywcgybbxAIjWX/fTbXja1d/bkwwyceBN2Y8g8KzH3nAMdlZh5zuHdRUDpZvkdgHSNYYCKEhQYHVWQ54I2k4h+ukcjYdUf8cCLNhun0zOmY+1VcPw1o5pnDiYwFTc9Jvmi9Bh6Aafsfuy7k5jhlSz8ZIPjXzMMkAcekncqYtOO70VjXmuRsHx+HAqRwQyWfaI3pqHFFDhQEXUxNmlyxgJB+vkpIvPSQ860x/JTQhrHdaxpII0uHm8f7wtoWY6nk3FYMFeQa7gdY5xf6i98EEOpMDO5W/Y0Rva8gXFoDS8f2UfuAZM5lYQMj+tE6QWEHC28TzLduQzw4ihjJtuxaB109vcOQItud1vtQy5ttzhhke3rHSi8FbYHTeCdniLTDV4x+qSGEQUyI8dILjUosYV9
*/