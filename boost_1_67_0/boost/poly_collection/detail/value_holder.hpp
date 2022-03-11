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