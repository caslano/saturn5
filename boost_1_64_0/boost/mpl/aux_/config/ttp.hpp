
#ifndef BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
    && ( defined(BOOST_NO_TEMPLATE_TEMPLATES) \
      || BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT( 0x590) ) \
       )

#   define BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS

#endif


#if    !defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302)) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        )

#   define BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING

#endif

#endif // BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED

/* ttp.hpp
3eXDmV953jOyXCQV397W14JnNLhY21PEnvkacxSMFgd0cT5XU9o6FlX/4tSdu1EyXu9T67bGG8JTph9h8spa+QKvrri5Wf69RJvXi4Rfw08xy6uMRLELdhMNPtJWIr0IZrBke9Cl6KfU3PskvcsEXpxJhGE+D3EcfuDLH+BWvmxwLMWAqeq9QCiTvJPcYZ4h4HT4Isb6hz27Ip05qSkBbmslNAeYuM1rP83g3Cn4dYrtCTcyRbM+6jfftQpntk8mn4HtIHbeZMhsooalNI9kpT7dWwfIAI3r2n1rcJL22p48yOT8r7l/C5UUAhxJNKERXWUAV6OAPmcv8JXOPduOt23JJOqljxeKFzKxNfOPI1aDMaqWTcWv+ePhPdsmIw0rGruSa3twPA3EhVvqSXduCOerBDlW8VPtL2dO8H+KBZwqY24hOJuU05qVSr3DvJPYzQvstzYXUcjTGTc9zn8kcQAMDJhBcvnO2eEGyR020UbzisJFyu7DygGSASUdtBac3sWXS2o1mKEjQ617KWRH9L0OARfCjBXCfUp9p1nEA6jTuwfvBzgMdcAuIQ==
*/