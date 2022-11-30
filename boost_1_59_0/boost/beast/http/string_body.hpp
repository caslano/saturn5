//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_STRING_BODY_HPP
#define BOOST_BEAST_HTTP_STRING_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/core/buffers_range.hpp>
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

/** A <em>Body</em> using `std::basic_string`

    This body uses `std::basic_string` as a memory-based container
    for holding message payloads. Messages using this body type
    may be serialized and parsed.
*/
template<
    class CharT,
    class Traits = std::char_traits<CharT>,
    class Allocator = std::allocator<CharT>>
struct basic_string_body
{
private:
    static_assert(
        std::is_integral<CharT>::value &&
            sizeof(CharT) == 1,
        "CharT requirements not met");

public:
    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    using value_type =
        std::basic_string<CharT, Traits, Allocator>;

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
            auto const extra = buffer_bytes(buffers);
            auto const size = body_.size();
            if (extra > body_.max_size() - size)
            {
                ec = error::buffer_overflow;
                return 0;
            }

            body_.resize(size + extra);
            ec = {};
            CharT* dest = &body_[size];
            for(auto b : beast::buffers_range_ref(buffers))
            {
                Traits::copy(dest, static_cast<
                    CharT const*>(b.data()), b.size());
                dest += b.size();
            }
            return extra;
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

/// A <em>Body</em> using `std::string`
using string_body = basic_string_body<char>;

} // http
} // beast
} // boost

#endif

/* string_body.hpp
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
*/