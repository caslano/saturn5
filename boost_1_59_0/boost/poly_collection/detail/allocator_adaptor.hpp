/* Copyright 2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_ALLOCATOR_ADAPTOR_HPP
#define BOOST_POLY_COLLECTION_DETAIL_ALLOCATOR_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/mp11/function.hpp>
#include <boost/mp11/integer_sequence.hpp>
#include <boost/poly_collection/detail/is_constructible.hpp>
#include <new>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* [container.requirements.general]/3 state that containers must use the
 * allocator's construct/destroy member functions to construct/destroy
 * elements and *not at all* for any other type. Since poly_collection is
 * implemented as a multi-level structure of container and container-like
 * objects, we need to use an adaptor for the user-provided Allocator that
 * prevents intermediate entities from calling Allocator::[construct|destroy].
 * allocator_adaptor<Allocator> does this by taking advantage of the fact that
 * elements are ultimately held within a value_holder:
 *  - construct(value_holder<T>*,...) uses placement new construction and
 *    passes the wrapped Allocator object for value_holder<T> to use for
 *    its inner construction of T.
 *  - For the rest of types, construct uses placement new construction and
 *    passes down the adaptor object itself as an argument following an
 *    approach analogous to that of std::scoped_allocator_adaptor.
 *  - destroy(value_holder<T>) resorts to Allocator::destroy to destroy the
 *    contained T element.
 *  - For the rest of types, destroy(T) calls ~T directly.
 *
 * Code has been ripped and adapted from libc++'s implementation of
 * std::scoped_allocator_adaptor.
 */

template<typename T>
class value_holder_base;

template<typename T>
class value_holder;

template<typename T,typename Allocator,typename... Args>
struct uses_alloc_ctor_impl
{
    using RawAllocator=typename std::remove_cv<
      typename std::remove_reference<Allocator>::type
    >::type;

    static const bool ua=std::uses_allocator<T,RawAllocator>::value;
    static const int  ic=is_constructible<
      T,std::allocator_arg_t,Allocator,Args...>::value?1:0;
    static const int  value=ua?2-ic:0;
};

template<typename T,typename Allocator,typename... Args>
struct uses_alloc_ctor:
  std::integral_constant<int,uses_alloc_ctor_impl<T,Allocator,Args...>::value>
{};

template<typename Allocator,typename=void>
struct allocator_is_always_equal:std::is_empty<Allocator>{};

template<typename Allocator>
struct allocator_is_always_equal<
  Allocator,
  mp11::mp_void<
    typename std::allocator_traits<Allocator>::is_always_equal
  >
>:std::allocator_traits<Allocator>::is_always_equal{};

template<typename Allocator>
struct allocator_adaptor:Allocator
{
  using traits=std::allocator_traits<Allocator>;

  using value_type=typename traits::value_type;
  using size_type=typename traits::size_type;
  using difference_type=typename traits::difference_type;
  using pointer=typename traits::pointer;
  using const_pointer=typename traits::const_pointer;
  using void_pointer=typename traits::void_pointer;
  using const_void_pointer=typename traits::const_void_pointer;
  using propagate_on_container_copy_assignment=
    typename traits::propagate_on_container_copy_assignment;
  using propagate_on_container_move_assignment=
    typename traits::propagate_on_container_move_assignment;
  using propagate_on_container_swap=
    typename traits::propagate_on_container_swap;
  using is_always_equal=typename allocator_is_always_equal<Allocator>::type;

  template<typename U>
  struct rebind
  {
    using other=allocator_adaptor<typename traits::template rebind_alloc<U>>;
  };

  allocator_adaptor()=default;
  allocator_adaptor(const allocator_adaptor&)=default;

  template<
    typename Allocator2,
    typename std::enable_if<
      is_constructible<Allocator,const Allocator2&>::value
    >::type* =nullptr
  >
  allocator_adaptor(const Allocator2& x)noexcept:Allocator{x}{}

  template<
    typename Allocator2,
    typename std::enable_if<
      is_constructible<Allocator,const Allocator2&>::value
    >::type* =nullptr
  >
  allocator_adaptor(const allocator_adaptor<Allocator2>& x)noexcept:
    Allocator{x.allocator()}{}

  allocator_adaptor& operator=(const allocator_adaptor&)=default;

  Allocator&       allocator()noexcept{return *this;}
  const Allocator& allocator()const noexcept{return *this;}

  template<typename T,typename... Args>
  void construct(T* p,Args&&... args)
  {
    construct_(
      uses_alloc_ctor<T,allocator_adaptor&,Args...>{},
      p,std::forward<Args>(args)...);
  }

  template<typename T,typename... Args>
  void construct(value_holder<T>* p,Args&&... args)
  {
    ::new ((void*)p) value_holder<T>(allocator(),std::forward<Args>(args)...);
  }

  template<typename T1,typename T2,typename... Args1,typename... Args2>
  void construct(
    std::pair<T1,T2>* p,std::piecewise_construct_t,
    std::tuple<Args1...> x,std::tuple<Args2...> y)
  {
    ::new ((void*)p) std::pair<T1,T2>(
       std::piecewise_construct,
       transform_tuple(
         uses_alloc_ctor<T1,allocator_adaptor&,Args1...>{},
         std::move(x),
         mp11::make_index_sequence<sizeof...(Args1)>{}),
       transform_tuple(
         uses_alloc_ctor<T2,allocator_adaptor&,Args2...>{},
         std::move(y),
         mp11::make_index_sequence<sizeof...(Args2)>{})
    );
  }

  template<typename T1,typename T2>
  void construct(std::pair<T1,T2>* p)
  {
    construct(p,std::piecewise_construct,std::tuple<>{},std::tuple<>{});
  }

  template<typename T1,typename T2,typename U,typename V>
  void construct(std::pair<T1,T2>* p,U&& x,V&& y)
  {
    construct(
      p,std::piecewise_construct,
      std::forward_as_tuple(std::forward<U>(x)),
      std::forward_as_tuple(std::forward<V>(y)));
  }

  template<typename T1,typename T2,typename U,typename V>
  void construct(std::pair<T1,T2>* p,const std::pair<U,V>& x)
  {
    construct(
      p,std::piecewise_construct,
      std::forward_as_tuple(x.first),std::forward_as_tuple(x.second));
  }

  template<typename T1,typename T2,typename U,typename V>
  void construct(std::pair<T1,T2>* p,std::pair<U,V>&& x)
  {
    construct(
      p,std::piecewise_construct,
      std::forward_as_tuple(std::forward<U>(x.first)),
      std::forward_as_tuple(std::forward<V>(x.second)));
  }

  template<typename T>
  void destroy(T* p)
  {
    p->~T();
  }

  template<typename T>
  void destroy(value_holder<T>* p)
  {
    traits::destroy(
      allocator(),
      reinterpret_cast<T*>(static_cast<value_holder_base<T>*>(p)));
  }

  allocator_adaptor
  select_on_container_copy_construction()const noexcept
  {
    return traits::select_on_container_copy_construction(allocator());
  }

private:
  template<typename T,typename... Args>
  void construct_(
    std::integral_constant<int,0>,  /* doesn't use allocator */
    T* p,Args&&... args)
  {
    ::new ((void*)p) T(std::forward<Args>(args)...);
  }

  template<typename T,typename... Args>
  void construct_(
    std::integral_constant<int,1>, /* with std::allocator_arg */
    T* p,Args&&... args)
  {
    ::new ((void*)p) T(std::allocator_arg,*this,std::forward<Args>(args)...);
  }  

  template<typename T,typename... Args>
  void construct_(
    std::integral_constant<int,2>, /* allocator at the end */
    T* p,Args&&... args)
  {
    ::new ((void*)p) T(std::forward<Args>(args)...,*this);
  }

  template<typename... Args,std::size_t... I>
  std::tuple<Args&&...> transform_tuple(
    std::integral_constant<int,0>,  /* doesn't use allocator */
    std::tuple<Args...>&& t,mp11::index_sequence<I...>)
  {
    return std::tuple<Args&&...>(std::get<I>(std::move(t))...);
  }

  template<typename... Args,std::size_t... I>
  std::tuple<std::allocator_arg_t,allocator_adaptor&,Args&&...>
  transform_tuple(
    std::integral_constant<int,1>, /* with std::allocator_arg */
    std::tuple<Args...>&& t,mp11::index_sequence<I...>)
  {
    return std::tuple<
      std::allocator_arg_t,allocator_adaptor&,Args&&...>(
      std::allocator_arg,*this,std::get<I>(std::move(t))...);
  }

  template<typename... Args,std::size_t... I>
  std::tuple<Args&&...,allocator_adaptor&>
  transform_tuple(
    std::integral_constant<int,2>, /* allocator at the end */
    std::tuple<Args...>&& t,mp11::index_sequence<I...>)
  {
    return std::tuple<Args&&...,allocator_adaptor&>(
      std::get<I>(std::move(t))...,*this);
  }
};

template<typename Allocator1,typename Allocator2>
bool operator==(
  const allocator_adaptor<Allocator1>& x,
  const allocator_adaptor<Allocator2>& y)noexcept
{
  return x.allocator()==y.allocator();
}

template<typename Allocator1,typename Allocator2>
bool operator!=(
  const allocator_adaptor<Allocator1>& x,
  const allocator_adaptor<Allocator2>& y)noexcept
{
  return !(x==y);
}

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* allocator_adaptor.hpp
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
*/