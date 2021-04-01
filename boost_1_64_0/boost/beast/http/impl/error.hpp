//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_ERROR_HPP
#define BOOST_BEAST_HTTP_IMPL_ERROR_HPP

#include <type_traits>

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::http::error>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {
namespace http {

BOOST_BEAST_DECL
error_code
make_error_code(error ev);

} // http
} // beast
} // boost

#endif

/* error.hpp
ogdyfBddabVQWXBCtkobbVR7aGk93AwLDXoz1DzrJZRjEB04On5639otqpXZRI5V6dnaE2H6aPrJXHPDaZNmnGlwuwkL+Fv7W7m75wUZ1UBNjMGyoYP6cmpE4YJ3a3EYIUzrODM0r0Yyd5vxnagurpwe/3XHclXa6FDBT2x1CLN6q+bABvo+tV5tPrvnePIAc2YqkYY98e5BR1hde4HY37xU6HcFhZ+jDRLHHijI87j01gw8Gbig56VIxaIlDfcqzoaK/B03Ae1qdTgcOhHwdeMfUQeTTyN113TOZW1EhbgihVDRoMsR1DSpPXsWBXcAubSa9Ymb+1H2mgaym5CA4+O5WEWLLn8hfwb8A1tpI6BoiFCC7NEqY7wfLl4sRTgTsihUttApp4dXZ7u/AB7ZnN70t1IE5WvQWSOGPSpDZiuPaaFJ0u6IdW+HcuKBk6eol23y46OlGwwCewg0k/sFRb2n9NQT+U5uktDsiTrPDZ5/rsB9pr/e9f1vevA3BQT8AoWOJDnZoxH7URITWAJzCgXaJkZxm+4uHOWzQ3AqixEL6ZFgL7mS7zktoQ==
*/