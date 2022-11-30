/* Copyright 2016-2019 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_STRIDE_ITERATOR_HPP
#define BOOST_POLY_COLLECTION_DETAIL_STRIDE_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/detail/workaround.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

/* random-access iterator to Value elements laid out stride *chars* apart */

template<typename Value>
class stride_iterator:
  public boost::iterator_facade<
    stride_iterator<Value>,
    Value,
    boost::random_access_traversal_tag
  >
{
public:
  stride_iterator()=default;
  stride_iterator(Value* p,std::size_t stride)noexcept:p{p},stride_{stride}{}
  stride_iterator(const stride_iterator&)=default;
  stride_iterator& operator=(const stride_iterator&)=default;

  template<
    typename NonConstValue,
    typename std::enable_if<
      std::is_same<Value,const NonConstValue>::value>::type* =nullptr
  >
  stride_iterator(const stride_iterator<NonConstValue>& x)noexcept:
    p{x.p},stride_{x.stride_}{}

  template<
    typename NonConstValue,
    typename std::enable_if<
      std::is_same<Value,const NonConstValue>::value>::type* =nullptr
  >
  stride_iterator& operator=(const stride_iterator<NonConstValue>& x)noexcept
  {
    p=x.p;stride_=x.stride_;
    return *this;
  }

  /* interoperability with [Derived]Value* */

  stride_iterator& operator=(Value* p_)noexcept{p=p_;return *this;}
  operator Value*()const noexcept{return p;}

  template<
    typename DerivedValue,
    typename std::enable_if<
      std::is_base_of<Value,DerivedValue>::value&&
      (std::is_const<Value>::value||!std::is_const<DerivedValue>::value)
    >::type* =nullptr
  >
  explicit stride_iterator(DerivedValue* x)noexcept:
    p{x},stride_{sizeof(DerivedValue)}{}

#if BOOST_WORKAROUND(BOOST_GCC_VERSION,>=40900)||\
    BOOST_WORKAROUND(BOOST_CLANG,>=1)&&\
    (__clang_major__>3 || __clang_major__==3 && __clang_minor__ >= 8)
/* https://github.com/boostorg/poly_collection/issues/15 */
  
#define BOOST_POLY_COLLECTION_NO_SANITIZE

/* UBSan seems not to be supported in some environments */
#if defined(BOOST_GCC_VERSION)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#elif defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wattributes"
#endif
#endif

  template<
    typename DerivedValue,
    typename std::enable_if<
      std::is_base_of<Value,DerivedValue>::value&&
      (!std::is_const<Value>::value||std::is_const<DerivedValue>::value)
    >::type* =nullptr
  >
#if defined(BOOST_POLY_COLLECTION_NO_SANITIZE)
  __attribute__((no_sanitize("undefined")))
#endif
  explicit operator DerivedValue*()const noexcept
  {return static_cast<DerivedValue*>(p);}

#if defined(BOOST_POLY_COLLECTION_NO_SANITIZE)
#if defined(BOOST_GCC_VERSION)
#pragma GCC diagnostic pop
#elif defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#undef BOOST_POLY_COLLECTION_NO_SANITIZE
#endif

  std::size_t stride()const noexcept{return stride_;}

private:
  template<typename>
  friend class stride_iterator;

  using char_pointer=typename std::conditional<
    std::is_const<Value>::value,
    const char*,
    char*
  >::type;

  static char_pointer char_ptr(Value* p)noexcept
    {return reinterpret_cast<char_pointer>(p);}
  static Value*       value_ptr(char_pointer p)noexcept
    {return reinterpret_cast<Value*>(p);}

  friend class boost::iterator_core_access;

  Value& dereference()const noexcept{return *p;}
  bool equal(const stride_iterator& x)const noexcept{return p==x.p;}
  void increment()noexcept{p=value_ptr(char_ptr(p)+stride_);}
  void decrement()noexcept{p=value_ptr(char_ptr(p)-stride_);}
  template<typename Integral>
  void advance(Integral n)noexcept
    {p=value_ptr(char_ptr(p)+n*(std::ptrdiff_t)stride_);}
  std::ptrdiff_t distance_to(const stride_iterator& x)const noexcept
    {return (char_ptr(x.p)-char_ptr(p))/(std::ptrdiff_t)stride_;}          

  Value*      p;
  std::size_t stride_;
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* stride_iterator.hpp
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
*/