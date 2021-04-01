/* Copyright 2016 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_ANY_ITERATOR_HPP
#define BOOST_POLY_COLLECTION_DETAIL_ANY_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/type_erasure/any_cast.hpp>
#include <type_traits>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* type_erasure::any<Concept>* adaptor convertible to pointer to wrapped
 * entity.
 */

template<typename Any>
class any_iterator:public boost::iterator_adaptor<any_iterator<Any>,Any*>
{
public:
  any_iterator()=default;
  explicit any_iterator(Any* p)noexcept:any_iterator::iterator_adaptor_{p}{}
  any_iterator(const any_iterator&)=default;
  any_iterator& operator=(const any_iterator&)=default;

  template<
    typename NonConstAny,
    typename std::enable_if<
      std::is_same<Any,const NonConstAny>::value>::type* =nullptr
  >
  any_iterator(const any_iterator<NonConstAny>& x)noexcept:
    any_iterator::iterator_adaptor_{x.base()}{}

  template<
    typename NonConstAny,
    typename std::enable_if<
      std::is_same<Any,const NonConstAny>::value>::type* =nullptr
  >
  any_iterator& operator=(const any_iterator<NonConstAny>& x)noexcept
  {
    this->base_reference()=x.base();
    return *this;
  }

  /* interoperability with Any* */

  any_iterator& operator=(Any* p)noexcept
    {this->base_reference()=p;return *this;}
  operator Any*()const noexcept{return this->base();}

  /* interoperability with Concrete* */

  template<
    typename Concrete,
    typename std::enable_if<
      /* can't compile-time check concept compliance */
      !std::is_const<Any>::value||std::is_const<Concrete>::value
    >::type* =nullptr
  >
  explicit operator Concrete*()const noexcept
  {
    return const_cast<Concrete*>(
      static_cast<typename std::remove_const<Concrete>::type*>(
        type_erasure::any_cast<void*>(this->base())));
  }

private:
  template<typename>
  friend class any_iterator;
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* any_iterator.hpp
72LY4sqkkwaJKJ59BfaUPuys9j0XDRgVQzQqEjoez560NJWm+TbFPXB/QjvUA1wNaSbV1pHYLjSt7Qo7kKNKDwb2yTIDV+XNAJIrZRuYMpF4pJLgKmXSPuCKb3vIp+S2M1Pq4wn0vcMHAx97iu9GAe3Z3XjJE97ydgYkAzRLIDiBcM9/KNAIzx4xJ2+qKEULhKT4ZzHJUmtN8nNohsD8OB8J2ykTGQjLKLiX5AWvDj3HKb6u7JJLxi/9NsaixyQaS6jcY95qnq/SdiCO4tLaVMo/om2XiRIqM0k3MwXVVPeefF1Zts2ujJfkCOaWWThBe7OK9HmpeBDKybejP1d95d4oxP3Uo48OBssgZnGhN7BKe6y4jJQAFLliTVc6dwXeJg57LnVDWgLoEMuTz7ePocWzAQIgo3E8I6uiHjc3V9AlaSBlf2WeyaganeU1DmzHGAXapow1IBFU7pPtjCn3ANmZ3ctDSk2DwO3bzkttnMZ6O5sRKUxwOQ26CYt8EKpQu47JPSfbobYKM3+S7arJ8BUfR3YCtKfAAtCrYQNBDeV055V3Gdx3Sy04AA==
*/