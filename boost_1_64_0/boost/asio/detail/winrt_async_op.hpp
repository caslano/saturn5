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
53kc/wUc/3PBg2ABeJi1lj9jreVT4FLWTC4Cg8GFYAq4CJwB5oELwXzWCl8MloHF4EXgBeB14DLWQl4O1oArRHzAC0U8WHP5IGshHwYrwS/By8ETrI18iv0qaxx3BUvBBLACHAWuBnPBNeAysErLZ0X7PoO4c7lrzWOP8Uca+BFgGN934VzfdQB7gdH8XBDB7XMkOBWM4vouWndfeBq5L27h++I2vi9u1YXLayTcjRxuK4e7CZRrTIzlcLTfXvs43U+7HD/tyqSdeQ0H5InU3q9muzs4XVJ7n7Xnw8HHQXGcfWAUb49l/xzwz6x1/xS3j0+z5v0z4FXgs+AW8AnwRuHn829QuH8PhJ/O31b37P4Ca5G/BHYC94PxvD2B/cvAOrAM/Cv4e/BV8D7wdfAZrndf5Xr3b1zvwimvge9x/SvOXyf7W6htoPhEUrq8f+/x2hHvgyngEXAi+AlYBP4dXAke5fz4grXRj4HXgV/yff8VeD9rMr/Ca1B8BIo1Iz4Hg8ATYGswRFwTMA0U4SaDx8HZ4ElwMXgK9IA/gL8EFdhfBbrALQGKf5rOCdAbhXPVWus767Wdc3Y06DvnsMbzPOwr2vHv0Xiu3PHz6TzbaDz/S/WdNyQ4/dJ4rt7RfJ3nXQizD86s92zWej64w3+95yM7/NN87lDboPucXmvWfr4V3JrgbJb28/hao/5zy7Sf82rN+s+s/QzdZ6n5zHrPYG2D5vPG2p9O97mm1lb72aT7vLf2v0v7ub62cf3nrB1eDejjtWYdaPfO5mlB70I5OgB3Cq57d6cyGa4Mbgvco3CH4JQe0MKHy4YrgNsAtxPuRbhjcKGJ0IWGmwW3HG4L3INwB+COwbl7oqzCjYcrgtsAtxvuAJyShGPDZSed1XM++/f/9/ez6f8tLq4orxACgGem/9cNGn954nvkLaT/V54r5E/oW0tuRf7i5YVIBtnkw6bsVmGzrPCi3FXl+UsL9VakBbgxTZFzYdCU0N8KHnO/GG4JjpGTSd8fizNWexf4HzlhVu7MWTMmTB3n/e63yTAOnOcdcrgV6DcbJOfErKZtAfz9ToQTmcLfq2WYLvLbYSn5p/D8dB6Dw3OXhU2OxXly5HmC6ftZtjbGKFoRqcKEw4bvb8vJbhL61AKlTsXcUGhWpTU9xj5C07DxHfMsx7MgfdhO6aNt2XI8D+JvGB8X5bQeN1Wf2fxxU/WZP924KS1+R502a/QPaP64IoRpfI3+Af/acUVaeS9gXb8nVdgyC4TuUj/vd/6MYv/KO6eLw0VJjaAk8t+t9sMdGK467TWZyK6zfi43l3PW7eFv2z3I7nfqQKQiUmXdABm+o0mPJ0rcy7SvUH1MCbe9B64jm9HqDUosb0PqadtuhLnBqOMjxyX8imxGqJs53BwZ7gGlvbKZ73E6H+6ABv2hdLL5jdob/9sgjNAfOSbWRAzQdIBmQsfL7fTcDiEghLPSAorgMAcDNC2gMrezrWLSA9LmPCzicc8LmHnMt+h309/JaXyzzb1eZDEXr0ze6+Ia/rzftZv7/bq531X/W9bcThgotu+9vaRXp1OXzv3NoG3HFmw8fnPzv2s3d6116+/d/z1rdFt/H7f/Dn5CziO1/5bN/ancVqNesuhP7cv9eP34e1d/XtsyExzN26eBA8FZvIZsLvsXG9aUrc/0rz9SGdC0Xb3CdSy3EUVwoho9wHbDON4juR9uFK/ZOpq/050HzuS1bMu4f/5icDx4Gfur2H81OBF8nf2HwVncDzcJ/J79quo9Xjj3r/cAxXnSwMngVHAqOAecBi4AZ4vzgnPB+8F5vObmfPApl7c/7uBH6HOBy+4j+nacTffPmfvkbNZb+98=
*/