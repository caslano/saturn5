
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
LtnpIoWY3kyq3bxSXF0nl/doDbQTcRt2km7B2n1uJp5XvEbQdoLrzlYVSHvIOCkMc2Xlc5dOD68U9Bk9GzURFDP5pG78zVf33nxabGe8cjd6LVGf2axTUFcmHY79umCFULt0v/yHu7tRi6nR4XbX30WuW3fKK80bhYcQ0mNBt6+YgSInWq8ilzZF9uSqKygG5q+0MUYH0RbvCnsRv7k29b3fCeZmvICxot7axsSJWkNPT3NfgdCpJKVqAN9MdaAme/2zJz+z6ovnFmlXHMxt5/tBwFTiQeYBMhaMg6nG8822KPoN3mLXy0v5k1s99+pyx6pqtXR09uRa4Wg0guj8IQdkUvFwX/GesA+wwHtY+/ZRbm5DI2pQPxCmuNX1t6xbaDeCTvm/alyM/w3V5vjPrJvI1oZE8nZ8eT+6XzqzH2LVyaNw5C1wqQvFWoRUn5cn8yjMLLmm0fT8XiIG9EEmTtZuwYEz3FzepcX1eK+atoAYOkUDPi4d7ifZ2J8lf6C+hw8UAzNeBNh/R2RmFl5PT117JVkIskvfS40dnI5NtHuej6ff741PrLl31R3skwMeF/TFPi0j411INOKXXS2nIGYdwbH3PxH/tlmwm3gRfVYsBFLSNdvJ7gi0VhdwV0mUfCr5mhLCRp6LYQjX+zlQ+6Ovr1V3Y+HXZVj2C2D2W6hRVMBbuFADy94vW2pKHMwIydvXJgSY84uXdwRf
*/