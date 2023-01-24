//
// detail/reactor_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTOR_OP_HPP
#define BOOST_ASIO_DETAIL_REACTOR_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class reactor_op
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

  // The number of bytes transferred, to be passed to the completion handler.
  std::size_t bytes_transferred_;

  // Status returned by perform function. May be used to decide whether it is
  // worth performing more operations on the descriptor immediately.
  enum status { not_done, done, done_and_exhausted };

  // Perform the operation. Returns true if it is finished.
  status perform()
  {
    return perform_func_(this);
  }

protected:
  typedef status (*perform_func_type)(reactor_op*);

  reactor_op(perform_func_type perform_func, func_type complete_func)
    : operation(complete_func),
      bytes_transferred_(0),
      perform_func_(perform_func)
  {
  }

private:
  perform_func_type perform_func_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTOR_OP_HPP

/* reactor_op.hpp
Ox/IClD6FP3q9Ixsd76euOCT4hS3CUXoxxqs8WSUXRfvssbLMVJtUrErTg/0Z457Xs+PHR/D227DtfqYydOWLPJGuKZxbhqwmCtPQ1DSTP39E4B5NMp1j9kHLfJ1yk3udIARLdXDLHKeLI+CEms+XSQPc02TvowQ9g8tliPgMTKsX0YAz5ry7qovlmhQzVKyTrwYuHH8LkCesP/6YkxYIUcjb+uaLkVHKLEOzxKNo08Ky7ePpChznMvaiJn9rc3QBdJdu6xNcp2lPc+V844r81RivTgiQzTKr9yG2B0qv5KP52j5lVtwab6CoSF6oXIyXngjfCfHnjywAtMfRabH5Ra7rGeK5XRzcSr8+hJ+meD8DZyNcG6FswHO7dQ7q99SnZsH53Nu6xmb7y+5ygtLEeRnejGGtaPSL4q9spnWocvKcCliEJjbYEVr6w2k6BnD7H+CfbnV5TiNKQh+CQ8aoknbM8rGbCJt2fRMXN8QTQqfeiO/Xqk4GFSbmwfb/inYP/dg1TDiMWwtr3km6joboe6b5B7nifIJcmGT7GiWUnT3j5RhdGKKXXrAtNQQoQy+yXli/eey43Qu++ow7OMw99zLDy/RdD4//g3qfIT916Hc+BmAARjiSWn5aQw0/xhESKkuIk3YH5lSK7a5ChkWOFckbB5HpBbj/u2Xo9dk5aM4Vc+liSOkc7BFSecyxfHSuWWCsxoKlpTdFWvO
*/