//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_EMPTY_BODY_HPP
#define BOOST_BEAST_HTTP_EMPTY_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {
namespace http {

/** An empty <em>Body</em>

    This body is used to represent messages which do not have a
    message body. If this body is used with a parser, and the
    parser encounters octets corresponding to a message body,
    the parser will fail with the error @ref http::unexpected_body.

    The Content-Length of this body is always 0.
*/
struct empty_body
{
    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    struct value_type
    {
    };

    /** Returns the payload size of the body

        When this body is used with @ref message::prepare_payload,
        the Content-Length will be set to the payload size, and
        any chunked Transfer-Encoding will be removed.
    */
    static
    std::uint64_t
    size(value_type)
    {
        return 0;
    }

    /** The algorithm for parsing the body

        Meets the requirements of <em>BodyReader</em>.
    */
#if BOOST_BEAST_DOXYGEN
    using reader = __implementation_defined__;
#else
    struct reader
    {
        template<bool isRequest, class Fields>
        explicit
        reader(header<isRequest, Fields>&, value_type&)
        {
        }

        void
        init(boost::optional<std::uint64_t> const&, error_code& ec)
        {
            ec = {};
        }

        template<class ConstBufferSequence>
        std::size_t
        put(ConstBufferSequence const&,
            error_code& ec)
        {
            ec = error::unexpected_body;
            return 0;
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
    struct writer
    {
        using const_buffers_type =
            net::const_buffer;

        template<bool isRequest, class Fields>
        explicit
        writer(header<isRequest, Fields> const&, value_type const&)
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
            return boost::none;
        }
    };
#endif
};

} // http
} // beast
} // boost

#endif

/* empty_body.hpp
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
*/