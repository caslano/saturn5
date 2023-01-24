/* Copyright 2016 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_CALLABLE_WRAPPER_ITERATOR_HPP
#define BOOST_POLY_COLLECTION_DETAIL_CALLABLE_WRAPPER_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/iterator/iterator_adaptor.hpp>
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

/* callable_wrapper<Sig>* adaptor convertible to pointer to wrapped entity */

template<typename CWrapper>
class callable_wrapper_iterator:public boost::iterator_adaptor<
  callable_wrapper_iterator<CWrapper>,CWrapper*
>
{
public:
  callable_wrapper_iterator()=default;
  explicit callable_wrapper_iterator(CWrapper* p)noexcept:
    callable_wrapper_iterator::iterator_adaptor_{p}{}
  callable_wrapper_iterator(const callable_wrapper_iterator&)=default;
  callable_wrapper_iterator& operator=(
    const callable_wrapper_iterator&)=default;

  template<
    typename NonConstCWrapper,
    typename std::enable_if<
      std::is_same<CWrapper,const NonConstCWrapper>::value>::type* =nullptr
  >
  callable_wrapper_iterator(
    const callable_wrapper_iterator<NonConstCWrapper>& x)noexcept:
    callable_wrapper_iterator::iterator_adaptor_{x.base()}{}

  template<
    typename NonConstCWrapper,
    typename std::enable_if<
      std::is_same<CWrapper,const NonConstCWrapper>::value>::type* =nullptr
  >
  callable_wrapper_iterator& operator=(
    const callable_wrapper_iterator<NonConstCWrapper>& x)noexcept
  {
    this->base_reference()=x.base();
    return *this;
  }

  /* interoperability with CWrapper* */

  callable_wrapper_iterator& operator=(CWrapper* p)noexcept
    {this->base_reference()=p;return *this;}
  operator CWrapper*()const noexcept{return this->base();}

  /* interoperability with Callable* */

  template<
    typename Callable,
    typename std::enable_if<
      std::is_constructible<CWrapper,Callable&>::value&&
      (!std::is_const<CWrapper>::value||std::is_const<Callable>::value)
    >::type* =nullptr
  >
  explicit operator Callable*()const noexcept
  {
    return const_cast<Callable*>(
      static_cast<const Callable*>(
        const_cast<const void*>(
          this->base()->data())));
  }

private:
  template<typename>
  friend class callable_wrapper_iterator;
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* callable_wrapper_iterator.hpp
EWvq4Y1jPZhak6AqCt7NzjAJpci7Xwb4jqk0SIpjsGZA2iBy6r3hYPLv3u5iqZWvZSsda/7HUQW6uPB72NBCH9VuZzhLZ5XPo04DNLwyDBxiPZBV4kMGC8e7u4ZntD7bGL1va5u6QTIR06FwonPRNwdc3IDUjwu7MoJGA0eD2APZFWGPX+J9+/R2hJ1oqjGbaJtQvfCqyXTlgQ4k9ujrmKvoq8/LsQRQfqFQBfnPbWjvqHbZd5120XRZ/T7tEnmpSkfLVoKXt2ok48q8fv/+BKMDv4mwCeCF4vV+ilYO4fE7Lq/RsdBt8hVfa1R2qndXNJO51dCfzTyMF4ZilxwG44MvY9MO3MvpFmq37dsfn5R8Mm5qjxO6GWf5M+/BNe1ZMVKeig5Nh4xjYW31aX4Swz2KX718qwXmHgCXvCLz/oev2qtOctGUNa99nth+22r11MEVFh/Mgp0HvFn/3PGqlrpu4Yntz/z2hkx7xTCInthe8UPrnD5U8k1Uag3dTXbKzEPl1YWNGyttrV8BjSzd2hSwdNTFvGihsteFuBJK/Gd1ymFdRMPaN2g6T6GV0e++DzOKgdf+DOspfLAxuHYP/rJ1QRBzyc7DeuzIw1ajphBxlraxAYSqlliax1zm+Uu3Ezd5M6vwKdurCDXbRMLE02/LObtMwievTkr0L0Ns+6LW/UfNqSRsbhhpgjNkeBRuXxuMql6lM9w6hZ8+
*/