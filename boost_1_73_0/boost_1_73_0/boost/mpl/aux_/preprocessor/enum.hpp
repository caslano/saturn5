
#ifndef BOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/preprocessor.hpp>

// BOOST_MPL_PP_ENUM(0,int): <nothing>
// BOOST_MPL_PP_ENUM(1,int): int
// BOOST_MPL_PP_ENUM(2,int): int, int
// BOOST_MPL_PP_ENUM(n,int): int, int, .., int

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_ENUM(n, param) \
    BOOST_PP_CAT(BOOST_MPL_PP_ENUM_,n)(param) \
    /**/
    
#   define BOOST_MPL_PP_ENUM_0(p)
#   define BOOST_MPL_PP_ENUM_1(p) p
#   define BOOST_MPL_PP_ENUM_2(p) p,p
#   define BOOST_MPL_PP_ENUM_3(p) p,p,p
#   define BOOST_MPL_PP_ENUM_4(p) p,p,p,p
#   define BOOST_MPL_PP_ENUM_5(p) p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_6(p) p,p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_7(p) p,p,p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_8(p) p,p,p,p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_9(p) p,p,p,p,p,p,p,p,p

#else

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/repeat.hpp>

#   define BOOST_MPL_PP_AUX_ENUM_FUNC(unused, i, param) \
    BOOST_PP_COMMA_IF(i) param \
    /**/

#   define BOOST_MPL_PP_ENUM(n, param) \
    BOOST_PP_REPEAT( \
          n \
        , BOOST_MPL_PP_AUX_ENUM_FUNC \
        , param \
        ) \
    /**/

#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED

/* enum.hpp
tF2nTBUxzsf2Komz4jXJi/hjm+XA+bE/jPWyd20x6Skov6My8B4W+yzeLWHUtRRisUmyfJsuF1m2SZNdPsYifV8JYwNXnLTpio8CeGfpELs2Hoka6VpaY7AMPOgObR/gkR76J46uv15cXHpDp+szVCooUHVAB6FBGN2HRnk4IBqY+caGGZPDBUsUtP7T6ZGt0l4dyAYpbjWJzllX2opcuX+g1r+ccFcScfviH1BLAwQKAAAACAAtZ0pSVy2eBaIBAACZAgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY1OFVUBQABtkgkYGVSUWvbMBB+F+Q/HIG+lHmy3TRrhBcYXddsSxeTqs9Dlc+xiSMZS2nnf79THaeMgdDpTp++++5OmUfntXK4ZFltSktmj/2r7Qq3ZCsp87cN7u8ku33arje5/B3sE8v4Oy7jp6cdtk1PtlBegbG6Qr3/PO3RTQcynnxMII1j2PxkX5VHAfKIHyBewC/7QhdJDMlMzBaCIPcPkj1i94KdgCAycm8OL9Ue2VpR4MEWdVljcWJJruDH0QR6YklFEo8sd1LtBEzTJE6vo0J/iq4Ws3k6W9xM2RetsfXRVpkdOgHPPWVit9Z4ND5ao9n5SsA8RAxqX1sjQDfW4Rkj
*/