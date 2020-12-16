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
qqpX5jcWlhrlPc3LK6vYDeLSrti5mXYe4wGxNCMRJLETRLFfMW2uYqgYw2Br6/spjD8VQWHZZeiDYRFujJ9alVdMWX0dwKGJ5f4EkxGKxHecKJWVx5JXE4NsbpwZLLg7+oIZOcZuDGdxzlHzPdid98k6vQnSRr4He83wPRgA8T0Y+vtY4/u7MA1COy+u+u2t3t/dhux1XttpVf4Q86YOYFoWD3J2MDYOGFO5GRv6lnomQObqG0xzvfl7TC/Mr8+Vas+rbQ/jNL5397R8G7SgabPbCO1xCwMae3u5Q2hBd8OXGuBR2TRiZpj+OsU8WFoHu4AS01Pk/doGxRSbG/LBsNs9sXnqiGqFBwsoL/rBGyNYt9vvnpLDqdv3Hiu7xhG1w1VwlD1B8Q9ooh8sZvG+5CTHQqdTyAeLexyUpK7Ow2Wj3GV/bUH6Z31wb1XewT2yoWybYmp4RnPJwD9w0O0XJx4l431Fq3AXTTE8WNUJ1ttFypNJ6fOnuvba6QeL/Qfxvsju92Gc9cfVQYS7mrZuxmAfkzQ9l9P27s/3Bt2hf+p9a6Z/6iRPS78Uwy40kNl/bG9huDY/UvcVwrsf/HyneRwGti0AeQR+FE8ffh4LPz34WUDC/Q7B7xT8nIYfvZY9VNvemXxP5Knju6ljKflqTlpTbMrKrbQdNdPNYyqPrqS6JUrH8b3MZFsikfnOLStXsgv4Wcd8rqry4E9K8nq7vl7zmbxCuI6TRbGXXbW8ewyL4sOPSuEo/osm+gA9D7M5yhVRmAdJWhZ1JPV7qOc5cKKAdzN78ABIhgWrvRPr8xc5r4Lfxp231/NHc/oAu89L5UgLHxzl8nqCigc+J88pZXLyekJqlaXnQp4ANy4HYXkkcpmfEvVOR908h6igK/BMA8/zO0DTaS6sb/YWdXwN5L/AMIu9Lj3v3YY02l+RPjlB6TJw++NOSs8iy2g7+uUOoM/J1WBhHlxOLfbW5qpBhJeTMR/rOwFLhxmJYTHJaXPLQMMYDYqGQ5fwfYLQNONBvc9cMeMtRmFk2aKqSXgnpT2l8L3JJcbnCdeJo8J1I80IhhHGSfa2u1a5fpCFUZxmhV/zalc0sEjJKbB7WvNjXE/KX8DZbJm7biCGrY+eDHoYM2CVlzMJA1+yOZoJEmPZJfuT0uDNi8K3o8zVvKDqm7zoZ4DnNczTws/DRPhReQSckHSB24jzf3qVv2NM/DjLA1tAvchHEdCPHm3GFH22kUc/LTMvKfCusXRkcXJ6qXtarreN8r3C4A29oszsMkDeim9aimjwvpfxeqIMi9Cz7Rx5wW/KXKW1mPu+3zJeR+RB7NsQr7m3vNw9BbOITFjuInqnehuaF/X4NXMfU8JZeCTksxaIALlyArylr52s2Qe6D4EO92U5z5y/EcxDugFRx1M+q8O7yA3mjSmd63l3ID7OX0/0PAUmut4t9Z6aro9Ar9yxXRfS2oBx/Qgaswz2Pr1TUq3VMVgwzs4bcI6pMFTnfEoH6FwGPG+mmEsMs7pGYJhXQfQzyGp/YalP78HfeIX1zcgvYivzIkFSxk6C/nAoj5OJPI5cN3Kv/ixDyqSx1B++wmxbaVwoS54cTZtgMnTz2t+gxi9R/IwXe3nm16vY/Q7NLjbifaxTfCqyIPJzR+Kn4LHABujDkIgRP5rXS54VSW6lMRsGpi+NF1GeUqSuH7tlkCBP5YqIp/MmVvY4S6M8yhyVN4j9ixmjbfZenre4DEIn9V1Mxyly38zbZyhPJhzf88I8LIVuppkFbGe1L/rqjOwbqh/j9mquapBqTH1d0m+u6FATPblXfQJBVOc835IYyMtcVrgPTD2lA3xHf4vqj2PEh5z888YOUGE=
*/