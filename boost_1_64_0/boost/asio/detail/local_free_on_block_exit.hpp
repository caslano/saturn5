//
// detail/local_free_on_block_exit.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP
#define BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
#if !defined(BOOST_ASIO_WINDOWS_APP)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class local_free_on_block_exit
  : private noncopyable
{
public:
  // Constructor blocks all signals for the calling thread.
  explicit local_free_on_block_exit(void* p)
    : p_(p)
  {
  }

  // Destructor restores the previous signal mask.
  ~local_free_on_block_exit()
  {
    ::LocalFree(p_);
  }

private:
  void* p_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS_APP)
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP

/* local_free_on_block_exit.hpp
+yRVhdQGcJ2HMaXjwa6rUfiIoODJ/8t7UVI1OK+PH42eo4V+slTfn4St7k1fO+orZpt30Jsx6n8FBn3BudPYFh2V6bgVG9BMvhXGLQXrsTTxNNVnP78IGP+vU9YVL6lNvFRI+tbDfomNRd8dvO3g9CM3tvGDhZfkPVnkLvGSKUMb65QgLi2o5Ja0SsxXtMCaKp/CMcnD/lKqfx5V5JTyQ6bianvaDnH1OiQlWCfnCdnS2SMs9f6dy46UD0B09nNGWF+oIvzixNkIFOKtlBJAe7iBFHYTueAcTyHZ5PjpIth1Wih0jd+5AYgzdgldm01dBnJemTOOoi7ZJtYsGHusg/slQdlO748wjiU7pgBXGuj8yh5ykgYnjJWwZnTCs1WFDnUxXs6nPnEHDIw4WhuEFVrm3Se8qZ2zynWwX1SmqiNGwym6cwmCaDdfZJw/y3E84orHrEAtz8295DxzHWP4aglhvz124+xqFgrJIrDd2S/3JPmP6sB5LgV1VaCHY0N5dp/g0XgqvLoxu2pMvE6UPbEHjD0HSGa9HEhH9uosZvZ2SYa5QMXRk55a7A==
*/