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
zfmUDS5mVCGj9idElTCqklEzGNWSELX+u5AVTmCUj1E/SYh6YTuiRjBqLqMaVdTma2z0E/qYYyVNgxvo+nd2ujfVD2FEzDUiJ2oOV5MgiRx919vmLN2s0EZHmZxJ0DciQrtLPISCnTJwgFINQaNPt0uj+5ynDtGOgLFp/Hur+FHWDgVTwW+DPaRQWSfulbVB1peiU/2vD22yPrxSodaHLP2ei2LrQ4X+qYtj6wPw1UX9rw+D
*/