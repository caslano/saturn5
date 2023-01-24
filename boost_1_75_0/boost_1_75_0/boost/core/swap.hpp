// Copyright (C) 2007, 2008 Steven Watanabe, Joseph Gauterin, Niels Dekker
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// For more information, see http://www.boost.org


#ifndef BOOST_CORE_SWAP_HPP
#define BOOST_CORE_SWAP_HPP

// Note: the implementation of this utility contains various workarounds:
// - swap_impl is put outside the boost namespace, to avoid infinite
// recursion (causing stack overflow) when swapping objects of a primitive
// type.
// - swap_impl has a using-directive, rather than a using-declaration,
// because some compilers (including MSVC 7.1, Borland 5.9.3, and
// Intel 8.1) don't do argument-dependent lookup when it has a
// using-declaration instead.
// - boost::swap has two template arguments, instead of one, to
// avoid ambiguity when swapping objects of a Boost type that does
// not have its own boost::swap overload.

#include <boost/core/enable_if.hpp>
#include <boost/config.hpp>
#if __cplusplus >= 201103L || defined(BOOST_MSVC)
#include <utility> //for std::swap (C++11)
#else
#include <algorithm> //for std::swap (C++98)
#endif
#include <cstddef> //for std::size_t

namespace boost_swap_impl
{
  // we can't use type_traits here

  template<class T> struct is_const { enum _vt { value = 0 }; };
  template<class T> struct is_const<T const> { enum _vt { value = 1 }; };

  template<class T>
  BOOST_GPU_ENABLED
  void swap_impl(T& left, T& right)
  {
    using namespace std;//use std::swap if argument dependent lookup fails
    swap(left,right);
  }

  template<class T, std::size_t N>
  BOOST_GPU_ENABLED
  void swap_impl(T (& left)[N], T (& right)[N])
  {
    for (std::size_t i = 0; i < N; ++i)
    {
      ::boost_swap_impl::swap_impl(left[i], right[i]);
    }
  }
}

namespace boost
{
  template<class T1, class T2>
  BOOST_GPU_ENABLED
  typename enable_if_c< !boost_swap_impl::is_const<T1>::value && !boost_swap_impl::is_const<T2>::value >::type
  swap(T1& left, T2& right)
  {
    ::boost_swap_impl::swap_impl(left, right);
  }
}

#endif

/* swap.hpp
Xte2JKy3/CX3elbhObvNmyDTj3CZ+4QbO67swW8J5xRdel39uSqTvSyMDRQd3ppkMvPUJ7ExEg6PttQMfaqN/yE3vi6RbhxitiSw6lakV9GvfVQr4Cgi0rZTK7Bd0OMkMDI4GTcn8+IFS+b6D3Bs5ZaPs3DVsWpyxYRv9EkMKHd4wBSYDvuEi15QC5wrr4fEvosKn9+EB7a8HdXgfCstKr2+wb06Cc2U96PTka/3mhnV+0w3Bv1Ft8HJ1Htca0A2U7x6tFR20DdQ1ws6quVNvDvixAv2Uxa7G/NyomDV1sQmYKRNyVLjrefzty7yRKp1vWIxfmj9gWK7GqbWx2uZLEOP4cz2WcrPffbVUqNyQd/Svi0NsP55DP3Mbrpal5ngGD1A9+eI15HuaIdHcjBqY4oGGk1mFo2h+Y4oxA1xOzzLju3xrvf6Qoxz8/d/w+/DlqqnRwr0yhwpezQaCeltZAmJfcN7z9CBcLHPVdfGgAUD/qkpZoXXoQJ3rLLr822zxTuF8DTXSinaTRP+TbVgPXvMydt96M3WuemGs1zP+3tjFhzPQmMSBKP3YIEhn0uzVwvkbSDnRMkGkufsGjvqM0EmgQ3qvHv7jslpEizVXMrufEzOj5s6QRVDw52PmZ3rqsz+MLNfN47005NQ/2nwWi+9tD3sCRL/4f+YVesr1lfDX2EsMOtUpKqyJXrj5sYZvWe71lKFR5G+dOLS
*/