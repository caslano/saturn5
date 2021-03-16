
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
nhrrOcakLX6Ym0K95SlUsWspRTX681KTlBpLZI0lssaTvAY0rK82gkqhryp+q2SNVbLGOl4jQ2MZz/JS13Yxa6yRNdbIGhvMGkY/RpsVKL7BayyTNTbxGn011teokaXUaJI1mmSNzSz+HncqNR6WNR6WNbaz+HusUmqskDVWyBpv8RpXaewqo8b9So2VssZKWWM3pTIzi+Bf589keXCBkRko21Zi1c6cwVqecn9JONPtXoFBOsKoH/JG7WMeO2o=
*/