//
// detail/signal_op.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SIGNAL_OP_HPP
#define BOOST_ASIO_DETAIL_SIGNAL_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class signal_op
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

  // The signal number to be passed to the completion handler.
  int signal_number_;

protected:
  signal_op(func_type func)
    : operation(func),
      signal_number_(0)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SIGNAL_OP_HPP

/* signal_op.hpp
/4J65gjZYnkWciNkKP2bnZqkOQ3lyua0KKn+zaOCk1apNVwtoPt8MiutLZ09Q+jcI8EBgSRWqYq8z/8VXkLVp9P7KcTojlwJsSx+kcCfn7NS1/5MMyo7c2Obb0pDDzfTmXuYUrX08jpzoarkjTDF1kxnLjQStLFLUksXmsWWLu4zHHj1+PSMmM9wSfTvJHLrUMfObOAtQy/4nGmxTaU62Bt7efiLe+Wp6z5wPQ5+90EP8aluQqzsK0TfAfJQ7zE=
*/