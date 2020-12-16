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
GjCDfn9H0d/vNOCbQPHZDLwM+A7b/dfA9cDfAn39pIX5HbDpJ3sivO21F3g+8H7ghcBvA/OA+4DLgd8DrgR+H7ge2AS8n2HmwzWEqFubfL6K8gwC3kY/zbcDRwLvBJ4H3AWsBu4B1gLvAm5h+DqGT8k4xLVswOPMpz9wK/NJjvDa3VBgFjAFOAZ4DnACMBU4AzgMmAtMA14LTAdeBxwO/CowE3gPcARwL3AU8HFgNvAZ4Hjq3aBxTRfwTyzPAPYN/fgWx4d72a73AXOA91PvHwBnA5vYjg9Q/+8CbwLuo1/ph9hPvw88BHwE+BrwUeC7wMeAv2F6KBfGYq5/AlawHw3ie2n9WMJ+tJT9aBkwB3gZ7WAFcCPwcuA1wJXAm4CrgLuBVwDvAhYCvwdcA2wBlgBfAJYCXwOWAd8CVgDbyPd3oAeol6kaOBhYC5wALAd+DggSPSZqXGsCHMX67QHMpB4vg68f8BVgBvCYQa4xiNxzlPsx5Z6nXDPoKOUWSr2Z9y3FWCD2OxmYAjwXOA44DTgbeD7razpwG/AC4O3AC4F3A2cC9wFnAZ8EzmN9XQx8hfytwPnAD4ALWV+LgHqhFgMHAGcD5wPnqP7HOV3gPTb97zr6b/8Cr4PbeB28HrgB+GVeD29if7sReDPP38rzp+S6yXlE4NPMJxZYwXye4rj/Q2CW8Hj7H/qM9L9n6Vf9EDAXeBh4NRDXHKm352n3LwAbgT8DNgFfBrK/cc4KcTb9LTLC28960K57chzoRfvuTfuOpn0PAsqab+AOYAywARjLduvHca4/sAnoAj5Fuacpx3rhPAd0sqmXk6yX91kvf2S9fMB6aWO9/In1cor18iHr5SPgLcBPeJ0+C3wQCNtQ9p47y9neX6S9H6G9v8Ryp4E8lEvkuBEBSqDcMM3P1xAiX3OIfEcNfMcD+M4a+NpC5HPNDo1vYhC+YgOfO0Q+Twh8Zer9CK7DNtf9xzge/wA4Gvg4cDzwCWAB8ElgEfBZYCnwELAOeBD4TeBTtFOc574JfDfAe7bogH0TKhGdCKzidcjD+7KrgPkS9qfTFiSdMqZTznQ+x3TWA/MZXthTa3cvgiaQ0ZfXji748/pv2Ysg6TOh+f76d+1HsGN4j//IPQnOzOqefQl8vsV2QU/fvgQlwIL/sX0JDmyMCu9N0A17E2yfEaX2J9j1AMoNagVFfTdKywTlgcpAu0GHQSdBSftQz6Ay0E5QM+gY6Cwo80H4LwR5QA2gA6AToLOgtIeitLmgEtB2UCOoBdT6UNjXWvgIH+EjfISP8BE+wkf4CB//7uNf4v+vuKZyUjf4/9P9/9+Hl8GeW3tqkbqP/6XzlmCF8VWFtbVaBuJW4wVq0dcYN2vOnGVLZ825nAzIWnhemYL3QuSBc/8CWcFn4mE6t5Mnv2BWwbJ8I5uUY/NgpAMeliPfXVhctxnyqYibDvm0OwxxhvRHMr5B4uflI+X8/GXzlhbmz1t6yayFijODfNqdPr4585aitHNt0vIonvxLLl58yeKLhVcxqrRahc+8LT65xLdi5GhN+TlrjOQKM65zGwz6CHVXlC5rZowFKqnzaPI94n7IR2ibuVbGxztYrWX7iqv9/RL6c00U0sKals0m32s5PbyM57BMCaBXwddgKZOsKzSUqViVCbymdeLrQ9jDwVymYtN6qiaWKZoCvUEHULBca5nK0Rbch9p5nU8i2up5XV7aCt51iitE0FgPrihrPXyMtmmx5om1nJrStTIEXY3fhuyLstrAGb3/MB+L8YoleG3h1SlmW2jrgi0gLbEFY9nyelrr4M/gS8uwL5tYhCqbySYg03mb8Jat2LTerKWnvU1MdKg3NHDIdnE=
*/