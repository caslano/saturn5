//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_BUFFER_BODY_HPP
#define BOOST_BEAST_HTTP_BUFFER_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/type_traits.hpp>
#include <boost/optional.hpp>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** A <em>Body</em> using a caller provided buffer

    Messages using this body type may be serialized and parsed.
    To use this class, the caller must initialize the members
    of @ref buffer_body::value_type to appropriate values before
    each call to read or write during a stream operation.
*/
struct buffer_body
{
    /// The type of the body member when used in a message.
    struct value_type
    {
        /** A pointer to a contiguous area of memory of @ref size octets, else `nullptr`.

            @par When Serializing

            If this is `nullptr` and `more` is `true`, the error
            @ref error::need_buffer will be returned from @ref serializer::get
            Otherwise, the serializer will use the memory pointed to
            by `data` having `size` octets of valid storage as the
            next buffer representing the body.

            @par When Parsing

            If this is `nullptr`, the error @ref error::need_buffer
            will be returned from @ref parser::put. Otherwise, the
            parser will store body octets into the memory pointed to
            by `data` having `size` octets of valid storage. After
            octets are stored, the `data` and `size` members are
            adjusted: `data` is incremented to point to the next
            octet after the data written, while `size` is decremented
            to reflect the remaining space at the memory location
            pointed to by `data`.
        */
        void* data = nullptr;

        /** The number of octets in the buffer pointed to by @ref data.

            @par When Serializing

            If `data` is `nullptr` during serialization, this value
            is ignored. Otherwise, it represents the number of valid
            body octets pointed to by `data`.

            @par When Parsing

            The value of this field will be decremented during parsing
            to indicate the number of remaining free octets in the
            buffer pointed to by `data`. When it reaches zero, the
            parser will return @ref error::need_buffer, indicating to
            the caller that the values of `data` and `size` should be
            updated to point to a new memory buffer.
        */
        std::size_t size = 0;

        /** `true` if this is not the last buffer.

            @par When Serializing
            
            If this is `true` and `data` is `nullptr`, the error
            @ref error::need_buffer will be returned from @ref serializer::get

            @par When Parsing

            This field is not used during parsing.
        */
        bool more = true;
    };

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
        init(boost::optional<std::uint64_t> const&, error_code& ec)
        {
            ec = {};
        }

        template<class ConstBufferSequence>
        std::size_t
        put(ConstBufferSequence const& buffers,
            error_code& ec)
        {
            if(! body_.data)
            {
                ec = error::need_buffer;
                return 0;
            }
            auto const bytes_transferred =
                net::buffer_copy(net::buffer(
                    body_.data, body_.size), buffers);
            body_.data = static_cast<char*>(
                body_.data) + bytes_transferred;
            body_.size -= bytes_transferred;
            if(bytes_transferred == buffer_bytes(buffers))
                ec = {};
            else
                ec = error::need_buffer;
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
        bool toggle_ = false;
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

        boost::optional<
            std::pair<const_buffers_type, bool>>
        get(error_code& ec)
        {
            if(toggle_)
            {
                if(body_.more)
                {
                    toggle_ = false;
                    ec = error::need_buffer;
                }
                else
                {
                    ec = {};
                }
                return boost::none;
            }
            if(body_.data)
            {
                ec = {};
                toggle_ = true;
                return {{const_buffers_type{
                    body_.data, body_.size}, body_.more}};
            }
            if(body_.more)
                ec = error::need_buffer;
            else
                ec = {};
            return boost::none;
        }
    };
#endif
};

#if ! BOOST_BEAST_DOXYGEN
// operator<< is not supported for buffer_body
template<bool isRequest, class Fields>
std::ostream&
operator<<(std::ostream& os, message<isRequest,
    buffer_body, Fields> const& msg) = delete;
#endif

} // http
} // beast
} // boost

#endif

/* buffer_body.hpp
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
*/