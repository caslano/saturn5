//
// posix/descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/posix/basic_descriptor.hpp>

namespace boost {
namespace asio {
namespace posix {

/// Typedef for the typical usage of basic_descriptor.
typedef basic_descriptor<> descriptor;

} // namespace posix
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       // || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_DESCRIPTOR_HPP

/* descriptor.hpp
b3h5LWtleS5kVVQFAAG2SCRg88nPS7dSKCjKr6jUzU6t5PJIzSmwUggoyixLLElVAIoopOUXKXiEhAQEQ1RxORYBNdgAZey4nIFq0vOLKqEGKJTkFHPp6upyBSfmpiokFivogoxUSCotUSgtTk1RyMxDNkghOT+vJLWiRI8LAFBLAwQKAAAACAAtZ0pS/kdU+70AAABKAQAALwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Byb3h5LW5lZ290aWF0ZS5kVVQFAAG2SCRgjU9BCsIwELznFXvUQwqehN5ExB6kFlofENs1DaTZkqRqf+9aWzwJwlxmZ3dm50ROp9B7eo7SoaZoVESRoe1TuASErKoKyBcBVmWRH47nNaghtuiiqVU05IDB/OMjdk2DTQrbZMMQJaJUNtCSotz4Pp7ZVQVTiz17a/LjvDO5CymlqNDaAPXgLUSC4f+HHkygpq4b3DRyWjwMp76/1ObO4pSUTCXltzrcyAM6dbV88ivsY6XAY0c8binERLwAUEsDBAoAAAAIAC1nSlKjMwe0owAAAAIBAAAqAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJveHktbnRsbS5kVVQFAAG2SCRgbU87DsIwDN1z
*/