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
FjVAuGMWOQKCcgwgM5kohDBABEJMAoIi4ySZhJFczEw4FPHAC0VdBfFAF29F8QZE1HVF1583C+riLR54AiKKC6Lwf9VV1XV0Twz7+fv5RKb7fetd9epVdXVVtf0/aV9zD7SvOpfMA9D+OYddZ7LrE9h1D3ady65z2fVAdp3Proew6xJ2PYJdz2DXfnZdxa7z2HUFux7FruPseiy7Xsyux7HrRey6iF0vY9fF7HoVuy5j18+z6+lcPz/xmgFL/eI=
*/