//
// detail/throw_exception.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP
#define BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)
# include <boost/throw_exception.hpp>
#endif // defined(BOOST_ASIO_BOOST_THROW_EXCEPTION)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)
using boost::throw_exception;
#else // defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)

// Declare the throw_exception function for all targets.
template <typename Exception>
void throw_exception(const Exception& e);

// Only define the throw_exception function when exceptions are enabled.
// Otherwise, it is up to the application to provide a definition of this
// function.
# if !defined(BOOST_ASIO_NO_EXCEPTIONS)
template <typename Exception>
void throw_exception(const Exception& e)
{
  throw e;
}
# endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)

#endif // defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP

/* throw_exception.hpp
6GB/jbucB6AjrLQxHMu3Bj3zQPjgrGCAiL7SBDCCOxeZL/IbFzp0yECwTYWBWJn+kvXyy1rmkj1ZE5SovV5y5lwkLizDv8B44Sz/W/qpn4gDhOGQ19Oe4ZB3RyfaBNYMUhGHCmuki41mPRKCkk9FJsezRhvaOpfahphc3uU5FwiMnnnpE4LdS6mQ9ExKEa1QaIvVxaOVFdHZstoPtxMSy0HbrQMlo2QFgMKSCqLELDkCtEvtna046aX0Ws6IJIrmn98/3sMB0U52tEU2FPQRxuKoftRHNgQ1Oxx1NRWMzypoZXMMlVMNoRxQQmRZYzUK7pBzl0upTfKQckzKoaIEqOSayi2MkwpVwl27BlaSgurSaUUOpXdVm3HjPcestMciUlMNoDbICdb0AhWKJCNqiWx0lPHLUj+RtixJVlFHEKxcOq24uiWJlmhO1nLL7VazYss22UauG2TjLOnUIqrAWLOtX8WMZdNpBsF1akuCo04UZOHmVv9LRjLsOkCh0ZUmYe/a5AWXBLnnU5BPDIWsWzRaf9Ep7DslKbWboFhILwv2+j/6/Ewq7mlzsO2Ttq+hfiwCVbxf24FIxZVbOXy5/wgH99eXcHZ6fHKY1EyhNzyNiLlN38g9ERvHf4qH0Q5I4VIXVJcLCNHzmJkh
*/