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
DTZ/JuNObils0O34YlpY19fywmNLP/5mtMGtsp515Of6U+fouudKAF0pc5qb4Sqj6xqons1epXysZCjtBET8/A70ij3hi+LIxFR1VYsrwxxScS0O3oIVY4vGlVf1Padnto6MT2P9rE8dIzEf4jx34aRBBOqrlMADNtCg0PDYlIIGyWisFaUgdSGNbpBBOb8YHRETL6DZIsyI4y0G46IU3qTDJqw8XeOrpHB0yScVw6y4unYJWpEqiYER8jN1JTFzWVT6qDqA7YatRnJO77KQQIQDeyxVPwWPhVBdweK2ioaGIqRuoOa6uuBU06Zsz6tmRMXMcSpIM9TZKtNY2JOQJ46wNz3binY5IXJnboL3VyfKIepZ3wOAQpZHWlU3Kybw4zbr0S3ACiqcJSs/cGyXCfA6pc5aSQhU/5PR2qv56/5t4uucWm4ll9bSvWNJlssWaV82Aa5qKxUeDV7XRKZKWvtnqYzvWastMM23t6WVliqy5+atlouivrbsVba/bTr9Wewtrf5c1kKaSbClH7YXeog0pRhSV+6NtO1wzFkj2MPBtdEvfYob/uVjVTuo6yJFq5zAGgoiqRFZ3i4zAfv97wVlQIR5XDnZQRug0z0cRoK9CpRlF+wIba0EApkJFtXctw+EqfvINIgEwuuyDBqpEE+ZuCHulzqOi6bkRKxCGpFepZxXr4PUfdl1NkCDwj7dVjhzT2kTYWd89yrD
*/