//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP
#define BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

// move
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class AllocatorType>
inline void swap_alloc(AllocatorType &, AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void swap_alloc(AllocatorType &l, AllocatorType &r, dtl::true_type)
{  boost::adl_move_swap(l, r);   }

template<class AllocatorType>
inline void assign_alloc(AllocatorType &, const AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void assign_alloc(AllocatorType &l, const AllocatorType &r, dtl::true_type)
{  l = r;   }

template<class AllocatorType>
inline void move_alloc(AllocatorType &, AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void move_alloc(AllocatorType &l, AllocatorType &r, dtl::true_type)
{  l = ::boost::move(r);   }

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP

/* alloc_helpers.hpp
UhfCdGS8nq/eooHpyVyZxUaYhxXbIEk6GR4rQWRV2l45B8sk82W2MLZfLViukItaVtEPZhJy5owHbWAFZC7MhmwYuwQm+WS7ZsnU5RVgUjI/ZgbHjoNhCjJXZoPPbuoIU5JJmQVr/pcL05CVZba24qrSsBQyd2YvZ9/bAUsj82KWuvPF37BMwez7S2NgRjJPZps2fewMMwl9Dnx15y4sX7Cjp6pVgkn+pedrZhO1S51gcjJ+Dtte1fKGKcn4mncuf/KEacj4fn7ZdWcfTCvkMp7N/A2mJ/NmNuv3dqdhBjIZs/y5bSbAjGT8HBb8Wy8HZiYLYLZ7VcfVMMln22tp5ao6O2BSMr4v5TcGnoApyPjZPkySL4MphZxMlzEeFifkXI68tNbTkfF9CbLv5gVLIyvDbJl3RH9YFhmfPcVw6gMsT6hX+n8tlTCzUK/Ky4AzsAIyfu7GB0O6wqT/2db75WaJJzAFmQez8C2HasJUZH58z04vugfTkvFzD+jVygumJ/Nh1tf99F2YQehleb0t4TAjGd+z5ucfeMDMZIHMmr3505qTfLG9dv/KKdcfJiXj+zlofU4zmJyM11s/fMxOmJKsHJ/hn3YBsDgyf2bZYV4HYXoyfg4ZrkG/wTKFNb9UjrsNyxXWXBs94ADMIszQuOKaRbCCL8LjKLBZIUz61fYcPl076w8LJfNkZrS0LwdTkvGzddufYe1TI9jReSX6wHRkHsy2OV7dC0sjkzL7t1PPSFgmmQvfM6lmBSxHnCF70zBYHllpZr/eTW8DMwvz/bfX+S2sgMyNWbVLN1fC6NnbZoYnflGPYDIyfra6CaOlsAjBCrNmHYJpyOTMdjR4KIHpyWTMxiaMVOD97Qoy/N18ML2/LYx+UgqWKdjUsBVPYevJSjKLmDFoHiyHDPcM32zlrnwlLFewvxvMvwe7IKx57ED1gTAzmSvLrd0xoy4sn8yZWfr+qEuwIrJwZjv6jN0HU9jZ1uvSY1ci3ttHkOHeVE7v7f1XZETjvb2ODGuWp/f20U0ed7LeD7JcBXpvX9n1S3WYhUzK7Mb0zpNgkhL2kl7fTf3dDphe58J0ZHiP8M12OfY5DRtB5sDsfIYsHu9hU8iw1xXp3MPyXk6ApZHJmAUt2f8IlkVWg9mYxh+2wiyC9T2yYzDe+8rsf84eQu99tQ8n38c1qCZDrrLdUN2R5x7ZxTY8IY1ZFbve/e5d7Gv/w4bnMgu1Cx/Vcc8d/Pd9hxSR4W+Ww+zCf01IPGz97xFJHH7mfrGr37uo6+KRxdY/PIIMuarUy88cPe8xq2aXHP/TdEOVbM1wuxn2k36RnCu2UcNTWK66Xb06P3Pxv45nVsNuZDLvU0+Ga0JBfdoFXEuDGcg8mF2t3n0SLEfIzUh5bw/LI3Nj5j7v6laYmUzG1zTNVMGKyPyZtXrj8BYmK2kvKcus3LSo/8EiyMoxc14cNA2mIXPja36N94BpBSv9T82jsBQy3kvVgKrLYQahl+zkFYkwI1kAswPJzhVgFmHNfGNGU5iklO2+/H2m3CSYnIyfg8eXNt1gEWTuzB7GtAmDqcj4fN0cSqTDNIItkvVNhWmFer6xQWNgejJPZl/eh8yGGcikzD6qdvrBcoT5ws6cVMBMZL7MImrpt8EKyHyYHV7RYzzMydG2Xuny9R7A5GR8X6bvP7kEpiBzZRbdLfQgTCnkpMt2voSpyfiexWdX+AyLE3J9c83WXnRCveVLhjaG6cn4Xo+ukzIFZhDqlQkPewLLIsNnLN9sw+MF5WA5ZE78OnvbuyEsV+hz98P/3sNMQp8bva+NhFnISrJ64dccnsLyyRyZ1V2WORtWINjWJwOHwIrIXFi9ui4=
*/