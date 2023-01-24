
#ifndef BOOST_MPL_AND_HPP_INCLUDED
#define BOOST_MPL_AND_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/nested_type_wknd.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>

// agurt, 19/may/04: workaround a conflict with <iso646.h> header's 
// 'or' and 'and' macros, see http://tinyurl.com/3et69; 'defined(and)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'and' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(and) 
#   pragma push_macro("and")
#   undef and
#   define and(x)
#endif
#endif
#endif

#   define BOOST_MPL_PREPROCESSED_HEADER and.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(and) 
#   pragma pop_macro("and")
#endif
#endif
#endif

#else

#   define AUX778076_OP_NAME and_
#   define AUX778076_OP_VALUE1 false
#   define AUX778076_OP_VALUE2 true
#   include <boost/mpl/aux_/logical_op.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AND_HPP_INCLUDED

/* and.hpp
WbmqmnfugXRHnW+fpQq0klrelupBMY7GPupXJJ+Pt9Rmvh0Ps/VeAjZYDjZ7ZioYs7mw63QWIXCDx1rUdX8YYc5Yo/hfRt5nrMJO2nhZDSNeb1HMOktXEEvlYzdPs0oTPy3Jz9oxeBrxPMPMxJX3IBJWmQ/XGHdGidmljW61BkkLpy3umc4ItlnGDOcmjYxrhD3LnokxMM35lrF+Vm+YYhSuQbX4WbqOOnqpAGoSLUSfMW4Q5pNSK96J7b3f3pt1b+zwfLbbMHTdO2FcdV6PYiBq+6sqd7WuIZ1jEWQfueF9MQOttLUHdahAHQRFrD85LVD3yr18rJPeJ605xT72S1zraF25TA4UkCHcUe3rzs4P9q5dcP4ate9HumciOBD85VMkk5KgFkrlDx1N9sEGUdGWVkbdXGbFdGpzym/vNaoTIN8isZ2EXIp9Vcl5NN77SM4Jp8IVTCZmcGjXR2bqvO/M545a6Ut7g11EUo+L/97YzyhhtiMGX8fb6uV0usr5LbvRG2+46q5HP30KmvzgZjDPQiEfmP6XLwyWw1K/Dmm+3U40hlQvcWAXwD7oTTF/EqfLTl5h14dqer7PEGGHLMAYBnh2SgToWmPWHVY/b7QVIS5jkAKMaj66x10WsR1O9Zflx+ZYmQTZVVNdk94FytvMLE5tNWFf04mMs73N6vuyWzTyZVuijJmc2NfkVxnyscRQumFCc9GP8T+b
*/