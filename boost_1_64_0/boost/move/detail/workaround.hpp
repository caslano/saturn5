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
h6b97cGLc9ZiUn1GRoatCt7moCbMeDLjItp39zbfQaF8/2Bae+gqB8luQf1WuNL4xmPkxPQtu4IxLCsIOR2sMxv4mjBMQacfQn7BetEJ1el4ZWA+2ccTyuew3TTYFsm/nryCE6C/68LaPV6R9woj7UqXpTGJLBSYcJsrQbzvdnHsovepgqMoxlhc5whp6JVdMbK5aeBcddMPbUlFRRq2uXCyuOf+vyE+KtKdgcVZ2c0WC7M0SI7pusU18NkkvjNcFKb7AlvlLyWc/zY3l6V2NJHxDBHGAj3OVnmRp0jYcxqN/cz6A0ydFbGq0a65u8XsCJbTmSTTh2Zab9MLoAwN09bvuZJmPBbCSr2feka04ZDBu/fyNMzVgV0/x+NwOb2LxLC+aZnGxVswXIYFqv64prgA3912iQmfd4FtPDmhyDW8W79F7JPJyoG8k7wxmnTcJ97ZZ+a5Q7628RVC9NIUEUmmBD4e2PznK61D2iYHBcHwHWLZdYI6O3eA6L+ZSjYp3IPOBlUlrta6TH+P7S8VnTfPDHg23g+eHiN+QsD1JdEzzz3PBlWyeJbRzg==
*/