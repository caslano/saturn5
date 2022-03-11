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