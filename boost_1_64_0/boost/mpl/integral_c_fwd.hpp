
#ifndef BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED
#define BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/adl_barrier.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

#if BOOST_WORKAROUND(__HP_aCC, <= 53800)
// the type of non-type template arguments may not depend on template arguments
template< typename T, long N > struct integral_c;
#else
template< typename T, T N > struct integral_c;
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE
BOOST_MPL_AUX_ADL_BARRIER_DECL(integral_c)

#endif // BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED

/* integral_c_fwd.hpp
YSlLcDN1N65YfCLq3zx6GEoG/2AqGjoF2yHM/xfiJNbu9vFNH5WjbGNoFTh1YMN2sDVsJ00+m413uVQm3WpfCsVRBK3rrm882JaJwzQsZkk5frb6GRFUKDBAUHEwpeeBnJuBACLPbZmLMUKTXwNrPQGyxuIIbS7cFLtObCFCFG3lYJY/3bAKUBEmBWiwzWg9rFU0Oq0xI4JXpSbRdWfSFfP4zZmlZ6ejZEWnFpul2peb521gC+O5QrBPtuJRbuO3aYKy3JunPLcYZCbatEl7PSX0Irw6hEFEXFjKAYnQxSs3M3IzvTTFvZISf2Xd1yWZnRU5AiA+XHgxLghtsNCsChVdg1r9ZKtIHlbSWdceS73ABeLxHyEeY/Y2JKeXexBD6s8k8yBne4BEI41pqo5wjPmdlyr9gXCmRlFjpTWCkD3jDWr8S+FdaBa56ALIHghiPnjQc6dTdsIoIiz6STO0B8BgO/dfxeNpvhLjPXlU6eKriFk9njEjzUZ0fXLhrDa8hbaKtgKe0nVB+ijjC5JbgPuTXs99ogKy8UaQWxi0ZNBw4MEez3XoQAAAEA==
*/