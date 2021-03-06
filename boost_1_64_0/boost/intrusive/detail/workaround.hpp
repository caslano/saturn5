//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_WORKAROUND_HPP
#define BOOST_INTRUSIVE_DETAIL_WORKAROUND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

// MSVC-12 ICEs when variadic templates are enabled.
#if    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && (!defined(BOOST_MSVC) || BOOST_MSVC >= 1900)
   #define BOOST_INTRUSIVE_VARIADIC_TEMPLATES
#endif

#if    !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
   #define BOOST_INTRUSIVE_PERFECT_FORWARDING
#endif

//Macros for documentation purposes. For code, expands to the argument
#define BOOST_INTRUSIVE_IMPDEF(TYPE) TYPE
#define BOOST_INTRUSIVE_SEEDOC(TYPE) TYPE
#define BOOST_INTRUSIVE_DOC1ST(TYPE1, TYPE2) TYPE2
#define BOOST_INTRUSIVE_I ,
#define BOOST_INTRUSIVE_DOCIGN(T1) T1

//#define BOOST_INTRUSIVE_DISABLE_FORCEINLINE

#if defined(BOOST_INTRUSIVE_DISABLE_FORCEINLINE)
   #define BOOST_INTRUSIVE_FORCEINLINE inline
#elif defined(BOOST_INTRUSIVE_FORCEINLINE_IS_BOOST_FORCELINE)
   #define BOOST_INTRUSIVE_FORCEINLINE BOOST_FORCEINLINE
#elif defined(BOOST_MSVC) && defined(_DEBUG)
   //"__forceinline" and MSVC seems to have some bugs in debug mode
   #define BOOST_INTRUSIVE_FORCEINLINE inline
#elif defined(__GNUC__) && ((__GNUC__ < 4) || (__GNUC__ == 4 && (__GNUC_MINOR__ < 5)))
   //Older GCCs have problems with forceinline
   #define BOOST_INTRUSIVE_FORCEINLINE inline
#else
   #define BOOST_INTRUSIVE_FORCEINLINE BOOST_FORCEINLINE
#endif

#endif   //#ifndef BOOST_INTRUSIVE_DETAIL_WORKAROUND_HPP

/* workaround.hpp
M1us4zwjrrR2NbI7gb1PWeoZuVqR+Uc/ItV2aYwOJKpLeDHb6GZv2mzFyfj718Gj3CTpM/pZf+70K45d4BUACh48jBbKlIY1eD1W0wmiREDMpDT1xUY8P4LyhmIuNtUJ06PGwwl+icDPr+myQFtugm7D28QFT6ttqIKJE11KhkKasJDkmi4utN45A0ev8/5y6hOel4kciNTb4YmK82BIVXwa8705Cwvel4DS6s2RFUp9spovF1tMtBWTMdAp6nt8nLwVa1kcbQcChlfvz4niarvjGJD5MJLapW9y5qYAkEWiWBfkceM3OOkNWePj+jjbiWzpqphCTd89HGLgihUUT3lN5Ajkp+Tdcyc7uT//ffwAb7HSQnJhZqsOiQj0bNzRATT5JW56ms7j0qXyX9Y5XJIezEtykc7ontpRvsURjWjPEC7gLvAJVUu2jzWter1f60zpzyUD90TEKkpC1lhKh/q6t+BR2Mvm6RZgFKHaqrxvwNgVcmM/IE2uod4t4aYfm+37c9XZlcRJ75AhGs9dkiu9kkwUez1YU+Ybvn4HfpFgCxEtPIZQKR6oyw==
*/