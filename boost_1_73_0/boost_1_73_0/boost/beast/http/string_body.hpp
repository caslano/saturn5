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
tjnNFSck0zBilLF8+oY+bW6i87sOUAZhAKSrT5iR4/tsc7OgxYdK/Jq3O8zshSHrxdpi1vHDPIQFbm8xUkJFo7+5aixIPGJqL3a7ZRrhbavr840nQL6aGX0anP+0bckYISFFuR+pDbrXNffFjlzGqQluI7e0toGjOa9mFMvlmYZzFap2q3PWpVQqU+Y+fSMYC3yty9ODpEgxR4UqslS2Pb85O1v8+4ap1YfM4viUha+fvZ/H3FbzNRjfvHAlqaRft7G5LrekY2WuRX3YHWWmyPDdqgUeTOReN2Lnc6yTxrJzMYqQH0FJs2EyRThy1wqyYKY4/LqP61fz0e8Hp5V28VbCHpymbhGc4tSbWzuVCQwfMrdwpQi18BOUvsEoTkgr9CKpA5mFY1/osXDGKWL3q9K1nfvx6vt0NjCvNuiQAl/rgENO7snNQYEXcxdQ62hNGGGn7QUjxjc+pUH7mRWUzKzmyW0Lmiy5NebdM722NGVFszqGyojyyGYaN1COhGFIeVKQEznuJVlAnEhZXykisWwqbIHObv9rQsyshcsN6iQesYWXDcZ47VpRCuXiItw8wAsOcknP1x9HRxfnx+36DYTt5MEGwNLoVg28TUdFCdncrBZrMqUqxDDxRC/aXkIRDmInbpXLt/Zyg1Md
*/