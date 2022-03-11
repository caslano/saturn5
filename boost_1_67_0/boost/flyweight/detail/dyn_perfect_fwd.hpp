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
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
*/