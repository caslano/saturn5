//
// ssl/detail/handshake_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/ssl/detail/engine.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

class handshake_op
{
public:
  handshake_op(stream_base::handshake_type type)
    : type_(type)
  {
  }

  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    bytes_transferred = 0;
    return eng.handshake(type_, ec);
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t&) const
  {
    handler(ec);
  }

private:
  stream_base::handshake_type type_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP

/* handshake_op.hpp
FAmcEWmlEgaS/5RLFoVTxYxZis+f/tTb+3TEP3DS3TPUgEkHbXcnLhfJFvgBkzbMe20u9jpveXMnpse+gn+o//kG3kyT+yKFfgyOMqtwXlkgu+m6GyN7rqVl7Tq/B2ccF2V3I6Ksn22MwB4negiDUs6jRMz+GmLF2cBNC9EhItMmpJSU4Q415i0XUejFjdHZnGq/c+hsy2XL3zN7pJbhn3IbKXqVnAsILsxgP3Gpv8SQOZisr8BUyYK93uInnpvE8j8WoiQK8+McgIc7OkSclDzVlgOdmY+4tppC3bHRmRdhzMjIwow5vJPPGjIu7YHHbFqdOuAFyCBFJhL+yG2/a2FUvcib4bcndNaY0eM0INeGsMHOxkHA+eSWbxzmMjqmsJ0ex8xmVCkNzw+jt0sSV0zhOkG42rMH45nMBeRGKbPU6bsiZqOjV65UQbtLWBdaa9RuODGnuhu/dStwMtCBq62z09OH4AJYgVgu/NCpeevDZZGdL9HGbF4/QcBh1u4/s68m7afmDxn8OhLz2ybjLsS0wq6dQhCDbBTk8wgfD1FNj6HcYrBZqzK52g==
*/