/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_CALLABLE_WRAPPER_HPP
#define BOOST_POLY_COLLECTION_DETAIL_CALLABLE_WRAPPER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/detail/is_invocable.hpp>
#include <functional>
#include <type_traits>
#include <typeinfo>

namespace boost{

namespace poly_collection{

namespace detail{

/* lightweight std::function look-alike over non-owned callable entities */

template<typename Signature>
class callable_wrapper;

template<typename R,typename... Args>
class callable_wrapper<R(Args...)>
{
public:
  // TODO: we should prevent assignment by user code
  template<
    typename Callable,
    typename std::enable_if<
      !std::is_same<Callable,callable_wrapper>::value&&
      is_invocable_r<R,Callable,Args...>::value
    >::type* =nullptr
  >
  explicit callable_wrapper(Callable& x)noexcept:pt{info(x)},px{&x}{}
  callable_wrapper(const callable_wrapper&)=default;
  callable_wrapper& operator=(const callable_wrapper&)=default;

  explicit operator bool()const noexcept{return true;}

  R operator()(Args... args)const
    {return pt->call(px,std::forward<Args>(args)...);}

  const std::type_info& target_type()const noexcept{return pt->info;}

  template<typename T>
  T*       target()noexcept
             {return typeid(T)==pt->info?static_cast<T*>(px):nullptr;}
  template<typename T>
  const T* target()const noexcept
             {return typeid(T)==pt->info?static_cast<const T*>(px):nullptr;}

  /* not in std::function interface */

  operator std::function<R(Args...)>()const noexcept{return pt->convert(px);}

  void*       data()noexcept{return px;}
  const void* data()const noexcept{return px;}

private:
  struct table
  {
    R(*call)(void*,Args...);
    const std::type_info& info;
    std::function<R(Args...)> (*convert)(void*);
  };

  template<typename Callable>
  static table* info(Callable&)noexcept
  {
    static table t={
      [](void* p,Args... args){
        auto r=std::ref(*static_cast<Callable*>(p));
        return static_cast<R>(r(std::forward<Args>(args)...));
      },
      typeid(Callable),
      [](void* p){
        auto r=std::ref(*static_cast<Callable*>(p));
        return std::function<R(Args...)>{r};
      }
    };
    return &t;
  }

  table* pt;
  void*  px;
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* callable_wrapper.hpp
4MOmfLmPEdGyQ8ynqT9Y5X3f8zFXViQqQu1Ya2cdOTgBrLXkdA491J6Ve4/YuMrC7Y3m4PLbG8uh57fnz2EtXKi1Lj9ftTEimvKTFi3UCvmg2jiYzUe7Knuwo/9M1ukWnd9ly9J7Krui6V/alI1dNa3b4u0tTGF7ewc67XWKOVtsOkHIfZJjrUEebbfo3qOTtOH/ls02TU+qQNj1f8HDtMTrmuHPBbHGmwrmtpd59Naq5trEjv0ZFi2CnOYKj/e61lbymWDN1cwhOXcqS4dpUlLr+d3E9uz96mZ3uvuS1OCAE+SjX/dp/cN9TB94CDKo9jj/XDRLFru9KwI6j/6CceWYqZP6+it3wErAy/cCGqSefru+46Jpi0y/ud/lt+MaI7jffbm5P9zZlw7ylAnOOOE+47mfQ2sjiPIapjd+ftphsMuZjOzjGuxVH9L4H6LbD4OttfbpF3q6Zzw0bcqFQ02TN1JGz5jyyqjb5JfxY3mbX0bjuj38Bn32xZ7O3P0GVEHN5onTIPqyY4mP0zPo3f0M9YldzarQ+PaVAW5XMA8CZ+UmBwJMTbK3U5xln2Ynjf1fHsJUU7UpfyigbfZkq3JXwFhIDMq/MVR+2Mpnrg3R9lm060O0Kmv+MxaiyQbwHcj2wTzeqsVbMH+bdjGsoFlZvqtSbaCPrbB9fdyrD8TuocxuJ9PMfYd/h3jPaZazdm2iJpYor6mNbWzcsCG+sW5DbO0K/lfJxX8HWLLBI9deUrF2Bf8v37m20v1aSXbqekZM66p8ZM+AnU07Pk/iBtLac5zT5hWVQufk072pwU3Yqym5r6dvuI8OAm12ltaOVqoaG6urajYm4q0NLa0N7dsSDc2bqxobapkngysBV+RsaKlOtFRvqKtpTzTXtRPB2nmG09Lc3trSmKhrrqpurHP4Vyn8rBnxTVVbE9WEwC0Nte31fhvFM5apbauJJ9qr1gdtnDYjPitAYl1j1fo2+HomZU4Ly9HQEinGKmFnzYRta4f/qsaW5rrE5pbGTU1Ifx7lTs+Wq2lpTWyua3WHJmTd4H6rdMeYOfMWQu9kTjDQ506SsoGQmZJHm5dLS3ZpgWM+tHOhuclHW8P6qkYkcvFn5+Lp0GRflHDxz4NWU9fansC5tjnwxr2N3CM3c5/BYeB1DGE8rdw5THLltd+apVOipu25Nm0xtHZobjKJjpDV1UQtZaz7LTXtde1opbWhGRM5T4P2Uq++LHl9XTOlGj26Vfn54F7l4eh72ZkFc7guC+FhXuNhzLhao4pc/bmwLI/XgmmtQ/e1icaqbXWtjuR+pyV3c1VTnUr5sr0Hugb1uq2J2qr2Kq/cDeLLba8hXl/XanHlyv7hgO9d3hjp0jzZP2nrEqMhvXQumHR+CzgjFPgceT4LLSRw1rZfde9zE21jhybnLO4NUx/p9Et4zpSt9xtW2cb6RH1VW/26Tc012fJ3QeM+kjbXGR3dbdlKHm94ycrzU0uHeHbDum2JeFVrVVNYnl+4dbfUbKyqrW3NPuitWl+X2BrP8SEU0V63PrBP1byg7fZt8Tq/TtHXzQvzFiBc2fcUk3tv2oKG5OdReBnOlb8ZuuHRUf96Ifdc4ez+snleIHNjS8vGTfFAJ65PXgY95LcBQPXO57OxBU+Nw510lLDq9QVRn9lr8S4fb3eDki+B+sM14Kz+EOpXXtvng91kGlfbI5SLuyG/sa6qGYHWt7ZsikNz9XgIWkNzwlVLVv435NlF1YvXbxTi1ShB9aZd+9TUV7WK92975dytQIxoTPI7BwatHh/V33O7u/rY5Lxon7TbPz8Uhza1r1sdVpYr6/F5oRgR0vfPwvQ6hoFtakl++FSwe5lJD9I=
*/