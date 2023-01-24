//
// windows/overlapped_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_overlapped_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of an overlapped handle.
typedef basic_overlapped_handle<> overlapped_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP

/* overlapped_handle.hpp
5K/hznzgzqqrnKqondSean91tDpdnaOuUn8HkzhrRdD3ohYGrT5QO6r1QLR9qc8CK6zWt8Jhv9W9DV+jvFHHYA0ZymygMdWYaWy1182eGi8Nb7OsWRd+rhXUWDfzc3OiY309zd3xPSq0SDelWyIWE6GBn9BVmZpA4wgmmklmxiIWt0PLn8G4vGSKsCVZFg58AbB2LbuD3ceeZa+xt6HvS3K1uZ4Yr5mcxDfhG4pdxFnySrmCkqEcUKLRY9523Yu77YeuYv/K1mRwlru9tuDGl+JFvgHGdTRysoJQF1phtLBU+FV4IXxcURGlzNaWaS30r8CBv+sP9TC0hsp2pzJs/92cFKcfo/f/ZJy4Ehxja6J+OOJp/hVPCa6CpUtaAaMHQHusgNr4VQgV24meUjVJtucD46S+yJah0gQpTVogrZTWS5ulncj4FnJXuaf8mTwQWvALebq8UF4q7wGS5sq35cdyHUVQWipRSoKSDKd9X/PQa+gH9Hv6LuMhHGR1szn80wR77t+dWmTPfyeQMVC0OXbsu9B16E50TzDkEHoNvZXeRf9EE0Zl2jFxzDAmG576MrjvOVOBrQr1GAm+68n148aBv1ZC023nDnJHuSZo0Ru4Az+pufRCqid3l4MVGn50s+KvVlNroe/HQ488VP9QX+g+hp9REYqhGRTDeGMGVMIqY71B5blTk3BtTfkR/GEhV3wi1oKzbQ23eEN6
*/