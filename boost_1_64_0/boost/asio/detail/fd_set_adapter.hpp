//
// detail/fd_set_adapter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP
#define BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/posix_fd_set_adapter.hpp>
#include <boost/asio/detail/win_fd_set_adapter.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
typedef win_fd_set_adapter fd_set_adapter;
#else
typedef posix_fd_set_adapter fd_set_adapter;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP

/* fd_set_adapter.hpp
hdXhvGg5UiowgnpZyTSO4GSvwsl8nE9DYmeP8B1kbHE5K4K3wznSQszO5uKyPW6dlgowcvmMab+EtYI/p/lQQloMdL4XLL07gsgheKPmRjcop8uTrExvv+yCAr87F7BfFTvg/25DMd7aRZKrCao1sqD/+USfOvu5t2Wk9bwjGESPfYhwHMXM4N0OdsAB2s4zIOjrAdnqlH/mUWF4QFN2lHprKHyyPzPa9f7doleTtF9PjnxWNzNwd+q1tharyTrql1VfuNDSzciqGn7yIcgM4pbFGBaOx8EPfjLyebOusRbu/JrbmhMvJpdmM6XLprmvsy0R0kz1zWr2Vq4xrZx0di+btJSOjMP9rVte8Pk10xx8Zlug+68nlOseuSUif7gM0pOWd7PGtCJevbK9xxjbBA43xZ7I8ci8NZ1pmlijQt+r1X9pylu+9dkyu8vRgwd9dU/veMKX+J0XMM4pNRegEJ/LbqBz5BzjJgEeB0zZ2oVO22VbwFN02TXpus3qFaSaIpN1YU6beu8seJ/H9lSPfmMUJzU+q5s2gjf5UjO5/7v8ImvDFb+wz/wY+A==
*/