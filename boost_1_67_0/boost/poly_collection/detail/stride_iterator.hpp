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