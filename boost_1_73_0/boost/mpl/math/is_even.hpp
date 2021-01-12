
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
2xZr/ltCUSbzOIP+/d0i6Xvue4yNeJadSNGDb+hDL92Hgz3OBdSy7lPXFRi+boZEA4n+gUTPVuu+654MjamATNpBbh3RCLfMuje82PAYeub2rQ8Xg8n4WFDGvksNj8Qw+jrumPA3Cz35ffF1j4BcukeIRRjk6qaH0Xt0Q7SqMu6Nl8VbZ9+/VFZFGuPmNsWN3ovh+ewjDbe/vsyMp+Os+3GuEW22T9vYGKmMU6AhJyKbmitr
*/