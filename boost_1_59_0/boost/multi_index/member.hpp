/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_MEMBER_HPP
#define BOOST_MULTI_INDEX_MEMBER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <cstddef>

#if !defined(BOOST_NO_SFINAE)
#include <boost/type_traits/is_convertible.hpp>
#endif

namespace boost{

template<class T> class reference_wrapper; /* fwd decl. */

namespace multi_index{

namespace detail{

/* member is a read/write key extractor for accessing a given
 * member of a class.
 * Additionally, member is overloaded to support referece_wrappers
 * of T and "chained pointers" to T's. By chained pointer to T we mean
 * a type P  such that, given a p of Type P
 *   *...n...*x is convertible to T&, for some n>=1.
 * Examples of chained pointers are raw and smart pointers, iterators and
 * arbitrary combinations of these (vg. T** or unique_ptr<T*>.)
 */

template<class Class,typename Type,Type Class::*PtrToMember>
struct const_member_base
{
  typedef Type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Class&>,Type&>::type
#else
  Type&
#endif
  
  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type& operator()(const Class& x)const
  {
    return x.*PtrToMember;
  }

  Type& operator()(const reference_wrapper<const Class>& x)const
  {
    return operator()(x.get());
  }

  Type& operator()(const reference_wrapper<Class>& x)const
  { 
    return operator()(x.get());
  }
};

template<class Class,typename Type,Type Class::*PtrToMember>
struct non_const_member_base
{
  typedef Type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Class&>,Type&>::type
#else
  Type&
#endif

  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  const Type& operator()(const Class& x)const
  {
    return x.*PtrToMember;
  }

  Type& operator()(Class& x)const
  { 
    return x.*PtrToMember;
  }

  const Type& operator()(const reference_wrapper<const Class>& x)const
  {
    return operator()(x.get());
  }

  Type& operator()(const reference_wrapper<Class>& x)const
  { 
    return operator()(x.get());
  }
};

} /* namespace multi_index::detail */

template<class Class,typename Type,Type Class::*PtrToMember>
struct member:
  mpl::if_c<
    is_const<Type>::value,
    detail::const_member_base<Class,Type,PtrToMember>,
    detail::non_const_member_base<Class,Type,PtrToMember>
  >::type
{
};

namespace detail{

/* MSVC++ 6.0 does not support properly pointers to members as
 * non-type template arguments, as reported in
 *   http://support.microsoft.com/default.aspx?scid=kb;EN-US;249045
 * A similar problem (though not identical) is shown by MSVC++ 7.0.
 * We provide an alternative to member<> accepting offsets instead
 * of pointers to members. This happens to work even for non-POD
 * types (although the standard forbids use of offsetof on these),
 * so it serves as a workaround in this compiler for all practical
 * purposes.
 * Surprisingly enough, other compilers, like Intel C++ 7.0/7.1 and
 * Visual Age 6.0, have similar bugs. This replacement of member<>
 * can be used for them too.
 *
 * Support for such old compilers is dropped and
 * [non_]const_member_offset_base is deprecated.
 */

template<class Class,typename Type,std::size_t OffsetOfMember>
struct const_member_offset_base
{
  typedef Type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Class&>,Type&>::type
#else
  Type&
#endif 
    
  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type& operator()(const Class& x)const
  {
    return *static_cast<const Type*>(
      static_cast<const void*>(
        static_cast<const char*>(
          static_cast<const void *>(&x))+OffsetOfMember));
  }

  Type& operator()(const reference_wrapper<const Class>& x)const
  {
    return operator()(x.get());
  }

  Type& operator()(const reference_wrapper<Class>& x)const
  {
    return operator()(x.get());
  }
};

template<class Class,typename Type,std::size_t OffsetOfMember>
struct non_const_member_offset_base
{
  typedef Type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Class&>,Type&>::type
#else
  Type&
#endif 
  
  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  const Type& operator()(const Class& x)const
  {
    return *static_cast<const Type*>(
      static_cast<const void*>(
        static_cast<const char*>(
          static_cast<const void *>(&x))+OffsetOfMember));
  }

  Type& operator()(Class& x)const
  { 
    return *static_cast<Type*>(
      static_cast<void*>(
        static_cast<char*>(static_cast<void *>(&x))+OffsetOfMember));
  }

  const Type& operator()(const reference_wrapper<const Class>& x)const
  {
    return operator()(x.get());
  }

  Type& operator()(const reference_wrapper<Class>& x)const
  {
    return operator()(x.get());
  }
};

} /* namespace multi_index::detail */

template<class Class,typename Type,std::size_t OffsetOfMember>
struct member_offset:
  mpl::if_c<
    is_const<Type>::value,
    detail::const_member_offset_base<Class,Type,OffsetOfMember>,
    detail::non_const_member_offset_base<Class,Type,OffsetOfMember>
  >::type
{
};

/* BOOST_MULTI_INDEX_MEMBER resolves to member in the normal cases,
 * and to member_offset as a workaround in those defective compilers for
 * which BOOST_NO_POINTER_TO_MEMBER_TEMPLATE_PARAMETERS is defined.
 */

#if defined(BOOST_NO_POINTER_TO_MEMBER_TEMPLATE_PARAMETERS)
#define BOOST_MULTI_INDEX_MEMBER(Class,Type,MemberName) \
::boost::multi_index::member_offset< Class,Type,offsetof(Class,MemberName) >
#else
#define BOOST_MULTI_INDEX_MEMBER(Class,Type,MemberName) \
::boost::multi_index::member< Class,Type,&Class::MemberName >
#endif

} /* namespace multi_index */

} /* namespace boost */

#endif

/* member.hpp
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
*/