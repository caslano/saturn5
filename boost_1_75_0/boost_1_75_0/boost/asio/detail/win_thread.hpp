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
oetaFBCv346K+Ho7RPzA3w13Y1/Eq69QJNf24Y+IT8He8TtwFMTxrdjIyjEdL95uatqN4kXcsRzlJzFhV58/1YmWT/xNcpUwcSlT2Pf4f1Q07Itc7x7+n1D6hXL6tQ/nNre/1tGvV9spp++fqIgrSP4GCsq9xPyvpTcRDF+zptvQKC/G6NGgmGvdonD7l3UfaBXD8dtWasl0vHuUUb62ko5sTsF8QY81rr/58/udO/pB+RrT8ULB0I7HcjE/7GDuxt/87OOr91zc/pBZevPetYodxWz8n43cf/O3aLZ6rRgTy4xt7GixaMgbzNfbr7KY5vjeW5IWuB9JYlJW3Bs9Nrmc5b82CPzN/3np9pxfKplMoa6SQf2Mdyx/lcKK3/wRX3+EbvFLg8yxu9zOh1WzfLPXgST9MnDcrH8swzQOxnXTXs2PqWX55Ul+v/l7g6pPP/S6A5cvqg5yO/OBzb9J42ia4886G7LLaNo5JuI5/9sDi0+Yz48o2/Q7/Mb5E5dvVIxlJh0ckb065DMbf7WD9+/wxs13Ng0PuwIvjV/MG3fhCxt/hMtewhdCgbuTah/dO0z4wqbsk65f2fDdXDf+5tsOc1JbfvEMM8Ag5/LBYpbPa9yxj6Qv+MsO8a/x/dePhId/Cc+Q9OFf0mdI/pl/yT9Dyg//Un6G1B/8S/0xpP6Zf6l/hrQf8y/tx5D2Z/6l/RnSf+Bf+g9D+h/8
*/