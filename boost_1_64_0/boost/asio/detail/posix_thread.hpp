//
// detail/posix_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_THREAD_HPP
#define BOOST_ASIO_DETAIL_POSIX_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <cstddef>
#include <pthread.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

extern "C"
{
  BOOST_ASIO_DECL void* boost_asio_detail_posix_thread_function(void* arg);
}

class posix_thread
  : private noncopyable
{
public:
  // Constructor.
  template <typename Function>
  posix_thread(Function f, unsigned int = 0)
    : joined_(false)
  {
    start_thread(new func<Function>(f));
  }

  // Destructor.
  BOOST_ASIO_DECL ~posix_thread();

  // Wait for the thread to exit.
  BOOST_ASIO_DECL void join();

  // Get number of CPUs.
  BOOST_ASIO_DECL static std::size_t hardware_concurrency();

private:
  friend void* boost_asio_detail_posix_thread_function(void* arg);

  class func_base
  {
  public:
    virtual ~func_base() {}
    virtual void run() = 0;
  };

  struct auto_func_base_ptr
  {
    func_base* ptr;
    ~auto_func_base_ptr() { delete ptr; }
  };

  template <typename Function>
  class func
    : public func_base
  {
  public:
    func(Function f)
      : f_(f)
    {
    }

    virtual void run()
    {
      f_();
    }

  private:
    Function f_;
  };

  BOOST_ASIO_DECL void start_thread(func_base* arg);

  ::pthread_t thread_;
  bool joined_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/posix_thread.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_THREAD_HPP

/* posix_thread.hpp
pPTCMraEV8IPShps7naeSnWDuhswrmBOIqO1thSwOFqesCXyOERYew/bUWXV0vspgS4ygcsgWmcRnoo86ym4DoC6kZFzuagt0VgpislFh92uJxjkF2DHYoUM//4BZMnSxn73efckDJ5xjC1Ra9qoONVcf/WWICbU/yxEG4Z7bvunSVKJag6tKJKj9yCGe3/6rlri7oOVYIALMIgr6+n8hwtUhxcQDTcEsmaakF2xOXd+8CBgWVPNmCEUXtLZGvbwEayV04TbGplerkOvW0wqvBuaZnjvi/bDWyBda2bLGoNRoO99z+ZRaT1irXVLXz0uLrJAJ21VZ68/38UihzFpF+IZ71L3B55V++Lem27j6K6h9Z+n2aI0EqcrYBbpSux4W5gPwl9SsbxbyVy+u7Rq2Zcl4iY2KG7ih0pVLmVal+40thEqCPXHjOxqbkf78d72Zw2p3J5kUjxsV0xp6bi+9I6pHTPubzS4t+tKd/nJwnDsIiAurNP2Stgxc11PCbSC//4J3SX0ONCmmQWtcLwzJ0LAtXaU5elIEz9TAcy3EssNbov3S6fVRIn32A==
*/