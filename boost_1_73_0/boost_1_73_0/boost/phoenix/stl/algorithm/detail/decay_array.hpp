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
9eyGIMZ2DtG2x0fznG4M1PdjT7WSJhGnfITvQw7/LWnPbQjmuHmGP81vEH+qXy8gXSxUfHJ2QJvbqq1BX7McSXU6lDpzjTpLqA7WxTpLqc5RBk+Yo35Uvc7T0YR7jEFT4lUQH8cR3vKGQvNKLx5liDaRnxG5TkOlpNfjfduUKLR6V/h40fhAX99aPq+GSpua/FyQE7jcAncm5YJ0NgRcjRomX0v8WHSH8yjtHTd0FDNs1U066inoc53xOL5C7zo=
*/