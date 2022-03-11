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