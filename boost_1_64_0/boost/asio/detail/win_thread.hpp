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
PN9+6dPH28Z7Yzq5UNsYqGKCx4+8Rse82dVXx0DTch1DnR4dQz1uHWPG4bQPj/tiuj+YR1RLIH/kM/OOdwePbiG95bqF+jzzjjpUtzj4olAvX4/CV34QX7LgFsgX+ZrWJ/lN8J1vy2/WwrqdG99G35h32OC+OOrTF19hrkUD+kLVa+BcizbdF6S3XLfmj25et1rvgdmDGkvo3gbeFD8bu38UmvMfthdB33dzaNVHkq71PSzxM+EJrKP9Ntze9r4l8iF0ZdA9IXSvhC9hTfCFMGezVW6wdC5nmbEE20GzPn1IaH8dzqH1Pw238T3b1RV8Weg6Sb715PumxI+H+3DtrnCe0IkXtKLGvSDi0FnxK6UNp6RneM2MNcN23uRrUtavwpfyb0b422ZNcrHknehZkywnT4/lcn47PCs8mnRrfTAq76RR/vqulPmTcGdTr1Rq9pHeIfmrwneFfqDXwqFBcm0cee6y3sv5mVdEs1f1dyn7ofDt4VTfd96u4HNSVhvzvv18Y9lShrxZC287eG+4QN6XjjEPRl3I+tWwmC+DsfJSbL9fyPq10hVAt2A4dB1Web/xozQ7TVk3RpJTI0m190SS2/m/Z5ty95PnI7E8nWt3m/nhonkemoJY3Sm1jxk96aJ5C5ol0r7avaZ9Lpo+A7DrjtF02XLC3EtcNHnQLM4Wmh+61+kHK03+QEKsnKQtFZEL2qcM5b9RKRe1a5vUr90Fkc5tbWsDvusg18g4XOAalxkyLkFrIxOFprNZG5kn8Qs9ayM1/JUiabtCsXGZDD+DBuraB+1lkCNJV0WSk4PWPzTPzIHW+seWWhZAPOsf9j6rjpUv47Ola9D47IFmv/RrbYPH55nSHIJmrozhu1Nsz3NCo+fuZK/qNcJM6PIJhbqeltfM3lVJkdm7kjWWqG2tUOOWvyuHTt17sfowI3NvEF0nOjVnhUunlpTLiTofnaq0/cw+xCyJXx926VJJzwCXSfo1YR8davZXFgtNx/DDocVGd61cKecwPTLXg7+qhf60xsOhNUI71aPHlsf6WGhnBeqx2yX9BfxG3Krn/OgJuTY83ImrPwl1EF32Oacuk/ILwEVCWxAO0mN/lfT2Zr60kbYu1rjhU9arcgbxzHaR6qaO2R7d1EtpBg1W3STCH0lawr++eknppw1WvdQp3y37hqYMGvQSNFVKQ9xFs2uwpZdWuNtmaA4MNnop16OXlOaoRdN1S+cgmjODrXlY+/6g9mRdbM2xLcPccyyDeFvVWx/sEcP4fQeKPNHN60vWx6aYzKl81xxbbptjlj85ZIS4kRHH3Ns5PCS/dAapG9gRnBnzOTrPPfdqCtl4sZ01liO0Ov8s+sVm/l0wPxZ/LByw96L0EyS+iPjrEn8uHLAXo/RrfL/RN8ekDxA7AOyjbc+J1UWrQZvvQKUNC+0uSbNoi1aWFVVVhWz0OS76PVo2ukzOaVfbaHNdtHVKew39yYyqrrHR5rlo9xIPekbLlb7sa9bdRy5QHz96n1og6RU8s00PCw2xZUKz2u8Z0dhaHJF87cw+xHMSX6DPQ+FQvcTf5EzDUmnbF0TXlK+37wdvFJrJYT3f7dGLsaq/LDQPatxq2xwb7VrD2/NCOy+UIXGrDUnhdK7dAM8Onz6qK38o/fhboyeD80TNGXaX3jV98hvJ21n67YCPbq0BhwrNx8Kxe/8+5nrWMPSErOVvIbSPJC9vYu9D80wjz+JYnsgWnuK6ePSfVfbmYZZO3dInktwhknR58HNFmuapG2b0WL1HjynNU8MsW4ktn/P4PlWaV8+Wsy2onAhlLBP9vGWm/T3Tzuuo7EadCQ9jIx3a+elx6Ihn6/2g45YcT3/oWfU=
*/