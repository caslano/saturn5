//
// detail/std_static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_STD_STATIC_MUTEX_HPP

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

class std_static_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<std_static_mutex> scoped_lock;

  // Constructor.
  std_static_mutex(int)
  {
  }

  // Destructor.
  ~std_static_mutex()
  {
  }

  // Initialise the mutex.
  void init()
  {
    // Nothing to do.
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

#define BOOST_ASIO_STD_STATIC_MUTEX_INIT 0

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#endif // BOOST_ASIO_DETAIL_STD_STATIC_MUTEX_HPP

/* std_static_mutex.hpp
MG5xGwdjHWqcyXAmpbM6wybyRT/1NNbHYs6yFrK7L6Z5TSP+fQgfwCS6JWuzMwG6lvVmSuhvmYlYRI3RS7Ml8QOs5LJCKcQUcfIDuqJKr7b05eiL/1TK1T2i0RIpCMlc4Ad8D7DuNp58CdD9JgWTuf4GmCVJHORaxOf6bTWnhTfXFBrLPUqvkon/LIXXszfCJItCxI/YMQ3YGsMZfsG/wIR55B5Z3FOpBP5qAI8+rORm4QmvKr7VGPhEyh8R5r4ooZy0SZs3HXFadsfYJNso7R5rNTzl2nVZdNVsEHLiJtLA/khaL72j5Zhrgi8MhtidcLGr2L1yKqWakjB5/+D5jqpNFoao+JbWyRJCC8qBDVCyq9xJEdbv6gmKj6L9g7qWQ1H4zP2/5UqQnNTkuewOk/JEIobKoVe76FyFRHpRcgHSwy+FbaoWWzwL9p5U/A9pXyuRkxS6oE1VGpK8AwltU4QdmI+JGcYD5X7h8yupjJH62PaV/pLV7FD+P1Fmk3NeAgSep6Dxxy9XstzKeH8IGWctKPwZTR26tpoOwqvH1K2Bk9xKc8zkAEjDnQ==
*/