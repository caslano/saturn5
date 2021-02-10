//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_PARSER_HPP
#define BOOST_BEAST_HTTP_IMPL_PARSER_HPP

#include <boost/throw_exception.hpp>
#include <stdexcept>

namespace boost {
namespace beast {
namespace http {

template<bool isRequest, class Body, class Allocator>
parser<isRequest, Body, Allocator>::
parser()
    : rd_(m_.base(), m_.body())
{
}

template<bool isRequest, class Body, class Allocator>
template<class Arg1, class... ArgN, class>
parser<isRequest, Body, Allocator>::
parser(Arg1&& arg1, ArgN&&... argn)
    : m_(
        std::forward<Arg1>(arg1),
        std::forward<ArgN>(argn)...)
    , rd_(m_.base(), m_.body())
{
    m_.clear();
}

template<bool isRequest, class Body, class Allocator>
template<class OtherBody, class... Args, class>
parser<isRequest, Body, Allocator>::
parser(
    parser<isRequest, OtherBody, Allocator>&& other,
    Args&&... args)
    : basic_parser<isRequest>(std::move(other))
    , m_(other.release(), std::forward<Args>(args)...)
    , rd_(m_.base(), m_.body())
{
    if(other.rd_inited_)
        BOOST_THROW_EXCEPTION(std::invalid_argument{
            "moved-from parser has a body"});
}

} // http
} // beast
} // boost

#endif

/* parser.hpp
S6RYIg/2VhrnA1TQYw50ni89uHOlKIrdEFF5RKeFsZ8gYif3ApQgeXheLdMCcp4Zq/cC+yiF2Phg8JYKqKiDriUYqg0CW1OzkssllJU12VcAEcG7cGWN0/CJOiUgM8oENXSpVgapsy1fl/y7ljqR7IDVgjygomgFERc7l52UZkwxZjdyDc6QJslbFMbthQPKy5IPlwYXWSi/ZAEjPa4olxLayNRdo1o+nyPaClmIB+5UkO+wv9cDzVdalXcCapLcChcIvya9QbMQfM/wB1RO6pT3myizOstANlxC6KUPpdHhwAbNwVfNNUO9hJ3XzJ9hEExPgV4liLXFX7CXRA3Ht7fx43bQ+wz47Jy2WRB77a/EpFxPx7+b42ETv1S2xV5on54PejyTrPRoaPQs7OIUveQwtx+efQwr0PtYIw2dIvuo5Q5zWGlcMCeAPWeST7gupMyYERJ+4nlhZqKI+dwWY4rfnkxeH5zEBycng871nKdWOI4Ro1NUeWUPHMENpLdsnAz2Gvy8PKDPAT1aZ433gHDSof972s4DjRzsTy9PTkKkECuVmagLYF5WMtwLk9FnmKK4NmQlKvTMJFzo6G5nsVjsQP/lDjyDpKhnGvXaMY6K6jkzDmjClFwIXE5ATrQOvwYVwzfYsdXuRdQ/
*/