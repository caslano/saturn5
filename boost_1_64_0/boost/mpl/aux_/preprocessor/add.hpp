
#ifndef BOOST_MPL_AUX_PREPROCESSOR_ADD_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_ADD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
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

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/mpl/aux_/preprocessor/tuple.hpp>

#if defined(BOOST_MPL_CFG_BROKEN_PP_MACRO_EXPANSION)
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_ADD(i,j) \
    BOOST_MPL_PP_ADD_DELAY(i,j) \
    /**/

#   define BOOST_MPL_PP_ADD_DELAY(i,j) \
    BOOST_PP_CAT(BOOST_MPL_PP_TUPLE_11_ELEM_##i,BOOST_MPL_PP_ADD_##j) \
    /**/
#else
#   define BOOST_MPL_PP_ADD(i,j) \
    BOOST_MPL_PP_ADD_DELAY(i,j) \
    /**/

#   define BOOST_MPL_PP_ADD_DELAY(i,j) \
    BOOST_MPL_PP_TUPLE_11_ELEM_##i BOOST_MPL_PP_ADD_##j \
    /**/
#endif

#   define BOOST_MPL_PP_ADD_0 (0,1,2,3,4,5,6,7,8,9,10)
#   define BOOST_MPL_PP_ADD_1 (1,2,3,4,5,6,7,8,9,10,0)
#   define BOOST_MPL_PP_ADD_2 (2,3,4,5,6,7,8,9,10,0,0)
#   define BOOST_MPL_PP_ADD_3 (3,4,5,6,7,8,9,10,0,0,0)
#   define BOOST_MPL_PP_ADD_4 (4,5,6,7,8,9,10,0,0,0,0)
#   define BOOST_MPL_PP_ADD_5 (5,6,7,8,9,10,0,0,0,0,0)
#   define BOOST_MPL_PP_ADD_6 (6,7,8,9,10,0,0,0,0,0,0)
#   define BOOST_MPL_PP_ADD_7 (7,8,9,10,0,0,0,0,0,0,0)
#   define BOOST_MPL_PP_ADD_8 (8,9,10,0,0,0,0,0,0,0,0)
#   define BOOST_MPL_PP_ADD_9 (9,10,0,0,0,0,0,0,0,0,0)
#   define BOOST_MPL_PP_ADD_10 (10,0,0,0,0,0,0,0,0,0,0)

#else

#   include <boost/preprocessor/arithmetic/add.hpp>

#   define BOOST_MPL_PP_ADD(i,j) \
    BOOST_PP_ADD(i,j) \
    /**/
    
#endif 

#endif // BOOST_MPL_AUX_PREPROCESSOR_ADD_HPP_INCLUDED

/* add.hpp
SmMjYdkTWO4J972CD1h/T+Bg8QE7w+kwFM6BYXAbDIcfwS7i40bA/fAk2Bqtk2E4jIRzYTd4JewOv4Y9oHFvRunx6U3y0RZp30ybNm3atGnTpk2btoBbc8z/Lwzg/P9Vlvn/UdKf3Qq/tj08FORZrD0q2TIHoP78/0bMA2j6OPW/O+c/So0jKGPkditz/uuUOf+fWsa4G/lDmKHJCRuc3/+79+eFMo5Dme+/R8/3b5a4Rc/F7t+/4bdbOm2K3Vi8ue/MW7eMe0HiFi3kPpb7O5MPA/g8H3r302sPI2AY7Cp92N1gNOwO+8MeMANGwXEwGt4He8InYC/YSeb9R8E+MA72hUnwFDgcxsD74anwSdgPdpd5/73haTANDoDj4ekwB8bBEhgPS2ECdMKBsBomwhVwEKyDSfAQTIZTZd5/MRwMq7zrFsIz4FI4FH4Ph8EWfC9nwmnwLOiAaXABTIdXw7PhTTADPgCHwyfgOXAjHAH3w5HwEByl4zZNitvU6LiNNm3atGnTpk3bv9qO7v5/bPzvcJSwA+Ash8NYii8w+//dGsafxxIDWCT+UD9SK1IM6XJjPnWSJwYgNTBOHp+Q4g0EHHkv/sbGASobmK++xDP/rVH+v9e/jiBNcvuDj5x++1vbUxP7Pv9N8g7ndytl37o4m7RJ2orV2189TPZXD4cxMAKGwm1hbWy7STu/DHL/7b5Z/32uTZs2bdq0adOmTZs2bcekNaP/P6vEGZh1AFdb5gGkiv/fS/zhaNKVxjqAiv8va6r9bb9f5gH4fHz8d19dtvqpS6pSl6LSo1+XPBkbMUXqMol0Db9XrtRF9kc8Yl1CLHWpdBZVjOaYEKnPvHD67ktcTj766nSV1Mka31jqjm+069HNPuTSxQcftQ2/fnjQ5HG++IZ8Z1y/BuIb0RLf6Amjpd/ae1zqYY47WY6LlOO6yXFZpHI5bor8bhvSGPkcLMd1gh1hCAyFneHpMBQmwTA4AYbDSbALjJB96b2xF/vitrbLSWsW69iLNm3atGnTpk2bNm3a/jlrRv+/qDBA/f93WOYATBSfe5D4fQNJ1+F71g6q7+dy8qPmd7v7/cUP5hz1fN4X3T5v+LPXjbIvGXXJCwtf2zdg8V1neHzeVJvUU+pv2HGkRPncUXzQYHiC+KI9YGc4EIbCdpY+/s3av9SmTZs2bdq0adOmTZs2bf+8/1/oqgiM/19jGf+/Svz/AeL/x5KWGpOHFf+fk/8rxv+HUxYpZUWFZZWlrtyCymmyB4Wh18C8gN/dMYT3Z85e/u1nP06/f/BNB3Y/sv97b7+5tBUOaKD/O0RiCKEwFob7mRewW8cOtGnTpk2bNm3atGnTpu1/bc3p/wdq/v/dFv9/WQP+/w1G/3+i4v//S+f/i99vHTvga5ujZcNtsw36c9vMlv032jaiVcNtS/1z21L+K23zxmuSlhjxGsfDcblVHUPu3FoSWpgwYP7rvngN96b/eE24xGsiYCw8CcpxfO/+j4uS46JhrDo/4jDHxchxp8px/WFkA/Gh4CVtbSmk7CU6TqRNmzZt2rRp06ZN23/VmtP/LygMjP+/xjL+v0r8//PErxlLuhE/LlPx/zl5wMf/iw/ZJP+xIX+x1O0vnnL544+v3R7x3LcpeZ3POC20m2+OgLSFNlrnCCjz1EPgCbCzpZ9/7GHWAVyk/Tht2rRp06ZNmzZt2rRpO6asmfx/+fD3/f+TbO06FdC5GfOLsTedz72fkH5eli2Eny1P5mdtW/CzCSPPHZvmjhfcaxkvsFbiBemk9qQzSTdzTPDe1vXiBRme9QLTHWWFM739zkGHiRmcJDEDF4kYQHqJa4ynd1nG/LeTeEK5I78=
*/