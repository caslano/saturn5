
#ifndef BOOST_MPL_BOOL_FWD_HPP_INCLUDED
#define BOOST_MPL_BOOL_FWD_HPP_INCLUDED

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

#include <boost/mpl/aux_/adl_barrier.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< bool C_ > struct bool_;

// shorcuts
typedef bool_<true> true_;
typedef bool_<false> false_;

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

BOOST_MPL_AUX_ADL_BARRIER_DECL(bool_)
BOOST_MPL_AUX_ADL_BARRIER_DECL(true_)
BOOST_MPL_AUX_ADL_BARRIER_DECL(false_)

#endif // BOOST_MPL_BOOL_FWD_HPP_INCLUDED

/* bool_fwd.hpp
AgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE1MjlVVAUAAbZIJGBNUstuwkAMvK/EP1ggjiE81EOjBQkhWqqCgiBV2xMKWVO2DWu6Wdry93VewCGOHdsznlGkw8wlcYYjIbXZEb++8PxLVmUjMYuiZRHgcRqVydHS31lI/zok/XJPtGCN9getl2mFQlo8pmduJ2QMJq5E83udHvS7XQifG+IVvdhiAB9EqiEajHSZ5bzab8Ek1WhchZoUBcNmBddI7J07FsGrT6s70hGlI5Hqbe+uf8+NsgZp4gOW54DF7xMb4GnzybyaDGgDL6s5ZMwCxDiVYpB+uQYs6HCIjeK0mfMGvu/22KFUdQ5EQTvHXYaryM9Zm9CehevoaRm0l6vw7T1vFDorCLnD2J0sso/1+dcvPFepZRe0g2xPp1TBFkGh43NRAYPwA2gt2Zs+e0eW+0KyAr0rbBzAcAgT1jbdcNgsxvOHcLUY8znFdkKK1Q2Y9KaUfr3P7l1+lH9QSwMECgAAAAgALWdKUo1oFSodBAAAURAAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTNVVAUAAbZIJGDtWG1v2zYQ/i7A/4FVEWALIuvdjj3ZQNB0S9BlMWKv+TaA
*/