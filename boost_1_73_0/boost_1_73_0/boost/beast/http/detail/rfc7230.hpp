//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_DETAIL_RFC7230_HPP
#define BOOST_BEAST_HTTP_DETAIL_RFC7230_HPP

#include <boost/beast/core/string.hpp>
#include <iterator>
#include <utility>

namespace boost {
namespace beast {
namespace http {
namespace detail {

BOOST_BEAST_DECL
bool
is_digit(char c);

BOOST_BEAST_DECL
char
is_alpha(char c);

BOOST_BEAST_DECL
char
is_text(char c);

BOOST_BEAST_DECL
char
is_token_char(char c);

BOOST_BEAST_DECL
char
is_qdchar(char c);

BOOST_BEAST_DECL
char
is_qpchar(char c);


// converts to lower case,
// returns 0 if not a valid text char
//
BOOST_BEAST_DECL
char
to_value_char(char c);

// VFALCO TODO Make this return unsigned?
BOOST_BEAST_DECL
std::int8_t
unhex(char c);

BOOST_BEAST_DECL
string_view
trim(string_view s);

struct param_iter
{
    using iter_type = string_view::const_iterator;

    iter_type it;
    iter_type first;
    iter_type last;
    std::pair<string_view, string_view> v;

    bool
    empty() const
    {
        return first == it;
    }

    BOOST_BEAST_DECL
    void
    increment();
};

/*
    #token = [ ( "," / token )   *( OWS "," [ OWS token ] ) ]
*/
struct opt_token_list_policy
{
    using value_type = string_view;

    BOOST_BEAST_DECL
    bool
    operator()(value_type& v,
        char const*& it, string_view s) const;
};

} // detail
} // http
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/http/detail/rfc7230.ipp>
#endif

#endif


/* rfc7230.hpp
dp8Gg0Fvj/RrYMxbVI04MLfTDphTj+XyrxqyagnjBJst1yePBS0EQ5R5PYdKx8oZGf60tYUq6zJECQEHAMA+IAMkd/nWVsmLq39+zMsd5fbXGGwXWxshIUVFBA/c3KDkhInGfnN6KFk84Go/8QbNLNyy50+uEPkFtPNhcvrDjmVjlIQW1XpkdtN93whfrMh5kpnNbfTWZWToKkZalHj6lwmoUipTB3UyX4JSXYUe0J8EZ0GuDXm61xCp3VGTal1q33J/u/13g7nVRagJonLvNd+dnSbKvj7nN6icW2rtn9m9+Uz/BAWxpH9zIuF3JJ4S4Qf1+XoS6B/NxBx8rg3SRK9cgrQkYxhpFiznl+2u/iEL2EKY4O03eNi+Roz+9ea02rbfKtquduaVm1MH9db2bu0CI4d0X6BWobH9NMnIUJS96pq8BHXbgeBYGLJyJigS74tQjZX7+/n4ATRYrXQ8nPZilF5NXn+rcmvwykSEo8kTS67moahU4uG6rNnM/R9QSwMECgAAAAgALWdKUgmvRmawAgAAHwYAACkACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2h0dHAzLXByZXNlbnQuY1VUBQABtkgkYK1TXW/aMBR9z6+4YtIEKCUdfVlXhpbRbkVDUAFt
*/