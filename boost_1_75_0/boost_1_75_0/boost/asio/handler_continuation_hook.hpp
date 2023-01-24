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
2lNN5PlSfYmNbwY6a7ajtCPuhCvKzmv/GlqD0pCheCxQo8PQjkJzs+YNbdbk6IMhvRSeTdPYDgpTu4OUwkU2is2blWOvHmE8ZALIV0ayw0NlV2PZPZFltydHt5uC9v+sXMG87SAd9ZM43q791bPYm7hJStgztEcOJ/78/Vn7ncdcBzfEXuxhB4MjZ7XqhcbFc7otepWA/4w+Bwfdj7MRyXMD+qn/MBttw12qvCEaGl4ZMtu2Nd+Pi+MjjzDbPtMROxvGEfHyBpjHxgoRgDOrJrk6RS9LZ92Gk0/8S5+RV6avynDVJ284S4BKvJhL8NSodvCBP5NkW2ij+zjdkxpy7N7rEfpkcX8PDEyFsSYtrOxyHkJorIILWQy1MSYc2DGftqK7FEhr9H5nj0aw7Vnrpepvo75rgJ1gC9NZrYzBbWLYFtw5iKp+Iz696ILn4aesOgUo1f6i0CUkLiw4yz5iaq8HUWhVtAhwbZQ2vMrKOQK8rOjOIQAGRK50iQY9Uk23NsbGTD4ReyjUssYIwkH1oUCoLchgvgzmydQWZLIcydVdgfEPMkNamAyQVcsjNsjmGoqJlQa8hp6TCQIi3tQc+oDUxjFZK5cqNo/rYl0MiI3BPws/vPAJUiKMYzE6ZW+0OoUsYmvFqTCm2FBThHXI44uI05/jPMkuZVXU1M/SPZlonLBO1BGR0r8obJNaU/sJmiaQHUK5sEpFYwSK
*/