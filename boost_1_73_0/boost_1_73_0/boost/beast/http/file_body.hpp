//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_FILE_BODY_HPP
#define BOOST_BEAST_HTTP_FILE_BODY_HPP

#include <boost/beast/core/file.hpp>
#include <boost/beast/http/basic_file_body.hpp>
#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <algorithm>
#include <cstdio>
#include <cstdint>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/// A message body represented by a file on the filesystem.
using file_body = basic_file_body<file>;

} // http
} // beast
} // boost

#ifndef BOOST_BEAST_NO_FILE_BODY_WIN32
#include <boost/beast/http/impl/file_body_win32.hpp>
#endif

#endif

/* file_body.hpp
WWziUOhvWKG/kU5B1Gwas2Zmq5ih0GkWkg5TraXepE8r7tNtYimjZ0eSdFlCfHiWQvdUWl2ma/+ka+vsK8ygz3SlcqIrNUXbhaxtd9LPHG3n5X0dVeM2XU2YdE3qrhTioaYQn28K7YVSt6iHkcQ5R5BEU6/SFOIRphAfZJ0fVHqbxmwms1XMbma2kdlmZviIpGajpcO24+JOpRsu6B61D4YLQ2Xzwo1HAvNqwms6r2jrbKqK2jllNSc6I1T2a04=
*/