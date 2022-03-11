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
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
*/