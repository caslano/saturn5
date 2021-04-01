//
// detail/win_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
d6qHkkj6SZLCABVT/X8iBwTPtAbBBiloifckIRYTnKUA1mso9ntA14A04uVd6N9kLgd3vBvq9+wHTdASoyrd136tKvABz8hI5QDIPHef98x/dobyt7yMggScHAVJ+FD+rxVN6Mh3wCF20KcZfuYxP2PjbWQiA+GXzk2kKwGoLhhsz2ws4J/SQPNBpU9kiWWGpRGAmeiQv1mkTbTF/W6OBnUgEz/GS2tipAQYKwQhFHkbgxXW6lBrENP22KTxKP+udHKUO7xv3kv3Seg5+LJxrrsvEZebxuD/Km7lCBXvcoPDsoXgCPjPo7lBoCIGq6NlfkwW/L9t48QVVIi6LCAzQm0XXF4qcPoz+Gu0crNkA3uicVC/hFuFsaGoUfyZb7GxbGGdviEKtSowXxYQRayMeYQ+HBBDyk3FZtg7bckLXIErTMs1TPzs2J4wQKgltDnteE4G/zXea8J1BCm22ZYe+KAtLP6Oslnx522yx320yc4NDhwbBgtY5csM/ttCqTBEs9kGfxSbnmAl2EGn2YUZNSEm4l2eq4WUUX02vfhiM3Le7swi1pRXWtQbbw==
*/