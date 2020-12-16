/* Copyright 2003-2019 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_KEY_HPP
#define BOOST_MULTI_INDEX_KEY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>

#if __cplusplus>=201703L||\
    defined(BOOST_MSVC)&&defined(__cpp_nontype_template_parameter_auto)

#define BOOST_MULTI_INDEX_KEY_SUPPORTED

#include <boost/multi_index/detail/is_function.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <type_traits>

namespace boost{

namespace multi_index{

/* C++17 terse key specification syntax */

namespace detail{

template<typename T,T,typename=void>
struct typed_key_impl;

template<typename Class,typename Type,Type Class::*PtrToMember>
struct typed_key_impl<
  Type Class::*,PtrToMember,
  typename std::enable_if<!is_function<Type>::value>::type
>
{
  using value_type=Class;
  using type=member<Class,Type,PtrToMember>;
};

#define BOOST_MULTI_INDEX_KEY_TYPED_KEY_IMPL(qualifier,extractor)            \
template<                                                                    \
  typename Class,typename Type,Type (Class::*PtrToMemberFunction)()qualifier \
>                                                                            \
struct typed_key_impl<Type (Class::*)()qualifier,PtrToMemberFunction>        \
{                                                                            \
  using value_type=Class;                                                    \
  using type=extractor<Class,Type,PtrToMemberFunction>;                      \
};

BOOST_MULTI_INDEX_KEY_TYPED_KEY_IMPL(                ,mem_fun)
BOOST_MULTI_INDEX_KEY_TYPED_KEY_IMPL(const           ,const_mem_fun)
BOOST_MULTI_INDEX_KEY_TYPED_KEY_IMPL(volatile        ,volatile_mem_fun)
BOOST_MULTI_INDEX_KEY_TYPED_KEY_IMPL(const volatile  ,cv_mem_fun)
BOOST_MULTI_INDEX_KEY_TYPED_KEY_IMPL(&               ,ref_mem_fun)
BOOST_MULTI_INDEX_KEY_TYPED_KEY_IMPL(const&          ,cref_mem_fun)
BOOST_MULTI_INDEX_KEY_TYPED_KEY_IMPL(volatile&       ,vref_mem_fun)
BOOST_MULTI_INDEX_KEY_TYPED_KEY_IMPL(const volatile& ,cvref_mem_fun)

#undef BOOST_MULTI_INDEX_KEY_TYPED_KEY_IMPL

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct typed_key_impl<Type (*)(Value),PtrToFunction>
{
  using value_type=Value;
  using type=global_fun<Value,Type,PtrToFunction>;
};

template<typename T>
struct remove_noexcept{using type=T;};

#define BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(qualifier) \
template<typename R,typename C,typename... Args>                \
struct remove_noexcept<R(C::*)(Args...)qualifier noexcept>      \
  {using type=R(C::*)(Args...)qualifier;};                      \
                                                                \
template<typename R,typename C,typename... Args>                \
struct remove_noexcept<R(C::*)(Args...,...)qualifier noexcept>  \
  {using type=R(C::*)(Args...,...)qualifier;};

BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(BOOST_PP_EMPTY())
                                             /* VS warns without dummy arg */
BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(const)
BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(volatile)
BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(const volatile)
BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(&)
BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(const&)
BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(volatile&)
BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(const volatile&)
BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(&&)
BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(const&&)
BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(volatile&&)
BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT(const volatile&&)

#undef BOOST_MULTI_INDEX_KEY_REMOVE_MEMFUN_NOEXCEPT

template<typename R,typename... Args>
struct remove_noexcept<R(*)(Args...)noexcept>{using type=R(*)(Args...);};
template<typename R,typename... Args>
struct remove_noexcept<R(*)(Args...,...)noexcept>
  {using type=R(*)(Args...,...);};

template<typename T>
using remove_noexcept_t=typename remove_noexcept<T>::type;

template<auto... Keys>
struct key_impl;

template<auto Key>
struct key_impl<Key>:typed_key_impl<remove_noexcept_t<decltype(Key)>,Key>{};

template<typename... Ts>
struct least_generic;

template<typename T0,typename... Ts>
struct least_generic<T0,Ts...>
{
  using type=T0;
};

template<typename T0,typename T1,typename... Ts>
struct least_generic<T0,T1,Ts...>
{
  static_assert(
    std::is_convertible<const T0&,const T1&>::value||
    std::is_convertible<const T1&,const T0&>::value,
    "one type should be convertible to the other");
    
  using type=typename least_generic<
    typename std::conditional<
      std::is_convertible<const T0&,const T1&>::value,T0,T1
    >::type,
    Ts...
  >::type;
};

template<auto Key0,auto... Keys>
struct key_impl<Key0,Keys...>
{
  using value_type=typename least_generic<
    typename std::decay<typename key_impl<Key0>::value_type>::type,
    typename std::decay<typename key_impl<Keys>::value_type>::type...
  >::type;
  using type=composite_key<
    value_type,
    typename key_impl<Key0>::type,
    typename key_impl<Keys>::type...
  >;
};

template<typename=composite_key<void,void>>
struct composite_key_size;

template<typename... Args>
struct composite_key_size<composite_key<Args...>>
{
  static constexpr auto value=sizeof...(Args)-1;
};

template<auto... Keys>
struct limited_size_key_impl
{
  static_assert(
    sizeof...(Keys)<=composite_key_size<>::value,
    "specified number of keys must meet the limits of "
    "boost::multi_index::composite_key");
  using type=typename key_impl<Keys...>::type;
};

} /* namespace multi_index::detail */

template<auto... Keys>
using key=typename detail::limited_size_key_impl<Keys...>::type;

} /* namespace multi_index */

} /* namespace boost */

#endif
#endif

/* key.hpp
LINQ9JRhkxPLK6dBUxOBbmLaOZUJMpH6aZn70hdlJQuVFj8+XIt5nq9+qZdjy2dWZuea30U/LY8/S3SFkYhyWVVOkAtZhHEhj9yJLkwL1VUqDWnpJiot2o7HzCuUpRMwM6xTo/uRPz5Eha/TMjvw1vZH+ipsUzhwr3lVNTZSXyY6LXhjC7Mwfspfye/Ll4nvekFZ3eladXZN/YVzCDXe/Hov3G864k1NHymfe9iT00f37TnwvL3T8uiUyvO4LGCfq+FtpLzSO1JNH5lyqkz604flkaosjsj6TtSfFVcx2d3ST6j51co0yGfxkakRxF7cqbFVMBivNgrpPPrnGlueXe2p05A12HdCBSh/bgNwVhU0KL91I2B6Mj+rDiEX1MFhXcRkjvermnMKNOtsJlg2SjD9SIasAzS2rjJrMG7GT8vIv8AOs/7uTR3FS+z3NfiuXyO+sKoP8Rbn1MWe+2I5v4KfN2WeLFxPev9POf9+L0ya/gtRLMNpbYt2euoFlZwuSlWkckrnm+GNDNKgWlBOp4VTHZaePKzKRnF+q/VA0pQlWahH089TvXodl//WWBwWztRzD8taGCSnp+JcqjqVV9oWTWdCserMY3fTPtnhWUrXJsc6gEN5z66tqwPhbmPjHudif2FlAifxiO3hGMzq0caL+CvD9InMbO2DCTlX/jbIUSvAM2CBFf1dDeXAyqaZx5r68/cBriH1TB26MMCZXlPbKv27ga+w7M4UUVIk1R3b2DF1iI5FVzosixDb1aEYf7N9HjGefY/BexmIW1lHfPAiZ2jWob5qdICLJLRjgRyWddjG1zYBPrtm1pxKWnnD0Pd7kHNuc8PRXcFsbZVyHXZLyN3vLYTTXBxZoz7o/oRlCA9gZsDYGusRSN9/weoTithJC3nnNgtMeT4S2mjdJ9BGir3BY5o+v0P7/KnsCB0YoC3/sd/OnSz2nSnQcmRKNewjqOyJDa8zhPfcIi3K5xfQnaDODe3c+stIP+yNQ3hxUTNN2KNDw1ZJj4NYKqVPbbibbh1Pk1na9/rDJ3RvWZVZ7L1gWiohqEz8LsKnOmZo4D7MH95hGJy5QXeFa44nbzC4decQv8MlJqhMqritOfv2jYyzuHxyWnkbJjoYjvWO2SHZPko4WsWcsklY+5Skbe3NlEeq8NJCF+Nzk3FwGEa8u4ni0A6VEbjTvf6dPIqbrIKpkaKtnVlFPdlmxsP5Fe6NIM4aGOb57i0G5/cP347fV4fm+cO3Iqc1z79JcZ7nyInuQThj7eH8gnEGw1m7J8N52eK7MuTcsmwvMl572e7chpzWsr3EcCxbxHfdG3FWZmgrCfHW7hHb2s77NDxsSmQud1/A+DwP71cTDEzL2z5RJ7cDzuaBuDaYPMPeukZVVlVBqH0n7Bk/iv9xHEHuu5/hd3W8LPKdtNBCqsOeUE4XtODe7gsHbG5OUdmnq7AiGWf1SkRlXk3HvYIz/FwkyHwZxLIQZ5ZOLS2/Uj1lbvLasj2wxuMncz+r/NTti6nqYtvPfTOVyUQsZZ54EQSl52gLc12+53GRpSN3stJJvRhvHrB0XKPcSiR+4vlOkfXjU/cBaDc0Me+KqZznikTFKI0Cnc/qb7p6RFUnMOPoqWFbxXEWjlP2TZn6eWiv6J8x/orlpStkmgRVlKsz7P2o7nl1bjYP8HCBu4Z2Fni+RkmayCzH4iCarDMxOuZPJnFZVGEqxSvGag/ee9b39Ld8TNp3UBnXF35ZJo6b5TS+mSrGffR/5gypCT8w52RMl8pHN3Wj2M0GdMU+1YR2GUweCktPUBRVXKQJ1YO5z3WIZ5v6b+tIZBH6RUR1SOw0UQWW47wlH7m5DDxXUvkjppc=
*/