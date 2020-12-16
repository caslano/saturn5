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
0olyf1IO7OUsbVb20z3PMedCvxtWSVpQ9s1kJqMRQG1XMRnlOMuM9DkaLgt8RMC2ZbD3ZbY+s/Ycc5wh2nGEV29CEmQR+sh4fjA3lnUg879o5V9kiLSLIKuT+UtfWpraKX8Vp9Oqy16c+oXfle2ApYVeyoL1ce7MMpZqsy9+H+n5fB4g2GZeFI4+sbYxj0CVQsGz9as/GjwqL8mLPAgDEsF85HrQp05BM7yad55r2hAQUAENGjv6ROMDK1dH2R8fjfR83irC2A+ztLSEYB1Sx+eMjbQI+O5n7bTMSyNvcfhNHdLe/51Cej5/4NEjvNUUx03eFJfg3HhARVZr2thIV3o9BMzN2yXSIReUdjB+0UCsarWKO7eCstMVBCqA0qmtOMR+mkaI5N7l+XOtVpb7ilVnpd/tdSs/o/zdGhmmWJn+h0jP+04U9mLEmu6pfMdw5B8tL43NkNyLst9snTX1wjIO8tJPSW4KCAc726yQh2rQHse7OQ9ftF27ygO/44jB3Oi5RsBvvRevOB80BdofYQXb9LhQrQmhKUx7zqlZs93Drp9iGsS6tThtH9SXZR8bcosg9Emaddp+XfbmRHV9Y0HenpIKGWxnXqufSl1m1pzPq6RoB0lVIH81XGlzS405sX08oPZIVj2mvQx7HFSAJU+t6GvfxRfADLgi6+P6rDmOAr9X5D10SDmF1tOybA5zHtp2iqctvG6SIJZ+L2/yp7sq2Cksi1XY7E8rsj8+2uAB3QnGPOxSKsEDxaZE1CrzS2fsuTQ+Za1L7V6BF6OoDmgKMWrA2lefsnTjTieCKdODU8aQ1lJz12CN49cZ6Ttog6DTCePAs834Vtt90Mq3wKNo2BtlnrILkhIDl83GsoTlhOpO8vg65wGTUJB1wqCNBXWV/AFgrSa35mZCqcc2PEHBI5LrgCFHib1uFqV5G2KIDik6yxLmfxKj2WmgVbB/tdaT7XOmLLARoCf4JZeF3EAsWbS94NCcWZd5ksNShr3SYOAem8yGmRlpURdVJ6za2GuIzJr84TkhFmWSHGllHfTnrHrsBEkcBLEnjP3nbmDt8nRfvDRntqnfqWAp6XXrF+PsWWGs9UNZh1fmLB2zF5YB1hePLJHOLbfF4+qc2Z6weEC5qGIpAwaz4VK1igl7cdm0/f3D4oElPQ6SAu1Q73Cxb+HWG2mQoI0nOyO457yxb0O41zAsEpJkvE5tqHXd3cBznSQvqtDvZaHMF5uQMUaB1ixGaAFcOpuDQPaeJps314Z26ccR1ivK/CwTYCTr7uS8Wf9xD5uKTlYirv0CjlHEdDR3FkOBlDIIhIDotL5IHuc5D+QnokmURVk0GTeTau3/YilVFPOW7qNYehWeEyvibruWo3ZZZhMjycD3+1+1ZOiWnaoI4phkWJ1coBYmZPilwQPv8CF+ehcHA5ABI5efopEkJMMTZR+y0qftDjbTfi1C4wUtoztgVNJcovTKBXNNSLMIB+XYa0mdYIy+j8RogdrdiYT31JpipIf9J+nhADDpNZmrey2YUWYba62VPrbS4zSkyrq9ypMtL2Ro5lU6HjHXxf6CtU8IK7/KysTMnx6IoNiBJIPqR68zeMSwYZVp3kP8eVw5Q7FrtVKom5iXB/h3o3ASD7k2fWLB2ufAJoHH/qUYY3Orp3WkrxrpQoyDXq8L7dRbHI/XRvXsd/acdSIk6+6qKTf6TVnkeZfqHo2mLxPrlsd6LsftX3j6Al23qHBi0KmztrKclXn+x8oT6iR6S06DHbvJtY0xu1ms8pTp79k303eh0Gch5v+l4XBwZg5biGNY+FDNHbmzNHWA/UZ62ELCrFvGPrW3vZVoDVQ/s/LNqzrKdulheKw=
*/