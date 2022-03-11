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