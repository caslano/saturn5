//
// detail/posix_signal_blocker.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_SIGNAL_BLOCKER_HPP
#define BOOST_ASIO_DETAIL_POSIX_SIGNAL_BLOCKER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <csignal>
#include <pthread.h>
#include <signal.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class posix_signal_blocker
  : private noncopyable
{
public:
  // Constructor blocks all signals for the calling thread.
  posix_signal_blocker()
    : blocked_(false)
  {
    sigset_t new_mask;
    sigfillset(&new_mask);
    blocked_ = (pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask_) == 0);
  }

  // Destructor restores the previous signal mask.
  ~posix_signal_blocker()
  {
    if (blocked_)
      pthread_sigmask(SIG_SETMASK, &old_mask_, 0);
  }

  // Block all signals for the calling thread.
  void block()
  {
    if (!blocked_)
    {
      sigset_t new_mask;
      sigfillset(&new_mask);
      blocked_ = (pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask_) == 0);
    }
  }

  // Restore the previous signal mask.
  void unblock()
  {
    if (blocked_)
      blocked_ = (pthread_sigmask(SIG_SETMASK, &old_mask_, 0) != 0);
  }

private:
  // Have signals been blocked.
  bool blocked_;

  // The previous signal mask.
  sigset_t old_mask_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_SIGNAL_BLOCKER_HPP

/* posix_signal_blocker.hpp
MC7Lf9zpvvynDYDihbv7Ka9dLIuWQeChB4bpwN+4x9XHKjgtyJnKaGrXCp2Qe4JvWo7cghA5JCwABMD4rL2qLSed1ytSAOfhMb1BpY6mvfdTJOIsJ952L5nTVIpI7AvPB6rjbKa2nk0NzILkQ0f82I0b+SG3EOalyyMCqtN0mEE7rs3M3r7Qipbk/lH4eICcIAXqg9tvXTVlM95WXnHWegjzIigZ4apToGYU0nVK37i9Y9VV9ExLzbMzN2MgQA2X/l6L0zbTTO8OWJtd/KJGvmD+d1VSzwSK1XKW93T/uj/z5nb5v8P9+GjnRfwX9MH/2PGFKXXbJ5Vvz4vkcyIkX3TzbcvH6s3uZ89KetrrE4hPvi3YbPaDgwOBh1YdURu6fq/fOl9SUtvx9DYYlzbySNd2xBVpLRTKJPCw8PSTQ4OOWP34199tbIU5EsUhhw6tZhJ+rVGJSg+le2ddspBEhFVpp67CuAmQ8QYnstGao7yrFL3XqkLRNZws1RUHphFpW8asJhPXNCxFXpfzavSMcNb+4T5h9Yy7nN0pM2G25V+ggtIrC+OSV/gQQzOQ+NRBS4ie5kw1p4QJ655Jt+APF368bSuMF1aCPHksPVJlp5aQJrX5JKEduMW17gv48hi4lU2SGbZS6zlrAKs6
*/