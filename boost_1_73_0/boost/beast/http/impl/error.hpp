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
s5yM1kbtWS6jkTCWcssOUY3ro8xmWNN4rXhTmWwEv6FI2VP3qLDZmqUAScbU76XSPzg8YbrJHwU0buQ8jCzCgASAIQ4xfhKQC+U2Pz7j9nga33tzdQ9N88baqdpfMccFQ3UYWxsl4YLSeeZgFaCBlpUlVZw8K2a1Twrfkt+daoVv8qxzZqP95GvrIX6AhOtDJ7I9mtuoFaTDaB27QjCTl33qqJY8myUfCS9oTLldWibTkX9P
*/