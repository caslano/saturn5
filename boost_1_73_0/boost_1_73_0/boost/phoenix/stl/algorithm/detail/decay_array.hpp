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
DryJ9oPuQFxZCTW1CIzp20D+eXxLZVmCKJbJk9EzNDT4tK7XO4qpQn0AA9i9J547fYvRlDkmpg7w2LngsapBU+YV8kmmTxdkTx5MlRlwsT5gHoGdvIEDqimF40lgB6f7eN/x+uD8wEGqh26aQfACyTdMmHJ/Q7ivO5i7rYUUNGA0i9NslEFSD0EIYUZMFt/78qswiTKXtAnVAw/YKxhaNEpIM0y27XXA1k5aHiG9PTn+bXh2enh89LrNnJfWDBPykxo3X5qZBXVu1kfk0j5db4rI6jr97uwC/nG2mlefnI/4d6vlbF2nWwV9V1haWQsRFCi3XuHNGVoqKJK6b4hG3l9WdlCcRY6InzCzE0fYRMGRzMd6ccDJweEdIsSfPKJypvBwWRDlIOPpTbCgeqASGUrwCdREFHNUjWvwA7k1/fmhJoMoZScdUxxQRF61lGQnm9fL71rFbA+k6BbU17mu17cH9Z2+JY3417aL+kDiLPIkwhvoZ5AnkC6laB9cEGXX9wOs4sAmYKTTgp938H7lJgUbFuMV+D2gnoCgY+2q2+2quGuDaC8OLK0dcMZNkbBYQaeqKE6RBk9VBl6+wm/eLKYiGIxZdNzuG+jE0CfAI+Ncr3SdoPZTVYPChjRo7bhj7WgEp2pDF4IoLrRd
*/