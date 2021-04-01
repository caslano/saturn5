//
// windows/random_access_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_random_access_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of a random-access handle.
typedef basic_random_access_handle<> random_access_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP

/* random_access_handle.hpp
Wi4/FL8BdiEh/eKUL4QXbJT7DdkrUdNgwvWA5XAg4zEP0oR4rYF4NdpW4oXsUrNyyrMG1fnQ821h6X8g5mSdeWw/avKAPYk03E0szWiT2yZ783hqoS6Tuv+1cetGaZm0plVFpDNAYLZAXU2m4jSh1ZMV81gusWG95FZRqLg6zTIqgT6CvCCrI1v3xxqIZYRqpViHaoniaMuIKyeQh3Qhoq0wEOQ1sOqAaLjLowyquFOtuxJ/APoR7NaPTROtBUvCGLA/DkWoIbqQrkZj/gC4gzWxsG1+XUyKpemdrVqAhEY/EVPhE9zlWORdAqzjgFw5bJyRh1cd24hJVmAveGjIWrv8bjqsydbKuWOs7Rhati/tbo5IQ9EkKPLrirrKCMe1wt4gVbmicRNyJLTbXaBm/Bu8V4kwHS38GyR2yVpskrnNBIeJVjXhfO++Dg1DoBge5ChrYu+yDULb1E9/lnpuS2sGfw07Zxu9xBICkX0dj6L99kH/0QWLeH73Jw1vji00U1QPFGfrA16/1fa8Iqb8dMm1Arxon1ty+JJ3eh6LE1pzQXtNQCeNGUuyEg==
*/