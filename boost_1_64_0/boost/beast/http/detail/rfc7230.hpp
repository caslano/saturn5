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
lu1X5d7K6OVStkV9rLJtG9/TvWgR19ssW9luJFx2H6tsxYZb2QiDobMu2/GRlO3ooLKd4lI2xa+MG+9lhh87Rkna1Sqtm319GQkn8tZZDN4LruUtkctpWw2+7SMar+WdwkAB8UyQ8XpbqNh8T853jhsyZth0jAzjoIzXhHeeCbtKuTcjTV9wXej30OsqzHAjDX7kW0rSyfDXp9jrrY5AN+PUpyre9Lcjecv+E2fZb5Syj5f3ab7MMbIOC+xvqq4+xJpkqD1nCcRZDKk5xsby3Rzf2/x2SpO2wXeSi35Mxv5tVNq5qh1EUk/W+J42wO9xpdRTi8wnmkJ5lQ9dz29cidPPyJB33gXKfYoxlP/nhc4p9Bme56lwJxubwNccXWeSHqF2QD7L+5l35sr3Zz/k092Uz0B6bBodNTnJ/PA0tRBdkFhiKj/34I/keCOc7ArxvFzlc3zE35bRziUSBvkT+BwaDL0CmXOJwsPdZSyTCS85S7xRWjd0pHI/6DWPkPAjtR7ocOW+M3QOIfXWKOmJfCT+sOD5gx77DlX+d8m8QcJTm3tTb71MneVAqbdR/nqLo3KS4rvouguaDialdkmmbjeWCYP541BVteHqcgqex/t56dS6FJ1PyDyhIHSeoPvVjVLnY2QM2ELGgKYFzjqvLW/Q2oYM5JVEvMWQNQ4gr7Bt2GwT56p0MyPu/1bbHJfp9zhV+v+x0v9bPfiUBurVNonnHAM+V+46I4v/Z6xjDPhEhZtrDIa3aXoMkPQIta05BiCXtYPtY0CXxG6MAam0DXv/j9s4ZS+gK3Mpu+zs60Ga359U+tP1WsrkI3DjCpZzhrwnv1Hhy9HoprAXqmentjOzXiZIvdRtYvBQVhkzHpYxo+mIddaLtbToPUYf4Rw7rlfuG73GDsI7x45rlfsqz7HjKklPxg7ir3vsuFz5Xy1jh4Rn7JhIfReYNvFZtrEjzT/Mp8bHtXvccKwJSp3eI2VMMeL0t1XCkereb/ru5p5jzW1+3ju1DUQz1uhvrSGBNd3uYA/Zv9B8ZKCtzKsrZevCnPL6Q1z0LFIX16rwf3MGk69D62wfDeU/OatgE7AbWI9P21EBfuYHdKxe334SfrS+n3XAQtM91RbeVJPLWfc6/KZ67aqfCr+Pka7D++0Y7OfC9lFhSuXcUSuNkbIO4+w/+2r/Ybr/9FLxf7GXQepxfI998M/WfPnkbAKXMVzkP1SltSZq2UubCflGLdC/+eWUwW+F+jdLFqIbc9/nT1j3b5q+Iwz1fCXvjfdFH1N2tK5jfwYOlYzrGobE6W1kiD5svnJPo+YT+YZOctPLONf/pC5XqHip/nPDaYNpw+06m6yodDZqvqrS216vRW5zjFrrU3O804aR7nBLh3Okqw5nsPCxxOIjuamFObTFREQ8xKk8t3bloRfpNmsemu7qqB4pXd4Rr6lyT2Ys2bxTdEnWuLBc2ky8LZFrTR3OMbY2M2feYdWiauym20rd7Co9Lljh41VbwIo87L0rci6C8EhaQd9AhSND+RpMikuD+RKbLWHPdsZB1fw5c44InNveTv785xSotBzfkksYRBRCg6BF0CxzbT/AX0N1Y4htkazPqx+ENyvOEG1X8bJy7yfjl/P9TL+W8Jm6j72o3POc31Iydr6v/DYXN6sQx8pY6THevaXCl7ZrvMvV9hGqfLa7WJzvyK2s8Urlj35NvsfHiN6+7li7DNUL0vMb+0Qpj/6eiMAey16PjaP8HlfLmHmupRMJ8DB/rl0r4v1uJE6QXkS5T0P669CLqDCLGFf197Wkk6HGk4HmOiL0qTmeJM3T5bxDxpPQ9YnIx5T+Teo+BtpvWsT1G4nOxTrbJGu0+zk=
*/