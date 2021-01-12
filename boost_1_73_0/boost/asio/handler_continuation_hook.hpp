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
pBBCTxnZSke6H1dWMAlnwDIkeochrW02WCf5hV8E7aKS/0f+xd9Kiv+fe2lJP36JhGxNQ/l/RT0JGw3WN/D7O95P4zcK70/g9yx+jfj9HL9a/Nrxexi/PKTRpXzxP31KikG8GU0pCYkpSWbtX1zCESkpyfx3+H8j8bPgF00xauuiFoO1Cb8lgP8Mfql4/xGeDjyvxO9m/G7F9378/PgtxW8bfm/h9yPE6SS9FP1noD/G6Lcp
*/