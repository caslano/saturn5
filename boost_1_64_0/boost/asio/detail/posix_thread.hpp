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
wFIhUbM3a9JU8U5ZfFBUNizW7BOpcWqmZt8oDe5NEC2HNPspzVZOpd4gjXwgyOnsz5qcU3LcRitHyzdYtATvE4rUoMton1Akj7VMgwevbzwoUqfXbB0cyQv30j6jQzTvNlzwsCr8Ws629A5mGMpIe+ivack0V74b9zCflmsuUCeHR2l0naAfjojSUF4NqBTRClB3ZKRui2LTVZmi7qiOOkq0WBlF3dG/rhP5ok+O+Q1dvemOgldQe+xvaJvOFmLYR+1xHbUySV0vx3fWetJRFvvzhGitswWIuQZRd2JnncwbdSdF62BFg2o8aOPJnXTa71j2xUB7yq9rcQm009Rt7dQoPRUdSk52ntZZ0yh6npg3YFqn/4oOEsM+dUaUhh6bI38m83n82JBs1PWyvJ9yluShHDSA4BMsjHu2yTVFXOVHtO+cEO/zH2rO7aCplkWzJX+c59OEO5VsL+eHdLoOii2YM7LugpAuUFesuzCkwwGWdVhW9NFFETr4E310cYjjleucxyUdeCgYnUXYT5eSTlwUL2EnIWf46k0Jhmj6no6HaV1manLOVjDFFlcBIlGS8Xn2ckOHpWD8Ch/eVOuurjTxpmxI+jxzVSSv2iqmcbXWdAcGeMz7GoM3bbrWh2ubrjNwnSfGpGdmmpcVRnurNM4X57ZXhcv+UpGu32/UvCa4Dm4yuRZc3RSbWsT23syaUr3aoPXG/KyMcN9z8VsNDKc2jN9m4Bnj+fftEtencUz7DsLlyQPLeacfUzMDWZa7InhVY+zjuyM1kIh8liZ5d1TPGZi718epNo/23kec77tb9zM2IvzA+T9AGHZO/wDmIf+gyesOpNZ4P2Tyujth3IdNzuEZW2HbhrT/EcnrgUFdJz5qcDiUcpqPaTyyjT+ueWrjHqX3hA9vVuQ6iCcZdz2oglYR9sZRX3qKcKyPgO3IP23w0nbKj8r2jOZ1wlw3zxKH0aQfnzMwu4nlUn583uCcMnW3YqvVlO3shQ48bzRHzYudNeJzKah56Vc0rW2ozb/s18BKDqfloIpsecXH608DcD60RyukwQQw/mshzlcU1LwereEsSPNGB02p3q7Ja5k3paYFvapK7eEtxto1NbrQszmFB71D55h3OvDadNK9G63T5rPuPaXrVBtUzve1LlwjnNYHStOpVqiMH0boMCFO56NoXheRdR930sns2PZPlC6yluj5IGl4cKO+8pkPk72FnxMKbqDfeBhLcb4wcJEPL25E7ssgZ+wX+crgzP3OX0tcNhPa74XcN8yJu9NwBiOG0/uWOZEPrrhk/DsDN9dufy/x7eBLmaz9AbFsLy2U1+vjfvThI2rN/k+Moz+4jn5mDAdE9SYJsTXXHcWlcZym1aV1vPgQyziWgYu7gmISJMfusRXn38vdJXGXdjsbT9mQHyeCN/dNjxvglQ+5PY0Xxbe9JjZ1+XwyQkMX0Px8MsDrO5iUx4RhXufB/p5Iair1otxbPbGJGXU2iQ8fUfd+JpU4ZSO6P+Y/mcbDRZTPJJUmbKJsv1P4NWI5JNwv3wy5KQMc2sb+myqKowaDcacO8u2aUGCZpmGOFqDiMnVMc1qJ65eacP+keNMZPG8fx3jTCzzXZ6cycD9vcEDt1JNlnCHMq3tMM4Y4fU9uJuQ2GCwM2PDNUf4kKJd/5ijObqh6nsXPCxbTnNWPcyyq09k0V1gjl06k1P7QiriDj5rZgxoceOB6UlxKcZ+eI6jx7SN11T7TOSN1Oq+5Qjy0DRao/WQhjRjk9PsT5onk0cXIzxvkcVUwipCfL8y3azYuQkB+/hDvyTIgv0CQ5xV3so8sGOR5gxZrsM4W0ppiq151S9gLKf+FFSfudEOVyhk=
*/