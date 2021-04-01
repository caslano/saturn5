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
teGvr0mHj6KCxNIBOwtTWeQRKFNuYukoMShX5Nfdf/i+RCABZXuCAihpOetT94chAVxGkNFU7VGi2rB9RW8TEx5QwUtkddEyACzGhMekBHHPD32MBwRTFgOlGheHgqEpneprrL/AvFtyLzospKWSX1KK7QBcRCvT6WI2Yj4mOXGFg/pVJjPc2QW0wC7Vah6ogOGYI5GzvsvEhYPluLH1c9RfdscnB+tnS1CPG/A9TjV0RStqcYSF311xlXqmrisIucVDwDq22peQKIqFapLdN00MzV/jKbzUpOdLnBGyzWQ1Z6v1+jBaxNOIHP6c+eDJbIkoGCWtOrKPOFYT+r/+7zeqXfRrjzV0Nlzpy7YE0+buyyDv1lfD9+6ed/LV/cNjBXJBans8bKE0I9gqAh7GxVzATnHCiTGc+/fm1C4TY9UVvySk3yjWEK47Qzfq3WvaGRdhhBqQ1NGIOeKsauITroZkP5obb3Xiu7BnbMFAEK896i6hLTUJcGKdfMy4XeDOhJwxXfob13IKWtA8/HPwNPbAdcXCwhUwwxuxt2uG9lTDSvZLTUcXbvnGPQ==
*/