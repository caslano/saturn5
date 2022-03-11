//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_SPAN_BODY_HPP
#define BOOST_BEAST_HTTP_SPAN_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/span.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {
namespace http {

/** A <em>Body</em> using @ref span

    This body uses @ref span as a memory-based container for
    holding message payloads. The container represents a
    non-owning reference to a contiguous area of memory.
    Messages using this body type may be serialized and
    parsed.

    Unlike @ref buffer_body, only one buffer may be provided
    during a parse or serialize operation.
*/
template<class T>
struct span_body
{
private:
    static_assert(std::is_pod<T>::value,
        "POD requirements not met");

public:
    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    using value_type = span<T>;

    /** Returns the payload size of the body

        When this body is used with @ref message::prepare_payload,
        the Content-Length will be set to the payload size, and
        any chunked Transfer-Encoding will be removed.
    */
    static
    std::uint64_t
    size(value_type const& body)
    {
        return body.size();
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
            std::uint64_t> const& length, error_code& ec)
        {
            if(length && *length > body_.size())
            {
                ec = error::buffer_overflow;
                return;
            }
            ec = {};
        }

        template<class ConstBufferSequence>
        std::size_t
        put(ConstBufferSequence const& buffers,
            error_code& ec)
        {
            auto const n = buffer_bytes(buffers);
            auto const len = body_.size();
            if(n > len)
            {
                ec = error::buffer_overflow;
                return 0;
            }
            ec = {};
            net::buffer_copy(net::buffer(
                body_.data(), n), buffers);
            body_ = value_type{
                body_.data() + n, body_.size() - n};
            return n;
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
        value_type const& body_;

    public:
        using const_buffers_type =
            net::const_buffer;

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
            return {{
                { body_.data(),
                  body_.size() * sizeof(typename
                    value_type::value_type)},
                false}};
        }
    };
#endif
};

} // http
} // beast
} // boost

#endif

/* span_body.hpp
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
*/