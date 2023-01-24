
#ifndef BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>

// MWCW 7.x-8.0 "losts" default template parameters of nested class 
// templates when their owner classes are passed as arguments to other 
// templates; Borland 5.5.1 "forgets" them from the very beginning (if 
// the owner class is a class template), and Borland 5.6 isn't even
// able to compile a definition of nested class template with DTP

#if    !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, >= 0x560) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif


#if    !defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__MWERKS__, <= 0x3001) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
        )
        
#   define BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif

#endif // BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED

/* dtp.hpp
XZECUuqmC9o7t60VYt60um6tFEfFFGlMXZcUWNjyqv/JPnbtLfqV/GjhdSvv/UUie7UjcpXWA5P40KvsOb2QADAkLlw3EH3nSSk7vkBJXBWxwwJLIG/DFJGMDYlt4wtK94cNJHhZYMCfde148DmDqTyrXmqyqkndp1ZrmS4qvYwKBW16Qnq7q10d0K4Ft42eM1/anwg5q6C6miQA4+5OcHcI7m7B3S24u7uH/MFdg7v7BS7u7q4h2MXdubD5d7dqX3Zrq6bOqfNwunumu2a6a6q/tfObuzv+QTHh70oXvf780iDl1b6ohnZY9nmZlOPv8ReFYPoeIjwj1m1naYcm4oZ50470Cw2Px4X4OUw/QccCtObj4e+OMj2XRa4xSMEiENkBsd3KH8o7vW0B+ELbxczrgWju4kW8nxsdcTJ/KNpZU2rEHn+RF0xWkp1PZPjQFL7BCrAG244/LbyjsD2qWJa5XZ4hr7ePLnIZceyphLLWhEMd4APVjQgzk1WEcTPnNXLUW6PzTcafpmWuYhQxbeibpKY+AKqoG4rRmSqTG/LsgACzvFrcW6+GrGRuu8tatZ0b5soSu+EkJc0hRsJD+8YwFjPmYCccs9ReppVLvNbULaTy/pxej/TvmIaw2TUQ2wiGqA5QDtBPtoJfZUnH1xRndQmBcUsNB9W5NV+zV1FDphKcCUOOWpUNhzspIY8SmbCbvEnE4Kt7oJy0
*/