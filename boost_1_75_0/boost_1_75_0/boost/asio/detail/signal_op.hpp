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
YUcmDPKcFiROZ3PawXSnBWQS6ifyzQJdwjp1G2174CEQKFzoSyiDFY7AUN122Z+RVSSgsfYZbWSi6RkI3VPJQwWIy8C7MrBxPJY4BkKHAMuX/cAbGFtQx0FFoQUkZaGFnNqOvSA7W8jkzA4N3de1s/72TxTf893sIBu6wTmK/sok6oYMhexfvdyhulQEAaaTakSAPca/Cgj440s/xB7ryykd/HWJzh7vRvY4Bdjj0glh7PE5lu7RJTp7HGPCVdmrjD0OMTH2eCWMPX77k9njB5Q9BqQfYI99l/TOHh9h7PHZ67HH316XPY78889jj6nShknShmRpwzjKKpOw1Ik/zB/xmgHZueMp4AGSJ6EVLx0CBgssrXX6z2KXs3+cXfaj7NLCAAwsupZjftArh3n1p3CyL/Z0MA6TLHnGUaYZS5lmPxlCgO1kj5Oyk7Q6w7nn/F7rdPyUOtdqdSZKniTKQGMpA2V1ptI6J2l1hnPSf17trc6Gn8JJr7yq1pkqeSbBciynxuR8f8BR7L15Cb2w1Y1hbNXyGGWrGx6mw2RZvs5Wt9zK2OoNf9DZ6nX56hd/jbbDsN3/dxi2bS/+0LC1sXo6FurDFn3teVNh2P4xJWzYfr2JpvtooT5sB+Kw3fpnNmyj1WH7r7Bh+9lPHrav0WE76dEfGLbuhb0P24fYsP3l9YbtjusO29V//HnDNjRg2dDTxZuHfo54M/Nn
*/