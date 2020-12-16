//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_DETAIL_WORKAROUND_HPP
#define BOOST_MOVE_DETAIL_WORKAROUND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if    !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
   #define BOOST_MOVE_PERFECT_FORWARDING
#endif

#if defined(__has_feature)
   #define BOOST_MOVE_HAS_FEATURE __has_feature
#else
   #define BOOST_MOVE_HAS_FEATURE(x) 0
#endif

#if BOOST_MOVE_HAS_FEATURE(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
   #define BOOST_MOVE_ADDRESS_SANITIZER_ON
#endif

//Macros for documentation purposes. For code, expands to the argument
#define BOOST_MOVE_IMPDEF(TYPE) TYPE
#define BOOST_MOVE_SEEDOC(TYPE) TYPE
#define BOOST_MOVE_DOC0PTR(TYPE) TYPE
#define BOOST_MOVE_DOC1ST(TYPE1, TYPE2) TYPE2
#define BOOST_MOVE_I ,
#define BOOST_MOVE_DOCIGN(T1) T1

#if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ < 5) && !defined(__clang__)
   //Pre-standard rvalue binding rules
   #define BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES
#elif defined(_MSC_VER) && (_MSC_VER == 1600)
   //Standard rvalue binding rules but with some bugs
   #define BOOST_MOVE_MSVC_10_MEMBER_RVALUE_REF_BUG
   #define BOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG
#elif defined(_MSC_VER) && (_MSC_VER == 1700)
   #define BOOST_MOVE_MSVC_AUTO_MOVE_RETURN_BUG
#endif

#if defined(BOOST_MOVE_DISABLE_FORCEINLINE)
   #define BOOST_MOVE_FORCEINLINE inline
#elif defined(BOOST_MOVE_FORCEINLINE_IS_BOOST_FORCELINE)
   #define BOOST_MOVE_FORCEINLINE BOOST_FORCEINLINE
#elif defined(BOOST_MSVC) && defined(_DEBUG)
   //"__forceinline" and MSVC seems to have some bugs in debug mode
   #define BOOST_MOVE_FORCEINLINE inline
#elif defined(__GNUC__) && ((__GNUC__ < 4) || (__GNUC__ == 4 && (__GNUC_MINOR__ < 5)))
   //Older GCCs have problems with forceinline
   #define BOOST_MOVE_FORCEINLINE inline
#else
   #define BOOST_MOVE_FORCEINLINE BOOST_FORCEINLINE
#endif

#endif   //#ifndef BOOST_MOVE_DETAIL_WORKAROUND_HPP

/* workaround.hpp
V0cZJy0Diw6hYvnU8Y1cHnzJat9k602wL2htaHckIso6+yxixM2L3vIGPjqt8t6j/shiywgUzdRrG8rpHOS3rcJw3XellGSbvvTe7mIA3LFp2oNWUoBCJf5VFq/ad22AyukOnbudx4QsQ4BkHRXjiZWJ5XHrU4qY3SffR8He2DgOvrxR/8WXTErBob26y5NlFO+LYbXENwaRxjo5hksKiL1ya/deOdXU+xvBFVgjYvx0WyrH+JOS1G8m9fc+5Db6wW92Pm4Bitfj1KEs4uFDA91aJN3KB2RVuzW9Ebe11Ikeg+va6Gxxcw+LKD3GcWFVjjDGw/btub015kFOuHR9VnBLug0+VnsYNZDNzwYY3Klxd+8GA/tmCuAE0QNc9Ix4KbtUZHS8h1McClAQLedrL4mryXlAsBmdWYVGlxR9kvE7C8lhWFnZbOwX9PGJikr69UTL6HcsGZscQc0oZi+Whn+m5CEMiM/ZxjwPU5ktsFnz+y1kJt9rGjAfje3kNNsLKslyhky2NZwSp9gl3/CIV72PRt736buBvo/T93f03Uzh/nVe9QP0vZ6+v6b31fR/G8U9Q9+u9dYddLzz6x39znyKS0YrI5wBpfw7Ul78o3a9+xnyY8s/NGlm2ctVgJ5sDqp303hyWvQdTelZd1IJVaDHbSqE1GHY8eXU/+yXHPqqsGOKUKBCiYoHkA95hN1DSdfo4ucsa79y2z75AKySc/VzRb2PgLd/XlgtoFHJ9a5YuEU0gzMrzJnPl1DDVEb/+RWyixKxs9JGQo2R9TIrK1SQRxihl0soSrikUS8xQufaJWgN+qs32Js1l9OBoHap5otmVrJ/lBTDb+x+9d90Fi5yARceuVJPfSXHnnMsT4E+zMU83wZBLUMKHbb+jw6p6crs9CApYr/DTckyFlVI4R+5lrv6qaXm6XEWgUbzzsqYpcPZhmR7cGpDjn50LtVvUZmcyB+MnhzxyDxCnsn20NkScbFkeFuUVlpjgkbHMByD2Oc/b3f6R0Ze2zun4cChn523wMC7KHDrobhHmmzDq9o2PuFV4R38epq8PkYiE2/ZTNe+5jIEAQ1iQ+QSWsRNXWRovf1we6B1MqX5aTKo17rRjz799SvFAOoJH2W+3ywBLsQbSHNz2zzuZfgknzrVhdjvZCSZ0ahf5kgyg5M86EwC8q1zJLmEk3wvI4lGtlGOJJrh/XyHm29OryLIjKOpDLtPDo6Rwwn6LY6OXNiss7nah5NnbsDgbnuSfWuP5VvvtM0WUu4wkVLdKk3u8FKKUyipB0mPRx2S50krz5fMPHtvljwrKQ8w/ngFK3j6yJkyN6EcGg5mCSfxVkGQtziukNS0RYHbIXdbxd5mFnuPUWwICaF39rPwU8lO4PkK92O9lBTYYPng+ItM/3t+NnC+xnTOB8RUknYhKu/6Je08QMQUfjB2odZtVu50BXe0VG+0QMhDmmGSx++v4BRaj5k9ci0D/tJCAXwpn2uDCQKZorBwkYo3VDD4GFS4q1mAVxpNmMsSFswYSvqP2809IQGELqW463w5g3YicsOtECnqu+FrP+Iyc13cmJPrYiNXin31S756veR264j0tKkUjM4je9SPn20Hz6DAHZ6ijIHIYmanfQYuOpopshjBX7LP1Q0sMm1yxDuGNNbfyLXX1Zugnfp5pw+V5hNIQqzXT/u8eVXBERG/+Fn7nJQGbhLk7m+kqjjLSMqCxcnh3Di4u9TP/zSnto1LYA/BUJ1pkAEfNPrtSk7GFTx8k8O1fFs9RwDUeZe7oqcDWCwCPOcZ3BcyNcrFmEdRuDFe/54gjun7Nq6wB/ue5jpqqRXtSV5toLuOzH/bbXRfYgc/OcsO1rg=
*/