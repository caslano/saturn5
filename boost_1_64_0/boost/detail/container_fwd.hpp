
// Copyright 2005-2011 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Note: if you change this include guard, you also need to change
// container_fwd_compile_fail.cpp
#if !defined(BOOST_DETAIL_CONTAINER_FWD_HPP)
#define BOOST_DETAIL_CONTAINER_FWD_HPP

#if defined(_MSC_VER) && \
    !defined(BOOST_DETAIL_TEST_CONFIG_ONLY)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Define BOOST_DETAIL_NO_CONTAINER_FWD if you don't want this header to      //
// forward declare standard containers.                                       //
//                                                                            //
// BOOST_DETAIL_CONTAINER_FWD to make it foward declare containers even if it //
// normally doesn't.                                                          //
//                                                                            //
// BOOST_DETAIL_NO_CONTAINER_FWD overrides BOOST_DETAIL_CONTAINER_FWD.        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#if !defined(BOOST_DETAIL_NO_CONTAINER_FWD)
#  if defined(BOOST_DETAIL_CONTAINER_FWD)
     // Force forward declarations.
#  elif defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
     // STLport
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif defined(__LIBCOMO__)
     // Comeau STL:
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
     // Rogue Wave library:
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif defined(_LIBCPP_VERSION)
     // libc++
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
     // GNU libstdc++ 3
     //
     // Disable forwarding for all recent versions, as the library has a
     // versioned namespace mode, and I don't know how to detect it.
#    if __GLIBCXX__ >= 20070513 \
        || defined(_GLIBCXX_DEBUG) \
        || defined(_GLIBCXX_PARALLEL) \
        || defined(_GLIBCXX_PROFILE)
#      define BOOST_DETAIL_NO_CONTAINER_FWD
#    else
#      if defined(__GLIBCXX__) && __GLIBCXX__ >= 20040530
#        define BOOST_CONTAINER_FWD_COMPLEX_STRUCT
#      endif
#    endif
#  elif defined(__STL_CONFIG_H)
     // generic SGI STL
     //
     // Forward declaration seems to be okay, but it has a couple of odd
     // implementations.
#    define BOOST_CONTAINER_FWD_BAD_BITSET
#    if !defined(__STL_NON_TYPE_TMPL_PARAM_BUG)
#      define BOOST_CONTAINER_FWD_BAD_DEQUE
#     endif
#  elif defined(__MSL_CPP__)
     // MSL standard lib:
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif defined(__IBMCPP__)
     // The default VACPP std lib, forward declaration seems to be fine.
#  elif defined(MSIPL_COMPILE_H)
     // Modena C++ standard library
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
     // Dinkumware Library (this has to appear after any possible replacement
     // libraries)
#  else
#    define BOOST_DETAIL_NO_CONTAINER_FWD
#  endif
#endif

#if !defined(BOOST_DETAIL_TEST_CONFIG_ONLY)

#if defined(BOOST_DETAIL_NO_CONTAINER_FWD) && \
    !defined(BOOST_DETAIL_TEST_FORCE_CONTAINER_FWD)

#include <deque>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <string>
#include <complex>

#else

#include <cstddef>

#if defined(BOOST_CONTAINER_FWD_BAD_DEQUE)
#include <deque>
#endif

#if defined(BOOST_CONTAINER_FWD_BAD_BITSET)
#include <bitset>
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable:4099) // struct/class mismatch in fwd declarations
#endif

namespace std
{
    template <class T> class allocator;
    template <class charT, class traits, class Allocator> class basic_string;

    template <class charT> struct char_traits;

#if defined(BOOST_CONTAINER_FWD_COMPLEX_STRUCT)
    template <class T> struct complex;
#else
    template <class T> class complex;
#endif

#if !defined(BOOST_CONTAINER_FWD_BAD_DEQUE)
    template <class T, class Allocator> class deque;
#endif

    template <class T, class Allocator> class list;
    template <class T, class Allocator> class vector;
    template <class Key, class T, class Compare, class Allocator> class map;
    template <class Key, class T, class Compare, class Allocator>
    class multimap;
    template <class Key, class Compare, class Allocator> class set;
    template <class Key, class Compare, class Allocator> class multiset;

#if !defined(BOOST_CONTAINER_FWD_BAD_BITSET)
    template <size_t N> class bitset;
#endif
    template <class T1, class T2> struct pair;
}

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_DETAIL_NO_CONTAINER_FWD &&
       // !defined(BOOST_DETAIL_TEST_FORCE_CONTAINER_FWD)

#endif // BOOST_DETAIL_TEST_CONFIG_ONLY

#endif

/* container_fwd.hpp
a5KUjsEru3mCs6c3bre5pPUua03fD8aagIkQsFqdaMirfLwh9eeDyC8xA7prB4veqOfNWU0eGvgXMZ3emTAEwm1upAh+iiLb9ywCPshDkyOSR34aHdPzKrt6HndQX6JRLLRsUbmorr0L6GyirXCQH7sEoOeS/J4zoQir3MCerYOjMLeo7Kp8hZao8gtx2z+2J8ISwfc5Imvxcj4in2X4gM0wcoQoME4mRMK5ZKgAKY7ldZJhP56Q5fCTzw/4JbpSFuqRpdj29HAMbJKbcLli8LMlw5ls3r2l30EI3Qie6qN3fMCshyTvx9WBcNd0xsk1vwjKo6EpJDzF9iS4zhC4plBcQ0B06ufnCtCDCvvisSAB3VeAjteAXvZxLzQUtFcGymKjPVC0h6wsGaHp3/bGJSGHjm00bBseCWtXiWxvjOgBAfJMzWdXeH4Z8tYd3fvzXpFqiNStpNSASB0npTaJ1FV46sJTQGGgP+xoepI9aQCiCxNEN83oRHwoIIYT1QW0yQe/jcDRuUt6uU5FHSwf0s8mSFBa0EPGr1vOWAAbyEmxGU8YUGcAtfNlXIUEJt7Z3O8wgQc4eADAgwnwIIDfZgUPc/AwgFcnwKsBfJoVvImDNwF4KAEeAvDtAByYRPD2NmiGtlmzpCGuwV7rZn5J8nOKT2hp0NHiio2h8nkX0RohU92kB2o6d6LaG/YOd1CYzUf22ZQBrI+gg3+q6QY1GD96kZSaznG0pg+KhzvmzYGcsteTLcNW0TeL0GUgqW3sAJkZ1Y6WVWo6N6TlryTl6dh4ydo4NpYilCTA8Lgsmq60dxtS8rF/ZaE+nAl1CJrybS8KbTnISTmaPSAePn3vaCnAfu+ZyOHbkVB2Lkv5ePLbspNqqstyy6aPFdIX8j5Y62xi0+XJ8FhXYFQuEAnhWZ6C2KM9F7IRLYBlniFFTmEfki+HoxBnLHWeNEpOiHeHLwYcAURKVp4LDqlrJ8NO9MyQ39EP0gJJpNVClWAgw5gm2m/V1dBIDmHtt5ga9JM+6oX+zcnUzxmoS/JnLA7ImoOEejWQY6Eu544FuZ/D7pvJ/Ux23+homYZDvSxAPzlBnHNuKhzuQCXggz0CQqNMdgqv41mA5emHQ+UXo5SB8aJd9d4mfgpB9UC41D3nOIXTM8bs4ZC9B8zHYYg/cYgKd8dSyN3MsFz5u6CzDKiKZKAp5JkvFQgEfsrdogLgjjlIDWb+IonqvnRIVcwuQmUKYgKMdyA1QbIfehogA+FggJ8PFwhuAQQcnjeNUUtN3eKoy5PINnh2QGR/4qYKExSNCqlxcFw6cnILdB10X7yXD+2jeXG5T8KTkvpkebprA34pRX9kAbOH/MyzJMG+x8mlntu+q2QJuqMAxZf1MC9KNrN8IfrwAGwvHI747iKwZnzDU+MxBTjC8lS5BLnvIIYIpBvNWRmMyfM2ho5gBrExgbLRVNjNAOrbToVnMwvvUeLYJI1vh+Lsg0/FOx/FlfscnOmNEzOIcxmmILJy7G4WMQcrKwu5MzGT2BOLqXgIWqmKXSHoAoyNoinunMBkErAQv2RFkklp1O3KSxp1sQnWwhRUclklxUBS9nuv3sm3HjXph5p2pTVBI/APecBpih4S5S0nP+ULlubNqi13iZcgShIvQZAhrxzAoAPi3XjM1YY0F8wzR0NgEJAg8j5YVP7yR3BGIx6EhZ0C4+Lt4Kb5WgpIJcaZUIkBd6uQO6Dg5SVkMC13Vb5S8XL7s2sRwivNxQm//gHpOmLsDjGGoyfHn3csgGf1eJiwCSW5CcefKiU7M46NIREvNRftDlT7GNMpmEuDKPLAfkFkKPwURvaEn6LIOvAzKLJd7CCqeeTtEeA=
*/