//
// detail/winrt_async_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_ASYNC_OP_HPP
#define BOOST_ASIO_DETAIL_WINRT_ASYNC_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename TResult>
class winrt_async_op
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

  // The result of the operation, to be passed to the completion handler.
  TResult result_;

protected:
  winrt_async_op(func_type complete_func)
    : operation(complete_func),
      result_()
  {
  }
};

template <>
class winrt_async_op<void>
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

protected:
  winrt_async_op(func_type complete_func)
    : operation(complete_func)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WINRT_ASYNC_OP_HPP

/* winrt_async_op.hpp
b4S+X0eN6h1bZ8XZT9Tgd3vpWXH8xFS/57cB6vj8GtAIlqTqLkW9mhiZpB0jGMH0anopHC+yjGr0dgpHsC70bP0P+QgWjl7/wsrgQPyvrOT/n1jhM/Kf8RHDSByZEYzEjtmP4Aex60V9M7Zv841BA5pRjfZD6vsxRRU1xJS+gb1sZQyrsbNEzKEJ+lhfXfFORKEIGh+9LVSwJJ2p1Eu6bf8wDIro/N3hBjugKOXS+R3TO1lFOOBRfdHIN+sjxY5gzFTNs1dFrFKyEAx+edTgJy0Y/KQEgx8So28W0jeUy14aJUapHSRHJtWj4XP7NqpkcUw4uApnLV7uUsrYcAzZjQ4LqfM5GFSvoL1b0avGQry9Z4lSrytiHRSFauk2R9iIatx+ZNGzJ1GfZjBC9hoaE9C0VIrRYVQTrT646UNsW4oQjXfirnA3xyajW2iYpEZFZOglf/wfh8WMQXKAT87/NC4mjoxBLRsjOEACzWNPZNsvQ7RJWQnb6n8aK31Ehfu5h9U86R4Y8JGkDtNqkLaijVazNR9BR67Sab47ZvlUcSuacSMKkWejkFYaPdmKZpc524rmEYtuuiMp3baixdeKoruYiAFkEavGamC/xDAW9R0bmjelm600U77VTvnMCltpm4qsaAb53uW9XnXYLyr7aGnDTAOqPqNcK5r61CuZK/hVdbbSTHpQFlSTaRe6WtD1FYVnoPC2Vtq2fpRT
*/