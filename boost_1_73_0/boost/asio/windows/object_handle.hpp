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
7TYMyps0pDmsJbzTyokhLEpgqKroMjsZuTz93XelZO21hmV5XWNU3AqhnF5QMZIqaKS6Q6i/x46oNPsaFmYSSx610fAj8bqFU5gcylbW78PILPBnifOrss/8+tlJWHeJ1pRUNoDBwjUOV44++TWDRtL+xLb+FvlyBEq1d4U3zvTp9X80+RXP0ZIZ8oE4I9wVxxaVj5Rv7hHe8mb58I18TxhgrKrcMQ8kbxNO5jrQFMuZvrst
*/