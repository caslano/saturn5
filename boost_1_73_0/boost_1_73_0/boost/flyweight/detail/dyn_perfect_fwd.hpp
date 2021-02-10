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
f3494L0L529RGwKztsBvm5ZrrKIFUTeV4PlB8h/qdMdLLuFstZxFiyRdBvHqKkjPl9EVPIXR6XP4vZMo7dNnIxhVYkPPHp57T597J7hAv1LO9C7V3NBTxi8KSiNmfAlz/ypwHgJeH+NjRRNAo4S00sBmuxqpb5nUBfZftKq2GPH1PFrEYez8JGRWdTmHV5S012D52rH4mcL1r2sZ0x04KlEdFYrkgTpcqJS8sbkmL222t0F8tgwXSRjNnQVD/lm/pXcPqzlqw4PQoBSlYYKEhhpRRUHtoDllV6PpSTubneF0F22DnnS2jPosv+gQm9aGHEnpPYi56Y3ZM0i3T+hQs4/8INDZR9n1Db8RUgoscsyLAgcv2r3akRjRtrTcUzvx4BzFdJ4sXMs95XL2uY5PH0wGXyXj6LTBGHjjBnHIF84YnV10FUEQMUJ2ZF8kBOlqu4YM0TWVYvnEc5wPJZdoOiqtX9SwRdH3pRHyoIVGaWHLQ1K26Al+P/0qlbFqqlXXZtyxo/Bel8PkM+3uS01hSJ+o74OmBU6KragquodGbRrqC6+dHrSfr4jQV1Mrc9Au9hAWdtJK3o+QIRPb87bhO9VjwpOLN1ggDieXBqCzLsIHpJjO/OVFMH46WRcL7FMbzsjxVpLn/mqWOPhq
*/