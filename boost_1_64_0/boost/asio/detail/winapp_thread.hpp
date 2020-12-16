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
IJGvoXxwTZaPF4drdZRx7q4QfIX6thDAmIQ41vM2h2vn7e3Z/uft3dne8zbSkPP2H+gcoziC7hnDHs/2mrch73/e3hWJMmqFfcX/YfM29BOy0M+yT8t6PBhtnLcrRZ8epqvHQPrzMJ9zNsL9z9ksY6wnnrPtCNfM2ZD/983Z2nLWjpOzmTe+Ea4947WCO926TPNx8sKqXDleqpLI3DpzyL8f/S5MeRbOorw5XrLkRbiC/L9ESiHKy3DW9cBxmTcR+7nlWZRE7l9XUfgrSlf8Ww/H9YF4Bj5LnGpBPJ7r51P400oU/tsGJ+RmJPA4rOEEqyc5p5KjpEjO3Tq6di2eTnJMuRHupvB7sf+ltYbTgLKX7edRkmlDvHaH0fY3xqrn9MfEhEfFhBZa8dqx/MFYycVl4F5Jhj8c/nnQZy3K7AG4X+Msy65kHscDsLGhb5O5Jm3SYdEmZwJRV3yOx5un+gzz+U/l8XoU3CJxZn24rk36Gashbz1Wc7h2rL6R/FkaDo6yggVFnnF6OYX34Xanxu+u5+yQ4/TNFJ4m2xvkfY7TXJcYf0WdnL8xOMFrDBY68fjrzRvgd/zNZk73Lfx8fy/cEsFNb1ov+WUlhdZ1gzjWz/Yy3C7r5jT5azS8SOiD7iwkL8+3JHMT+YtlGumW9fNXCu8p6wfyls/yWfARJzTaZh1KYz1xuOFZHuRE4MIGY1Hnrmqf2oCwh+B+DLmHgXVwhntAFQp9Y0fQOCHPySHPStgXks9sHSh8stRbIb2rF1cUebjJ7CQzSTeH++ed4HZhaD/F2vZj4HLjcpd8FMY2lGVsQ7Jv72E+/SXct+fCtesn7Bjp2xDo6BFmVd9oihyni+QYfZHLoT8903I8TXm2kXE6y3F4P/mnY599BOUVGsF5Ces+C+dI7pW9JHeFcpGWf4eudaR439H4reHq4DH8AMlcRk/xKk/oz5lT9heZ/nlCeV43LftceZ10lOMtdMA1qYNX+R+k+8Q+YbZn9B5ctZjvR+rK3/fzE8unSF7rq8l/QBmthOr7tJwnSyCDa3hybcX9XE0nXT/mynIvoPCXlVHQgsud43Q19imet5+i8ALu1yyPsYa51fR9TbaFhSS3E5I2OddLfnDW4TDJOEz7YwK/dy0hmUFk9Yk58OWY8DDcAqRbp/IKB8QV667XVedpnPeyU8e2FNbwHsQauKVirv2RsT3woG7VJjhOquQ8u4X8ZVZjPMtnyvn1bvIXWvb5tsCfkoyT/MUyjZ6mbWGqDB9oUffwc92vI7lZPsfZn5PMBMV6nA+cw3BVgO9N3v3ef32uSHJnNovfkfLghkBB+4+19TmvqNqSA1hywHOcS8ECfoHl8/dEKTeUnzFFu/Zvp4CfIQ0650rdtPkMi5/yYz7TBHmtvjs68L531nc63G3i3d6gL8ZCfB1QrPXlOJOU3tDX7BlwopQZYv0+ImXGN7s8eIzX9Gce4y3K6AUuoyR9GSW7M8qAS2AcKRr9Rdoy4rSYUMSCF5rjpLIfPY/84cxbZtI+OA4k2S/j+LULw88ShjaSDUReBv1TKV2clUr0fsdd1FGhXxwn3hrudjHneeuPNuL5DgQRqzLgeHGaZ1uKwvrJcL82Ttmmn6HO4+QzGaXrNX/36Wy0SXinGK8NuiA9Sx1YHqkkyLWLkqqqhfhoJutNymjWN6oW4qMct3MZbrqeOdUTbvimIcbiNNJ1bPwUyOFvlrVpntvmlhbMq+Jnb49slkc2qPJNFOUr10NYZ5ZNkteFnrweZbLunGbyvSlLjtV03151drqzsf21R/+rNdQZzbFWdcbycYb5V45N56Hdaecl7RjySYpxDLlLcDVrdeAxlocQSz126cY=
*/