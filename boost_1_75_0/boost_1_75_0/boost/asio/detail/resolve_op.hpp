//
// detail/resolve_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVE_OP_HPP
#define BOOST_ASIO_DETAIL_RESOLVE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class resolve_op : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

protected:
  resolve_op(func_type complete_func)
    : operation(complete_func)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_RESOLVE_OP_HPP

/* resolve_op.hpp
ysp0jphDtw0aZPYamYTvl5axh1Q4GWXfCsRGQNYikFZgqwDIjQRkLbtWA7KWgLDLiojJqoPhJU6JaEuOUY6QM7rk2sQ0g/SAEbbDxCxjYoTmzoRZP+RUc66lPU8uM8mpRumoIr/ryulyrWvhijwgyPJHKAm9h12e8QSqFlOs/vt/JAOPHp9yBDg6oJywA9tY2yHVQDActhMQiwpgGsk+2CWAf8XSZig9IlC6QSt9kXuu0YajsT4CN/YUa5xjMFD2RPk9aAfIwzlds1IKW1ffinN5XYunDAa5fW5cpGNee3qc3jFLbvCmQTcSm1IK/WuubJ8Tl+oYClCjoQwqteq9E+Q58UjvDds2psZN1AsvV1MGm8YJ9V4jFI8U/2oJZEXJoo9lA0JkmwkwYgR5MMeIiZDkQrNseBEtaMaUN8VL3LPUXugPkVccbRemOSm+Ve+rwOD36lakeIYX21PjDA5GL14YePHIQXWTGQSvY+EGL8gOXd5aGpgEbWDkUnVU8izKi3rXOhgY5lrnByqB2iEYpMzWqhzBlXlG/hgH6RrUMFz9az5ILfdPk4fyQQqi3abW6xiJfXdEuqBlcww40IWtKHsM5eM0OvDCePUFwbkDt5I5fKzQZ4LGiicJ2ZgjyG8mZramZLYID2+CG5UnRBGkW+h6qmxtxZgbh3njHEB/e9OY6vbGSxqh1bLD/4LeexmctBGqkjPiNtbwQjWe
*/