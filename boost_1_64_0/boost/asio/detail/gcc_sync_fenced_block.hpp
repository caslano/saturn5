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
fBnpVOlrSyMmYxkA4dBXzFbdnRmwNeq3/U226J295QW/0JpSwRmKvwFC2kjzgxk5FrJYiRj7uXLVdVblXWRqCQOCFKF3RfnLe+PtvLrbzgQmcats7bQzNMFwueIbeFmci0yblXn+j4rs8lCtGcCxYJ7iag1P1f7qKAHIVHEjHrn2VQpXrApCNgt9mq8I3zofKBDYOSRDynw4XEKAhD3e0ymtL/014SLeRwgiAAid+7hs/6RumDrze/j3eglHKbjgLtOzMNfoAZwIUkPMJRoyLLGhVRyE5FP8KbNis03GlqKs4SHRsfWrb9HmOcQ7EfpyErv/coysgg3iNZD/pJJlmlUeq7/T8wZBFiBNr64AEBlL2cKHmTIMp4C/yIVEWbRuH0XrTFg4JjqAiryba3ivr7oncfvgifqFZTMNpBIFyOCud8q9zH6No/2X1jy4Am264YUZC0o0naZuvtEwpVKoyJPXPSUKb/txxuibEwxH124lWJL5B5CJ+2658qG4C2tKY7jVvdIHEXaiSef+14xfDciNOdk/B7SUd2VQ2LL+21AthxPCB5HDYNw1cg==
*/