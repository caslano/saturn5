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
ykub9TNdM0ZzPufJWVB5cdsV95ZQz+WaH+qdI1/S4bgDqVMYOul9bnpBKOy5csuEzzRqNqDFS3JrmV+whQMvohZ+DLQLaU+NnDCiTNLebqmU2sgF7pmY3hILM63c3Z9ipmLEzG9mz76dGRoK0WKFWQvsOXW8+/68AZ8hlxGPfUGR72O6mHQluiMOYdM8t/JxYYIb5zG9hnvR9STPA7OnMDvPZM2Jng16IRedz3luuil8LbJF7jh1x8JOUECshItj1CznS9MZuvQS7hWGqLtcJULBVZEYCs08NS9Ox7ZcfCwmLpaawBF+OJfjLSfPAwfWHmPkwVDTuNa3e6/Pzl1g5xewcxfYeansDHwsMx+/mHKBZp9Ks9Op9XUJFKgOqA6obklUx0BxeshZOurbl4T61irI/MwoMv+va7aVtq6yrMeeaYYjx7zjBLmzzaGPrBtmBDF1PiGaO+TKWaOaSyuZwXAZg4lSIfOUEKHknwJlQWkpHJQVfv9bIJ6YDuJzvwxm0yVaJbTbgO3yv59Lg+1j30WlQ3BZQkyyvWc/71U68+/LcsaZlhBmgqUKa85AMnoXaxohGvghPD3yQ/gV+CHgh4AfAn6ItCwAfsiC2M59kmR9fs40mzpAusyQvhJYvtDrWuPC7PLpFxmmWlPq
*/