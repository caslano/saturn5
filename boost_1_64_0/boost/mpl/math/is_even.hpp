
#ifndef BOOST_MPL_MATH_IS_EVEN_HPP_INCLUDED
#define BOOST_MPL_MATH_IS_EVEN_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
namespace aux
{
  template <class N>
  struct is_even_base
  {
      enum { value = (N::value % 2) == 0 };
      typedef bool_<value> type;
  };
}
#endif 

template<
      typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct is_even
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
  : aux::is_even_base<N>::type
#else
  : bool_<((N::value % 2) == 0)>
#endif 
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_even,(N))
};

BOOST_MPL_AUX_NA_SPEC(1, is_even)

}}

#endif // BOOST_MPL_MATH_IS_EVEN_HPP_INCLUDED

/* is_even.hpp
06jjr4NKLYnC01/0UHWnAYevEgKXl5OCkUZnSf6FPAzyXYNhrfE69K8RIYtT3nvl473aNkl6KtsGRjB8W35MkyZUQhImB51z+/UhFYsR91S/KbrKE9ytdwhRff1cZ9rLpMpIT7KUTVH66VGtZ+fuTag2/DkWX6sKVF3I4h8mMPQ5vrqrxLSrKShyqGA+gBwZKKVCV1+FNp2nsqUsyR5MGTQxvlos6wLgnlKSKFAcE99Y2ZaoSJnaJE/D5hBvddEgSpHEyPQIoiNtL1DTHiCJIKuNQ8769xbco8T3nP8KUX9z3RMUeo/a7uniQjq8bfA601uUyFshzn68deXhYFBxiNoPi8emqoZSjk/MAojsAYLuIfnjj4VluYGT9/xFIIPXLqSmInEPZTBbjnFScWqPFCt98dclB20+WR+0FUfX6tnAFEoAm/jbw6uyTQv/yAnmT2c6tpBFV36LrmdWJ+UQ/etgzD7q4yxYt+0zTFa6bj4agIe6MPH7X1E221KxPFQnhF10+BMFnm+THroYIcln5eh9Kr0/p08xl4AaY91wi+Z09K7wYv5UKyqt6w==
*/