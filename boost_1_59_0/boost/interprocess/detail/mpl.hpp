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
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
*/