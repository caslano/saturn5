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
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
*/