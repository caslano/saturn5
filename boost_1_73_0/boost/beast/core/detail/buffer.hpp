//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_BUFFER_HPP
#define BOOST_BEAST_CORE_DETAIL_BUFFER_HPP

#include <boost/beast/core/error.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional.hpp>
#include <stdexcept>

namespace boost {
namespace beast {
namespace detail {

template<
    class DynamicBuffer,
    class ErrorValue>
auto
dynamic_buffer_prepare_noexcept(
    DynamicBuffer& buffer,
    std::size_t size,
    error_code& ec,
    ErrorValue ev) ->
        boost::optional<typename
        DynamicBuffer::mutable_buffers_type>
{
    if(buffer.max_size() - buffer.size() < size)
    {
        // length error
        ec = ev;
        return boost::none;
    }
    boost::optional<typename
        DynamicBuffer::mutable_buffers_type> result;
    result.emplace(buffer.prepare(size));
    ec = {};
    return result;
}

template<
    class DynamicBuffer,
    class ErrorValue>
auto
dynamic_buffer_prepare(
    DynamicBuffer& buffer,
    std::size_t size,
    error_code& ec,
    ErrorValue ev) ->
        boost::optional<typename
        DynamicBuffer::mutable_buffers_type>
{
#ifndef BOOST_NO_EXCEPTIONS
    try
    {
        boost::optional<typename
            DynamicBuffer::mutable_buffers_type> result;
        result.emplace(buffer.prepare(size));
        ec = {};
        return result;
    }
    catch(std::length_error const&)
    {
        ec = ev;
    }
    return boost::none;

#else
    return dynamic_buffer_prepare_noexcept(
        buffer, size, ec, ev);
#endif
}

} // detail
} // beast
} // boost

#endif

/* buffer.hpp
2xXLR6JRNHgy3bTCVfm4kxF0W9TNp91cPpLNs23+jZ1dgU3dPb1P2tzXPzAY3DIUCsOOfOu2J0fGJ6KxyV3xxO49yalUOvPUbC5f2Ltv/4HL21atbl+z9qLHX3zJhStlMP3L+bSMOc4Cz7PxSC520Ro1zyYaJ9av51N8fMq/BS1vIp1KqVkk+TYmo9IRnQiOTeQT6ZSaYy4nTyGZbHYnkukcRo2bR2A6GY1hVKdTMQ7OxOQ5
*/