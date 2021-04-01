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
0d3b6W7jp2wo4tUYPpKjrS+95g1xMsxReoZJMqwmHFrJ3BfC7shNzP13JHbxnoyVFTHaxs+pu6Svsv0S4Ly5LwSVZbjtXcyM3DLSH1EFO9bvtSvels2Am+AdBg5CADTFPM/pr/8zFCbck2UId0aZt7pvrHyvBl+6TF4R64Ycv5PcndixefMIzLlWFwITyPWVtVs8ivj4YUb3WVQ7+vR3ASrH7HSqyQZs8iATmlEwigoMSKIQHSKiqmY207hFBJ9y6vJA5w2parMFJeUrprt/hjf26euuPomoSTvFmyOTnXIEixfC8FuQLF3pZYRS8D4kfsesCCCHrGEGNHMj1Pe45wHtC8QNu01mkLGplNQCO2nRBGYwL+CSfxihRfkBYD8Z29rR8BbYkKyGIbx+UhtoFEyO1AS47wt7J5hPoaa0sCDTa2QvRMH8BTxGPTOyGMtlOZprB0BPqsxepMieF/1I4AD8XfHsUwf8KWgKkM3ugGqZAeaP+VgCVVFJclFCSGji1Kw3mNqqKHuZ74qVX7SpQkBMm9TDVWats0Pcmcxdl158m9JxhNBOjN+ZGw==
*/