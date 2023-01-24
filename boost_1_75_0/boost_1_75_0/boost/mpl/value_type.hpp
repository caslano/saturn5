
#ifndef BOOST_MPL_VALUE_TYPE_HPP_INCLUDED
#define BOOST_MPL_VALUE_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct value_type
    : apply_wrap2<
          value_type_impl< typename sequence_tag<AssociativeSequence>::type >
        , AssociativeSequence, T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,value_type,(AssociativeSequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, value_type)
    
}}

#endif // BOOST_MPL_VALUE_TYPE_HPP_INCLUDED

/* value_type.hpp
KifmDIcaYWU+0dMxqnAZ0tdUadkyQgL7wSXO327ArmC/kpBnxgBDXnnokQlcB4pojw8/pI3pWzrXsg2KqlqUP/KMLO1GxOzDLFPre+jCD0v8zieW92U6q3pQg+i39Y41P+A7myCJh2mU4yVG2S7lPlfKrAD2roAGU+7VhdmwI74ZtfM7yjxwsUtiCTiuBeW44Lbt1sdKTKHEFG7xenf6GjP3kHK2b/pX2huqxfujhFtUEXoXpVsmb4PF14iHjWD/7B/2wMikY/kzQaAyoWpdTCNt/BNZqSimEOPIRq1uGNHB+9uUaS1dl6TJl8IPtildg7Hci6LG8zxst03dXQUcc3Vbr5jLbogy2zlHAomiKmSfodx+SW8hnTLGJcAi4Gel91AhmSD9zchqpNvAxHPSW6VnAk+DQoc54DRwFjgDnPNQ2MlL+ZZAoGMBt2qEKeohcYJyBMw7ZbnM+7qmlMUtO45tPOkx6FGcyjeZHh7MT/CdxRwbbRinX8ig92kWAJXjrO7mH7Mg41ON3S0Xt97TRKVS+8Owlitmk/looy8UdUjLyrAU4J/OPaRpX6+Zk1C7slsHOjX/xWttG7bq60Q0xfDJjT2dheDLomuzzruhG+kNByrtxN+NEqI6LGAtRoJc7nz63fpIrBnnZT68iaUDiyc53uoG8tgDTExAWBRZjmST6YUje4b6PUnDxz226JNK8FFPMMUAdn/qYZ40
*/