//
// detail/null_event.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_EVENT_HPP
#define BOOST_ASIO_DETAIL_NULL_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_event
  : private noncopyable
{
public:
  // Constructor.
  null_event()
  {
  }

  // Destructor.
  ~null_event()
  {
  }

  // Signal the event. (Retained for backward compatibility.)
  template <typename Lock>
  void signal(Lock&)
  {
  }

  // Signal all waiters.
  template <typename Lock>
  void signal_all(Lock&)
  {
  }

  // Unlock the mutex and signal one waiter.
  template <typename Lock>
  void unlock_and_signal_one(Lock&)
  {
  }

  // If there's a waiter, unlock the mutex and signal it.
  template <typename Lock>
  bool maybe_unlock_and_signal_one(Lock&)
  {
    return false;
  }

  // Reset the event.
  template <typename Lock>
  void clear(Lock&)
  {
  }

  // Wait for the event to become signalled.
  template <typename Lock>
  void wait(Lock&)
  {
    do_wait();
  }

  // Timed wait for the event to become signalled.
  template <typename Lock>
  bool wait_for_usec(Lock&, long usec)
  {
    do_wait_for_usec(usec);
    return true;
  }

private:
  BOOST_ASIO_DECL static void do_wait();
  BOOST_ASIO_DECL static void do_wait_for_usec(long usec);
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/null_event.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_NULL_EVENT_HPP

/* null_event.hpp
Y7QOnzvMcXT4Eyjp6hs707KjzK1u8+AcDjVO7u01Bp07ujPddozP6taxnens44xVh/+A2Tr8NyzSuVGd6auY7Zg1XnG8+67bfP7bOtMSXeFH8+Yt+h2d/hnBnWm9rvMXTuhMW3Wb/zimM410zPTuzjQVVdvLvBtrbc/GGhtqusWD3uPe6RzPxYDDhr/q72GoDm9HXocHnei6dPhGTNfhC8cZvw5fjEU6/FnU9KvGal0Z35luRtN567z+/e6TbnzAevtgZ9pkn+KEzrTmZNt1NrEzXYZ+HT7jQ52p5/DhbN1ilG5wx6TOVNB5/vAprl3X+LhTjVmHH5jcmWbo8L8xTzdPd30fdl91eArW6vCv0NTh+7Bbhx9Av86d0ZmuwNChw9n8FTtTTofHY6wOT0FRh7+CPh2+BRVdPLMz3YrFOvwIVujwwWd51nSBL8FWHd6CHTrcebZnUodHYvARw9k50atr/PJU49Gtj3Smt0wzJh0ef25nKutwHxbqJpf7HF/nZjn/5e6TLn/J8/X1zrRU1xZ1pn+gX7f5nde4/iNdC8/GYF3hO9Gjm3zBtzxruspvqHam+brC92KsbvGLWKrTd9w3FHS467vGrMNvRVmX+aTl7p0u/MyxV1qvusRz0NQV3oWGTqs602HYpHPcj+lv8NnbPO+/cC6du70zLcBe+9R4Heba3uBBd/iM7eH7kdke/idG6fxqaxUVHe6+2/Orwz3YoIv3eK7vtZZ0jdegpSt/6kzXYruu8arNxjbM3PK8+zvTBF3bajyYrRt80IPeYzq8EkN1eCPyOtvmXYF5Ojz4WXOuw0OwVmf/847CjKO8o/iHmKfDd2CxbvEpL7quNw5n1/WSe6TDo7BaV/jgfuvW/uGp+825Dl+K7brN57zsXts//F9M0eEhr/je0SWeg6au8CZs1+EnsFeH+zHYMcOvIKfDN7+mK43V4dtQ1IUDutJUbIrj8w3YY3v4KQwYPvxVH/DarjRM5/lsbDY/4d9ghw5vQr8OP4hhjpkGdKUrkddNfhJzHafNnzrQdh0+ZGBXmqzDIzBDV/gRDM05zkFd6XzM0uEtg7rSfB1+DEt16XVdaQ5m6AofcnBXyunwJwe7dh3+Noq6NKTL79auNCian0ZdhzdlXampw8d1mhPd4vd2d6X0JuuNn0HzzdZJT1f6GBbq8JNYpsMHH9qV1usiX4E9OnzIYeZKh9+MnrcMZ3OCUbrOxcO70nb7VPjfWGFOsqFdaRr6jaHCL2OAfXJHGA96dPXIrnTsG7rSBMcp8kz02r/MCzBKV3k5ljhmnTeippu8C1Xd5oHDulJFZzwCC3WeJ2KfLvJMpJzj8wK0ba/ycrR0nTdit27yLmzSbR74RteoMx6Bhs7zRNR1kWeiqcu8AGt1lX+JvOsNn3mU+6vDl2CKDs9BWdf5IYx27eETh5sfHV6KGTr8jZx1pcPfwhIdvgFrdfhmNHX+TV2p781daadu8H/RMufsz5w1Dzr8OAb1Dn/Vnb1daaQu849Q0+GHsEKHH0NDp6O70vexVTf4CfQe7Rnns0a4jzr8OUzQNV6HnbE/P4Q9usVvfat5MJ4CVzDJ9vAOTNfhD4zsSrN1eAoW6QZPPsaa89kyL0SfrvG96HHeFvdjru3hIcfaT4dPQk2H52KtDn8Rm3WNf4W9zpU7rit9AQMcs8oPYLpu8+tGOYd9CnwFhsU+POV49y6a78AG3eTd2KzbfPDbutJqnfGJWKmL/DUs1jVOb3ftOsfjMU8XeS2W6ha/Nu9Z1hkfj0W6wOdjvq7z69/hvG/1PuEKFusqr8I83eCHMVu3OXund5rO8XhM0UW+FJN1hWtYr+u8Bct0m4e8y9g=
*/