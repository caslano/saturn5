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
aQQifGYDZzsRn8XA0UZuo7Oa+Gaw/19sNtbXdxh3NkMjmoDa52ziDXjtoYzH5Z/D5JvFrdmtyM0Z4KrFLVSbnyvANepN1S7nNjl44eJWbkmai/U7D/PFUsmRbWxeHwYTDc5nPol7NZqfNZrw2dptkJs/yHntEcktYHKeP96CPs4fbyHmSjDiD4trtlKrWWEfL0wcVqW5r2wRhdc9R7QBh86bi0q8XqvBuRTTX0xhjW2xrcGHLlrNbVG/OHGUJdf9EgaGZRRjLfwPLiQ9ea3dHdRs3RST7dF2sVmstfQ41WPqGjAXhwqR+SxpctACAjlh/DGmZmuVAHJLMVd2htuj7D21V1ly4ntodq1eg0bfKlb4Gx7U55chDU1SGFvWwGAUQ2w5A5Nz7+VNzIX5YY3sXSGMi2SQWzHMieQwvZUU1xAndbfG9qzM+Ai2HNKuorBheKnH0mNkf1xV49C4nKbEEwovuY3NBE72rKbwCnzTkONwvknFVcsynZTCajCJtlvyuiit8XalQtpehcG7R1xxRqZ+urrEy8FKIZvW0Ly3Wb1dKVNbxTQzkgPf8Y09zH9Nwn17aNcyMDGTkuNEH+Giycp+z72H8u/XvGpRMm42grOLTTUeDmjetwdt0MCdbZBCfG2N4xBru9S2chrH2Y6sr7zGxXCLTWgbzqNgcDAuqjjraJw8acMRl2fdICe6n1evybjraR4qo92Czwgqbn3NCdOHt4Xzg6yPDTTnSR9syNhmzjY8LJN2I8K5O5B2SGEtHpdIuzHjFficplMjbBOJ1etbtLkv2YxVwTbznLapgfsqEXOhchUDGt60jdxwgMNo7MtSkCs7UMy6uv4qB3h0DnNOkGu0FTcS5Ix576jB6TGYfLCZwZnvVnBN3Iv2weYhjfbBFiFO+6Di48I+qPp4vw9qPs7vg7qP8/ug4eP8PtjS4OplfF0K4k0T55FkMsA9woW7sG219LGd7M9j3LbGcIe9bN9bGfjgWsn8MoxvrXEeb8jubQxcDKaNoqvG6201J8/jiG+ncTqvcb/Y3sBH+B7FDibmVtT17I4aV+eenTQGPqmKswfiO2ucB0lKYxeFb6Pm2btKTNQNY7uZ2BKU1+4Sa1eHnSbWJPpjDx+Otaj6+J6Sw7olbC8ftgSmsTdhdOsBR1QxEbSwbveRXJ3u7+1Lx3Q3hp+j7CexVtM37uwv8ba3mcQOUFjLk9iBjJELKM2DGPO49qX2YImL2mftIRKTtc74oRLHU4eoeErjMIljrRN2uMSw1gk7QmKidll3pML0OfsohXlOCaX8PEri3Apkfz5G4hHnymMl1+FceZzmeVbCz6YkHjiHniDxwDn0RI3T7Jj1J0lcnkMZP1nj2H6lvadIvMO58FTFh8+Fpxlcq9QQdwsrRX6/1umSq8mWRvgZhKNHaf7Dz50UTvewZds4y8CxQDyen23gwRmVLNs5hsY3q+K2cK7BOzw+nefDbBeeNlWk7ef7OJwMIn4B4WJiyJVB6V/IeLsB2Y4QdhFjW+H5mbCLJUauwjQvkZh0IGsvZRy7P9fDZQLL2qvBu/NS9I6AGtzho3cbXB7JibZEfrzCz/MpD4YSGmbp+ZChCb4z4KoAp98Qwc+IAryL2fMzoiAnTeNrrWuDvMc3zwL3wa4L6MTtK1ln1/s5MaZj2jf4cdGGg4nT86KgLlC+mwJ8uyZy52dFQa5RLspx/Bbk8F4jXNsRdqvC0MWI3aaxUXkeul1h+rnUHQoDE6EgjnFv6k7F0U0/6Zu7CF8dXpOxGg5WjN9t4Ob9m3sMXFhjjmv3Gpz53OI+E/f0GHp/ALfrFTWWP8Bcb09V3HpC/YMm1mz2NOqVbaX+Ic2J520=
*/