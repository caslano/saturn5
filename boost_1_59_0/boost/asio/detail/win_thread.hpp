//
// detail/win_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_THREAD_HPP
#define BOOST_ASIO_DETAIL_WIN_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) \
  && !defined(BOOST_ASIO_WINDOWS_APP) \
  && !defined(UNDER_CE)

#include <cstddef>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

BOOST_ASIO_DECL unsigned int __stdcall win_thread_function(void* arg);

#if defined(WINVER) && (WINVER < 0x0500)
BOOST_ASIO_DECL void __stdcall apc_function(ULONG data);
#else
BOOST_ASIO_DECL void __stdcall apc_function(ULONG_PTR data);
#endif

template <typename T>
class win_thread_base
{
public:
  static bool terminate_threads()
  {
    return ::InterlockedExchangeAdd(&terminate_threads_, 0) != 0;
  }

  static void set_terminate_threads(bool b)
  {
    ::InterlockedExchange(&terminate_threads_, b ? 1 : 0);
  }

private:
  static long terminate_threads_;
};

template <typename T>
long win_thread_base<T>::terminate_threads_ = 0;

class win_thread
  : private noncopyable,
    public win_thread_base<win_thread>
{
public:
  // Constructor.
  template <typename Function>
  win_thread(Function f, unsigned int stack_size = 0)
    : thread_(0),
      exit_event_(0)
  {
    start_thread(new func<Function>(f), stack_size);
  }

  // Destructor.
  BOOST_ASIO_DECL ~win_thread();

  // Wait for the thread to exit.
  BOOST_ASIO_DECL void join();

  // Get number of CPUs.
  BOOST_ASIO_DECL static std::size_t hardware_concurrency();

private:
  friend BOOST_ASIO_DECL unsigned int __stdcall win_thread_function(void* arg);

#if defined(WINVER) && (WINVER < 0x0500)
  friend BOOST_ASIO_DECL void __stdcall apc_function(ULONG);
#else
  friend BOOST_ASIO_DECL void __stdcall apc_function(ULONG_PTR);
#endif

  class func_base
  {
  public:
    virtual ~func_base() {}
    virtual void run() = 0;
    ::HANDLE entry_event_;
    ::HANDLE exit_event_;
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

  BOOST_ASIO_DECL void start_thread(func_base* arg, unsigned int stack_size);

  ::HANDLE thread_;
  ::HANDLE exit_event_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_thread.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)
       // && !defined(BOOST_ASIO_WINDOWS_APP)
       // && !defined(UNDER_CE)

#endif // BOOST_ASIO_DETAIL_WIN_THREAD_HPP

/* win_thread.hpp
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
*/