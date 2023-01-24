//
// detail/concurrency_hint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CONCURRENCY_HINT_HPP
#define BOOST_ASIO_DETAIL_CONCURRENCY_HINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/noncopyable.hpp>

// The concurrency hint ID and mask are used to identify when a "well-known"
// concurrency hint value has been passed to the io_context.
#define BOOST_ASIO_CONCURRENCY_HINT_ID 0xA5100000u
#define BOOST_ASIO_CONCURRENCY_HINT_ID_MASK 0xFFFF0000u

// If set, this bit indicates that the scheduler should perform locking.
#define BOOST_ASIO_CONCURRENCY_HINT_LOCKING_SCHEDULER 0x1u

// If set, this bit indicates that the reactor should perform locking when
// managing descriptor registrations.
#define BOOST_ASIO_CONCURRENCY_HINT_LOCKING_REACTOR_REGISTRATION 0x2u

// If set, this bit indicates that the reactor should perform locking for I/O.
#define BOOST_ASIO_CONCURRENCY_HINT_LOCKING_REACTOR_IO 0x4u

// Helper macro to determine if we have a special concurrency hint.
#define BOOST_ASIO_CONCURRENCY_HINT_IS_SPECIAL(hint) \
  ((static_cast<unsigned>(hint) \
    & BOOST_ASIO_CONCURRENCY_HINT_ID_MASK) \
      == BOOST_ASIO_CONCURRENCY_HINT_ID)

// Helper macro to determine if locking is enabled for a given facility.
#define BOOST_ASIO_CONCURRENCY_HINT_IS_LOCKING(facility, hint) \
  (((static_cast<unsigned>(hint) \
    & (BOOST_ASIO_CONCURRENCY_HINT_ID_MASK \
      | BOOST_ASIO_CONCURRENCY_HINT_LOCKING_ ## facility)) \
        ^ BOOST_ASIO_CONCURRENCY_HINT_ID) != 0)

// This special concurrency hint disables locking in both the scheduler and
// reactor I/O. This hint has the following restrictions:
//
// - Care must be taken to ensure that all operations on the io_context and any
//   of its associated I/O objects (such as sockets and timers) occur in only
//   one thread at a time.
//
// - Asynchronous resolve operations fail with operation_not_supported.
//
// - If a signal_set is used with the io_context, signal_set objects cannot be
//   used with any other io_context in the program.
#define BOOST_ASIO_CONCURRENCY_HINT_UNSAFE \
  static_cast<int>(BOOST_ASIO_CONCURRENCY_HINT_ID)

// This special concurrency hint disables locking in the reactor I/O. This hint
// has the following restrictions:
//
// - Care must be taken to ensure that run functions on the io_context, and all
//   operations on the io_context's associated I/O objects (such as sockets and
//   timers), occur in only one thread at a time.
#define BOOST_ASIO_CONCURRENCY_HINT_UNSAFE_IO \
  static_cast<int>(BOOST_ASIO_CONCURRENCY_HINT_ID \
      | BOOST_ASIO_CONCURRENCY_HINT_LOCKING_SCHEDULER \
      | BOOST_ASIO_CONCURRENCY_HINT_LOCKING_REACTOR_REGISTRATION)

// The special concurrency hint provides full thread safety.
#define BOOST_ASIO_CONCURRENCY_HINT_SAFE \
  static_cast<int>(BOOST_ASIO_CONCURRENCY_HINT_ID \
      | BOOST_ASIO_CONCURRENCY_HINT_LOCKING_SCHEDULER \
      | BOOST_ASIO_CONCURRENCY_HINT_LOCKING_REACTOR_REGISTRATION \
      | BOOST_ASIO_CONCURRENCY_HINT_LOCKING_REACTOR_IO)

// This #define may be overridden at compile time to specify a program-wide
// default concurrency hint, used by the zero-argument io_context constructor.
#if !defined(BOOST_ASIO_CONCURRENCY_HINT_DEFAULT)
# define BOOST_ASIO_CONCURRENCY_HINT_DEFAULT -1
#endif // !defined(BOOST_ASIO_CONCURRENCY_HINT_DEFAULT)

// This #define may be overridden at compile time to specify a program-wide
// concurrency hint, used by the one-argument io_context constructor when
// passed a value of 1.
#if !defined(BOOST_ASIO_CONCURRENCY_HINT_1)
# define BOOST_ASIO_CONCURRENCY_HINT_1 1
#endif // !defined(BOOST_ASIO_CONCURRENCY_HINT_DEFAULT)

#endif // BOOST_ASIO_DETAIL_CONCURRENCY_HINT_HPP

/* concurrency_hint.hpp
kCfxFalNpV7fYtFaPxkhEmLw8E1dag4QKd7phUn1xrn9USwiglZhuTvY7RhIXFba0XPBjnwHAbXQhh9F6/NXgqrdHdEdbNODtlmkbeMJCEmgEFuNeJ1E9vUq4a3sE0p4p6Yywoume7zQpdaBA1x90BDEf04deW8ZG3OUhZHeRf3nN+xl86DQ2up2mdZeffp2k0W+htUhXYtPzSXYiu9J/jU5GP/SO4zDy+ewnO43oeG4Dybw5sEtAWZ9hVj78WR5sPHG3mjuk3ugaqmrG/E90EJ3Ak/Cb3xH58tOdoZTrRzw1J2k0sZ4yatvBpQAVZPh8EqKJ4Mm0wPVLl1ghQEDJ4h4jOopaWVCFAnDwhSDEAH0CRCR05Nw49M9gnPfa1B3IPA4EE2kC+YfQGAcfDH7rxDGmLcZfuTtqILR5iRQOVSFZ+tA9u4RrftzRWtdkfWEaN2RajUqxLtqkjr4TXGUeLcaKPGqrg5B7/t6SkEquql1k1bwhklLhcoia53yqrCYN07i4fWdwj+LrN9N4oXIT6iLthu8Cf8EvbPr9qJDAdRgAx7J/MxG+F/wgjkTvTNxAn4uUJBft0KIHgz8o2m6mH/E1w3+rZeaB+ccEYUqGPsd99OZEPoEhM/Is4sxSqGYrF+Ma6hhBmAAquwZBE+D8cr5D8T8bYE4CyjZUpV0y4efucKcoItbK2xzpBIUMdQYkbU10MfnBOJMskK+
*/