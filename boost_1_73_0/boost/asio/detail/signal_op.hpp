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
5E6AXJaeILCyLyb25qnS862kut2nxtXwyr6Q8XAc9C/joWeegA/NKeLBlmfS+gvZ2W/Ic2m9Gndq8HCae+Uwqxym9d9s8zBjObMjub8Ug5eApP4CbP0F2PsLcPQXkNxfQEp/Ac7+AlL7C0jrLyC9zwAKYZRvv5i90tNfyExPAtL7Tp/j3/A4Avg4lmXjUV4sxP45cIebNw7qThsdoR3WK9wr146QRenopbIovQ9NeWJuxYl6
*/