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
uTDTiJd/rklTl1ct96LSdeXD4B3kxYCRTF/swm65u4ovMwv9yh7XEDJLGFkyxtHtaQLvJ0RB9BexRVsh551daSiOZVpycp5KM5uguuCyjpW28LFMk6gUtdta3mQUYAcgfOn5RpwB6VUlDZe9cdTl0hzyZ2CfZ/2iL4TecJ9LzUhND2yg9B/GmZAu6Bp2jz/GUv0b/TJbqn/gv1wX2z3HWIP/HSOYQbnMVXOpYrk0b4uhURXCC5fEyM1xRn/M2xzKZ0zV7Xk72O5/c5WuvAxl2uwncBXhAlB0P84RbKL94ylUnHvqy6/jHahVnJGux1W6jkBoUUPNa9V3+8ENOSUmjNTaGBu+MmQLwP1K68a/sky0s3hPQxro0++re09gcXFbJEJOL/E/wd63TAVoismKdd8DmRjyjPWmbQ/oehPCE/31CCyY/NibhkExsQq454KFlo12/4mKwK40wJd8OXShfRUUuqREsfaHPNiYLYFKNPCeBLWg36zD5EAtTnCebdWqudUgnPfzBE1cpPGIlmp8X1U4AXgzBBwtccppTMFhwxS6VKzl4QaMWkkRR6opH0SHknnkUMDZcMr4IRdG3JfXrgzlGzWTuNu1iJDJNOzbHs4MpqsGg2e+rwu7WacPRMo+y+WfNeh4BLCCWfjcBQNc65+JitX0MOgZFjaDUygGLmpUtI59DyEiZZqIp4r+fw9lGoLDEk3vGGlaqtG0
*/