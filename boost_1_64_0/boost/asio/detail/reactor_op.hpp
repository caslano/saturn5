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
2B6EEHPxgVE+lLVwS2X7gZsF5YAB3KGzwvdoZjzGbHpvgedno4Bf24Gqpu85cm8XShhUJvRweDqa9JnpUsuqds2eD4eYAHNVD+U3ksxx3ItjFAxniT18g354DRxvvXTYhfRFK0yQ/ZbOm9XUXUkMv0X04Hg9bH33+YY28zzrlQ84F8HZme8VIUFvrPzC517dYQzxCvIIINsAPBoKIBIH4+XSiDIKAd/ApIoami/sf0G0FI5KXhiLSsTT9xDR4Gk3mzTZSYhEB7U19sJOZuLUyeTNLlnNEkRTpIA4CRPq1Irjo1LVm8XopZWGB5yV+QUrTOnfMEI25HX9mge68rRtwqMWI/7y0xSoHA76sRRZ92UYwZXpQ/uBKcB2UkLJ7plZm6zJyD+Fc6YoU1ri2PuF5siYeULQcjSKfBeoRCn66MNGiGtpmxXIjTWABJ2uu8EqLAJRvmdoEbz8Rpyr2LoJ5RIgmmsrOzed/UNMawBdl4ztzrdZbue17lIr1hJxQWb76Fz0NdqovGeOu48ymFq5YvxwTdkgNs4KWtgq6OieP7IzJj8CvSK5F3JMFw==
*/