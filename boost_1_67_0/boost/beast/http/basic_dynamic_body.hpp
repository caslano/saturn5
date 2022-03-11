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