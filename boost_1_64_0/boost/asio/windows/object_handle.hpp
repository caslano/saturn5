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
8erjArgwj3gM2WPXhVBocDhlf7ElB58dwSF6+q31nIassQywgRsl+LaETIHvY01jyc9cSrw3avaTkpWxRjOpDQfJu6s3bAILWyUKJ1BS8oz5Q81mFoZBsPR6P8SlbxGUCj4mIBUbCN/nL8sP/e0KULj73kADzg9lSpB7veq8qugsxP5nZYpSSbf9fP7i5V4Cv3MFFtIYJdj9MHYcGuZd09XF26bzteNEXd6MPdsO4JTct1m8IeoBz6/DaAC8iTkR0kvVkm6/BnrCR8JdZdZMS3frzSPiJs0L8NxhpU5OVxG5DVmQNePYDsHTJBqrzxR3zpwI1xrpLyX866046YKphfCQ727TiG72KZI7OEsuuYND2A5LIoXVCM+R4DTwSdQ9jtiJAII01jDOv1TC5HA8jfM/AlVjdb/j92mqeeNatxubgyxTVwqAa7mGpQZe8J7YmV7VAZfmaxsOQ2RVBVxBMCNHk04bIsbUlKcJohxzbZQEkdlwRDG9E/YKDLleNJN77bPRnZhINCNUzEd5pK43fA8+OKYbQX28bBJbLZFUrHImKsFl6/EAcG2HWA==
*/