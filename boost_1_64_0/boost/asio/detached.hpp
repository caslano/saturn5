//
// detached.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETACHED_HPP
#define BOOST_ASIO_DETACHED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <memory>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Class used to specify that an asynchronous operation is detached.
/**

 * The detached_t class is used to indicate that an asynchronous operation is
 * detached. That is, there is no completion handler waiting for the
 * operation's result. A detached_t object may be passed as a handler to an
 * asynchronous operation, typically using the special value
 * @c boost::asio::detached. For example:

 * @code my_socket.async_send(my_buffer, boost::asio::detached);
 * @endcode
 */
class detached_t
{
public:
  /// Constructor. 
  BOOST_ASIO_CONSTEXPR detached_t()
  {
  }
};

/// A special value, similar to std::nothrow.
/**
 * See the documentation for boost::asio::detached_t for a usage example.
 */
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr detached_t detached;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) detached_t detached;
#endif

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/detached.hpp>

#endif // BOOST_ASIO_DETACHED_HPP

/* detached.hpp
1O7KdJJvXELeWqXl2sMNQsZ1jSpFcMhSx24uSIiEFq0z95nu0fkNEJGISq9kq76jWaftFSiDxDTbJIu1Nt1dDtOBA2FerarU2v54qV1qoZZi2CMo7VlexruIquR8R6EXrDhsjXvNwDSxn0kW11WjhbqMDdVutv2SUiAr4RDo+E9Y2c4VVYZJhX3OY5sFrvjLG/uSaiH0KS+g0cBGx/shUhGtCGFDVuOYb+V7orAw7TPb9q0w9Sg27TP767Ad65aF/1qppb5azfGUtn8pP2JtYAuEcPkF8yXXR9ruYw1d2Ti88yNXTf3JY/9pJ1tC2bt2k6p3RvxSG61GmB0/YEgX0QicM8E8XbA7kxnI69DcxO0yoidPydlEnn1NJ2+PQ/FjRxAurhDf+ghGT4jb0yulkltCdfjEiobpMLXbGbCSHvS4FQUawWnAf+8ApOk2NsN0XGIZG8y6KnU524KttQQT30ge/IYmI757MFgYex0gFXV0Jkvrh8C2HhPP9THy29AvvYOo70uwZp7r0KtsyYrWOSZpytP34AkSkswyTcSfrawN6csXT9BDis0i0w==
*/