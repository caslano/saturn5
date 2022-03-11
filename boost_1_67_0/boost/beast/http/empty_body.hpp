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