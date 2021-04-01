/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_DYN_PERFECT_FWD_HPP
#define BOOST_FLYWEIGHT_DETAIL_DYN_PERFECT_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#define BOOST_FLYWEIGHT_PERFECT_FWD_ARG(z,n,_)                     \
BOOST_PP_CAT(T,n)&& BOOST_PP_CAT(t,n)

#define BOOST_FLYWEIGHT_PERFECT_FWD_N_AUX(n,name,body)             \
template<BOOST_PP_ENUM_PARAMS(n,typename T)>                       \
name(BOOST_PP_ENUM(n,BOOST_FLYWEIGHT_PERFECT_FWD_ARG,~))           \
body((FORWARD)(n))

#define BOOST_FLYWEIGHT_PERFECT_FWD_N(z,n,data)                    \
BOOST_FLYWEIGHT_PERFECT_FWD_N_AUX(                                 \
  n,BOOST_PP_SEQ_HEAD(data),                                       \
  BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(data)))

#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)           \
BOOST_PP_REPEAT_FROM_TO(                                           \
  1,BOOST_PP_ADD(BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS,1),        \
  BOOST_FLYWEIGHT_PERFECT_FWD_N,(name)(body))

#define BOOST_FLYWEIGHT_PERFECT_FWD(name,body)                     \
name()body((ENUM)(0))                                              \
BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)

#else

/* no rvalue refs -> [const] Tn& overloads */

#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp> 
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/size.hpp>

#define BOOST_FLYWEIGHT_CONST(b) BOOST_PP_CAT(BOOST_FLYWEIGHT_CONST,b)
#define BOOST_FLYWEIGHT_CONST0
#define BOOST_FLYWEIGHT_CONST1 const

/* if mask[n]==0 --> Tn& tn
 * if mask[n]==1 --> const Tn& tn
 */

#define BOOST_FLYWEIGHT_PERFECT_FWD_ARG(z,n,mask)                  \
BOOST_FLYWEIGHT_CONST(BOOST_PP_SEQ_ELEM(n,mask))                   \
BOOST_PP_CAT(T,n)& BOOST_PP_CAT(t,n)

/* overload accepting size(mask) args, where the template args are
 * marked const or not according to the given mask (a seq of 0 or 1)
 */

#define BOOST_FLYWEIGHT_PERFECT_FWD_MASK_AUX(r,name,body,mask)     \
template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(mask),typename T)> \
name(                                                              \
  BOOST_PP_ENUM(                                                   \
    BOOST_PP_SEQ_SIZE(mask),BOOST_FLYWEIGHT_PERFECT_FWD_ARG,mask)) \
body((ENUM)(BOOST_PP_SEQ_SIZE(mask)))

#define BOOST_FLYWEIGHT_PERFECT_FWD_MASK(r,data)                   \
BOOST_FLYWEIGHT_PERFECT_FWD_MASK_AUX(                              \
  r,                                                               \
  BOOST_PP_SEQ_ELEM(0,BOOST_PP_SEQ_HEAD(data)),                    \
  BOOST_PP_SEQ_ELEM(1,BOOST_PP_SEQ_HEAD(data)),                    \
  BOOST_PP_SEQ_TAIL(data))

#define BOOST_FLYWEIGHT_01(z,n,_) ((0)(1))

/* Perfect forwarding overloads accepting 1 to n args */
 
#define BOOST_FLYWEIGHT_PERFECT_FWD_N(z,n,data)                    \
BOOST_PP_SEQ_FOR_EACH_PRODUCT(                                     \
  BOOST_FLYWEIGHT_PERFECT_FWD_MASK,                                \
  ((data))                                                         \
  BOOST_PP_REPEAT(n,BOOST_FLYWEIGHT_01,~))

#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)           \
BOOST_PP_REPEAT_FROM_TO(                                           \
  1,BOOST_PP_ADD(BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS,1),        \
  BOOST_FLYWEIGHT_PERFECT_FWD_N,(name)(body))

#define BOOST_FLYWEIGHT_PERFECT_FWD(name,body)                     \
name()body((ENUM)(0))                                              \
BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)

#endif
#endif

/* dyn_perfect_fwd.hpp
NItWrggki8ryztOh0B4h0+cP7/v6GrN+4Bok41TJuzeZWBZQk4EA04d2L4ceG9V+BOdWRnNINstbueooVD3u4rlM8a3p6FpOjm9ZV6w7Qji35tpW1ucIboCWnxvgZf0mxY7/q9uziWh1sxfp4SGxr8htuySnPwBZEh0YgNvJj0LXVjV6UvN3uSAeVZ/Hj0dDwmCzI+9W8hAXXE+y694dvPP0CpEIAG3C47GlUt8JBX2kOqj4EcG6HkD3Yh/C3Pr+7pRWBGJ7Kgs4TVPvfNoveZcvOipexs06Gs+bCUIpUenl3DV5aPmIXRWK5o/e8LleEUW6RUj6Gs8tsL6MTs1cJucsGf7YPLJ+OkAL55ffHtph/dl60kNdyfR24DdQXaamXFOYf2vfQNEPeMw4G2XcEn31jA8EE10HikqltYaGWMGd2OU94cQ+PaVKJp3hFQPONN008mr34Q1DD/Zwa+BaujRMhNIabi6EkS98oqagxBSjU0+BY2r/lGVU97lPsaTuqx1/wNpl7uHZqqJIR90CbFbOVw51e+vyfBLmU7fK71aoe7Le3DtXN10qxw==
*/