//
// detail/wince_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINCE_THREAD_HPP
#define BOOST_ASIO_DETAIL_WINCE_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) && defined(UNDER_CE)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

DWORD WINAPI wince_thread_function(LPVOID arg);

class wince_thread
  : private noncopyable
{
public:
  // Constructor.
  template <typename Function>
  wince_thread(Function f, unsigned int = 0)
  {
    scoped_ptr<func_base> arg(new func<Function>(f));
    DWORD thread_id = 0;
    thread_ = ::CreateThread(0, 0, wince_thread_function,
        arg.get(), 0, &thread_id);
    if (!thread_)
    {
      DWORD last_error = ::GetLastError();
      boost::system::error_code ec(last_error,
          boost::asio::error::get_system_category());
      boost::asio::detail::throw_error(ec, "thread");
    }
    arg.release();
  }

  // Destructor.
  ~wince_thread()
  {
    ::CloseHandle(thread_);
  }

  // Wait for the thread to exit.
  void join()
  {
    ::WaitForSingleObject(thread_, INFINITE);
  }

  // Get number of CPUs.
  static std::size_t hardware_concurrency()
  {
    SYSTEM_INFO system_info;
    ::GetSystemInfo(&system_info);
    return system_info.dwNumberOfProcessors;
  }

private:
  friend DWORD WINAPI wince_thread_function(LPVOID arg);

  class func_base
  {
  public:
    virtual ~func_base() {}
    virtual void run() = 0;
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

  ::HANDLE thread_;
};

inline DWORD WINAPI wince_thread_function(LPVOID arg)
{
  scoped_ptr<wince_thread::func_base> func(
      static_cast<wince_thread::func_base*>(arg));
  func->run();
  return 0;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS) && defined(UNDER_CE)

#endif // BOOST_ASIO_DETAIL_WINCE_THREAD_HPP

/* wince_thread.hpp
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
*/