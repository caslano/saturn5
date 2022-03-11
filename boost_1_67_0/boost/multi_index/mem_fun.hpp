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