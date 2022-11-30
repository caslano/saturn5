/* Copyright 2016-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_VALUE_HOLDER_HPP
#define BOOST_POLY_COLLECTION_DETAIL_VALUE_HOLDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/core/addressof.hpp>
#include <boost/poly_collection/detail/is_constructible.hpp>
#include <boost/poly_collection/detail/is_equality_comparable.hpp>
#include <boost/poly_collection/detail/is_nothrow_eq_comparable.hpp>
#include <boost/poly_collection/exception.hpp>
#include <new>
#include <memory>
#include <type_traits>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* Segments of a poly_collection maintain vectors of value_holder<T>
 * rather than directly T. This serves several purposes:
 *  - value_holder<T> is copy constructible and equality comparable even if T
 *    is not: executing the corresponding op results in a reporting exception
 *    being thrown. This allows the segment to offer its full virtual
 *    interface regardless of the properties of the concrete class contained.
 *  - value_holder<T> emulates move assignment when T is not move assignable
 *    (nothrow move constructibility required); this happens most notably with
 *    lambda functions, whose assignment operator is deleted by standard
 *    mandate [expr.prim.lambda]/20 even if the compiler generated one would
 *    work (capture by value).
 *  - value_holder ctors accept a first allocator arg passed by
 *    boost::poly_collection::detail::allocator_adaptor, for purposes
 *    explained there.
 *
 * A pointer to value_holder_base<T> can be reinterpret_cast'ed to T*.
 * Emplacing is explicitly signalled with value_holder_emplacing_ctor to
 * protect us from greedy T's constructible from anything (like
 * boost::type_erasure::any).
 */

struct value_holder_emplacing_ctor_t{};
constexpr value_holder_emplacing_ctor_t value_holder_emplacing_ctor=
  value_holder_emplacing_ctor_t();

template<typename T>
class value_holder_base
{
protected:
  typename std::aligned_storage<sizeof(T),alignof(T)>::type s;
};

template<typename T>
class value_holder:public value_holder_base<T>
{
  template<typename U>
  using enable_if_not_emplacing_ctor_t=typename std::enable_if<
    !std::is_same<
      typename std::decay<U>::type,value_holder_emplacing_ctor_t
    >::value
  >::type*;

  using is_nothrow_move_constructible=std::is_nothrow_move_constructible<T>;
  using is_copy_constructible=std::is_copy_constructible<T>;
  using is_nothrow_copy_constructible=std::is_nothrow_copy_constructible<T>;
  using is_move_assignable=std::is_move_assignable<T>;
  using is_nothrow_move_assignable=std::is_nothrow_move_assignable<T>;
  using is_equality_comparable=detail::is_equality_comparable<T>;
  using is_nothrow_equality_comparable=
    detail::is_nothrow_equality_comparable<T>;

  T*       data()noexcept{return reinterpret_cast<T*>(&this->s);}
  const T* data()const noexcept
                {return reinterpret_cast<const T*>(&this->s);}

  T&       value()noexcept{return *static_cast<T*>(data());}
  const T& value()const noexcept{return *static_cast<const T*>(data());}

public:
  template<
    typename Allocator,
    enable_if_not_emplacing_ctor_t<Allocator> =nullptr
  >
  value_holder(Allocator& al,const T& x)
    noexcept(is_nothrow_copy_constructible::value)
    {copy(al,x);}
  template<
    typename Allocator,
    enable_if_not_emplacing_ctor_t<Allocator> =nullptr
  >
  value_holder(Allocator& al,T&& x)
    noexcept(is_nothrow_move_constructible::value)
    {std::allocator_traits<Allocator>::construct(al,data(),std::move(x));}
  template<
    typename Allocator,typename... Args,
    enable_if_not_emplacing_ctor_t<Allocator> =nullptr
  >
  value_holder(Allocator& al,value_holder_emplacing_ctor_t,Args&&... args)
    {std::allocator_traits<Allocator>::construct(
      al,data(),std::forward<Args>(args)...);}
  template<
    typename Allocator,
    enable_if_not_emplacing_ctor_t<Allocator> =nullptr
  >
  value_holder(Allocator& al,const value_holder& x)
    noexcept(is_nothrow_copy_constructible::value)
    {copy(al,x.value());}
  template<
    typename Allocator,
    enable_if_not_emplacing_ctor_t<Allocator> =nullptr
  >
  value_holder(Allocator& al,value_holder&& x)
    noexcept(is_nothrow_move_constructible::value)
    {std::allocator_traits<Allocator>::construct(
      al,data(),std::move(x.value()));}

  /* stdlib implementations in current use are notoriously lacking at
   * complying with [container.requirements.general]/3, so we keep the
   * following to make their life easier.
   */

  value_holder(const T& x)
    noexcept(is_nothrow_copy_constructible::value)
    {copy(x);}
  value_holder(T&& x)
    noexcept(is_nothrow_move_constructible::value)
    {::new ((void*)data()) T(std::move(x));}
  template<typename... Args>
  value_holder(value_holder_emplacing_ctor_t,Args&&... args)
    {::new ((void*)data()) T(std::forward<Args>(args)...);}
  value_holder(const value_holder& x)
    noexcept(is_nothrow_copy_constructible::value)
    {copy(x.value());}
  value_holder(value_holder&& x)
    noexcept(is_nothrow_move_constructible::value)
    {::new ((void*)data()) T(std::move(x.value()));}
 
  value_holder& operator=(const value_holder& x)=delete;
  value_holder& operator=(value_holder&& x)
    noexcept(is_nothrow_move_assignable::value||!is_move_assignable::value)
    /* if 2nd clause: nothrow move constructibility required */
  {
    move_assign(std::move(x.value()));
    return *this;
  }

  ~value_holder()noexcept{value().~T();}

  friend bool operator==(const value_holder& x,const value_holder& y)
    noexcept(is_nothrow_equality_comparable::value)
  {
    return x.equal(y.value());
  }

private:
  template<typename Allocator>
  void copy(Allocator& al,const T& x){copy(al,x,is_copy_constructible{});}

  template<typename Allocator>
  void copy(Allocator& al,const T& x,std::true_type)
  {
    std::allocator_traits<Allocator>::construct(al,data(),x);
  }

  template<typename Allocator>
  void copy(Allocator&,const T&,std::false_type)
  {
    throw not_copy_constructible{typeid(T)};
  }

  void copy(const T& x){copy(x,is_copy_constructible{});}

  void copy(const T& x,std::true_type)
  {
    ::new (data()) T(x);
  }

  void copy(const T&,std::false_type)
  {
    throw not_copy_constructible{typeid(T)};
  }

  void move_assign(T&& x){move_assign(std::move(x),is_move_assignable{});}

  void move_assign(T&& x,std::true_type)
  {
    value()=std::move(x);    
  }

  void move_assign(T&& x,std::false_type)
  {
    /* emulated assignment */

    static_assert(is_nothrow_move_constructible::value,
      "type should be move assignable or nothrow move constructible");

    if(data()!=boost::addressof(x)){
      value().~T();
      ::new (data()) T(std::move(x));
    }
  }

  bool equal(const T& x)const{return equal(x,is_equality_comparable{});}

  bool equal(const T& x,std::true_type)const
  {
    return value()==x;
  }

  bool equal(const T&,std::false_type)const
  {
    throw not_equality_comparable{typeid(T)};
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* value_holder.hpp
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
*/