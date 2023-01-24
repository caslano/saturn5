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
oktR5SPrtYjd9iOJFVS4KApoMfJtXcNerGnfI8wldUZ0sYiDyJozkkt1T1MpOrZRXyrYjrRnRZe3hfBTBah2VDP1ceCaI1n8jsEHtypLoFlD1+56aV3aW3T7Mr8DzUJNHVr4kaIo0tS7ywk9ChNFfVc0nxk1ZBCW1D0jeXrUmeQzkrqozrZtC1f0/mONAkSk/QTqmWtUg+aCAzp658QXoIfssFD+ytW27UJwMH/5SLDTh3bcCs1RbxW60618V9AZ2U9E7MX207c8EbcX806VeiJFOeJP6JQj+kSFckSeiNpLeqVimBR1PqBvBnrsSGOY/RzB5yjsVZArhVw6clG4w1iUlHrQjEIu6nP1VFbKmPpBhaJU/VSoAxWLgvmxKAA9JYKpM4sEFYnzLdG0zizVVNW4kcnaqYLTAjbVbBhGnVHIpV4wFtr0IiZ6fQ17GSkdsXwmTDtiKS5SpDpiKTZSxDtiKT5SRDtiKUZSRDpiKU5SBJy0+iaq8RmZxT/E034Si88GjSXkIkXIRYqQi5TfcpEi5CKF4qIzVshDCsWDD83XQY566eVDLcuwKlG3FKGddaZKqVAWkxKjvTTv8l3fxeAeT3FG1Jt0xlBlIkKTpZBXXOAV7+Qfh0F5RZGXLvCKCI9NlpChePHNisYs0DMp3366Vw8FmLGfgFwd5I7UzncYI8NnRFqGzwfKQRk6Ol5lOmhiuX3WZ5S2lutJ
*/