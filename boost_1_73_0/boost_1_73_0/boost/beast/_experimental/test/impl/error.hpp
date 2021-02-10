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
wobh5aqAg0O6lv7Dz5vwkoDnLLCV0+7pbn8q41KzqmPbABuUGr9HbjC4x7nhjmuJdnAeR4lAftOH0ehj1fj1HNNRDByjLAELvqMXHhcMKwb/Rtu2s6qGeTvHem1UFI2zPLaMs/UdBPgiZUpxPsPBgMtw+dit1QUxG1qw0OaWFHqJBFPGc5shd1zStQdothV3wd6QIhkaLu3wKJTzDh8KtqKI7ouZacKGiXg5F8u241ctHOIgyWvo7lj/rj6OxriA9eVBYD6fd+VCAEPZRWr1NpxJPyfq9Oz32/fnt5cno+HVZaeqJzZUPyfh72fXv1/dnHVocFFhwcjAadfiolwhg6x7zciUULqxVSxFEFiEVByoBxXkIiKYFesQJ4wGUG4pJhcivab8TjNulWQ0bG7/5QaZhM+xQtdle26OPM4w2HFm5M6SApF5oq+Ysqbs9QrBnD6cBmHU6oNi60A9z3EG5/b7gb3DFURxicWsyPx9R6oIR3WvXaaNnwSyrESW7XZg5iY3bAwDhOzpMlc+A44nLsjfYH91aJ4pI9fG5MKXaW3ZTCzCAMHbGRRtIDeFTrf1ovno/HT8z7PrK++1U1ZU5cao1fd02Kos28witwTpXBl7Ci7Q4vKcRoiQyLjPsk16CU4xpWse4AX3c4P9
*/