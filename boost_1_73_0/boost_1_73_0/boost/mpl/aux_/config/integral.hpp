
#ifndef BOOST_MPL_AUX_CONFIG_INTEGRAL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_INTEGRAL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS

#endif

#if    !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__EDG_VERSION__, <= 238) \
        )

#   define BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC

#endif

#endif // BOOST_MPL_AUX_CONFIG_INTEGRAL_HPP_INCLUDED

/* integral.hpp
5eJ2Zbm2Pwa+pS6jGKGoRds+pcek+ApKtT54PQOcigP8Elzg3+DT3EjsK26UFSWCSWfSfwnUnzLTd4YX2jQq/EIxcfwVmyLbgakMiExjA9S9YPyBbggJYgX9Nle6z6LHvS8FIJ61kqqcMoI/mWN3i5dGo5ZTrQ7hL26996+PEJIdwYPLPcvvsTuiic/WtB2C3DaldfZ1fhtfL7702ExKrMn8wfrQY0tTek6RKpRmbkP4jFjzWVk84okR+FdyN9NOY/yH6EAP426K2xUhS1M5SOQoGfmDZDQQiR14QZYGA5m4tkwSKcYjx/UDTIKUDGPPSVMf7cR27HQ4TLB//j3t+K5ENMWk3xV839K1qlqTgLTHCQbO2A18B93Aw9EAg2TkjJOBK9xsmI0dKQUd83AYjJxBKgLpjVPpSmfoD/GdUr0ZhJOa9OOqSMIyf67JMzQvCi5fXxQ9tm/3Y5tG1mvvWscvnz8BUEsDBAoAAAAIAC1nSlIj5DtHJgMAAC4IAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA2VVQFAAG2SCRgzVbbbttGEH1fQP8wYeGXwBSpS+WIoAUItpsYaS3BUvJSFMVqORIXIXfZ3aVl9us7vOhSJHADJAUCEBRndy5nZs4M
*/