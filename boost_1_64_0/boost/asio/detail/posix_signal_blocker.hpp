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
jRatyw2UqkpkURkjqokUFzbbJfC+T3sGfbMV98yKydfOYUQG15KZAxA9ZdyLsZ8A+50/y28/C2OfTzJn921dhI/LssPZ4GwqHSaq6KQ+yXgkkAz8Zy9qJGJzggvtU063FLxVcMCEk2NIGFLPW74jNZEyoLcwACxFdQID2DKpEtE9kzZU6ItYlA7xH2ByqYAuFTA0z5p7f8mGCbaWUqBImkUnk1hDlarUxfa08dZZvHNCL5DrRtYG505Pc2mCWwTBT9GOqwMsYh0bpBvHGbA6+LgrCMnlugTFS12NUMnfNhtJyEXg0Lf6qKJDPV5wnrVPE9x/OkoPQdCIJdIRHtqvo91b8n+EvpxpUWgEzayHCIzfKQB9KaqINNO9KUSid2UdMyN0fvJDTWvsAjbesgl6fa7CfqTl2sRm38MJiQf210oQvmCBds8Uff6OUZF8V4cpE5D/0ZFp+ow7pR8DINvZLk3mfyq9XphPpjqtt3QlQlRFTWFaaifk0S5e+oW7aHt9L+DUyVzOVGbkqL7Ha1t9NM9bejybD+9z5EztzhpDJmRSIIIyYsueQlWJUw==
*/