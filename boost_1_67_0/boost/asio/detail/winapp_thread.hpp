//
// detail/winapp_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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