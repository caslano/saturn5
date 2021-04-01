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
RySjUxP2NVTQxt6k/vYqmEC4Jn3TmPoMLfFcmemuxpuBx2RaetwUBbKiLvf689M4uGC98pq1IZskZpIg+TrEELs1bHENjisKWnMyFRFKjhpyS3WhsCXUi2xklqGenQN9f2mDeeUqTvYlbcJdIk1ICeQt0rL1y8N3SNarJ+Hj5fsT7t7MVcUDBmKwOwyn+HyqXGSWWbvSLB2g28xcwDfr8DkbzPCUbkB71YpIEngqdHOu5JBo1/dJRXxnkxue6/qSj2sxrnoq4cn+MohQGVdTxylP+sjbZvoq9dHaEr7B+dDpQOFZsqC8XV6yQuNXu9fAO/NvDOeeV729rz+TA+bQECh6GeWscV+OeLMejATK2CMZDeX1S3VAFiMHfnW7NQh7KeKHs3h5XYVfFRX6/d5vF/qhN4UNLeADLOKCWT6fLUq1E4Pm9AMcptNWztGypzSatXQI7zsTXXpSrUelfqY3ZcbMOsD6R+fFHDj1RTPN/jij38pUb4aUihS6oy4uc7uSzuk/ePVCEWUPJ2iIm9m/4z8kV1UKObAXYSwUKEQ9i5JdY+2ptMk5pRJwLg==
*/