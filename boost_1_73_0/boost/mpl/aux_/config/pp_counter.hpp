
#ifndef BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_AUX_PP_COUNTER)
#   include <boost/mpl/aux_/config/msvc.hpp>
#   if BOOST_WORKAROUND(BOOST_MSVC, >= 1300)
#       define BOOST_MPL_AUX_PP_COUNTER() __COUNTER__
#   else
#       define BOOST_MPL_AUX_PP_COUNTER() __LINE__
#   endif
#endif

#endif // BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED

/* pp_counter.hpp
VxTmhuP+0Gi7WI31WJ1NeBhbsjZPYB2ewbocwHq8gPWZzoacyMa8lU14F5tyFpvxUbbgM2zJZWzDdWzHLezAr9iR22nZ8D4feRPaKQcJ00P6Hwn11aOsx8fYhAvYik+zIxeyK59nTy5iPy7mUL7Ai/ki7+EyPsKXuIbL+QtfZnTee5WluILS6WAI7+UJ7+mpwlOFjHCdNC9cn85nDT7BRnySLfgUW3MB2/NZnsDnOYCLmM4l
*/