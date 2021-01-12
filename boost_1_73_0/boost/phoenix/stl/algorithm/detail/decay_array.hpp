// Copyright 2005 Daniel Wallin. 
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_DETAIL_DECAY_ARRAY_HPP
#define BOOST_PHOENIX_ALGORITHM_DETAIL_DECAY_ARRAY_HPP

namespace boost { namespace phoenix {
namespace detail
{
  template<typename T>
  struct decay_array
  {
      typedef T type;
  };

  template<typename T, int N>
  struct decay_array<T[N]>
  {
      typedef T* type;
  };

  template<typename T, int N>
  struct decay_array<T (&)[N]>
  {
      typedef T* type;
  };
}
}}

#endif

/* decay_array.hpp
/gpn842RFXR52QjiQu7Xhmxn58t5ZFXwt9lAVW9HrDMRfhVBHpDXrpypLqiFvNB+pT+6xR3u3sbgyBWKzskZaBh9tkAPo9HHN9z9tiYCL0/+CufbjZGX6L2c43Pn00vlfHI3dXAQeoSOnH8I/fNzD1GQ3KVw5HsJd+8/Iv/kRuT9nDjxjCE7uH8rRh5dA3icohP6Moyzy17Ej9iCscjeKHKs29YgZ8CX3Pb3iQFaonvYoBld
*/