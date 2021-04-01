//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_IMPL_ERROR_HPP
#define BOOST_BEAST_TEST_IMPL_ERROR_HPP

#include <boost/beast/core/error.hpp>
#include <boost/beast/core/string.hpp>
#include <type_traits>

namespace boost {
namespace system {
template<>
struct is_error_code_enum<
    boost::beast::test::error>
        : std::true_type
{
};
} // system
} // boost

namespace boost {
namespace beast {
namespace test {

BOOST_BEAST_DECL
error_code
make_error_code(error e) noexcept;

} // test
} // beast
} // boost

#endif

/* error.hpp
rWx3nFFxaE1VpWYNcxq7twiAL2Kl6atNtTBfpwLVex2YScoISTnrR9NHOYl4f0I+a8HqW9coRQuWzlN2Y5GyUsGVJQfJXQV59oyGK2N+uXDHNJM8M8AxTgniwJbgh7+W8xHV2vP051IF6EhHVELW5R2CjqSjvc58JyuqEmMp1XYFKMLapQnTPGHVD5lcsUVOFAeKXQacn3YqidCdJOJbfkiqykECrhJDDU+++oUfC8n6/vdod7ph4fugh3ruRfH/E7BzSBBnsOC24jISjV9c+V7QsHkGRtG4eTaaPBc/YqU6db58VnzxiVA58JEnRzf8Ah21GnYe88Y5hGGeaXjrSCHtt0AFYhm991w3mD8q0TFyIJseKVfoSbWgy6s0tTt1+eccyGFDSjo/r4sHHb+JgcgO62eF4Yy6kz6OKaZuMqfj7r38XKH1inyZrIkeLeoUHBoeVPIcQoNdXKiXLEOheQIQElutF2m8oZjLCVukJMm/VkUhiVtHE3VnyufP2XvkG3gmYr2YykgaR0YZbtXxfAxsdT7STs8edHQfUaprJGCJ9djEVTweCWFgSg==
*/