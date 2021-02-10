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
c3RzL3VuaXQvdW5pdDE2MjAuY1VUBQABtkgkYNVVbW/bNhD+7l9xcIHCTlU766d1SYt5btIadezAVlAEyyDQ4tniKpEaSSUxmvz33TF+U5rU+9AvoxGROd3d8/De1D34easBB7B3JeEvoUV7sDi35m9M/dPaSXIHDz+yuqJ9H0gXtiZ3SRv2m9xBK5gkK5RjPifJPqAr5saPLlteJXwkCZmxZd+US6sWmYdWvw2/vH37K7yGN4dvDiP4ILTCHKYe9QztIoJjGSS/Z+L2tuPwfQToQeSdlas4Uw6cmfsbYRHonKsUtUMJwoFEl1o1o3+UBp8hzFWO0B+fXw5GHyO4yVSasZOlqcBlpsolZOIawWKK6vrBRymsBzMnc3IulfPksPLK6A5hI3i0hWMfDC9yZ0BcC5WLGQEJD5n3pfut200rmxP7rjSp66br63cyX2xuckkkCrEEU3rwBiqHEbBmBIWRas47BYSEZTXLlcuiLRuC0rJrLDjMc/ZFdgrdA22E6So8EatBSYyV580Z7RjqJjNFTZHiyF7mldUERHEgJWkozBFUWqINyuHma4hVTEOAn03Nlq8Eo4kMNHtTGEybMBNOuQi+DOJP44sYvvQmk94ovoTxKfRGl+zs82D0gVKvCMwC3pYWHYFbUEWZ
*/