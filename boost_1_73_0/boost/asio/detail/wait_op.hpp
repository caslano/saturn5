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
MVF8vnv5Tpa5AhOm7+AMqvvpveGK87w8j0oyhtbCuZiA12A+jaHGbttVIlkuyvF9hb6BMWLf40qDyY4ixbRCS1xdn6Hy06HQGHqT2CMObwKI0UXEqiphXiCiB2rtd1sb1yHmoNvXW+hhbdTla7/Rauul1Qjh1T0LlIITSwNIomQvLz8lBdttXetVI7AAXQuTTCr6fpJZxbPdy2uSWMWzvPq8CEbGgajV/5Bv5oII4hCFjfQu
*/