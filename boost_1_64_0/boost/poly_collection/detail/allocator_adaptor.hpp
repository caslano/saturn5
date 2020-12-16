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
jIVj3LuO9o49gG4Y10e4tnId5Up/mzHc1Snz8JE4+u6h/afRL46Di812yt9f7EyQK0x9lHylHD39nLyWeUnpr+H9DSXO+I+hP73Yib2pxJk6ybiLHp0boTdTVy1tv5m51Ucpdzv417jvb3PvJSz1gy+/odiJV0Hn7+k1JbQLZjfl/oIcz6dMJ5tY3fYuhc8a7j9MuWuK2c9PG3P5PMbzrxFytQ7vXYqyb8LHN8AlvHns9KES3teDr5eUOBNd6P/3PFfqJw87TA74MWTS85DJEfzgcuTdQrtJZMcOZa+ifTBjL0TGB9HzUvoqfKdPo93XUtdabLUf+i5w82h3J9+fR12LoaGbDrduyjoP4vuvp+5lyLCRed4OdEA9Ux1ue5RdN5vfs+FCB85J/PsryMOaSXqaOo7D5zNmO6NvRcd70c0O8FfBA22WHkIX8Df5B3SxBR1eRt5+fbEzGsMfXwnPP6Gem8B3oRt+BG/sGu7T7gg2m/hIsVMKLn0AOdFbmvuj10CrAHMz+Sv6cuNUx1p0gf7L/uH6CXK8guuaEqf0Np7d/ZA293D/5ei6Ehx8lb8Ff0GOMv6OXUr5Yvg4iZw15IHT6OaN8PRBeF+PnK+Gthren1fCfXziYmzl2oJyZXPRRxF/U8/0i2n/ZZRx9XgF9y5D523o8Q3k9eUl0Ip5Z5/75L4dlyHn/eBeCU+rqeeVXB/Dbkf47EGH1dikHPt8DF5dGy6lPy3yfLfMzTGwz4hr429Sx8PQ31vsTF8Nz29AFnQ60Ysst/P9PvjBn8ZKKUtfGb+WuVo9mKvQySH8LgHfjxY75b+Gt9YSZ6SpxIn9Cx5j6HY35dLMTS7HB/bT1n7Kv486XzKLCxts5fMT1F8Cr29Er9wb3+72D/gp5/4f8YeX4Rtx7PCaEic9lz7yB+5vBfsgn5V8VnBdTxv4HHvs8X90hi7HL8BuH6f+QeS9CJ/mXvzt8IFfjW+Hju5jZ6HDjyDLJXxSTyllJ1+KvumPIwfxub9j26Pw5kCDPnIj9a+nj/0YX6D98V/xXD7J39i4rBPaI7Odsvncf2ex0wF+GhnG9jv4Fm1jjzJ0P+L2sYPUVUX9y+C9CD5cH6Jc2QlkfRU8LqW9X6Kfp4P/KWUpN0VcmXwYXpvRQ8L9mz7wAOVjyLgXmdGj82wu109d/aLP0ttom/42djXtuXEOuUZraO83xMFLwH0WW6LX6VfQzw+BqeX6Hn6CH4y9H3tfCJ46453w8KMi+iN1vAwa/jy1gL9XI98I8e9hZLm6hJyDsp9AJ/iPm1ukD8Gr63vj8PUpN0ZwuTHkLHR0otgZwTYdq5EJnsvdmPs32kcXE24Z+Csrh9YNvwOUw7bT/ch9ECz6iLVSFv+Io4P0Q+gqw9/YIT6CDT+Mr4GN345/XurNAzrc79h3qpu/r8c+/O28i9jQQFyGT+cO6nkK8hbha8/Ejqu4TtIufX6SsrFD2Og16NNttx2fegR93A+PB5HxM15cd1weX458U8SAGO0+B7+i3tEP4fM/od3nc72UvsVnHL2PlhPD3jHbmYaH2B/BY7P0zci/BjnpzxMvJcbspgz9vcz1T+LjOLoYe8B7Zl9+Cbw9Cx8hfo/3lzjxrcSSD4MbgL9XU9cB+Hb7+hOo7yT4Sr6DHbkarPssYg52B5tOg3d16vot5UYYa0eJqWXYhnev0B3tVxehd9qiv4+6fkAMjZUg60eI36XI+FXo9PNp6pqei49jvzi2HBtCX/eBo99OfovrTbRLjjd9AF/pplw/f1PXBLF6ir4xWQEv19LG3fTRrxGj+tCl26exbfoH6KOXeiuINdh1/AByNCDzVej5IFjqjvcgo8sn/I//E5w=
*/