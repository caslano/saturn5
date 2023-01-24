//
// detail/std_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_MUTEX_HPP
#define BOOST_ASIO_DETAIL_STD_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#include <mutex>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_event;

class std_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<std_mutex> scoped_lock;

  // Constructor.
  std_mutex()
  {
  }

  // Destructor.
  ~std_mutex()
  {
  }

  // Lock the mutex.
  void lock()
  {
    mutex_.lock();
  }

  // Unlock the mutex.
  void unlock()
  {
    mutex_.unlock();
  }

private:
  friend class std_event;
  std::mutex mutex_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#endif // BOOST_ASIO_DETAIL_STD_MUTEX_HPP

/* std_mutex.hpp
iXGs1jnBZL1zLBGXtM75PJl1Th/snNhiCXrnH+TD5FDvTKA3fpI3k/X+eTWZ9s9AFrErWeshv0HtoQJ6GajXBP/hFUY1JefPRtvZ0avdqCmq2zGDm8fN5WbD/0mUc4WlzihJaNZTN9LUO9T087g87l6ao/VmqIs6t0uGPg3tDwFTVjx8NNLA5kSYvsQ/NHcCd/HO8VW10KvFXeT1y+2KrwqDpaomvFenKpWt7aWqMzSwGT4l3xl8PtmEz2dP4PP1Rny+cwSev3wyiE/feXw+ewCfVe/j8w81+PzL2/B85vGqNmqBZJaqCLVah5eL8NJA6zPADCVndEpV7F54qLyZ3XkuUUBptvN430rcK2g5EvRRWF3kGQMzOxkAjMyGrWWNfXw4rvBwG2kZMY7BbSRl8mb9ji56A1vYN/rBK1Cae954Nw6FTO32j4MKXdTWAfNkN+XtZwHsA7W/R7yDSOIjOGvxEd6I/A/HghD47iAzV+P2Gsly4OpuQm+ef9++FKB5vkCHJvwDMhuVRu9g8lXZVQUHMLk1mY6s1tnJnHqZkxK3/wUrG8z06/1uX2+HvtgJvxotYL5bnty4Aepo35RW8szn0fa0dnrkEA1kw08dAgx9qS5faRSDDwuGLIlmS6uBkfz7GnpYMLuInyGUlhat4V0rVj6w4v6i2YU6cLjkhJIOaNWizu21F6zMHmyPDkyuW5lcoXeB3MScuwwk
*/