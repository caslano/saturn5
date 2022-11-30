/* Copyright 2003-2019 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_MEM_FUN_HPP
#define BOOST_MULTI_INDEX_MEM_FUN_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>

#if !defined(BOOST_NO_SFINAE)
#include <boost/type_traits/is_convertible.hpp>
#endif

namespace boost{

template<class T> class reference_wrapper; /* fwd decl. */

namespace multi_index{

/* mem_fun implements a read-only key extractor based on a given non-const
 * member function of a class.
 * Also, the following variations are provided:
 *   const_mem_fun:    const member functions
 *   volatile_mem_fun: volatile member functions
 *   cv_mem_fun:       const volatile member functions
 *   ref_mem_fun:      ref-qualifed member functions (C++11)
 *   cref_mem_fun:     const ref-qualifed member functions (C++11)
 *   vref_mem_fun:     volatile ref-qualifed member functions (C++11)
 *   cvref_mem_fun:    const volatile ref-qualifed member functions (C++11)
 *
 * All of these classes are overloaded to support boost::referece_wrappers
 * of T and "chained pointers" to T's. By chained pointer to T we mean a type
 * P such that, given a p of Type P
 *   *...n...*x is convertible to T&, for some n>=1.
 * Examples of chained pointers are raw and smart pointers, iterators and
 * arbitrary combinations of these (vg. T** or unique_ptr<T*>.)
 */

namespace detail{

template<
  class Class,typename Type,
  typename PtrToMemberFunctionType,PtrToMemberFunctionType PtrToMemberFunction
>
struct const_mem_fun_impl
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Class&>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(const Class& x)const
  {
    return (x.*PtrToMemberFunction)();
  }

  Type operator()(const reference_wrapper<const Class>& x)const
  { 
    return operator()(x.get());
  }

  Type operator()(const reference_wrapper<Class>& x)const
  { 
    return operator()(x.get());
  }
};

template<
  class Class,typename Type,
  typename PtrToMemberFunctionType,PtrToMemberFunctionType PtrToMemberFunction
>
struct mem_fun_impl
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<ChainedPtr&,Class&>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(Class& x)const
  {
    return (x.*PtrToMemberFunction)();
  }

  Type operator()(const reference_wrapper<Class>& x)const
  { 
    return operator()(x.get());
  }
};

} /* namespace multi_index::detail */

template<class Class,typename Type,Type (Class::*PtrToMemberFunction)()const>
struct const_mem_fun:detail::const_mem_fun_impl<
  Class,Type,Type (Class::*)()const,PtrToMemberFunction
>{};

template<
  class Class,typename Type,
  Type (Class::*PtrToMemberFunction)()const volatile
>
struct cv_mem_fun:detail::const_mem_fun_impl<
  Class,Type,Type (Class::*)()const volatile,PtrToMemberFunction
>{};

template<class Class,typename Type,Type (Class::*PtrToMemberFunction)()>
struct mem_fun:
  detail::mem_fun_impl<Class,Type,Type (Class::*)(),PtrToMemberFunction>{};

template<
  class Class,typename Type,Type (Class::*PtrToMemberFunction)()volatile
>
struct volatile_mem_fun:detail::mem_fun_impl<
  Class,Type,Type (Class::*)()volatile,PtrToMemberFunction
>{};

#if !defined(BOOST_NO_CXX11_REF_QUALIFIERS)

template<
  class Class,typename Type,Type (Class::*PtrToMemberFunction)()const&
>
struct cref_mem_fun:detail::const_mem_fun_impl<
  Class,Type,Type (Class::*)()const&,PtrToMemberFunction
>{};

template<
  class Class,typename Type,
  Type (Class::*PtrToMemberFunction)()const volatile&
>
struct cvref_mem_fun:detail::const_mem_fun_impl<
  Class,Type,Type (Class::*)()const volatile&,PtrToMemberFunction
>{};

template<class Class,typename Type,Type (Class::*PtrToMemberFunction)()&>
struct ref_mem_fun:
  detail::mem_fun_impl<Class,Type,Type (Class::*)()&,PtrToMemberFunction>{};

template<
  class Class,typename Type,Type (Class::*PtrToMemberFunction)()volatile&
>
struct vref_mem_fun:detail::mem_fun_impl<
  Class,Type,Type (Class::*)()volatile&,PtrToMemberFunction
>{};

#endif

/* MSVC++ 6.0 has problems with const member functions as non-type template
 * parameters, somehow it takes them as non-const. const_mem_fun_explicit
 * workarounds this deficiency by accepting an extra type parameter that
 * specifies the signature of the member function. The workaround was found at:
 *   Daniel, C.:"Re: weird typedef problem in VC",
 *   news:microsoft.public.vc.language, 21st nov 2002, 
 *   http://groups.google.com/groups?
 *     hl=en&lr=&ie=UTF-8&selm=ukwvg3O0BHA.1512%40tkmsftngp05
 *
 * MSVC++ 6.0 support has been dropped and [const_]mem_fun_explicit is
 * deprecated.
 */

template<
  class Class,typename Type,
  typename PtrToMemberFunctionType,PtrToMemberFunctionType PtrToMemberFunction
>
struct const_mem_fun_explicit
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Class&>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(const Class& x)const
  {
    return (x.*PtrToMemberFunction)();
  }

  Type operator()(const reference_wrapper<const Class>& x)const
  { 
    return operator()(x.get());
  }

  Type operator()(const reference_wrapper<Class>& x)const
  { 
    return operator()(x.get());
  }
};

template<
  class Class,typename Type,
  typename PtrToMemberFunctionType,PtrToMemberFunctionType PtrToMemberFunction
>
struct mem_fun_explicit
{
  typedef typename remove_reference<Type>::type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<ChainedPtr&,Class&>,Type>::type
#else
  Type
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type operator()(Class& x)const
  {
    return (x.*PtrToMemberFunction)();
  }

  Type operator()(const reference_wrapper<Class>& x)const
  { 
    return operator()(x.get());
  }
};

/* BOOST_MULTI_INDEX_CONST_MEM_FUN and BOOST_MULTI_INDEX_MEM_FUN used to
 * resolve to [const_]mem_fun_explicit for MSVC++ 6.0 and to
 * [const_]mem_fun otherwise. Support for this compiler having been dropped,
 * they are now just wrappers over [const_]mem_fun kept for backwards-
 * compatibility reasons.
 */

#define BOOST_MULTI_INDEX_CONST_MEM_FUN(Class,Type,MemberFunName) \
::boost::multi_index::const_mem_fun< Class,Type,&Class::MemberFunName >
#define BOOST_MULTI_INDEX_MEM_FUN(Class,Type,MemberFunName) \
::boost::multi_index::mem_fun< Class,Type,&Class::MemberFunName >

} /* namespace multi_index */

} /* namespace boost */

#endif

/* mem_fun.hpp
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
*/