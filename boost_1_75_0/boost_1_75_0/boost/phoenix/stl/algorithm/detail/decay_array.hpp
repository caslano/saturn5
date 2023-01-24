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
VlGxaDkg9AfF6af5kA8SLB+csPz4SI8AdNdbv39GPsJfArii2bP22gp4laJWdHOFSezWQZcGu/a/yDILeyfD9gktgs5+tNawak/xq5bxLduneS2A5sMsTj1PXWyqtlTV7Poi52OzOiCetpiu58tN3S/HHqNqb71ta7hbbtjNflxfkDGFFEEeB8Q/SIIj9/GE6yd+4LmdENAb9wTUvYpv/cXI5CjX/K0lEXI2djAsPSw3+vyWA5fNe1MA//LFkFbSEosNUSv1YXDO9CyPl/QCK0l/V08yP5k9AaNt0U7NBkWpC0JM0CIRPOqi1u4ZBTH0ehaaWN7gA3niWkMGoZ75BfsyJZ29MuY7CvnwtkNuTz7Y/5ObMzLukRkPe2MaQfUF4gr1ifaWR1uMzLH6H9rbJhXlVGfPdel4ufPn7CQOAZHP2Yn/CAuZzbYIM86D9SrD2AlmJPcxMzjpEJuuA9cHrpd3gBR2d2+7SO86k8czQBjlw6rRxSGcXaDEk6KHkdMsOCtOzuOM77GayiK1aeBZ8exM10FDBV+tEndVlxMjw4Amr3QO53MYjlJhHwwnKq8k5eHGmdwKldl3CaKPYAvwX1xuXBDACU1OKb0t1b61o1+1sbKXx0rYpJlXOjx68RusWbmKnvhitkrV5YKdyVROj6AFc76NTMoQ2ZvBYWHvlwe5X9NU9F04K6/bfXZ/znfDPnDTb3sNZCvLiZno
*/