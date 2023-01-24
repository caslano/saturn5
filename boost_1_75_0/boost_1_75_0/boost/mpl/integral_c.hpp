
#ifndef BOOST_MPL_INTEGRAL_C_HPP_INCLUDED
#define BOOST_MPL_INTEGRAL_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/integral_c_fwd.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__HP_aCC, <= 53800)
// the type of non-type template arguments may not depend on template arguments
#   define AUX_WRAPPER_PARAMS(N) typename T, long N
#else
#   define AUX_WRAPPER_PARAMS(N) typename T, T N
#endif

#define AUX_WRAPPER_NAME integral_c
#define AUX_WRAPPER_VALUE_TYPE T
#define AUX_WRAPPER_INST(value) AUX_WRAPPER_NAME< T, value >
#include <boost/mpl/aux_/integral_wrapper.hpp>


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
 && !BOOST_WORKAROUND(__BORLANDC__, <= 0x551)
BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
// 'bool' constant doesn't have 'next'/'prior' members
template< bool C >
struct integral_c<bool, C>
{
    BOOST_STATIC_CONSTANT(bool, value = C);
    typedef integral_c_tag tag;
    typedef integral_c type;
    typedef bool value_type;
    operator bool() const { return this->value; }
};
BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE
#endif

#endif // BOOST_MPL_INTEGRAL_C_HPP_INCLUDED

/* integral_c.hpp
O5PIWVzzcUDyRyvmqgtJQL6pRo3Q4cT8/oknvshw2o34RH5YShiZ58zu2LSlTCiXKjaN8R/xSsf+2NN35LQXIQe0v1OKRGxPS40dAf+oCjcXz55VpvXUaD/InWIFxvhUCrm2t5STFIzZ1bz8hMiqoT2SP6XK/9FhhgeEN3eqkksnLbaw8yIRdtuZNu/GgjXCyCH1R/P2/EGtJHP1cwv2PSqRhHRxGc1XCL09FY/sXMbEJFfn1cTZ1pIX7hTWltXWlNbh1aX0A+5CjU0m8Gvw28vOT8EvtGVB8jHvTg3buMT3KPwMkwZwr6vy2Uul7XbDoQEBC55lmYmHuxjt0zGOms2Le+JZqbc3dJwZuIN/pKcEn7UzcPvW3O3XGxQNFOSk2idLcTOypG8e5Zzn7Fb6FtVutW9kwEztOV2Vvxpml7nUQcw8mRNER0zPm99L7mL8sXpk7eMNmUoKVvq9vmY0nx/ROxf7ptgZV0W2XCy0k6STZJokmuQ3TdPeDQ8j0ZOxtC7ThBJ1+An9pHWkBH3WRGFvciPIxPGnpGnXor1O6w9cOZDoV+1RyWIW9M7B/lsoS6/oiYK1ZAEDW+5UYdZXb8Qx+nkIUqU9cqWJZJDG2MatmO9VwuZ0i0IfglPfOHDfyZK5o7u/4kWlsckNPQ9yiKT/g5zwWST2Ds/Omz9C1SpMRYTFbd/VAgnevVvEc9rmWkKH/ZC7wn4owoXK
*/