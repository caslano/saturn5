//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_META_UTILS_CORE_HPP
#define BOOST_MOVE_DETAIL_META_UTILS_CORE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//Small meta-typetraits to support move

namespace boost {
namespace move_detail {

template<typename T>
struct voider { typedef void type; };

//////////////////////////////////////
//             if_c
//////////////////////////////////////
template<bool C, typename T1, typename T2>
struct if_c
{
   typedef T1 type;
};

template<typename T1, typename T2>
struct if_c<false,T1,T2>
{
   typedef T2 type;
};

//////////////////////////////////////
//             if_
//////////////////////////////////////
template<typename T1, typename T2, typename T3>
struct if_ : if_c<0 != T1::value, T2, T3>
{};

//////////////////////////////////////
//          enable_if_c
//////////////////////////////////////
struct enable_if_nat{};

template <bool B, class T = enable_if_nat>
struct enable_if_c
{
   typedef T type;
};

template <class T>
struct enable_if_c<false, T> {};

//////////////////////////////////////
//           enable_if
//////////////////////////////////////
template <class Cond, class T = enable_if_nat>
struct enable_if : enable_if_c<Cond::value, T> {};

//////////////////////////////////////
//          disable_if_c
//////////////////////////////////////
template <bool B, class T = enable_if_nat>
struct disable_if_c
   : enable_if_c<!B, T>
{};

//////////////////////////////////////
//          disable_if
//////////////////////////////////////
template <class Cond, class T = enable_if_nat>
struct disable_if : enable_if_c<!Cond::value, T> {};

//////////////////////////////////////
//          integral_constant
//////////////////////////////////////
template<class T, T v>
struct integral_constant
{
   static const T value = v;
   typedef T value_type;
   typedef integral_constant<T, v> type;

     operator T() const { return value; }
   T operator()() const { return value; }
};

typedef integral_constant<bool, true >  true_type;
typedef integral_constant<bool, false > false_type;


//////////////////////////////////////
//             is_same
//////////////////////////////////////
template<class T, class U>
struct is_same
{
   static const bool value = false;
};
 
template<class T>
struct is_same<T, T>
{
   static const bool value = true;
};

//////////////////////////////////////
//        enable_if_same
//////////////////////////////////////
template <class T, class U, class R = enable_if_nat>
struct enable_if_same : enable_if<is_same<T, U>, R> {};

//////////////////////////////////////
//        disable_if_same
//////////////////////////////////////
template <class T, class U, class R = enable_if_nat>
struct disable_if_same : disable_if<is_same<T, U>, R> {};

}  //namespace move_detail {
}  //namespace boost {

#endif //#ifndef BOOST_MOVE_DETAIL_META_UTILS_CORE_HPP

/* meta_utils_core.hpp
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
*/