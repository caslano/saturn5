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
3uZsfKBmmD7WrZqz8QeZs0m3znUNVK6tJ8SczXq+3Zz9Rk/QnH2o5zzmbLKW/+K85uzyoDn7697m7GbVnN2kmrM/GtCcfXgAc/azqjl7uGrOHqSasyNUc/a5bm7O/qabm7O/UNUuZIqM0Azboebst6b3b87Oi+GiOXY5xJyNlyiavxZqQ+D275i+5mzC14ru/z+Ys6u7f0hz9vy/+//T5mytQwFzNrlEBMzZr1p/YHP2mA+5/JjeqRG672POnvu573/NnP2rUT+oOVt4/lvN2d2pA5uz70j9XzBn407232jOxnZ9uznbHvd/tjm7UVs6B8mErZqz8W5fc/ZiCjsiA8BA5uyffNqHVw+Ys8frVV4dqcn3Nmfnfer/rubs7k+wD9/PnH30E5Vv/27m7Gxd/+bs2782mkd8ZTQ/CcfXcGS2GM23wvEsHKe+JoZaOGQ12tihPyM1VGSrqcARJRmVwjqFByrnyg6Ts718DPLCecA3z2dHkCOaCVurCER7vfffaISuNIQy4dmWavWLoWSEbnK793ZSACv+PdjaSYZh/LujhX430V9Gf0/R38P09x00648ZCkz4hqHIhGNyCHbtMmTCHxgzfUd1JyYQlZ2voXJ2aWk3xks3D6IddThbMDTAmt77d6CtjZajco183OVuRNDuZztxjgyFdYOXW8/QzdOdGDUN5P5hdDHdt60TqcoW+Juvwz2mCn4V0S8c
*/