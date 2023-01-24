//
// detail/gcc_sync_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_GCC_SYNC_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_GCC_SYNC_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__GNUC__) \
  && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)) \
  && !defined(__INTEL_COMPILER) && !defined(__ICL) \
  && !defined(__ICC) && !defined(__ECC) && !defined(__PATHSCALE__)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class gcc_sync_fenced_block
  : private noncopyable
{
public:
  enum half_or_full_t { half, full };

  // Constructor.
  explicit gcc_sync_fenced_block(half_or_full_t)
    : value_(0)
  {
    __sync_lock_test_and_set(&value_, 1);
  }

  // Destructor.
  ~gcc_sync_fenced_block()
  {
    __sync_lock_release(&value_);
  }

private:
  int value_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__GNUC__)
       // && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4))
       // && !defined(__INTEL_COMPILER) && !defined(__ICL)
       // && !defined(__ICC) && !defined(__ECC) && !defined(__PATHSCALE__)

#endif // BOOST_ASIO_DETAIL_GCC_SYNC_FENCED_BLOCK_HPP

/* gcc_sync_fenced_block.hpp
5GrinHIqkojOtL2Mvwg99ebZWWv4TVfSWW1r+NIoH82nwXPSGl4Zh7fTO/NKou8LVvGtcLTbrWcb6kfFZ3GrDm1AiFXn9zXhyIKzchr7QpVuS2bTHztxx0eE+ebqS5aYRKfIwgd6APLoThaAjCW/mewvaJOV9zH+aENWYOiSuROXUwsXZgoO7r5j2Gs1tlQorWp2qolzI/iUJzZYsuCuWE/QCfAL2lNaUhTVSLa0lcHEYuhuYYlU4JDqlIsW+Ap6qu0g5BdgnkqRSiAU0iMVmsXPTwZhxSgFzO7bUPzUulInUFhE/a9z8Rx5x/taJETtVTJV2hOK5IfjaKWgcn5JCRDXhzaID3+mv6pY/WugN0LUGx2sN7QpWCAmuOYAGZyIDBZigZ+xygT4myxPfF8zeVf/FYzC0xoZbJMMi2867gYMgiS9B/ytyyxP2WAF70cLstYPkT99j6xMDjxRiCakVL6Yna2JJ3WNwCWkVJj8Mr49XZk1Fy5dnFW3/hyxMiXMj2I3H39Pc8yv/gWywJEup1S3HIGahfm9+oh/lKSt0JOqgcRM3/X1TGSVn8vUdyvcz4lQbStcR5E6k4ARTEuoOPftbH4tSAyC+lVZ8OV69DMqTzYcokwmvTPzb9RjF8P7sVyNVWdfbAPaDlMfLVkePIdw+5TM6XxOtRUcpDfHTOnQJem1tCGVs9Rlwc6+M6KNmLz40oEXf0e1nMv7
*/