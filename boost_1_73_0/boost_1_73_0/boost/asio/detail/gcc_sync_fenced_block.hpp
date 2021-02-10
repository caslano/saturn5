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
ziHOBNHuJI1SYTBsTqYnpEqXhAqLsfGHgznlfjJU6GnHtSLN9YaKCXaL5lEtU1vDzCbMDBXSZ931c2CMfXkIQHtmTtLSA4R6NrLiQvsnuXB1L3EAZR1ZqDvb8WDKKBPI2eqq8KGYBu8fNsAE9Cq7seqdDTUg43OsTaOZWIip3zTmj/EpFx7yyo6iYSbr8VWP4naRDt6p+AoEE82E0B7KUSiyRU44bIxLvI4+wrHimlIPH5TehBmEyoTQVxXiV+BgznxFr3ZGAb+SlZHKlwJt8sE60XGk52q3Y2t8Tq5Dti1JOrl6H0iZplG0AWY2EE886JHEApZAlYv8+gzN9qHTcwQi9Gkjy/ASjrNhGV6g5tlAlgtJPdYbZkGWS1irpxvmS7Qy07zy5ovhgttMZ6WmbX3IPceyziHQc76qhjyDURbWb5iRnHxUhz/8bvWH39k//EUBjQp5tPENN20xVj4SY5uHB1Xs2wguFaQm3aiegRdKzao5MiAdyh5dhQ3RPaRHU73BSz+WIAnXdQ+vqeUjTUvzCJhgcvxtXEosvYdQOAb2a8+452lmPdCy+6aDEx5aMLg5bsUYMEwB0T/Afgvf9Qjfv6/MpocMqnQ0d+7znJMeaxX1RseIB8kcMeyK41s+FkvZpdrj2jBfooNh
*/