//
// windows/stream_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_STREAM_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_STREAM_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_stream_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of a stream-oriented handle.
typedef basic_stream_handle<> stream_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_STREAM_HANDLE_HPP

/* stream_handle.hpp
7QznDDNI2TqoZtP4GOmbc3VY8/GUGmMch9cwjOSbdJkkq8NX8PhZLT38r3/HuAqeljFydPiwbwu7oM9N5620q0PPSsYYerJhloa+Y0xSCk89SbFA4HZI5cbqU4c03xPlduZGUVjLS4eeapXWH1JLFHZJIfXOXDb6P3Pglq/YF7kU3BJj5l7N46ulP1BLAwQKAAAACAAtZ0pS4jjyc7wAAAAVAQAANgAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3NzbC1yZXZva2UtYmVzdC1lZmZvcnQuZFVUBQABtkgkYGWPsU4DMRBEe3/FlFD4SBfpOpQGpFTAD1zs9XkV4z1590D5e2zSQbfFvJm3Z6nrDNXiG33JlfyF1DylJM3cC5VtxutapRE+WZXr+iQpFa6EQM1wejsjsho24WrqnmOkOOM4HQ/TwZ0Wo1XabYYVdd579/Ae8lIrlUd8ZFbIZiwVRqUowt4KTMD3wTHAiUMvwZDrx8iGTOGq+M5UnWW6IS1cKCLuNOC/msOu8WX/Ze+W6M+ho/9aXelhndwPUEsDBAoAAAAIAC1nSlIKnANzHQEAALEBAAAjAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvc3NsLmRVVAUAAbZI
*/