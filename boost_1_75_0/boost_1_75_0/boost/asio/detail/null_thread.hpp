//
// detail/null_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_THREAD_HPP
#define BOOST_ASIO_DETAIL_NULL_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_thread
  : private noncopyable
{
public:
  // Constructor.
  template <typename Function>
  null_thread(Function, unsigned int = 0)
  {
    boost::asio::detail::throw_error(
        boost::asio::error::operation_not_supported, "thread");
  }

  // Destructor.
  ~null_thread()
  {
  }

  // Wait for the thread to exit.
  void join()
  {
  }

  // Get number of CPUs.
  static std::size_t hardware_concurrency()
  {
    return 1;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_THREAD_HPP

/* null_thread.hpp
vRkFH6UcHxA+Mhsus2O6s3LtiCE1JKgY0ta2a6x9Z6pgdt9K9g+DS1oXQh0v1fl2YYc0eI5p0NAOgoZ2ECi041AEGsLVIb+9ToeGXjmPQUMfIzSU8zvj6pBXkSk2eBRcqdSN01bGIoPVeHQ8/t3ergFDXpzS5CesxU8oixqn9KgA0KbzIwAQvoorRPBTfmG4CgDh3hRlZWChEQCKdcrXnq8DQKwyaiGrPugiACjWNRmSykbOM82BDFxk4dwjHZpyAE88M/HzZHVd9bs1ZumAb1cyCVmz7hGY7fLuOEV/xwAWLOnTndHRn+0J+HfHVPpLCNGu9DMaqiI2WLjdE9VQfS4lCDOdiAAlnDEiQGMlqv/W2nixtjnPqpJDK7irqbRqqovQoCF4XOethAR9q05cKUcUKIlQINxaETEMfEnJ5XbnE/hzQYW4xTZTSJNUomzic8htU7b4HFN/Bl6NRMDndnz2MqECnjLiGEY6EKw5N4x8Rj2WGK8YJ4nnGhQvkQT6CASkqRcE3Mzt8XnwjSBOwVFRpO0MReL9KoLkYQgS574Lh+wYiuS+HSfJpOK0F8Jhblanx+QZEJ4LEOFB3gbn4ou3+fMJ26F5MbiGRWONCumoSFEQ176ol95iD/QeUD4Xn0MyQVaxZZeF3UcQtTEbUJs6xVp1AGR+OMS6iNeQrUC8JtkcjdegUDplBZdGkYCWMdmkVSYRHZEXxQ2I
*/