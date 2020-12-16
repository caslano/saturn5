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
Dl+QvCE9GmXRDL0xBouwAQdwAQ/wEckasSZUhB8CMRNrsBNHcRNP8QNpG3PeQUU0Qk8EYyn24hLi8Af/NOE8iDKogWbohmFYgI04gVt4hgQkaUpNoDhqoQMCEIyVOIZH+II0zbg/GqAHxmEu1uAEHuM9fiNZc+KJHCgLX3THOKzGKTzEH2Txo3bRHP0xFWtwGPeQgPQtmINohmGYj12IxhskakmfQnV0RjBW4wSeQrSi96EIqqITRmA+whGDd0jTmjMrasMfo7AQuxGDl7BtuBdKwhe9MQbzsBGRuIznEG3ZF5RAQ/THJKzAblzCa3jacU+UhC/aoy/GYxl24zLeIkV74orKaI4+GIfF2IlLeAXVgbMKCqA6/NADQzENSxGBU7iD97Ad6cXIh9Kohkboh+nYgCjcRzxSdyKmaIQ+mIIwnMIj/EC6zuQXaqMDRmExduIy3iKFP7WHOuiKiViHk3iIn8jYhfxDdbRBDwzDFIQgHFG4hRf4ikRdyUPkRCnURgcEYjxmYA224xiicQPP4LrRA5EDZVAPHRCAKViNSETjGX4iXXf6OIqhMpojANOwEScRB9mDXEMWFEMNtMcABCMU+xCNR/iIxD3JJRRHbXTAUMxEKHYgCjfwFLIXOYWiqImO6IFhmIJV2I0zuIw4fEGa3uwF6qI7piAUB3AHf5CxD30JJVAdTdAVQzENoYjAKdzGB8i+5CMKoDxqohl6YDTmYzOi8BBv8Qep+vHdgIIog+pojoGYgOXYjWg8QgIS9+ebDd6oh9YIxFSsxG6cxUPEI0UAz4AP2mAoZiMM+3EVzyAHsL8ogapoiX6YilBsxE4cxGlcwQskIHkg5wgURAXUQ1v0wFBMw2JsxnFcwUv8RKqBPBfe8EVXDMNUhGADDuMyXkEOYh+RA8VQCY3RCyMxG+uxE9F4jHgkHcxz4I36aIk+GI7JWIYtOIBLeIxvSD6Ed0MBVEQjtEUvDMN0LEc4TuAmnuIbEg9lBiEvKqIpemEkZmI19uA8HuALUg/jLIOSqIrm6IrhmILF2IQDuIhH+AA9nH6A/KiAxuiAvhiBaViIddiPaNzDK8TDjeD3KIhKaIMAjEMIInAY5xGHH0g7knpCbfjBH8MxBcuwH+dxA0/xGXoUMw+5URI10RYDEIwQbMFRXEUsviDRaL7PkQX54IP68MdwTMB8rEY4DiMaj/ABNoj3Qy4URgU0QEf0xRjMxFJsxWFcxGN8gRnD75EbJVADfuiGoZiAuQjFZhzFTbzGLyQfS89CHpRFffhjIKZhObbjJG7hIxKPox+hAHxQBx0QiOlYjZ2IwjXE4ieSB1PzKIW68EMAJmApduI0HuAVfiPNeGKLAqiEhmiPQEzAUkTgGGIQhy9QE6hhZEYRVEZjdMMITMFSbMEhRCMOCUg1kXWiGGqgFfphHBZjF07jNp7jB5JOYp0oiPJogPYYgPGYj3U4gEuIxVfYyeQrsqIwfFAH7RCAMZiJEGzEAVzGE8gprBU5UBJ10RkBmIh52IZziMV3pJ9KPFAL/gjCDCxBBI7gCj5ATWPPkBF5URp10Ra9MArzsAGRuIhYfEWS6cxO5Ed51EFTdEB/BGMJInAA53ALTxAPM4PZhVzwQX20QRcMxHgswlrswUlcRhziYWdSF8iPMqiPtuiJkZiB5QjHAZzBdTzGFySZRY9EXhRFBTRGbwRhNtZhD87hLt7iN9xs9hQ54Y166IAABEMIKZTQwggrnPCIRCKxSCKSimQiuUghUopUIrVII9KKdOIvkV5kEH+Lf8R/xH9FRpFJZBZZRFbBv4eJf0V2kUPkFLlEbpFH5BX5RH5RQBQUhURhUUQUFcVEcVFClBTeopQ=
*/