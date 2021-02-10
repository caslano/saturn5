//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_MPL_HPP
#define BOOST_INTERPROCESS_DETAIL_MPL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>

namespace boost {
namespace interprocess {
namespace ipcdetail {

template <class T, T val>
struct integral_constant
{
   static const T value = val;
   typedef integral_constant<T,val> type;
};

template< bool C_ >
struct bool_ : integral_constant<bool, C_>
{
   static const bool value = C_;
};

typedef bool_<true>        true_;
typedef bool_<false>       false_;

typedef true_  true_type;
typedef false_ false_type;

typedef char yes_type;
struct no_type
{
   char padding[8];
};

template <bool B, class T = void>
struct enable_if_c {
  typedef T type;
};

template <class T>
struct enable_if_c<false, T> {};

template <class Cond, class T = void>
struct enable_if : public enable_if_c<Cond::value, T> {};

template <class Cond, class T = void>
struct disable_if : public enable_if_c<!Cond::value, T> {};

template<
      bool C
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef T1 type;
};

template<
      typename T1
    , typename T2
    >
struct if_c<false,T1,T2>
{
    typedef T2 type;
};

template<
      typename T1
    , typename T2
    , typename T3
    >
struct if_
{
   typedef typename if_c<0 != T1::value, T2, T3>::type type;
};


template<std::size_t S>
struct ls_zeros
{
   static const std::size_t value = (S & std::size_t(1)) ? 0 : (1u + ls_zeros<(S >> 1u)>::value);
};

template<>
struct ls_zeros<0>
{
   static const std::size_t value = 0;
};

template<>
struct ls_zeros<1>
{
   static const std::size_t value = 0;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_MPL_HPP


/* mpl.hpp
AAkAY3VybC1tYXN0ZXIvcGxhbjkvc3JjL21rZmlsZS5pbmNVVAUAAbZIJGCtUm2L2kAQ/u6veHoKp200d/epV46j4tFWSvVQ28M2JazJaLZNdsPuxhfwx3c2ekihxS83IZnJMs/LTNJ8FS6kCk3SaL5+uWg0cTbi+o45OHvAo9G/KHH/bo7jPQ4XgyLOZyRCnBD7uIOziD3aNSI+atz5Oo7PyETemH+EHhjFvuSTRpNxA13ujFxlDu1BB9e3t2/Rxc3VzVWAB6Ek5Zg6UgsyqwB3aX3yPhPbbc/SfQByEHmvJppl0sLqpdsIQ+A6lwkpSymERUo2MXLBL1LBZYSlzAmD8eN8OPoYYJPJJGOOna5gM13lKTKxJhhKSK4PFKUwDnrJaOZOpXXMVzmpVY+lCY5MYZnCi4vcaoi1kLlYsIxwyJwr7bswTCqTs/Mw1YkNk+fRe5krjlPM2UEhdtClg9OoLAXwfQEKncqlz7wKPiyrRS5tFpyssJBKQ21gKc+ZimGS7MEyYXrcTOC7ULJb6XyyWlmvtMl08Vcjr5BJlpVRLMMr4J5U84IDVColU/fWQz8rHLdZr/Y/n+TkNYVW7AQX/SmG0wsshJU2wNNw9mn8dYan/mTSH83mGH9AfzRnrs/D0QN/b8lKBrQt
*/