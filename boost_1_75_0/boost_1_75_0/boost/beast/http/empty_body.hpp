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
nwaiClqMRToGOxMVXnQMljwStRCLF4rSOJFCLJ58CzH0NhGyYYzF2TzG4s2l9sJjvkwe3rBXAlUTOlbqLKxlB1//a4uihEJV9/Sg2Cq1vj+I/HZH7e5Fft41LRHgVkO9BJJ8f2bnbbhETaKhLtJn5Jnl6snc5BXztiz1Zqy/3mBqdzPWQywNjySrh5Fn1aWoh5G3fa33f5xmjD4rndmpdi+N0e4F7dsN1YbbPaVr96Wp7dotmdSZdv9xfft2n72+XbuLdO0e17V7eft2N03sTLvXxmh3QPt2f3433O5Xuna33KzFGtaf5007p9pBVQ7p5s2xzvPqy3jalRnwm2UeaVfmhzd+q0xjuzI72pcJ80vugGgVA2JUfMnUYejJP6LECYIBsuHx3XjgaRZZ+LiLRTMvZm7Czj0Zqhf14muMWHA2FrwKCr7XNaLg311GFhhq2z2ak/G4cOl8KM0CV35LMLdte0LLtmYYGTnFwFKQe9MfuJwdpbqMRa2EldkDFXfBMUb5jbcVZd15YlU+1ZasizvGZQ2MGDagTtt0yngYMt3xk7ZCOglTjHEyKIDd55gQWARjMEHk/m7pPw7hHt1vC/oDFV3ZLXweMYAxOONRApvGD4CBWJ+zGgMhwqhMw0s65JmTjELIZvfXK6UOds6NRSu1hm8+KSafGX7tSUVRaQFIIxh+hPvhv30du4Mj+ijD365jRxl4UK3Jr4eD
*/