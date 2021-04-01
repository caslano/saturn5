//
// detail/handler_cont_helpers.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP
#define BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/handler_continuation_hook.hpp>

#include <boost/asio/detail/push_options.hpp>

// Calls to asio_handler_is_continuation must be made from a namespace that
// does not contain overloads of this function. This namespace is defined here
// for that purpose.
namespace boost_asio_handler_cont_helpers {

template <typename Context>
inline bool is_continuation(Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  return false;
#else
  using boost::asio::asio_handler_is_continuation;
  return asio_handler_is_continuation(
      boost::asio::detail::addressof(context));
#endif
}

} // namespace boost_asio_handler_cont_helpers

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP

/* handler_cont_helpers.hpp
VLt5S/dup9HGZySjbaEnqGT8vLXZMBq1o5ulGpnppoDX4kFwQ85H8wSp8TbA6WXemxw0koOOIjJqJBOp4dr+jr2OOoyKjdOXr5UznCcLk+yj49CLumxJY1SG38e1GlGl70iT5SwPWYD2lrmq+Z9IpHeiETnJ2KrtlkfZMX+E/wdjH2hex3KO7htd5rHaLj1BPiY1T/ITAUaxNr3viLvs/Oa6QLRv5XBCEOvi64hcih6jlGQS3GX1nTFUN9Ny39mSZFRKYNXLkCTw6MSLi+1jyfZnBUwX5d7AndhV+lYSnLCdYYIZlHQ3vWvgYnyo8nJRGSbtqzwPgcF7SMPKkDgfDU6TrPZYgkpRvD4GQUz78T2V2wlRxogV8YDw+13xBWtFbwTgqtcMo5WVnW2BcYy2cxL3R4A6kEKgd+CTcSV5z1w9+Wr6OusesG1GFnAdgmuLCJ9jbA3ts6gqcS9KIRNQl4GwrmhLVjiQSHrCJPzpgIvUets12pnaOMILlVD+i9gL48uuRfLw2V3DGg03OM0xztNeZgg//e8dZcJJgxLJARzEjarFF1NT8F8TXA==
*/