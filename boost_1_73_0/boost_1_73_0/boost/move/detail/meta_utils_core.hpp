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
RN9RETAAefcVwROJSsjTp6bdybDjU93cmc/zWF8Jnzu4eF6KQZPla5A9x7kuhkyWr0F2XHfkGqUrAO6jHhSwu3QuJleviUI7FFugEaXXgBuP/0NHYyyV+It17lGpSHiKt/MVnU6T8fuhMOJBnCeboW2V2Va7g1o1TzmfBlF0dCCjT6qjmTlPY6ByfKyr7T/m3gIO4uKpyg5uLqayt6zNPcja3Xit/b9t/wJQSwMECgAAAAgALWdKUoAPa67rBAAAqAsAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDAyVVQFAAG2SCRgpVZtc9pGEP5+M/yHHSVubAoceNxMQ8Az2AibmgAjCadpkmrO0skoEXeqdDKhmfz37p14ceK0wVN9kHSn3Wdfnz11FM9VwHJ+SjqxiCQ+PvLVUmZhfkouPW9qbjCduB6p15P4JiiyhHToTqhDSz3yBFye3fGsnschJ52Mp8kKP4dMsRKKthotOG42YXJF+kzxNnjzogbHL+C3ItEffoXWSfvkRRtFLl55pIRrg3axnpsFjdhHTs6lUFyo+oiLWzVvQ3O7461SrhU+KZomLBb6g+CBiqVoQ5DInBN0uHSpQ9cuoufnSazVS88Ds0CB0uYpmSuVovhmCR3BFpiw
*/