/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_SIZE_HOLDER_HPP
#define BOOST_INTRUSIVE_DETAIL_SIZE_HOLDER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<bool ConstantSize, class SizeType, class Tag = void>
struct size_holder
{
   static const bool constant_time_size = ConstantSize;
   typedef SizeType  size_type;

   BOOST_INTRUSIVE_FORCEINLINE SizeType get_size() const
   {  return size_;  }

   BOOST_INTRUSIVE_FORCEINLINE void set_size(SizeType size)
   {  size_ = size; }

   BOOST_INTRUSIVE_FORCEINLINE void decrement()
   {  --size_; }

   BOOST_INTRUSIVE_FORCEINLINE void increment()
   {  ++size_; }

   BOOST_INTRUSIVE_FORCEINLINE void increase(SizeType n)
   {  size_ += n; }

   BOOST_INTRUSIVE_FORCEINLINE void decrease(SizeType n)
   {  size_ -= n; }

   BOOST_INTRUSIVE_FORCEINLINE void swap(size_holder &other)
   {  SizeType tmp(size_); size_ = other.size_; other.size_ = tmp; }

   SizeType size_;
};

template<class SizeType, class Tag>
struct size_holder<false, SizeType, Tag>
{
   static const bool constant_time_size = false;
   typedef SizeType  size_type;

   BOOST_INTRUSIVE_FORCEINLINE size_type get_size() const
   {  return 0;  }

   BOOST_INTRUSIVE_FORCEINLINE void set_size(size_type)
   {}

   BOOST_INTRUSIVE_FORCEINLINE void decrement()
   {}

   BOOST_INTRUSIVE_FORCEINLINE void increment()
   {}

   BOOST_INTRUSIVE_FORCEINLINE void increase(SizeType)
   {}

   BOOST_INTRUSIVE_FORCEINLINE void decrease(SizeType)
   {}

   BOOST_INTRUSIVE_FORCEINLINE void swap(size_holder){}
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_SIZE_HOLDER_HPP

/* size_holder.hpp
MW/y3GnmrBr9b82MW1bkbf9z8c9p5WmcU/SIKiv5Odv0wlHRZT0RcjLT3+1Pzb7WdjXyTFR9GtcaaTufWwtGR+v7IvrujaWvqYuJ6bs3ibq49zTq4q6cxuviCK8NdJT3EEocCCuvOStG7yezG3mXOI1zQtrO9u/ImGgdW/XiuT5MR/8lQt8X4uuJrP8OsSMBP3w1/Zv+DoEuUe8QOyL88NnlfWBsdHm/iiKHw8urmpfYeTmcRN07fBp178nsxuveQJVzzrjod/wizuvx+nKG3vCNvlN6xX2/J35y7/ekF/Z+j7zzu2j6+Hppqp85PlpzQWqlX1XD2II1TJzctLUy9vfznxuZ4S79lV4wvG+38fX43GMpIp8dVIZuEuqqMhScHVkG8znPqX9nONLEz3HqT1pu+yeo60TP3pPqIz8TpOzwaTgQXYvDdV2zrnzN5Q2zR6JtnqPvfKuM3H3Bcmr1J4NtiDeF/L307rDLwL4wv8D8aQyf9Z34wIBQnMtZ22tG2HfIDI2let2kcVYwM9jW93cesP2FW2l918R9jrkZD3Bu2MdWndnHNtZZzpf4D5IKOpvvwD8wxyYFQ/qN7mzSLVuxasNa22/xCRNnHvMKC43cW8i9bPaNQ076Sg430749fm3iDArqWdDECciOWXCNOf5gcC2WuiuYamw01JRNJ8Eq16Um7uU8nk5D3kuPySCbyzdtWUG61jXRztgzO175TZ/lYepwwfle/8xw9c90Trp/5iaT/kTvO6hJt5R0L8ox3/kP2PcsO8524lwcitO2+qHIb6Wefi/7+u0aWK+gmXYQUHz0i63XNcYOObIhtdhs38mVsSksj8KJXh7Vf1IeqTkJ5jG3kTzylccDfh671od1hJFGMrZ+WvmZbX790GwPNHkNJJ22xFmmsSkTMNRyOD7bbJtwa5bVb5bkGD+7Tek7pT7y+BR0g6PhkNB8vnPUpthjnfzpXrHb8S8ZubYpjnaQNK2xSwnMrSR+RB+yP/7BXJt1XL81Jk63FI1L4c/vLzXtQoOvaHw3rzB9X/7Yzs8b2cyUDH/NCX9alt/nctDE6dmQvtXH+pbSn25kLduoff2ykW2FrNpM+fn37hnpg0LH26t9okfGbF/Lns2ufnNT5lPkea9Jt29KqP8jaxLncLLGYu16vf0091ismGOrdg1qGFt1KTJmrQPiryCsJKwirCasIZQRygmXEtYS1hHWEy4jXK5+vS+qX28D2x0sv9vDNB7G8+uenmSdjeUTn7g6z+H9vW/5+7b6Y1faD6SsmgsQ2p6k7dfzI/oRinwffeaZqz0cFHrPHmxfE9a6QTHusVmw3Mi0Cp7L/w8SdE9RWtn29cG+GGP7rHv2OhMnJTgMjW8hKG7Dvaa8zL/fXWHinosbijZ+Hfus2fcUfknv9HXZavb92XnPftgce4zvvC2Vl3W/sq77FwdrnJTas8Nm+17uVT1JbYLp8xtAW3PPVPpOSSOt/cpA1P1EcY4S56FQnLYVUX1v+Yozsshv65/2bnhNaYfPGRLSc4LfDpeb7aDVzycf+xkmaLxC08ZW29/Ls6arM1ttHUUyz3I1Q+w6xlC/ijX0LTeMnXLMd/Pbs8eM7Hnu9zmVSz7Y+SPJqoZ27hlzfIiz//gr5thwazxnBe8vVjtnjo/QuCylbbUxPzLHW5k6sIfzdnAafpHN+c2OrgOKc4w4R0JxWudH1YGm2D50vdcaPcwcqrB3/Dmz6oXXpHBexNC5SB9qnwsznyPmOPXeJu6ClAXBVJf9ScsxltxqJ/qY48UpDwTK8WH7ts4L2g5jPyXUO7v61Kv8a/x+czyN8qSEnzul+5xJd7gzvY3GcJVjGJnqX++DTfw=
*/