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
BJ1kNdyYmvbaeIP8HaWsGADZNt/XTocMKO+ln7threwZ2Gvisduq5dR1bFHBvM0xUuX+GqmNm0Uy7YtFBKEX0NefqxFbT0Jm+uILJnJNrI7maCfCkF1xIlLAEpG5xHWn7rwWvka03bKkyOsFjzfypmMUKmfxRQGpjTQZiXtGDJ/6zkS7ICIg9czJixAx7DSLfsNLfFGgqk3XC5HZXNMx8IHWKpmp5j5DiQ/0QP7e4pKus0trYuaJSaVZ5M4C7ku2tq0P8JWAka2tqL86OR7+v3d14bw2wmyI1Va1vNVlLbLmY6xILYYsWpxjJyFOyE15ytZXNAU4dktb3cMKnua395bXc/Oia8XU0LOblk+4srHKFTW7edat5sIVBWo7O/oKrBgKwWVpM2e5smN6ypKli41Vw+q6rWuJTZSSSvJDCe8dn7PU+YW/VpioBMknSO3d+UoWjbzFlGKcbQksc+L6QR+yftLniiftQ7VLJHD86cA49PDi1wrElcbzERcPXKnvmLSPr/ttbjehYjmC1wbwyuKLGN7keXzVziYiBHN9C2OcGy3mXe7CbCXMXIcW7pDduk23QqeKAnYbn4bsDW23qN1uY47XF9bYNy+nRjC32w6YU5Pl8hcraXmEcYJgy4hhm9NccIoyt4thWMjp
*/