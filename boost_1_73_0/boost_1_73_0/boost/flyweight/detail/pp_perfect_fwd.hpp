/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_PP_PERFECT_FWD_HPP
#define BOOST_FLYWEIGHT_DETAIL_PP_PERFECT_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#define BOOST_FLYWEIGHT_PERFECT_FWD_0(name,body) \
name()body((FORWARD)(0))

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=1
#define BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body) \
template<typename T0> name(T0&& t0)body((FORWARD)(1))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=2
#define BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body) \
template<typename T0,typename T1> name(T0&& t0,T1&& t1)body((FORWARD)(2))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=3
#define BOOST_FLYWEIGHT_PERFECT_FWD_3(name,body) \
template<typename T0,typename T1,typename T2> name(T0&& t0,T1&& t1,T2&& t2)body((FORWARD)(3))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=4
#define BOOST_FLYWEIGHT_PERFECT_FWD_4(name,body) \
template<typename T0,typename T1,typename T2,typename T3> name(T0&& t0,T1&& t1,T2&& t2,T3&& t3)body((FORWARD)(4))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=5
#define BOOST_FLYWEIGHT_PERFECT_FWD_5(name,body) \
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0&& t0,T1&& t1,T2&& t2,T3&& t3,T4&& t4)body((FORWARD)(5))
#endif

#else

/* no rvalue refs -> [const] Tn& overloads */

#define BOOST_FLYWEIGHT_PERFECT_FWD_0(name,body) \
name()body((ENUM)(0))

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=1
#define BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body) \
template<typename T0> name(T0& t0)body((ENUM)(1))\
template<typename T0> name(const T0& t0)body((ENUM)(1))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=2
#define BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body) \
template<typename T0,typename T1> name(T0& t0,T1& t1)body((ENUM)(2))\
template<typename T0,typename T1> name(T0& t0,const T1& t1)body((ENUM)(2))\
template<typename T0,typename T1> name(const T0& t0,T1& t1)body((ENUM)(2))\
template<typename T0,typename T1> name(const T0& t0,const T1& t1)body((ENUM)(2))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=3
#define BOOST_FLYWEIGHT_PERFECT_FWD_3(name,body) \
template<typename T0,typename T1,typename T2> name(T0& t0,T1& t1,T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(T0& t0,T1& t1,const T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(T0& t0,const T1& t1,T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(T0& t0,const T1& t1,const T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(const T0& t0,T1& t1,T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(const T0& t0,T1& t1,const T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(const T0& t0,const T1& t1,T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(const T0& t0,const T1& t1,const T2& t2)body((ENUM)(3))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=4
#define BOOST_FLYWEIGHT_PERFECT_FWD_4(name,body) \
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,T1& t1,T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,T1& t1,T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,T1& t1,const T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,T1& t1,const T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,const T1& t1,T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,const T1& t1,T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,const T1& t1,const T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,const T1& t1,const T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,T1& t1,T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,T1& t1,T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,T1& t1,const T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,T1& t1,const T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,const T1& t1,T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,const T1& t1,T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,const T1& t1,const T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,const T1& t1,const T2& t2,const T3& t3)body((ENUM)(4))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=5
#define BOOST_FLYWEIGHT_PERFECT_FWD_5(name,body) \
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,const T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,const T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,const T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,const T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,const T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,const T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,const T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,const T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,const T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,const T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,const T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,const T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,const T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,const T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,const T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,const T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))
#endif

#endif

#if   BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==0
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)
#elif BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==1
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) \
BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body)
#elif BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==2
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) \
BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body)
#elif BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==3
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) \
BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_3(name,body)
#elif BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==4
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) \
BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_3(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_4(name,body)
#else /* BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==5 */
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) \
BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_3(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_4(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_5(name,body)
#endif

#define BOOST_FLYWEIGHT_PERFECT_FWD(name,body)           \
BOOST_FLYWEIGHT_PERFECT_FWD_0(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)

#endif

/* pp_perfect_fwd.hpp
eZuq3vuLWebs2695EmfxNJ6ljiVqTMEf/of5LHA8sXYG6Wyzf3kmLBdcj0klvh4b4x787cCXuhvDk960uDDqtGrp/sB7RjONXiGbyYiAXoz+slsHh0dvZja0o2Y8Z0c3ANXbDNR2sYsamejb7dY/jrfmtmj/0g9n/rtwFmZLxy/L4aY99g73vUGoJMgWSQSX/mwROAlquj+UZRfk8cW2ocPYm16qvm1JcyyHu2lwXEQXUXwV5bGdKRMkpB66MkqDAPxZGtOReZfslp0GyWWQDKdlND7aIxl3HZLg4yJIs+2m8y9QSwMECgAAAAgALWdKUvgxmujaCAAAfRUAADQACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1JUU1BfUkVRVUVTVC4zVVQFAAG2SCRgrVjbctvIEX2fr+goD5ZcFOhLUo693q3AImwzpkmGAO0opSrWEBiKWIEAghlIVuL8e07PAODF9CXJymWTBmb6evp0t7yrE3r4m/0Ij8XRd38W9u8CP/hsL02r4lcVm+MXFovP5P7g4hU+f0BVn7a3Pi/O6IdufaZTe2vR6HrJ3xeLH1B3xUbyP32+fLXgr3jibjb3L4ryvkqv14ZOL87o8fPnf6JzevLo8fMeDWSe
*/