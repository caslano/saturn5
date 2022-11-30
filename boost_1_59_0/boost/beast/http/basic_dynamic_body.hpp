//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_BASIC_DYNAMIC_BODY_HPP
#define BOOST_BEAST_HTTP_BASIC_DYNAMIC_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/detail/buffer.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/optional.hpp>
#include <algorithm>
#include <cstdint>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** A <em>Body</em> using a <em>DynamicBuffer</em>

    This body uses a <em>DynamicBuffer</em> as a memory-based container
    for holding message payloads. Messages using this body type
    may be serialized and parsed.
*/
template<class DynamicBuffer>
struct basic_dynamic_body
{
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");

    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    using value_type = DynamicBuffer;

    /** Returns the payload size of the body

        When this body is used with @ref message::prepare_payload,
        the Content-Length will be set to the payload size, and
        any chunked Transfer-Encoding will be removed.
    */
    static
    std::uint64_t
    size(value_type const& v)
    {
        return v.size();
    }

    /** The algorithm for parsing the body

        Meets the requirements of <em>BodyReader</em>.
    */
#if BOOST_BEAST_DOXYGEN
    using reader = __implementation_defined__;
#else
    class reader
    {
        value_type& body_;

    public:
        template<bool isRequest, class Fields>
        explicit
        reader(header<isRequest, Fields>&, value_type& b)
            : body_(b)
        {
        }

        void
        init(boost::optional<
            std::uint64_t> const&, error_code& ec)
        {
            ec = {};
        }

        template<class ConstBufferSequence>
        std::size_t
        put(ConstBufferSequence const& buffers,
            error_code& ec)
        {
            auto const n = buffer_bytes(buffers);
            if(beast::detail::sum_exceeds(body_.size(), n, body_.max_size()))
            {
                ec = error::buffer_overflow;
                return 0;
            }
            auto const mb =
                beast::detail::dynamic_buffer_prepare(
                    body_, (std::min)(n,
                        body_.max_size() - body_.size()),
                            ec, error::buffer_overflow);
            if(ec)
                return 0;
            auto const bytes_transferred =
                net::buffer_copy(*mb, buffers);
            body_.commit(bytes_transferred);
            return bytes_transferred;
        }

        void
        finish(error_code& ec)
        {
            ec = {};
        }
    };
#endif

    /** The algorithm for serializing the body

        Meets the requirements of <em>BodyWriter</em>.
    */
#if BOOST_BEAST_DOXYGEN
    using writer = __implementation_defined__;
#else
    class writer
    {
        DynamicBuffer const& body_;

    public:
        using const_buffers_type =
            typename DynamicBuffer::const_buffers_type;

        template<bool isRequest, class Fields>
        explicit
        writer(header<isRequest, Fields> const&, value_type const& b)
            : body_(b)
        {
        }

        void
        init(error_code& ec)
        {
            ec = {};
        }

        boost::optional<std::pair<const_buffers_type, bool>>
        get(error_code& ec)
        {
            ec = {};
            return {{body_.data(), false}};
        }
    };
#endif
};

} // http
} // beast
} // boost

#endif

/* basic_dynamic_body.hpp
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
*/