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
2JygbOld8Tfs6Q2ynTeV3fzvtplvaXt5NMext418CPrYBNBsUBVoGegZ0Meg2N8SjK6gkaBy0DzQItDy36J27+gW3aJb+BYLOvrvtv+XTZmEf/2zDwnMmHpsTm52vuUN0DS+AFX9LZu8fQBD5QjMnmi9R4cdWGz2RQ6bfbGpyWXWW9l9bSW+7L7DqLdGo7c0XK86Ob829mGczymP5RptMZiDAb5k5/zoLMcI0x/BPkS5nVRM1S9SXhqjmdch/0A1r/OTlA+JCZahvZtVHqab56F8nprH3Cjlu2Lq5nmmVkwn/56KP0fNC30r5TsVP944IVA3L2R2kVhdqX9E5ukm4YLr5lnXi3ytkk80ZlZMA7bnPN5LIt/S7IivkQ8wq99R9pvGetl/nDncaItZ5Il4l82EpXy6kYZ0Bq3t70Th+R59cAX8yHvJPbhZWnZ2hZWAgHP9KhbsWby0j0G/HEsq9vqbNI75OUAau6U7t0JhMLdCE8bk4jbLvhatJ2EicZ2MweMqZs6om7+8WWTlWqXP7sI+mxHH7wfaSXJBba354O66PovHyvQ5gfrWJTtDZDPZj21dKcqOsYfkqGjc3KtzvOVxMC9qhu9zYpo13rTnDouPfh6Vcjmqv34r5YRmGvsP+UeyjIwgPRlTHGoPYv/+WvibN6N9iPL9Qu1C0q/3VPWdmh0Az+31+GKKi9nFSGrWwmgv9RjZPaz6K2NGGD3Nq8wPjbBxxXGTK3wJyia/jucxFvs044Bzx6JrUrnDlvKlyG4r92SOVe14JiQDO/UMztMmS9k+x/kxCcaxMZJDje3/TZLktZC/Z6YF/94tk7m0fI6flujv4oNkHVP6S1zrhODfXYt379/f4L7Xsux9OYPsfdfW7cu397Wt25dr79vUQ+3Llj6PfdVq3yApX6vKA6WcpMp5evu0hz2u0sMet8Blj4s8nhcy999Y5sjJNxmTnek9JpS1Rz8uKJuj+vGeUk5x+R1YGvg7RP5+qs/sLuXblb1tdGeOEyVPewn761jhf8aYypw7JUpnb/KYxn1SvgpvKCd42ofaA4uEJ9OkvYg6ssLHCcfFrjxPKavz7OI5RjJQ6o6cUVa+y42Y/97LyhlV+Wh8fIu42PiYFunN42OadY5PahE70BD5p+V4vM+8pk/keKdLPqhtMDZMA3p85ufJ9pGfh78X0jZu/wfeb/avsPUNPfqX8p9jvrl7cLJtgbeYXHu0o6N/+ViDVvgxK5UmZbRKJ8mDgxff1kYt+lqceaB+HdKObj+JjiJbZAbLeNpkMJ+Ao38GHL9P2wr/bJPtQH3prKc87VWu9x72/3SRP0Pk91TyvcPbmb8jicJ/oCllpb+jsY16hk5XPgOthPcao72UkSFCyj8gY9EQxOvsBj7KWO9GHDPTIHeS8F2C74fTRdc0yLaT4xyP8i7SRy4TnhZmnQ78IOb2F/4Zlp3UqsdRkh127RllR85y2tLvEp5DWLbPrxl/2+W9CeTP96MxfjsB1W+d7z7uPrqWfgrfgOJB79DGvWIHRx9VDz5tHyX/GCOZfXRnaecA5kyzsc/uW3NmVcykHvZPyHGtZJQdcs2NvXU2b8pcqtZavUJk2mpt3+CnTRtlxzEyjcHyfMoyvJ87e0H2OZH9RPNt484zlORsI+bvSlXtoa6dz43w50uW8/myhXMSeNsT/z32UO+cCn+/PXQnsYfefuSJmy5dHlj0TMqs3Pi9x7X679pDnTkJ9mJOgm4qJwHnHjQx3+fRHng+7YFVzhj6euQeYyz844yFf4KxpsvVd7XMI4hcHvNuGYyBzqJdtQ/tnbsBXwTuxdjzKsaeLwauoh3rFdpbXqVdcTXtam8w1vFN4Go=
*/