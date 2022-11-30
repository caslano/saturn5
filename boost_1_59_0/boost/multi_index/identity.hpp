/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_IDENTITY_HPP
#define BOOST_MULTI_INDEX_IDENTITY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/if.hpp>
#include <boost/multi_index/identity_fwd.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

#if !defined(BOOST_NO_SFINAE)
#include <boost/type_traits/is_convertible.hpp>
#endif

namespace boost{

template<class Type> class reference_wrapper; /* fwd decl. */

namespace multi_index{

namespace detail{

/* identity is a do-nothing key extractor that returns the [const] Type&
 * object passed.
 * Additionally, identity is overloaded to support referece_wrappers
 * of Type and "chained pointers" to Type's. By chained pointer to Type we
 * mean a  type  P such that, given a p of type P
 *   *...n...*x is convertible to Type&, for some n>=1.
 * Examples of chained pointers are raw and smart pointers, iterators and
 * arbitrary combinations of these (vg. Type** or unique_ptr<Type*>.)
 */

template<typename Type>
struct const_identity_base
{
  typedef Type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<is_convertible<const ChainedPtr&,Type&>,Type&>::type
#else
  Type&
#endif 
  
  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type& operator()(Type& x)const
  {
    return x;
  }

  Type& operator()(const reference_wrapper<Type>& x)const
  { 
    return x.get();
  }

  Type& operator()(
    const reference_wrapper<typename remove_const<Type>::type>& x

#if BOOST_WORKAROUND(BOOST_MSVC,==1310)
/* http://lists.boost.org/Archives/boost/2015/10/226135.php */
    ,int=0
#endif

  )const
  { 
    return x.get();
  }
};

template<typename Type>
struct non_const_identity_base
{
  typedef Type result_type;

  /* templatized for pointer-like types */
  
  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Type&>,Type&>::type
#else
  Type&
#endif 
    
  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  const Type& operator()(const Type& x)const
  {
    return x;
  }

  Type& operator()(Type& x)const
  {
    return x;
  }

  const Type& operator()(const reference_wrapper<const Type>& x)const
  { 
    return x.get();
  }

  Type& operator()(const reference_wrapper<Type>& x)const
  { 
    return x.get();
  }
};

} /* namespace multi_index::detail */

template<class Type>
struct identity:
  mpl::if_c<
    is_const<Type>::value,
    detail::const_identity_base<Type>,detail::non_const_identity_base<Type>
  >::type
{
};

} /* namespace multi_index */

} /* namespace boost */

#endif

/* identity.hpp
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
*/