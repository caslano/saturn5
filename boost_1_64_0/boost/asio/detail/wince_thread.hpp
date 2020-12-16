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
kHd5PGBOSMnFLfmavcYPyDdj/FDXzpAPriEfHjve5rHDnujND7qmi7kN0NNCPkAboJD1aQP0Lxc11wYo85/ZjRwuneDJcX+j9gxuxvmf33tgXdlz3xwv0efczzJyrvuwg397X1wv/J6CPOW4bpzXtPqt6GrUrz08dnP9eL631s8egH4sY/p86eBwrf6N51l/fi4wPO9JW2jd2BYav08vhrtefMvOoTIpxE6L6qJ8PD9yOeA7iZGrJ8d7HWwE+YvlOxDKDQlwmUj5VA2/LPZqaNYtR1N4rHwfc5B/sufZW8MFlAS8nMKnQleRH/MZixw1712VJNNLfqd1kj9B2gtenI7vG4LjHO6oex0T/sDWMrOAKBcDpxDuBddId68yP9uDuR0Ebz3jrWIdjMu8XJS3Zv3iO3POYJYfKd91Y0YJ/9eC05rfifCVh67NsnwnaqOo6QyTHLStKE6C7SdKmOk6SDHnrXLMl8EfQXHa2ZZDU9N1EG4boSSXhLSjeJ5X0xqoe3fyHuPWULxQadeqN/m/xPN6sn5dnXVHmV9M46JpWdgj1HwKiyr5e6gTqJBMR1uC5NQWMuVztOv139D9drfV4HRdlEyrQn3WkJzidzKHawHcMqSVD3wa9/m7DOEPZH02PB73LG0oaHnpv9Nyu/L1Yov3vQqTdZ5FxnUembadr3vKBm1cXq+g+S7RfV9KbQeF/Pew/+4Rbv9r0u/d9o+m8/odc+bPBy6DTMXFmrbve+2IZVPZLhm+g5F/ZEhv1MZGZRvObg+XdgyGjkEYriUpLqt1BE7PzpzI0In8F4UMwb+HlC7gmojCufHRsh39itJMtuxTxTLNzrJ/3EX+K0OyURpmfapExkmW/fAO8s8OGaaEWa5VJY0WMgc1z8KcDv5jLnGz9UU5Lr5HsmEhum9Ycv2xN6Ufi7uOlOP7ULq2zayMjX2R40whmW7shyUg8rdWxwr8NO2Q6+FKyifR1kX5ibJVyTCWP9bTz/WAvmmqzTDXYYPNMJZZk6ZyN7u+MHA3s8weKVMzWy/zY/gv5HdxXn/Fty/J4wwtsBbHa7LzPTzOuH5+1+j8reto+zn3fe3cT31zKpUr8uK+eob9texPH+Ptz4Nf29dL2H+Prm/PzHArdDVcG15LWQ2Z2rGQB41IUVlRZcmc/IKqsv6m7Rl9m2W7W/ZVDqd2k8BzDM8Vch7cTDKXKHa51s7x+Dksge4Wa3OaMf1ZChf2uyIs54dc4E6Su0iuxX+MtIbCpcYHvn9FUx8+v8VDP1xj/eT6lmF81nKJ4vy1+TO8y/2MSwOr9+O79fOtK4DnW5f38yv6xPl9ftXaW8npa/787tTpxo/ulno5A9DL6ee53anT+3c/0HO75Izta86lHTeu6VzaceOC5zm14tKuzzTn0s4aFxyXdtY4/1zaWeOC5yFuKpf2mn7mXNqOcU3n0kYcX1ynCA+e6/Sf7J0LXFVFHsfPufeCCFdFUJ6KKIo8FBFF8Rm+34rvRyagkJAKJPioqC6uW1aWrFmZ1Ua7JlZuq2W7vbas7bmVsWWblRWVlbVWVuZWWu5v/vd/hnPPAy7Yti/5fIbvnXP+c87MnDkz58yZ+Y0/WtqaZu9aC63/P/VH+yrTJLppxMecMVNnTpg2VV63Rt4Ny3TXbUeY9XUrO4PrhnOarhvOY3vd6llb/w5uo26Eu0y0Ud40iskDRYVLluWKFrR4CZ6EOG0jOpraKg4TK9ude8j/S2Ut/gdzvYHUyTZmh9wfSGNyKpGAtX15bTlHREhSSCqG8rqCTf1AnE/3UvhU9qMVHEfPZrb9QjvJvgs9v/j7Hot0+jwrHKJjIG0dFPJ/zv4F4V5/q3HS71NXu1g=
*/