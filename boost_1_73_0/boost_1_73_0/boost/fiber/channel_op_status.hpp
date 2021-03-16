//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_CHANNEL_OP_STATUS_H
#define BOOST_FIBERS_CHANNEL_OP_STATUS_H

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

enum class channel_op_status {
    success = 0,
    empty,
    full,
    closed,
    timeout
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_CHANNEL_OP_STATUS_H

/* channel_op_status.hpp
NQe66DaJPZ7RnmVc0/l86tnkU6HWhNUdrw5WdciRVtgvMz5FpFBECi1SAXNsqHRWZxqIsi8tisniTmmRHs/Sp4dY+tBElr4m5XzS2cRTHVs7rEarGkWhhBRKSOE+sSdKSV0CUy0CxAvSXogskPW1i/Zupl5pQ9fKMT1IXdTsrlzpaLp7dV24nP9RnFF3mJIH0bQfE3vZ2fPgL8ZDmfqT2/pAeywbmC6eTBkrGqWxNBIHvGbNYjwNw62xLB9/LJY=
*/