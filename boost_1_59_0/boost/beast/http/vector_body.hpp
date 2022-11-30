//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_VECTOR_BODY_HPP
#define BOOST_BEAST_HTTP_VECTOR_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional.hpp>
#include <cstdint>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** A <em>Body</em> using `std::vector`

    This body uses `std::vector` as a memory-based container
    for holding message payloads. Messages using this body type
    may be serialized and parsed.
*/
template<class T, class Allocator = std::allocator<T>>
struct vector_body
{
private:
    static_assert(sizeof(T) == 1,
        "T requirements not met");

public:
    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    using value_type = std::vector<T, Allocator>;

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
            if(length)
            {
                if(*length > body_.max_size())
                {
                    ec = error::buffer_overflow;
                    return;
                }
                body_.reserve(beast::detail::clamp(*length));
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
            if (n > body_.max_size() - len)
            {
                ec = error::buffer_overflow;
                return 0;
            }

            body_.resize(len + n);
            ec = {};
            return net::buffer_copy(net::buffer(
                &body_[0] + len, n), buffers);
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
            return {{const_buffers_type{
                body_.data(), body_.size()}, false}};
        }
    };
#endif
};

} // http
} // beast
} // boost

#endif

/* vector_body.hpp
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
*/