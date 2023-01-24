//
// ssl/detail/read_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_READ_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_READ_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/ssl/detail/engine.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

template <typename MutableBufferSequence>
class read_op
{
public:
  read_op(const MutableBufferSequence& buffers)
    : buffers_(buffers)
  {
  }

  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    boost::asio::mutable_buffer buffer =
      boost::asio::detail::buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence>::first(buffers_);

    return eng.read(buffer, ec, bytes_transferred);
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t& bytes_transferred) const
  {
    handler(ec, bytes_transferred);
  }

private:
  MutableBufferSequence buffers_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_READ_OP_HPP

/* read_op.hpp
Tk5xSM9LpLhD7kJPM/xtlMZp7BBcuCQ3DcdBoXk5Obo0dwOHO+q3dAsx5zvqtZqfKXF/CMX5/JEkQRsy9ldwR6SmsXkFbg7GMK58aSHxnVFxR+MhF0xtkudU1zhwc3cO0mWMV/Do3Gxt0JigoOYD0OTgpCnamZDKLBfe1zwjmHLxfVNqVglupQc1GwT33e//3y/yTRWTBJAJsBSgDOBNgE8AjgGcA7ABeL2lYroBDATQAkQDzALIBSgCeAHgfYADAJcBvDarGF+AfgAjAUIA4gDSAZYBlAGsB9gKUA5wCqAOgHkb0gEMAJgKMBegAGApgBFgPcA2gKMAdQC3ADTvqBh/gDEA0wEyAZ4EeA7gTYBtAFUAlwBsAF7vqhg/gKEAEwGmA8wByAF4EuA5gNcAPgI4CvADwDUA1RYV8wDAKIBpALMAsgEWA6wB2AKwB+AMwGUAr/dUzH0AwwEmAswEyAZYBrAO4H2AwwB1ALcBOr4P8QFGAsQB5AI8DfAawA6AYwCXAG4AeH2gYnoA9AMYCxAJMAeABVgN8D7AfoAzADYA1VYoL0AIwEyAHIClAKsBXgHYDLANoBzgKEA1QB3ANQDFh8BjgAEAYwEiAGIAcgCWAawGeAXgfYBdACcA6gDkH6mYzgD+ACMBQgBiADIAlgKsBvgnwDsAhwEuAPwGoPgYZA1gAMBYgOkAswByAIoA1gN8BnAA4BTAJYB6
*/