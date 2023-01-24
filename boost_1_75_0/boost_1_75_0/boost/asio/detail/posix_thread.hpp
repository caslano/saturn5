//
// detail/posix_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_THREAD_HPP
#define BOOST_ASIO_DETAIL_POSIX_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <cstddef>
#include <pthread.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

extern "C"
{
  BOOST_ASIO_DECL void* boost_asio_detail_posix_thread_function(void* arg);
}

class posix_thread
  : private noncopyable
{
public:
  // Constructor.
  template <typename Function>
  posix_thread(Function f, unsigned int = 0)
    : joined_(false)
  {
    start_thread(new func<Function>(f));
  }

  // Destructor.
  BOOST_ASIO_DECL ~posix_thread();

  // Wait for the thread to exit.
  BOOST_ASIO_DECL void join();

  // Get number of CPUs.
  BOOST_ASIO_DECL static std::size_t hardware_concurrency();

private:
  friend void* boost_asio_detail_posix_thread_function(void* arg);

  class func_base
  {
  public:
    virtual ~func_base() {}
    virtual void run() = 0;
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

  BOOST_ASIO_DECL void start_thread(func_base* arg);

  ::pthread_t thread_;
  bool joined_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/posix_thread.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_THREAD_HPP

/* posix_thread.hpp
W/+CRxM6F1BoI87tIP61FbWb64PF2VXOI50oflU5j9KAYVtsMp0oMTg+hT0O8WljCz5XPbUeGNFA9IHYyphiFz23nOB4T/f8OcjIt3aGMfIqFz8aGHpg5OXGYMs82zAt1+tm5OKJxGyMDJqVvk5GG0aj536NiW8kJv41jYkv0pj4L2F/s9+Fy60YWfjL7SsLMDxqNjHxiEKViV+kMfE4uN7MQFORic85zpl4/N6jTDM4nInXOu6RDKoVqIUoOYLvj0NfG+TQ1So8W5E/j7PfSfQnl0/NcBYd7/Ri0f2DyJBDE8H5bGeQRcdJgSw6vsNZdKqHs+hrO1UWvSI4vsq+XZ0qi84CxA7unqEi+Aaw6Cue6sOiY2Fi0QlKLrv1GmTDsRvJ1HuNS1cfH7w6wKUnh3DpiK05nsuJS2edvbj0n6tc+h80Lt2lcel7AkjWuPSfI01MKpCqs4pd7mNI2lzOt6kU7lfEqpdyVp33cGBG3aQx6pZqbwyw6rCL+jmz7idm/Qgx6/4gs459CDDrfnkr7R0qsz4KmHVeYsM5ssxFEWlS2XVqm3tfZ7eq5Oe7TpBjxw5yjv2AUeXYt9GI4+AEOHZEBq8VOXZ8RBw7Eb+tCDvx3TmcWqhMu9V5gjPtM+bbk/KrotO9U0M1A9oqlN/F769bqhcUJ0eIMVJtBAzo2cR3j5/jwKSDOPmBbFapWvcEzsPzj/5hdKLLeSww
*/