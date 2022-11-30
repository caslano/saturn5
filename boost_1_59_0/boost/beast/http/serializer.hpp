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
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
*/