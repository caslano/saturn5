//
// detail/winrt_async_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_ASYNC_OP_HPP
#define BOOST_ASIO_DETAIL_WINRT_ASYNC_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename TResult>
class winrt_async_op
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

  // The result of the operation, to be passed to the completion handler.
  TResult result_;

protected:
  winrt_async_op(func_type complete_func)
    : operation(complete_func),
      result_()
  {
  }
};

template <>
class winrt_async_op<void>
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

protected:
  winrt_async_op(func_type complete_func)
    : operation(complete_func)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WINRT_ASYNC_OP_HPP

/* winrt_async_op.hpp
/v0opxl6ikGRj997zCaGtgY3piOyeUj6/cX6NiaSrgdPLF/ND/RDDbNv6znsNlt4wTPgq+tsaBH+9854DhIh4d8RWcxjihJd9FznGfPQNNjUcFvdfqo+mrUV1LFzDeLZlGVpdug9Zwr/TgR4QEcHcm94+WlkhGZMFFrYbjfAyEwxgHbbvdJ2PQYx1rmYmtyjE0/f13D3ebm8gVW1qAB+jV5o8O/QdbENsEcYUjySgsL+rMqDTVZUxEiHPZy0E4q6gBlWrcoUf5ar1eK+fixXy0Ux18quUwWd6VEwATHYoyWvWAgqGoSc9f5sKIAKQhEHDMwe+Nl50ucP/MyoNlMBo5AnIeTKaDpv5nU4nvQHfutg9j7EEyaFvabW2xfMoZQuhoBONBe+YOOrdaKr897pjJPkNeaL3/x2AblR8EhTfBQk2cDqSutw5ZwoTdATCtlpjXL+PKiEmo5DrmT7jCqVZRs8WA39esX8p4L9SFpR/QjXIE7kvV7BUBui+qrMP1BLAwQKAAAACAAtZ0pSIS7OP3YAAACJAAAAKgAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2RhdGEtYXNjaWkuZFVUBQABtkgkYCWMUQqDMBBE//cUc4HtAUIpiD8KhQrmAotaTQlu
*/