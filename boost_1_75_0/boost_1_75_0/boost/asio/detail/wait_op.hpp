//
// detail/wait_op.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WAIT_OP_HPP
#define BOOST_ASIO_DETAIL_WAIT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class wait_op
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

protected:
  wait_op(func_type func)
    : operation(func)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WAIT_OP_HPP

/* wait_op.hpp
vUUuUnCPaos6AKP9XQcrzjVX+NdVW+ozTNC1rfOoM8hK9MBZ0aeOpwWi7k4uYIXqRXacHnoaioXZUPyiWawbg0cP2ram1fTxSwVtwhhMnGWU7zLLMcABbJxYb+pzQIjCK6mDATtgsAswGIiqzzJOhCj5aJaUg1eERdQbuIBNdp6QK9CGR+a2czCg7zLTMkCs3RAtTuVsj6Llr1gUi8Ytb+AFgVKOtUrZkguoXGAe6YwdeQx60vbewcrPMRv5+NOg4k3NLzb5bftqxGD6eqOpDq3r8yzVkbIz1vbKAcB/LJTlbzWLxJw1D4rD67iAvF+Gx0bPdcr9BZRbLAYt62/zpsISfPF2S8WlYry0MUuIqI6fFfhWLmhzOC/ysRiRLkRV1E2tjg9Ed/mrLQFTV4YCINuRtICPXX2JGpCYOmTnxQrgIEa5jWI9z6IhfB3AimD8bRIxQb3yAZD9Pq08h6QysiklJzi0aaNtq9lxoDS6PsuQItYbA33hZTy8dJwa0NRxWu6qj0x1NG3OfBMdvULKQ6WDXAty55Ouk0HFnFodmQV9k0ccHUIfSDV0a4R4qbA01uUthCSntSSQAKiSJRmGSWKgEG8MJNmvJoEUWcAf0moq/KnV/ZBAghV4QTgMizN4kBpHrurklOvpovHhdR1sv0mNDYv6lm47xKrnuKGvYnNBNIFVR8IsH653Ool8QvUPwdNrMGC4fXmiXXVz
*/