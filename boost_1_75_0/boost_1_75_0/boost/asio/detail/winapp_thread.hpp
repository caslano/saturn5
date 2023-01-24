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
E/FXGG7oRTrtNJ4wmFIQj5eVdzo+EgbIeSBEi1PHA5pN/uIGc2oqEFWsOEUbSxkgS221o7FaPKAtH3CYnxUwmv4Pe+8ZFkWTxY82UVRwBgUVBUERxYAi02Oipw8mzIqSFRRRMYGigGQYxISoYE4omMUEiAFklCFHkSBJEImSGZIkCbd6Znhfdtf/3t2999O9zkNT1RXPOXWquk7Xr7qaUdutoUKpr66iKZ6pQF9N+QpLKZUgp/M0qi5J367O7/VSnQXaXW6ivhSgK52CLe/XNKqReMy3vrez3bv4MmqnZERt0BkcfP7RLqZgZ4gl/XPrKzehgWjTgK34gGZNjq0AxkG9AmrO6aCOXBrzAj1c4+qthW996TUFgvBfz/nh+t4pA9ot9jKIdfcvGr4ZiPtZyb7mctQZS9Q5SXF6gphNlFiS9Gr27R18mySROAyrRw0zHiXdj/HXT/fxB9Hx2wTvC7bWbM/5a+zU/HfkZwrJl/uL/DE18wRkGvDJrH1MPaYFHIypGSuIWiSI8uVbCF9WMVK83TM1kLGBBjM0VJ5TXKTdbC+OJkAx/Aoc5NA86Nmef6Ben8q3COUIiPHu6nWbpb1Czn3a8RT7EWfElh3nOnSfRo9WBzQFz6RsZQc5xOEp/hcBxtcrDAkfL4j6Th1kHK/4F/OW2X8/kYypb/Oub65pzhJ8F8W9+cwIVI+876nBsW1xsv2wpVSgw88z
*/