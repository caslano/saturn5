//
// detail/signal_blocker.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP
#define BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS) || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) || defined(__SYMBIAN32__)
# include <boost/asio/detail/null_signal_blocker.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_signal_blocker.hpp>
#else
# error Only Windows and POSIX are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS) || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) || defined(__SYMBIAN32__)
typedef null_signal_blocker signal_blocker;
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_signal_blocker signal_blocker;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP

/* signal_blocker.hpp
fDvAfr5TxAE82Qd/yBS2nLlqFlVDw4tWw6ZNlkWl1DP1k5rUNR/EcoTuHqE6tOBP6UqiVxmKYksBFI8MsZVll80ik8Z54dZSACkWKFDY0yjgKVHrLeHs7QrEmDnrG/YHwL6lYsRRiCu61vz3WYVoafdmvmHpiFx8f/y//6M50R37pktFRFiSBn4dUp3XM9ykG4PYE9RIerOoo4UDpIndnRTRj5E7PTg7Oz2LxXPf1/CwSeHKjzt9IXWOB+SBkcZq3ln+bp0aq6eE/g6UVEy1wSdvg1K/ShFX7zhDcqiVlYJJKnZiikK/Fs+CRbEmsScPTh4OWLPYk2P5vbSPHh0N7Pc/vvnh+Vv7Tft4Kc+sK+zD+HBp798/HRg6Ynt8ejIQl8z9pwMpbezpg0f6dGkfnD4Y2Ff/cXVljx8+PI1++/j4SJ+46Wxg3l69AqRHp2cDy0eFL49Xcujbq8s39uzs/sBePgXCOPFSMOfDqydYfSYPl/JkJCKcyCvB9QEer56/fP0cVAPsFbc+eMS0+nInpZu2Q4Eg+sWCTrSdaW7rwqGPBFCxhAn1jXSQGRIVp8o41rrWkCsZr5iW0SaPr7bSBm53CGzI26/YKYt96tRzn/lNWXg30xNaCIblFh3BPPrm9kunMu0p3bebp9CH
*/