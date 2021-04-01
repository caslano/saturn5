//
// detail/wince_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
NALbbJ9hJ8SwMqH75RufaDqieQFmO7fePGakNvCylmKV4VOS5QjBn5A3oqwL8l/0HgXn1ZDLHEh47b5jaaOC4ZOko81/aq+KhARHOMyf55kcVbAJ1vgi7yiFTpCNvsJdlyq789pmENMYS3FYsrwbWFqXpb384XeQu2cY116I59iquRYGmTrS8UFpX/vn9M6j/JwWv+CVWLWB95Lrmwi4f1L871OB9AY8pNH0Ebw8AtpeiFS2al0TfNbrQKvUxuwIwJzxSpgC/EyrBPYjuAEcYwZsrNPwPMWag0bNfEBofZrsHh8AVmf5+VO7iGa6AJVATHzJglldkzwj2KQY24KEOddbBBAeGOX3w0L788UApk6oCuhrrcOranWC7CkxWxHq6o4mcHmPxeH15+yrKep5Eiw08kN/7ge1KivGdPUNGSdMCNwpQ9t6jpiMSEiv02md8oKrelDrAFEPnLgVgOsPd2qD7b6rDt3k8eN0DkGJiqAXquMO1CXcEShPji3euZGWoL5Lb0VnID5W23IGhrAwKxWrpynzKFprXX655KdJRkA0/6CJvT6gPVIAwA==
*/