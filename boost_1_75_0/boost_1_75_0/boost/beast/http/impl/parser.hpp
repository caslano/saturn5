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
NZhCk5F6fYxmpO4NjoH2HiEuxu6S8wzmpiiiIDN1ViSIJ0zvIDdTv30EEW2jlQnj4dDpz83U30FxKZipP71MMzRvWIbW5E89x8+l0TGcE2E5C6rRziSOPODkGK5/vWAZn5dmVmv+MqOh+VSqOE9UbInhYDAMgklsjFqzOayGHstAJ+RY4KFUU57jiVqOZqDcx0vt4lRLXcZPNcqp0XOOL8UObHiWd2C1iXPAZhLz5AnkghXavKG3YBvKT5Ae/w7lvMWqGngHmV3+sZwa740cJXbvHb0USIVG1i9X7u9T+ntHquhptxa5dFii91LB8jvfBJGYzP50XqS/KHIuL+JPzm1xlNvhkh6r1jYv84TmoMDtCdj9ysKXVVV+Zz2Sf5sDqsnleBz4ga53INyjC8JCzKHbwQev2rUi87AIZmZg5qpX8QZQNY1uAOPkmXBGlVc/dB4n/N2h2BgXo/0Z5Cy/JZ5rp8+7mMh9ButJUxbSAXkvLt8TnNwHGeME9tNd8RqaneJne8GIVycEzngFCAFw22sQmNCOKRklLrN3jRK36JI+Qqnnrj7afbrfKO28zxt1Er/LntBTiFHBvStDdiOJcWpgr6rOxaxLSCAxBJBLmeCVuBAz5VeQm0urB1GzA9XHAy0xE08JHDGXWOUfA0di/Tb5M/nH5tisA1kf8wUwXNhUpweroGX80CsfVJ33YwrbhBWdocDZr4gb2ocI
*/