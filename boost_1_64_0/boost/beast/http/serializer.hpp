//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_SERIALIZER_HPP
#define BOOST_BEAST_HTTP_SERIALIZER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffers_cat.hpp>
#include <boost/beast/core/buffers_prefix.hpp>
#include <boost/beast/core/buffers_suffix.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/detail/variant.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/chunk_encode.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {
namespace http {

/** Provides buffer oriented HTTP message serialization functionality.

    An object of this type is used to serialize a complete
    HTTP message into a sequence of octets. To use this class,
    construct an instance with the message to be serialized.
    The implementation will automatically perform chunk encoding
    if the contents of the message indicate that chunk encoding
    is required.

    Chunked output produced by the serializer never contains chunk
    extensions or trailers, and the location of chunk boundaries
    is not specified. If callers require chunk extensions, trailers,
    or control over the exact contents of each chunk they should
    use the serializer to write just the message header, and then
    assume control over serializing the chunked payload by using
    the chunk buffer sequence types @ref chunk_body, @ref chunk_crlf,
    @ref chunk_header, and @ref chunk_last.

    @tparam isRequest `true` if the message is a request.

    @tparam Body The body type of the message.

    @tparam Fields The type of fields in the message.
*/
template<
    bool isRequest,
    class Body,
    class Fields = fields>
class serializer
{
public:
    static_assert(is_body<Body>::value,
        "Body type requirements not met");

    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");

    /** The type of message this serializer uses

        This may be const or non-const depending on the
        implementation of the corresponding <em>BodyWriter</em>.
    */
#if BOOST_BEAST_DOXYGEN
    using value_type = __implementation_defined__;
#else
    using value_type = typename std::conditional<
        std::is_constructible<typename Body::writer,
            header<isRequest, Fields>&,
            typename Body::value_type&>::value &&
        ! std::is_constructible<typename Body::writer,
            header<isRequest, Fields> const&,
            typename Body::value_type const&>::value,
        message<isRequest, Body, Fields>,
        message<isRequest, Body, Fields> const>::type;
#endif

private:
    enum
    {
        do_construct        =   0,

        do_init             =  10,
        do_header_only      =  20,
        do_header           =  30,
        do_body             =  40,
        
        do_init_c           =  50,
        do_header_only_c    =  60,
        do_header_c         =  70,
        do_body_c           =  80,
        do_final_c          =  90,
    #ifndef BOOST_BEAST_NO_BIG_VARIANTS
        do_body_final_c     = 100,
        do_all_c            = 110,
    #endif

        do_complete         = 120
    };

    void fwrinit(std::true_type);
    void fwrinit(std::false_type);

    template<std::size_t, class Visit>
    void
    do_visit(error_code& ec, Visit& visit);

    using writer = typename Body::writer;

    using cb1_t = buffers_suffix<typename
        Fields::writer::const_buffers_type>;        // header
    using pcb1_t  = buffers_prefix_view<cb1_t const&>;

    using cb2_t = buffers_suffix<buffers_cat_view<
        typename Fields::writer::const_buffers_type,// header
        typename writer::const_buffers_type>>;      // body
    using pcb2_t = buffers_prefix_view<cb2_t const&>;

    using cb3_t = buffers_suffix<
        typename writer::const_buffers_type>;       // body
    using pcb3_t = buffers_prefix_view<cb3_t const&>;

    using cb4_t = buffers_suffix<buffers_cat_view<
        typename Fields::writer::const_buffers_type,// header
        detail::chunk_size,                         // chunk-size
        net::const_buffer,                          // chunk-ext
        chunk_crlf,                                 // crlf
        typename writer::const_buffers_type,        // body
        chunk_crlf>>;                               // crlf
    using pcb4_t = buffers_prefix_view<cb4_t const&>;

    using cb5_t = buffers_suffix<buffers_cat_view<
        detail::chunk_size,                         // chunk-header
        net::const_buffer,                          // chunk-ext
        chunk_crlf,                                 // crlf
        typename writer::const_buffers_type,        // body
        chunk_crlf>>;                               // crlf
    using pcb5_t = buffers_prefix_view<cb5_t const&>;

    using cb6_t = buffers_suffix<buffers_cat_view<
        detail::chunk_size,                         // chunk-header
        net::const_buffer,                          // chunk-size
        chunk_crlf,                                 // crlf
        typename writer::const_buffers_type,        // body
        chunk_crlf,                                 // crlf
        net::const_buffer,                          // chunk-final
        net::const_buffer,                          // trailers 
        chunk_crlf>>;                               // crlf
    using pcb6_t = buffers_prefix_view<cb6_t const&>;

    using cb7_t = buffers_suffix<buffers_cat_view<
        typename Fields::writer::const_buffers_type,// header
        detail::chunk_size,                         // chunk-size
        net::const_buffer,                          // chunk-ext
        chunk_crlf,                                 // crlf
        typename writer::const_buffers_type,        // body
        chunk_crlf,                                 // crlf
        net::const_buffer,                          // chunk-final
        net::const_buffer,                          // trailers 
        chunk_crlf>>;                               // crlf
    using pcb7_t = buffers_prefix_view<cb7_t const&>;

    using cb8_t = buffers_suffix<buffers_cat_view<
        net::const_buffer,                          // chunk-final
        net::const_buffer,                          // trailers 
        chunk_crlf>>;                               // crlf
    using pcb8_t = buffers_prefix_view<cb8_t const&>;

    value_type& m_;
    writer wr_;
    boost::optional<typename Fields::writer> fwr_;
    beast::detail::variant<
        cb1_t, cb2_t, cb3_t, cb4_t,
        cb5_t ,cb6_t, cb7_t, cb8_t> v_;
    beast::detail::variant<
        pcb1_t, pcb2_t, pcb3_t, pcb4_t,
        pcb5_t ,pcb6_t, pcb7_t, pcb8_t> pv_;
    std::size_t limit_ =
        (std::numeric_limits<std::size_t>::max)();
    int s_ = do_construct;
    bool split_ = false;
    bool header_done_ = false;
    bool more_ = false;

public:
    /// Constructor
    serializer(serializer&&) = default;

    /// Constructor
    serializer(serializer const&) = default;

    /// Assignment
    serializer& operator=(serializer const&) = delete;

    /** Constructor

        The implementation guarantees that the message passed on
        construction will not be accessed until the first call to
        @ref next. This allows the message to be lazily created.
        For example, if the header is filled in before serialization.

        @param msg A reference to the message to serialize, which must
        remain valid for the lifetime of the serializer. Depending on
        the type of Body used, this may or may not be a `const` reference.

        @note This function participates in overload resolution only if
        Body::writer is constructible from a `const` message reference.
    */
    explicit
    serializer(value_type& msg);

    /// Returns the message being serialized
    value_type&
    get()
    {
        return m_;
    }

    /// Returns the serialized buffer size limit
    std::size_t
    limit()
    {
        return limit_;
    }

    /** Set the serialized buffer size limit

        This function adjusts the limit on the maximum size of the
        buffers passed to the visitor. The new size limit takes effect
        in the following call to @ref next.

        The default is no buffer size limit.

        @param limit The new buffer size limit. If this number
        is zero, the size limit is removed.
    */
    void
    limit(std::size_t limit)
    {
        limit_ = limit > 0 ? limit :
            (std::numeric_limits<std::size_t>::max)();
    }

    /** Returns `true` if we will pause after writing the complete header.
    */
    bool
    split()
    {
        return split_;
    }

    /** Set whether the header and body are written separately.

        When the split feature is enabled, the implementation will
        write only the octets corresponding to the serialized header
        first. If the header has already been written, this function
        will have no effect on output.
    */
    void
    split(bool v)
    {
        split_ = v;
    }

    /** Return `true` if serialization of the header is complete.

        This function indicates whether or not all buffers containing
        serialized header octets have been retrieved.
    */
    bool
    is_header_done()
    {
        return header_done_;
    }

    /** Return `true` if serialization is complete.

        The operation is complete when all octets corresponding
        to the serialized representation of the message have been
        successfully retrieved.
    */
    bool
    is_done()
    {
        return s_ == do_complete;
    }

    /** Returns the next set of buffers in the serialization.

        This function will attempt to call the `visit` function
        object with a <em>ConstBufferSequence</em> of unspecified type
        representing the next set of buffers in the serialization
        of the message represented by this object. 

        If there are no more buffers in the serialization, the
        visit function will not be called. In this case, no error
        will be indicated, and the function @ref is_done will
        return `true`.

        @param ec Set to the error, if any occurred.

        @param visit The function to call. The equivalent function
        signature of this object must be:
        @code
            template<class ConstBufferSequence>
            void visit(error_code&, ConstBufferSequence const&);
        @endcode
        The function is not copied, if no error occurs it will be
        invoked before the call to @ref next returns.

    */
    template<class Visit>
    void
    next(error_code& ec, Visit&& visit);

    /** Consume buffer octets in the serialization.

        This function should be called after one or more octets
        contained in the buffers provided in the prior call
        to @ref next have been used.

        After a call to @ref consume, callers should check the
        return value of @ref is_done to determine if the entire
        message has been serialized.

        @param n The number of octets to consume. This number must
        be greater than zero and no greater than the number of
        octets in the buffers provided in the prior call to @ref next.
    */
    void
    consume(std::size_t n);

    /** Provides low-level access to the associated <em>BodyWriter</em>

        This function provides access to the instance of the writer
        associated with the body and created by the serializer
        upon construction. The behavior of accessing this object
        is defined by the specification of the particular writer
        and its associated body.

        @return A reference to the writer.
    */
    writer&
    writer_impl()
    {
        return wr_;
    }
};

/// A serializer for HTTP/1 requests
template<class Body, class Fields = fields>
using request_serializer = serializer<true, Body, Fields>;

/// A serializer for HTTP/1 responses
template<class Body, class Fields = fields>
using response_serializer = serializer<false, Body, Fields>;

} // http
} // beast
} // boost

#include <boost/beast/http/impl/serializer.hpp>

#endif

/* serializer.hpp
2KnVp3FOUe7csgbSJ+FjVd51UfVaBZN2wPE/7LTZeYdtzivbnvZ5TVxg3qVZzwyadGl+67Tpq7PzBp1klX/e4PksZ1rmXrv2CPOyi6Q3WeVl0Gt50r+iRWC+voRN42Vt+q0JOlTKJapdayB/xU6sq912QkoeWzpHlsdSfqVddex72p2CloH5/DJ24nXplOcEfdokrLQ7rVTeWkEkL5X/keWlXXaxzXll29PuTGoVPO9S60nTIus3Z255QUP5lhqQb76g7t/o1KOab2Lfr3xOig9ePzP0aSxrTP3Ejl/9lOCa+plxhHnqrZ9Br+XMDSgwdWPHurFy3Ri3bky58WPc4+ep82s63nfywZ4vFH/8RHrlrOOa68boj96axJo5A5qxe93cCd0Yt2etYtUvUQUTEBkbkf4L1T+i/JyxERnLQIxOMtbcBS6B3aAdfq2ETw0SvqeMrfSCbWWMo7247bHAWgnfRMK7xwIvleX0fgstu5e5wtXVE26FhLtJwv3eFc7Yqg+3VML9RsJd7AoXX0+45RLuOgnnHutMrSfcQgm3SMItdsIh9YS7SsJdLeGWucbisiTcKRLOPRbXWsa2EmB/GbsaLGNXJ8AkOAy2hSNgijufxW6zIPn8a4nPdInPaTAWnu4KX1NP+PMkfJGEL5bw813ht9UTfpKEnyzhp0j4U9xjgBI+Nkj4/hJ+AIyUscMYeLwrfF09158t4fPk+vly/Tmu8MbL+usPkfAnyPVPlOsPdcLLb67m+qMk/Gi5/hi5/smu8Kna60MJ31eu30+uf5wrfEY91z9bws+U658j159lqLXZ/Nc+cNY92KRf66DBdQ7+zd55wFdRpAF8970AAQKEACGBBEIPEDCUUKMEpDfpHZNAiIkEEpLQBCQISEdARJCAIAioVAXBRlH0UFEROU8RFRUVPVT0ELGd9995325ehaBY7u7tj49/pu7s7Oy8nfm+nfGyxoG3tQ0ut65Bodc0QA/nvIbBr16/wPfaBS7rFrivWYB+inTol84ggZX4bh8ZhsxFnkbOIGGV+d4fSUOWIE8jZ5CwCNY4QLKQ/Ai/jsp/+A//4T/8h//wH1c+/oDv/0cmJmdkpFyj7/93RmnW3G6+Lu/3sBSsC7cQkveymmORQiYmp6QYJUhU6xCofbtyGXOiN6lKmkfJ7zFkt7A3skf+zgoXP5HHxX8v4uyvRYh/JQf3SfgTwieFjUIdbKF4Zf22OZ9yzPbnfTtxreY7fu9vJLzPN/15305MVfNNN1fs+e+lM2fGzV16cXn+pYisv943EvX6Gv6JSydsTDk2dn/TyFfv3Hfijea+vu25dt9UONaclmdVnuGduuua0yEyv1QeVoIVYR0YBtvAcNgdVoaDYQQcByPhPFhVbHCrQ7X3MXwK1oRvwNrwNKwDv4DR8AdYV2yu68PysCGsBq+DdWEj2EDcub/Cltd9rLw8u4gvW97fzY63wIb319vv7ssu8rvb8J7KLnLN7Hh/rQ2vD/vd/zrb3f8Vu925kf55Dv/hP/yH//Af/uO3HH/U+H/kNRr/3+g0/o8W49RpxWUPNriFkHUHvI3/xTpMxv+lA1hDwtgvg/w6Ip2EnYVdhF2F3YTdhT2EPYU3CXsJe4v0cXP3FXc/N//+4h7g5j/Qzf1tWIF7kIQNFg4RDhUOEw4X3uyWV6K4k4TJwhFu8UaKO0U4SpgqvEWYZqXzlHQJu1U4WpjhJc0Y8RsrzBRm+ch/nPhnC3OEucLxwgnCicJJwsnC24RThBed6nqq27mnift24XRhnnCG8A7hTOEs4WzhncLvnM41x+1cc8U9TzhfuEC4ULhIuFh4l3CJcKlwmfCS0znvdjvncnHfI1w=
*/