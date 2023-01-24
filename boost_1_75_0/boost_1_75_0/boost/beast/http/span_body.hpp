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
sVlr7ZmGGpbmZWkiptF5N8meJY2HNkQYnYQPavCrZDPWaOecH79EPa/cusvgNdF8ybeuZKeRGYwRsQ+3XKLGPoxoCuOEsS+sGsQduWdENRRnjSnxtVCJIsVc05+B2kold2LJYPpoqtKYt2eNCMtWzKJTPcXGCLig5UVRfcjEKp5d0b4PkHdJVF5qbmFEXhVOk06bQndrBxMLWB95HsmeGUor9GQtzBjkUTVz3i6hk6iVg+0mmFBP5ZjC6Oxu3XqNulfnpqy8VpGFrQUWPsm/NMu6kIWfziW6MyoLr2JOEgMzM4HjwxGQlmSJgUUUth8vBMBLakYwTWDr+8mCMiJLGWXs4Loa9PW76YsM1cdv8WP/Gx8/djcz273I5QMtdG88rLl8FNExV6YF6qRLnzswp4V59LWEPfoWkf/2/yPvTeCbqLbH8UnTNEm3FCFSF7Ro1Sou1aKvtaINpJBCAhUEqyzWhyIqKEIjRUGWtNA4BOqCIorWhwsoCD5RVqWVpVWWsigU9Wndp1YUlwdFhPnfc869M5M0hfp8/r7v8/l/PpTJ3Hvnrueee+5Zb1fYFf72RqN23eBGtRI8vPYAdp+/qHW+olaWcldrV+GxZcj7Sq208bwY1LbL/2qUO+f2xpLTde26xaBtlyq0d5sX6TlLHNinnayinRi/zgUqcVOUVop3w3eC3t3wbULvbp9y/bZoWndXCq274Dt0CQdz
*/