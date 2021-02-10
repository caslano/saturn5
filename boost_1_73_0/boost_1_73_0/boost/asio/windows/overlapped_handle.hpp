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
dcVOyCBPoPU5iP+ewB0v94hc5n+ep5Q/3kNNOL6qI9n3MYDX9a9PGXyLTtjS29fVuhB/AVBLAwQKAAAACAAtZ0pS36Sw3dUAAABPAQAAKwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3NwZWVkLWxpbWl0LmRVVAUAAbZIJGBljjFrw0AMhff7FW9soWcK3UwplC4NdMvU8RzLtuAimZMak3/fO6dDoIsGve9J35fK3MNWojFmPrOH46LFe3yH91KT1z16C5+U1x5H1xVekthExWBZNyrwJUkdbOEjOc1arj1OKkInZ5UQYwyHCQmjbpI1jeD/Vcx8IbmJ4IEFw9XJsFbGqB4bHzFpCTdR5zP9rQ3smMkNaajeNHa4Y9ojcmzsC2K8C5I0i/DyDJ4g6g3rQtPcZXRt5q3+Y9XH6EIlZbSqPVWEkJM5VKjezhkD7WAXfgFQSwMECgAAAAgALWdKUjQyDVggAQAACwIAACoACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9zcGVlZC10aW1lLmRVVAUAAbZIJGBNkbFuwzAMRHd9BbcslYGuRlGg6NIC3ZIfkC3aFqCIhkg18N+XkpPGgCcf7/iO+qE098ArorcSrmjOC2XpYTMf
*/