/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_PERFECT_FWD_HPP
#define BOOST_FLYWEIGHT_DETAIL_PERFECT_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

/* C++03-compatible implementation of perfect forwarding.
 * Usage:
 *
 *  # define NAME ...
 *  # define BODY(args) {...BOOST_FLYWEIGHT_FORWARD(args)...}
 *  BOOST_FLYWEIGHT_PERFECT_FWD(name,body)
 *
 * where NAME includes the return type and qualifiers (if any) and BODY(args)
 * is expected to fo the forwarding through BOOST_FLYWEIGHT_FORWARD(args).
 *
 * In compilers capable of perfect forwarding, the real thing is provided
 * (just one variadic args overload is generated). Otherwise the machinery
 * generates n+1 overloads, if rvalue refs are supported, or else 2^(n+1)-1
 * overloads accepting any combination of lvalue refs and const lvalue refs,
 * up to BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS args.
 *
 * BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) is a variation omitting the
 * overloads with zero args --when perfect forwarding is available, this second
 * macro is exactly the same as the original. 
 */

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

#define BOOST_FLYWEIGHT_FORWARD_FORWARD_AUX(z,n,_) \
std::forward<BOOST_PP_CAT(T,n)>(BOOST_PP_CAT(t,n))

#define BOOST_FLYWEIGHT_FORWARD_FORWARD(n) \
BOOST_PP_ENUM(n,BOOST_FLYWEIGHT_FORWARD_FORWARD_AUX,~)

#define BOOST_FLYWEIGHT_FORWARD_ENUM(n) BOOST_PP_ENUM_PARAMS(n,t)

#define BOOST_FLYWEIGHT_FORWARD_PASS(arg) arg

#define BOOST_FLYWEIGHT_FORWARD(args)\
BOOST_PP_CAT(BOOST_FLYWEIGHT_FORWARD_,BOOST_PP_SEQ_HEAD(args))( \
BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(args)))

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)||\
    defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#if !defined(BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS)
#define BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS 5
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS<0
#error BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS must be >=0
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS<=5
#include <boost/flyweight/detail/pp_perfect_fwd.hpp>
#else
#include <boost/flyweight/detail/dyn_perfect_fwd.hpp>
#endif

#else

/* real perfect forwarding */

#define BOOST_FLYWEIGHT_PERFECT_FWD(name,body) \
template<typename... Args>name(Args&&... args) \
body((PASS)(std::forward<Args>(args)...))

#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS  \
BOOST_FLYWEIGHT_PERFECT_FWD

#endif
#endif

/* perfect_fwd.hpp
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
*/