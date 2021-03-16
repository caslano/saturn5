
#ifndef BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED
#define BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/lambda.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
    || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
    
#   define BOOST_MPL_AUX_ARG_TYPEDEF(T, name) typedef T name;

#else

#   define BOOST_MPL_AUX_ARG_TYPEDEF(T, name) /**/

#endif

#endif // BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED

/* arg_typedef.hpp
QpMoNMgzrj9OcLHrPwf+FlIIx5znUwidPR643CBPb5GnT8vT02NmwHRRzLx3bcy8tyVmBkx3y9OH5ekPITSTQniSngdMibjRDC4nbUVPqFTcyC6LG1lwtNQ0Cq2H0FwKbYYQ7khNgI9nDpjfGuepvIS6N242n38zbmzwvIRejRtr/ApCiyj0XpxnzRMqnjCyYxJGYnbCSFRC6CoKbU+YmN6WMDHdJ7L3JXiaOaHaBXtRsA8hdAqFsrLMgM64F3g=
*/