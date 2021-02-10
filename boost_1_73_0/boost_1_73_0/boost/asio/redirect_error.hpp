//
// redirect_error.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_REDIRECT_ERROR_HPP
#define BOOST_ASIO_REDIRECT_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Completion token type used to specify that an error produced by an
/// asynchronous operation is captured to an error_code variable.
/**
 * The redirect_error_t class is used to indicate that any error_code produced
 * by an asynchronous operation is captured to a specified variable.
 */
template <typename CompletionToken>
class redirect_error_t
{
public:
  /// Constructor. 
  template <typename T>
  redirect_error_t(BOOST_ASIO_MOVE_ARG(T) completion_token,
      boost::system::error_code& ec)
    : token_(BOOST_ASIO_MOVE_CAST(T)(completion_token)),
      ec_(ec)
  {
  }

//private:
  CompletionToken token_;
  boost::system::error_code& ec_;
};

/// Create a completion token to capture error_code values to a variable.
template <typename CompletionToken>
inline redirect_error_t<typename decay<CompletionToken>::type> redirect_error(
    BOOST_ASIO_MOVE_ARG(CompletionToken) completion_token,
    boost::system::error_code& ec)
{
  return redirect_error_t<typename decay<CompletionToken>::type>(
      BOOST_ASIO_MOVE_CAST(CompletionToken)(completion_token), ec);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/redirect_error.hpp>

#endif // BOOST_ASIO_REDIRECT_ERROR_HPP

/* redirect_error.hpp
WuZuiyEVDG4liWdo4zPa6ME5EgXUAKQlH9jStMg0xlEg3TG8iS0tibyRIR5g0D0ag1AYkknVRZy0K0EJIZT2Y0ftBh84yT3QKlngECdD1hQlhIHLLdr3ViqKKS/gPUoU4IdyYEJGszpkRZKLPDijy7fvrkdhmyRltm6qtRRqScyFVXbd1wGyZaxtX1yqwi3qAGZ2kMb5EYl+jEFtzMOBWVAv23TlbjEYDnWPGKkKUSw7VE5rzLFcAqOg1YKj6fQ1UlI8pkcExMI3XP2KWeCMmWgoJrcVKMnVahLz3UrMgEBu4F7oAdD+t+WCLqO7lKoRW5gTCsQKRZF9gM5hW0PQtO5peKx0lHsuZ6RTh0WbEw6JcIbCbGxeZLPB4dYk6OPfO43hlyeD4RdPB8eD4TGoByYRTUugsTVM55v74xHNe6N7cGEL+aga37EVONRHE1Ko3XSNcC2YfLM4Ph0+XCN3yxDXfmhLGWIpD37e1p27kmCiEFfKRDt116+uQj1J0UxwxAjb/NRqcExFnlE6mozXWd6o3UIqcE5ZKjM6q0lNwAsS8qvM30o9tWlIMAhZ3UkrTPMsA1vZHQAaF3yXCKjI9GjDM6ZHc1AdQsvrxKVbhcFw/H2cz4wu6ySuuobw7mza+VgEYY7Gmlbp3Tid
*/