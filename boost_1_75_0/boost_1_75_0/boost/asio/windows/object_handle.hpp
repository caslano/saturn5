//
// windows/object_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2011 Boris Schaeling (boris@highscore.de)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_OBJECT_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_OBJECT_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_object_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of an object handle.
typedef basic_object_handle<> object_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_OBJECT_HANDLE_HPP

/* object_handle.hpp
1wIrz2HEfbny3AG4qKecG++F0azC1+JVvhHfgu8CJBvET+Y3/8uKuM9H9TghQjdokTRhmfBIKCJWFc2PVm5jxBZSR/T1fWm+vBx96arEqP3UvWoMMvis1lGP0wfod3V3o4RRxmhndDN6GS3MKCgQKtydcrW+Qw9cNAr8M6Nw7juX/EJC6HA6jh5WWFczG7mxkS7FNPqX+e30wlxwzHFXYRX2LVuGqy+MFxYiuu4jpmqLzXB9g8Up4nLE0Gnxd/Gt6CfVlRpKneBqJkuLpe1gt9+kl1JJxEcDqIcBiItv5M3yccTDC7kY2FMD8/eFW5gHhfW9clV5ohRVq6iqrUrPA8leqIFaHY3W2mAckrXR2nEtRG+pj9c36bf0SkZvYz64/x6cgxucQw/wfLZ52DxvXrJcA3Svu629PMHwBPweCT7+hmSQA+QcIommDTqNTofrO0NvR67fZIqyIktzAhx/MrJ1PLTtPu4a9zvHwOk34pPgOb+GV18F/jnEH+Uf8Qfhi2+DK94KYXAa3cS1YkMpQK4HlfYxAAYs+dN3j1F5TdFaaxFaM6OtQSW627pDJv0IyzflI/gO/HJ+De8hFhXLiBVERtQx9pHI0XZSL2RdJbkm8ipcbgG0T1KHqhnqWf26/kAfa2yDLnanduBYCrlJcugaTH1GBJb1YdYyPzE8W5qriVbM4RZyrzirNuMAX0xwF8dA4c6VNiGLz0l1
*/