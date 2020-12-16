//---------------------------------------------------------------------------//
// Copyright (c) 2016 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_DIAGNOSTIC_HPP
#define BOOST_COMPUTE_DETAIL_DIAGNOSTIC_HPP

// Macros for suppressing warnings for GCC version 4.6 or later. Usage:
//
//   BOOST_COMPUTE_BOOST_COMPUTE_GCC_DIAG_OFF(sign-compare);
//   if(a < b){
//   BOOST_COMPUTE_BOOST_COMPUTE_GCC_DIAG_ON(sign-compare);
//
// Source: https://svn.boost.org/trac/boost/wiki/Guidelines/WarningsGuidelines
#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
#define BOOST_COMPUTE_GCC_DIAG_STR(s) #s
#define BOOST_COMPUTE_GCC_DIAG_JOINSTR(x,y) BOOST_COMPUTE_GCC_DIAG_STR(x ## y)
# define BOOST_COMPUTE_GCC_DIAG_DO_PRAGMA(x) _Pragma (#x)
# define BOOST_COMPUTE_GCC_DIAG_PRAGMA(x) BOOST_COMPUTE_GCC_DIAG_DO_PRAGMA(GCC diagnostic x)
# if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
#  define BOOST_COMPUTE_GCC_DIAG_OFF(x) BOOST_COMPUTE_GCC_DIAG_PRAGMA(push) \
      BOOST_COMPUTE_GCC_DIAG_PRAGMA(ignored BOOST_COMPUTE_GCC_DIAG_JOINSTR(-W,x))
#  define BOOST_COMPUTE_GCC_DIAG_ON(x) BOOST_COMPUTE_GCC_DIAG_PRAGMA(pop)
# else
#  define BOOST_COMPUTE_GCC_DIAG_OFF(x) \
      BOOST_COMPUTE_GCC_DIAG_PRAGMA(ignored BOOST_COMPUTE_GCC_DIAG_JOINSTR(-W,x))
#  define BOOST_COMPUTE_GCC_DIAG_ON(x) \
      BOOST_COMPUTE_GCC_DIAG_PRAGMA(warning BOOST_COMPUTE_GCC_DIAG_JOINSTR(-W,x))
# endif
#else // Ensure these macros do nothing for other compilers.
# define BOOST_COMPUTE_GCC_DIAG_OFF(x)
# define BOOST_COMPUTE_GCC_DIAG_ON(x)
#endif

// Macros for suppressing warnings for Clang.
//
//   BOOST_COMPUTE_BOOST_COMPUTE_CLANG_DIAG_OFF(sign-compare);
//   if(a < b){
//   BOOST_COMPUTE_BOOST_COMPUTE_CLANG_DIAG_ON(sign-compare);
//
// Source: https://svn.boost.org/trac/boost/wiki/Guidelines/WarningsGuidelines
#ifdef __clang__
#  define BOOST_COMPUTE_CLANG_DIAG_STR(s) # s
// stringize s to "no-sign-compare"
#  define BOOST_COMPUTE_CLANG_DIAG_JOINSTR(x,y) BOOST_COMPUTE_CLANG_DIAG_STR(x ## y)
//  join -W with no-unused-variable to "-Wno-sign-compare"
#  define BOOST_COMPUTE_CLANG_DIAG_DO_PRAGMA(x) _Pragma (#x)
// _Pragma is unary operator  #pragma ("")
#  define BOOST_COMPUTE_CLANG_DIAG_PRAGMA(x) \
      BOOST_COMPUTE_CLANG_DIAG_DO_PRAGMA(clang diagnostic x)
#  define BOOST_COMPUTE_CLANG_DIAG_OFF(x) BOOST_COMPUTE_CLANG_DIAG_PRAGMA(push) \
      BOOST_COMPUTE_CLANG_DIAG_PRAGMA(ignored BOOST_COMPUTE_CLANG_DIAG_JOINSTR(-W,x))
// For example: #pragma clang diagnostic ignored "-Wno-sign-compare"
#  define BOOST_COMPUTE_CLANG_DIAG_ON(x) BOOST_COMPUTE_CLANG_DIAG_PRAGMA(pop)
// For example: #pragma clang diagnostic warning "-Wno-sign-compare"
#else // Ensure these macros do nothing for other compilers.
#  define BOOST_COMPUTE_CLANG_DIAG_OFF(x)
#  define BOOST_COMPUTE_CLANG_DIAG_ON(x)
#  define BOOST_COMPUTE_CLANG_DIAG_PRAGMA(x)
#endif

// Macros for suppressing warnings for MSVC. Usage:
//
//   BOOST_COMPUTE_BOOST_COMPUTE_MSVC_DIAG_OFF(4018); //sign-compare
//   if(a < b){
//   BOOST_COMPUTE_BOOST_COMPUTE_MSVC_DIAG_ON(4018);
//
#if defined(_MSC_VER)
#  define BOOST_COMPUTE_MSVC_DIAG_DO_PRAGMA(x) __pragma(x)
#  define BOOST_COMPUTE_MSVC_DIAG_PRAGMA(x) \
          BOOST_COMPUTE_MSVC_DIAG_DO_PRAGMA(warning(x))
#  define BOOST_COMPUTE_MSVC_DIAG_OFF(x) BOOST_COMPUTE_MSVC_DIAG_PRAGMA(push) \
          BOOST_COMPUTE_MSVC_DIAG_PRAGMA(disable: x)
#  define BOOST_COMPUTE_MSVC_DIAG_ON(x) BOOST_COMPUTE_MSVC_DIAG_PRAGMA(pop)
#else // Ensure these macros do nothing for other compilers.
#  define BOOST_COMPUTE_MSVC_DIAG_OFF(x)
#  define BOOST_COMPUTE_MSVC_DIAG_ON(x)
#endif

// Macros for suppressing warnings for GCC, Clang and MSVC. Usage:
//
//   BOOST_COMPUTE_DIAG_OFF(sign-compare, sign-compare, 4018);
//   if(a < b){
//   BOOST_COMPUTE_DIAG_ON(sign-compare, sign-compare, 4018);
//
#if defined(_MSC_VER) // MSVC
#  define BOOST_COMPUTE_DIAG_OFF(gcc, clang, msvc) BOOST_COMPUTE_MSVC_DIAG_OFF(msvc)
#  define BOOST_COMPUTE_DIAG_ON(gcc, clang, msvc) BOOST_COMPUTE_MSVC_DIAG_ON(msvc)
#elif defined(__clang__) // Clang
#  define BOOST_COMPUTE_DIAG_OFF(gcc, clang, msvc) BOOST_COMPUTE_CLANG_DIAG_OFF(clang)
#  define BOOST_COMPUTE_DIAG_ON(gcc, clang, msvc) BOOST_COMPUTE_CLANG_DIAG_ON(clang)
#elif defined(__GNUC__) // GCC/G++
#  define BOOST_COMPUTE_DIAG_OFF(gcc, clang, msvc) BOOST_COMPUTE_GCC_DIAG_OFF(gcc)
#  define BOOST_COMPUTE_DIAG_ON(gcc, clang, msvc) BOOST_COMPUTE_GCC_DIAG_ON(gcc)
#else // Ensure these macros do nothing for other compilers.
#  define BOOST_COMPUTE_DIAG_OFF(gcc, clang, msvc)
#  define BOOST_COMPUTE_DIAG_ON(gcc, clang, msvc)
#endif

#define BOOST_COMPUTE_DISABLE_DEPRECATED_DECLARATIONS() \
    BOOST_COMPUTE_DIAG_OFF(deprecated-declarations, deprecated-declarations, 4996)
#define BOOST_COMPUTE_ENABLE_DEPRECATED_DECLARATIONS() \
    BOOST_COMPUTE_DIAG_ON(deprecated-declarations, deprecated-declarations, 4996);


#endif /* BOOST_COMPUTE_DETAIL_DIAGNOSTIC_HPP */

/* diagnostic.hpp
jFmyIfhhuZLmlAI1+qzZ+4h8OSJPmyFbIh1tcMjdyFCnS/CjciZGglNqdOiz4Fofc72Qp82c0MfF5ZAkGSq02HDQVQcSlKnRJ/AJuXI5rsUJDXpMuNon1YAKLZZsCH7KPCBBgRpNpuz39JsTUuSp0mNO6NPikiRDizEbrvQZMSlTo8+IwGeNO1HylKgyJNTXd67GjTgkSY4iY2YEPydnzuCUDlP2P6/vHFGizYQVkS+IySFJcrToMiM4kDPXI0GBMk06TAl8UX25FlGylBgyJ/Ql84AcFbosCX/ZuHFMghpNpuwN5csJJXpMWHG1r4hHnCJ1Wow5+Kp4JDilRocF+1+TI0dEKdGgx4TQSD24EYfEyVCkzowN4a+rMcfEOKVAnzWBb8ify3EtopSo0qDHlsg39YVDclToMmNDeKzuJEjTpM+ay33LfOGELA3a9BiyIvJtsclRocuAMRsOvqMfpDmlzJTARHyipCjRoMecyHdd39yNHEUq1OmyIfw984YziHFKmQ4LAt83HlyLKHl6zIlM1YUbcTcyFGnRZcyMgx+oD8ckKFNjSuCH4nNClQkrtoR+JH/iJClSZ8CM8ExszqBGkz4jpgR+rD4cUaJNjzlbrvYTeZOkxYANwZ/KlRpT9ufGkCgpqrSZsGJL5GfGkDhFKrToMmND+OfqQIJTytQYsfcLbZAlT4Mhc7YcLsQmSYYiLQaMWbIh/EvjyTFpyoxYEPiVdrgZKfK06TFhxZZL/VptOCRJhTotBowJL80XmvTZ+406cUSKLHmGzFkR+q25QpwcFVoMWLIh9ju1oUaTKYGV+UeKPCWqDJlwtd+LS5IMRVqM2XClP6g5ZTpMWbP/R2NKniptJmw5XItDnQFjZizZcKU/qTExEhToMGLKgr0/qwdRsjSYMGdL6C/aIUOdFks2HGzMFc7gmAJlmoxYc62/is8JKfJUabPlUn9TG+5GnCItBoT/Lj5nUKDMgjX7WzmTpUSVNitC/zDXOeRu5OgyZkn4n3LneqQp0GHN3r9cj0TJUqVNjwlbIj6dcCMOuRtxMtTpMubAvV7H1GiyIGDdhctxM1L0CJ1FDHLUGRAMOp8EaQrUaDIl4HOPe1yOa3FElCwNekxYETmb+MTJ0WVG2D1l1yNNgT4L9vwPlX2uRZQsJar0mLPlUucQlyQZinSZsWTDGedUA06pMWXN5Xze+4QqPYbM2XK1PbXlbsTJkKNCnRZjNgTPrR8kKFCmyZQ1gfPoB1GytJkTOa92iJOjy5ig9R2vRIJTmnQYsSBwPmNHlCxtJqy40fnlyJgZV7qAvpOmQJ8114roOymyNGjTY0vogvIiSY4BS4IXEpMzSHNKmQ6BC4vLCSmylGiz5VL76kmSInW6zAhfREwSpKnRZMqawEXNCW7GCSlKNBgy51IXcy0Qp06LMUvCB/LmDI5pMmLN3sXF5YgUbYZsudQlxCRDhTozDi4pFjHSFOjQZ8HepcwvjkjRY07o0saIQ3LUWRK7jDiU6bDmWpd1PlHylGgwZMWW0OXEIk6SHBVaDJgRvLx8SXBKhxELAldwnXEzTqjSoE2PCVsiV1QLDomTo86ADcErqS9pytSYEriyWnBElBPylOgxZELoKuJSYcCYJRvCV1VrjklzSpkmfUasCVxNX7gZUU7I06DHhC1Xu7q2yFGhTpcxS653DW1xSoEmfRYErmlciJIlT4/QtdSGu5GkRZcxSzaEry02ZxAjzSlNOvSZEriOucO1OOKEKhNWXOq65hBx6nQZMyN4PWPN9TiDMlMud311IUqWEj3mrNgSuYHacCPi5CjSYsnBDY0x16NAmQ4LAjcSnyxVhqyI3Fg8chSpM2ZJ+CY=
*/