//
// placeholders.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_PLACEHOLDERS_HPP
#define BOOST_ASIO_PLACEHOLDERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_BIND)
# include <boost/bind/arg.hpp>
#endif // defined(BOOST_ASIO_HAS_BOOST_BIND)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace placeholders {

#if defined(GENERATING_DOCUMENTATION)

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the error argument of a handler for any of the asynchronous functions.
unspecified error;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the bytes_transferred argument of a handler for asynchronous functions such
/// as boost::asio::basic_stream_socket::async_write_some or
/// boost::asio::async_write.
unspecified bytes_transferred;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the iterator argument of a handler for asynchronous functions such as
/// boost::asio::async_connect.
unspecified iterator;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the results argument of a handler for asynchronous functions such as
/// boost::asio::basic_resolver::async_resolve.
unspecified results;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the results argument of a handler for asynchronous functions such as
/// boost::asio::async_connect.
unspecified endpoint;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the signal_number argument of a handler for asynchronous functions such as
/// boost::asio::signal_set::async_wait.
unspecified signal_number;

#elif defined(BOOST_ASIO_HAS_BOOST_BIND)
# if defined(__BORLANDC__) || defined(__GNUC__)

inline boost::arg<1> error()
{
  return boost::arg<1>();
}

inline boost::arg<2> bytes_transferred()
{
  return boost::arg<2>();
}

inline boost::arg<2> iterator()
{
  return boost::arg<2>();
}

inline boost::arg<2> results()
{
  return boost::arg<2>();
}

inline boost::arg<2> endpoint()
{
  return boost::arg<2>();
}

inline boost::arg<2> signal_number()
{
  return boost::arg<2>();
}

# else

namespace detail
{
  template <int Number>
  struct placeholder
  {
    static boost::arg<Number>& get()
    {
      static boost::arg<Number> result;
      return result;
    }
  };
}

#  if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC < 1400)

static boost::arg<1>& error
  = boost::asio::placeholders::detail::placeholder<1>::get();
static boost::arg<2>& bytes_transferred
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& iterator
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& results
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& endpoint
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& signal_number
  = boost::asio::placeholders::detail::placeholder<2>::get();

#  else

namespace
{
  boost::arg<1>& error
    = boost::asio::placeholders::detail::placeholder<1>::get();
  boost::arg<2>& bytes_transferred
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& iterator
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& results
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& endpoint
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& signal_number
    = boost::asio::placeholders::detail::placeholder<2>::get();
} // namespace

#  endif
# endif
#endif

} // namespace placeholders
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_PLACEHOLDERS_HPP

/* placeholders.hpp
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
*/