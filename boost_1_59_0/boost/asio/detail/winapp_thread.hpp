//
// detail/winapp_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINAPP_THREAD_HPP
#define BOOST_ASIO_DETAIL_WINAPP_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) && defined(BOOST_ASIO_WINDOWS_APP)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

DWORD WINAPI winapp_thread_function(LPVOID arg);

class winapp_thread
  : private noncopyable
{
public:
  // Constructor.
  template <typename Function>
  winapp_thread(Function f, unsigned int = 0)
  {
    scoped_ptr<func_base> arg(new func<Function>(f));
    DWORD thread_id = 0;
    thread_ = ::CreateThread(0, 0, winapp_thread_function,
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
  ~winapp_thread()
  {
    ::CloseHandle(thread_);
  }

  // Wait for the thread to exit.
  void join()
  {
    ::WaitForSingleObjectEx(thread_, INFINITE, false);
  }

  // Get number of CPUs.
  static std::size_t hardware_concurrency()
  {
    SYSTEM_INFO system_info;
    ::GetNativeSystemInfo(&system_info);
    return system_info.dwNumberOfProcessors;
  }

private:
  friend DWORD WINAPI winapp_thread_function(LPVOID arg);

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

inline DWORD WINAPI winapp_thread_function(LPVOID arg)
{
  scoped_ptr<winapp_thread::func_base> func(
      static_cast<winapp_thread::func_base*>(arg));
  func->run();
  return 0;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS) && defined(BOOST_ASIO_WINDOWS_APP)

#endif // BOOST_ASIO_DETAIL_WINAPP_THREAD_HPP

/* winapp_thread.hpp
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
*/