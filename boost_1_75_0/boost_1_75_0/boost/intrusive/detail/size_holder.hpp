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
10hjQqE+39V5GjbWqc64/WZ1V07bPq1bhkJ7/cskjjBxLy5RvpP4OTIS8gbP5k45AmzfoUQkV26up7G0Q00bBcgwcB86lz5sHkThBIRYCRKqVd0f1eZWfzziQ5J+Fhm2bDEEiS1///KkBu1iJ6TzEHEuOYNZ9Uzcn1yH0cyehoHXT6JQnPPYjeuWsaz+YWT39B00RuNzzPthX+jBPuzLAulaLWH2sMZW1sbzBhVWCKZlIXiLKhnSDk0oCHDQVSH8cRqLgzrBblw7+n4DduJZKGWqd3IrR2PsC9vsUCmlepJP1XesBUkQ3dfT37bWiyX8liCDZLJIv7RL7UjmEaKZdfip5xGpT83Ffsmb0/hRAj43Wv5jdHZ07NzcctdU4+LlnX2ybuO99rVD+KyGz2ZN1G4qNcV9SoFlSpeXDOO66vecComScZXAmO3Fn1PyW9QO6q8/Akh15+bmGrzlo7rM+f4iucUuJ9LebCu4tLGddt8QFPzFdWpH0r+5tLbWLfaBR6CpxeMJEc8luEuEyDeKdODzddeJ3TLIWu7hIJdtQ2yj26S4jNylG2h+p+CDex3IhgcSILw3Rg15REx7CbYg0m8JmbSBFuj+FcGzSlImDh8YJcBlt1lrX29xMsBaH6VUYNuQ7vaTLFngKrzlRKgKHXmOiYkRYfi53ry4LuD1gB0Tw0nKT6san5fk1L55X6IZqXN4XQ+5Wji+quE1
*/