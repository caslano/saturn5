/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_GLOBAL_FUN_HPP
#define BOOST_MULTI_INDEX_GLOBAL_FUN_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>

#if !defined(BOOST_NO_SFINAE)
#include <boost/type_traits/is_convertible.hpp>
#endif

namespace boost{

template<class T> class reference_wrapper; /* fwd decl. */

namespace multi_index{

namespace detail{

/* global_fun is a read-only key extractor from Value based on a given global
 * (or static member) function with signature:
 *
 *   Type f([const] Value [&]);
 *
 * Additionally, global_fun  and const_global_fun are overloaded to support
 * referece_wrappers of Value and "chained pointers" to Value's. By chained
 * pointer to T we  mean a type P such that, given a p of Type P
 *   *...n...*x is convertible to T&, for some n>=1.
 * Examples of chained pointers are raw and smart pointers, iterators and
 * arbitrary combinations of these (vg. T** or unique_ptr<T*>.)
 */

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct const_ref_global_fun_base
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,Value>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(Value x)const
  {
    return PtrToFunction(x);
  }

  Type operator()(
    const reference_wrapper<
      typename remove_reference<Value>::type>& x)const
  { 
    return operator()(x.get());
  }

  Type operator()(
    const reference_wrapper<
      typename remove_const<
        typename remove_reference<Value>::type>::type>& x

#if BOOST_WORKAROUND(BOOST_MSVC,==1310)
/* http://lists.boost.org/Archives/boost/2015/10/226135.php */
    ,int=0
#endif

  )const
  { 
    return operator()(x.get());
  }
};

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct non_const_ref_global_fun_base
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<ChainedPtr&,Value>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(Value x)const
  {
    return PtrToFunction(x);
  }

  Type operator()(
    const reference_wrapper<
      typename remove_reference<Value>::type>& x)const
  { 
    return operator()(x.get());
  }
};

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct non_ref_global_fun_base
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Value&>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(const Value& x)const
  {
    return PtrToFunction(x);
  }

  Type operator()(const reference_wrapper<const Value>& x)const
  { 
    return operator()(x.get());
  }

  Type operator()(
    const reference_wrapper<typename remove_const<Value>::type>& x)const
  { 
    return operator()(x.get());
  }
};

} /* namespace multi_index::detail */

template<class Value,typename Type,Type (*PtrToFunction)(Value)>
struct global_fun:
  mpl::if_c<
    is_reference<Value>::value,
    typename mpl::if_c<
      is_const<typename remove_reference<Value>::type>::value,
      detail::const_ref_global_fun_base<Value,Type,PtrToFunction>,
      detail::non_const_ref_global_fun_base<Value,Type,PtrToFunction>
    >::type,
    detail::non_ref_global_fun_base<Value,Type,PtrToFunction>
  >::type
{
};

} /* namespace multi_index */

} /* namespace boost */

#endif

/* global_fun.hpp
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
*/