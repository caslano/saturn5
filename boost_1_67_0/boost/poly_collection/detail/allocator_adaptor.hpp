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