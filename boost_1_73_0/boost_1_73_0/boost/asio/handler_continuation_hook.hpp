//
// handler_continuation_hook.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_HANDLER_CONTINUATION_HOOK_HPP
#define BOOST_ASIO_HANDLER_CONTINUATION_HOOK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Default continuation function for handlers.
/**
 * Asynchronous operations may represent a continuation of the asynchronous
 * control flow associated with the current handler. The implementation can use
 * this knowledge to optimise scheduling of the handler.
 *
 * Implement asio_handler_is_continuation for your own handlers to indicate
 * when a handler represents a continuation.
 *
 * The default implementation of the continuation hook returns <tt>false</tt>.
 *
 * @par Example
 * @code
 * class my_handler;
 *
 * bool asio_handler_is_continuation(my_handler* context)
 * {
 *   return true;
 * }
 * @endcode
 */
inline bool asio_handler_is_continuation(...)
{
  return false;
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_HANDLER_CONTINUATION_HOOK_HPP

/* handler_continuation_hook.hpp
iRhntc3eTzEWvnz/7lWP/qBXd1meJ7M0yw87q3r70DqyYuo/8Epj8shEIloSjbEU0NFfWWUzxaTqrXEwwCL98IHIS9Q53qAFnk51/3RU2tH3fHguFZVrPPsEFC5JrkuQLZ2PnDEM+l+CNz1a/yRfT3WCLTCI39zsIOkRyn27TCeLrPADwchT8Lmj2TrPj1ZpszhqSsY5psEC7U0XCMDmWZ7OeaQukkej6LgfOZau+ipJLnib/76uG+7fzWga9KbnxuvGbco1oRRx/rwuiQUQotBBsEliz8A0rq5e9Q3Jk3IFJllzNxNfNXhIBKR2tOGDJHmDvQTWK4RHmARNe+RSEBtivh8wHax6DyJPNsmaPWY+9H7q60mVjQMuJnVDc0hpG93dwkQXEgPKJeH0lJrt+Q9xF9TxtCy8G290dHCWoyNeCLobBQY2crKOgUAKLMgdgfgSmgD1cTCyZZanFQDSAdeEiJKx0hFTVuusA7skZjb0Ap9kRd14IjaQXJxR24FrYYY+4++wNVlT+3yWjPFGKT8W2HYgn9KM10Xl8xTvm1JpxJzJs7ajYQEFPXD1hiaz/EqOemjToQgCRF0omrRgu96saN/zfNMTXAWtADMirGzkhfMfmiqd6KLWY9onXhMT9q2FJkLcAGKa8CSt
*/