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
g2FLr0zjR3XD+71IfqjPE0FJvAfVhLRakYNcM42FeM2Vb41jV2/cTxLOKJv0+Gzu6ZqLmtSngAQSq3AXIssiUUrCgHhBSzczyq8NyDFV3EabHQJx8bQILkJsx0XQSd6BB6N2nPDBOTGLbSzlF7KYA1nq5nN5FovRfiHDLfSdwnimlqkZqULzrgRBPetr9e9VWsw7bzL6QwYfXUZjckuG4ASDHQ++q249+wh7IJ/dqFRr8Stz0UNUdKJ7v5vd7GlFL6kj8o3HkFhLWRqxfvMDRP7nsxjN2ktyVXPjZ0YhbK+GITffZRLq7Ebm02WQPmlR0uWx6Lp7Rm48o9qxywzMjn3rB9F2bNUnKhOn75/l3IHjiO9CVKcgHEBWDTwWbz6IZqqnVAQOP/X1+XDYd3OMYG5GeSwTTK7XSILz5s6g8bgDEWgM0/Vyjwj+ldEC3R716/GwnMFdy3OJjW0EmtCILR+6qb1sgZcX8SiqXwKkO9CvDHk/ii+wFQdU/olAaeNBjUcZ4V8W/APkH5UPz0z4B9lH5a6ZmU+b7QG2SKajxjWQ3KIk3lBkpthiOaHMvKOSVztA5GVnRyexu3Jhe1YsuZPIr2yQYuk9Cf3KWlY1qH5lLZWtd3cTw57ZMFGuQO9Qj9pR+QbpR1fgeo0Z/KpYPQPfXn6o1eSHkw3hDY/bJr7S/Bk1nE5jON2hHQL5r+BdwJTcQu52/ucyiVwd
*/