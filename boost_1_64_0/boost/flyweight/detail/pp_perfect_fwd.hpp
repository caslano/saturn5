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
iU9KcBTZRLnDX5wVIqJwZY4KvfZ3M9h1mdXIOp35F+SwMqNgz1gz5oSfEOkJxa2VGTXdplSymWpFwERGQumoBYS1aMvggD1SONqfSX3aKQ4xPqeKkRcpFiq8DJVz1CNlR6McPnN8VIlqAI16XTjJ4MGWEmdIWN3JHts7qUiFFWJ12z3WvgHM5JQtM9PjSp25B0DE47UXMgqVfQAa/M7+5E06z7gVvgDSZiBvgEjYSInxkSjYjVgUDDv4b6UubC+rSICIyu/bs/VFBQYjPBZ93CLeURaq8YGi+u6b16sfN8MOicIzSbSJOcGF/Q0EsWOmpcPkSTifWDdo4xQd3gezH4ErnyFnnVv2BqSF2sxLaymB3ctnwLe7C8OMg6/rMN1WP6ixMqB8C2Bct3x3lnJOCx7s9yZHI0qYqYOk9z++VnqOuQ1H0psHDAICwk3UWJpq717cwDERxIkmqwLHVWYVDPlscvmQEk/UetUevhxi7XunU1Dw6JqYIMBudGy8KCDZ2v00XWMZy1gFZYUEJeihVDXLKnBgxge3ALZIpV1S/9dg5lbDi0En0OZaaw==
*/