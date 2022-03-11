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