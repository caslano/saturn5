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
A71Xs3aa8my69ykvUP7n5GnYdEnWy1rbrXamfTAUG6OOaRoWfdySsvwH8ygbOtv+4sjJcT4d9iKtRt/CYMhsc1KLe7rGB+fIiDBOIkT6yHPmExvnaKjdq04vQRUrAy1Addm96e4TKpHVCGuPPbpwZ/Ipc2a86X6DUog8lb4m7JDUhgUGCA3RZmfGm+6+OWriBqfGVAf/kS100OPnwia784x3TdMONrJyhXvuLW4YX9mm+z16XDjDoVlHyvefVKL8TO97Nt3vga1S36Xy7J3eHTSX57ZW0JkhYhmReIv0e9zJvkeCAB0ZmuTRhX+PReNX3WI2elYloiyTwJgM6BX4DGMsnh1Vxie/xfwYHRzqSZx4dODfY9HERTo6NPAxR02RwB/u9Ruoi5DM53kTlXG4lfNh04xWKixeE9q0mun4ty33O3ZJ1dRY+2yZKiZ5Bd/DHC8pExmSdLlfc8qV0dFFq6yZYQXlZ723b7EY3BYO9aJNdAwqLotiwUPvpZfvN9w2/+0Ws4urIimacOyDGziYukLghDmTOef2wawro67CbDb6SvAq+bLeISxAitz2Ww9KQO4Rn3N1iaoER3p1ZXTZ/nxpSesy5+iSI4YoLNMy6YIrpwEYl0hy/n/R0SWET60ps6xKA5L6jp5tVnpMO+WHMpY0SXrRqPK3Vl6xgoHgVUSJsnc8b+M6JIjYzzG/sfy4PH/Jz1g7Zl0nmiIdY7uVQeCE1bB4FrPfOcf2A20Wt2GVOeXDz4vV+aRqiBUTS/Yqt0+UmJo7hPz/Fx3GsCril3zeq1x7NO0SgdikxtFhQ6b817cd7J2DOYe3CpqkwSFVonWgMyQ3kNaMT8yR0QZ1V0VpKjJP+dyxuZbpPsFlhG2RROMYwwvnGBSYCTw3I/n3+AZriyiuujJU5xF+P/kJ0ydexefFBgHjXeTTQZusJOY1MOf9VE4XYH7Kk1zFOEkVyJn5oUrvKc47YwJ6lzgozAUrm1ad7xEOmXt451m8b9NnWLQHnwr31XM9Eq5HDkc5hsaV9MCOY/UVRA/dnsvnmc+7xxdNosro4X92wbRnpf2lTCeB5qzCuN9eJzOJGJ2eqfsHldUEbdpXLbqrUemkqobxtztlx5irYPpmTc7KXlzy5DEIaJ847963L4oex2SZ7hNk52LtyB03slhTISoZZsTK1lt45uqwZV9D5WCqw2V2EWItJC8NmHMrXfZhVrY0mMo85P1RRVSTpDWq7GdrW8OREwZJ3xV5HJcBe3qA+2bXHL4myBKs3CLjY5GdwLvr9iUmI6rKuI6ywd99tectn3dkCBnzGpdhyr4/uhsG4/DIHrlAQXX5BdMljru4b0Q/pcsYNjivdHHuWf7zRjdmD24VeUl2WhfzAp1tHHqOue/VTn/IuwLRrOSTvMr0BzvHz1Ie9B3svntEUQ2Tmo21PrSh1+vhqpXax+py56iMDmE1VSHTkAT0NQW+Ti865fZyDwn3Xtv7y93eD3bzq9l5VRsnfdSoNfKokP5Nu4m18+Etr2Z3yTqBaaxsAn3EQgLw1Isu6iRkODhz5uXvODqkOH/ps6RDw3vS/Y5q2Lj1y69msc8ZltiwHNbpbacAck/g3w5/EfRN0fUx/NPe1MD2noHx07+GxQ7HcKPALz2Wv30wIo//PfwaZkunVYX7KJDjTT1MlQnM+b8jIw2aPi3QlOGoCzaAWE/OsfRomneT8Yo8zoosGydD/7mjzVXn8MZBliVxWZWDvevv+tZ39vHXsFhKUcIVEg39b/tzR+vDuf01LOahSeqyUZ9/295v+S/z8nO49sso9ZZvLe1Qj4PJTe482Meou0gzpYA1E3kCGI99cs1NLL4OutRVP9gF/Aw=
*/