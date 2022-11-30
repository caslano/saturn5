//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_CHUNK_ENCODE_HPP
#define BOOST_BEAST_HTTP_CHUNK_ENCODE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffers_cat.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/http/type_traits.hpp>
#include <boost/beast/http/detail/chunk_encode.hpp>
#include <boost/asio/buffer.hpp>
#include <memory>
#include <type_traits>

namespace boost {
namespace beast {
namespace http {

/** A chunked encoding crlf

    This implements a <em>ConstBufferSequence</em> holding the CRLF
    (`"\r\n"`) used as a delimiter in a @em chunk.

    To use this class, pass an instance of it to a
    stream algorithm as the buffer sequence:
    @code
        // writes "\r\n"
        net::write(stream, chunk_crlf{});
    @endcode

    @see https://tools.ietf.org/html/rfc7230#section-4.1
*/
struct chunk_crlf
{
    /// Constructor
    chunk_crlf() = default;

    //-----

    /// Required for <em>ConstBufferSequence</em>
#if BOOST_BEAST_DOXYGEN
    using value_type = __implementation_defined__;
#else
    using value_type = net::const_buffer;
#endif

    /// Required for <em>ConstBufferSequence</em>
    using const_iterator = value_type const*;

    /// Required for <em>ConstBufferSequence</em>
    chunk_crlf(chunk_crlf const&) = default;

    /// Required for <em>ConstBufferSequence</em>
    const_iterator
    begin() const
    {
        static net::const_buffer const cb{"\r\n", 2};
        return &cb;
    }

    /// Required for <em>ConstBufferSequence</em>
    const_iterator
    end() const
    {
        return begin() + 1;
    }
};

//------------------------------------------------------------------------------

/** A @em chunk header

    This implements a <em>ConstBufferSequence</em> representing the
    header of a @em chunk. The serialized format is as follows:
    @code
        chunk-header    = 1*HEXDIG chunk-ext CRLF       
        chunk-ext       = *( ";" chunk-ext-name [ "=" chunk-ext-val ] )
        chunk-ext-name  = token
        chunk-ext-val   = token / quoted-string
    @endcode
    The chunk extension is optional. After the header and
    chunk body have been serialized, it is the callers
    responsibility to also serialize the final CRLF (`"\r\n"`).

    This class allows the caller to emit piecewise chunk bodies,
    by first serializing the chunk header using this class and then
    serializing the chunk body in a series of one or more calls to
    a stream write operation.

    To use this class, pass an instance of it to a
    stream algorithm as the buffer sequence:
    @code
        // writes "400;x\r\n"
        net::write(stream, chunk_header{1024, "x"});
    @endcode

    @see https://tools.ietf.org/html/rfc7230#section-4.1
*/
class chunk_header
{
    using view_type = buffers_cat_view<
        detail::chunk_size,             // chunk-size
        net::const_buffer,   // chunk-extensions
        chunk_crlf>;                    // CRLF

    std::shared_ptr<
        detail::chunk_extensions> exts_;
    view_type view_;

public:
    /** Constructor

        This constructs a buffer sequence representing a
        @em chunked-body size and terminating CRLF (`"\r\n"`)
        with no chunk extensions.

        @param size The size of the chunk body that follows.
        The value must be greater than zero.

        @see https://tools.ietf.org/html/rfc7230#section-4.1
    */
    explicit
    chunk_header(std::size_t size);

    /** Constructor

        This constructs a buffer sequence representing a
        @em chunked-body size and terminating CRLF (`"\r\n"`)
        with provided chunk extensions.

        @param size The size of the chunk body that follows.
        The value must be greater than zero.

        @param extensions The chunk extensions string. This
        string must be formatted correctly as per rfc7230,
        using this BNF syntax:
        @code
            chunk-ext       = *( ";" chunk-ext-name [ "=" chunk-ext-val ] )
            chunk-ext-name  = token
            chunk-ext-val   = token / quoted-string
        @endcode
        The data pointed to by this string view must remain
        valid for the lifetime of any operations performed on
        the object.

        @see https://tools.ietf.org/html/rfc7230#section-4.1.1
    */
    chunk_header(
        std::size_t size,
        string_view extensions);

    /** Constructor

        This constructs a buffer sequence representing a
        @em chunked-body size and terminating CRLF (`"\r\n"`)
        with provided chunk extensions.
        The default allocator is used to provide storage for the
        extensions object.

        @param size The size of the chunk body that follows.
        The value must be greater than zero.

        @param extensions The chunk extensions object. The expression
        `extensions.str()` must be valid, and the return type must
        be convertible to @ref string_view. This object will be copied
        or moved as needed to ensure that the chunk header object retains
        ownership of the buffers provided by the chunk extensions object.

        @note This function participates in overload resolution only
        if @b ChunkExtensions meets the requirements stated above.

        @see https://tools.ietf.org/html/rfc7230#section-4.1
    */
    template<class ChunkExtensions
#if ! BOOST_BEAST_DOXYGEN
        , class = typename std::enable_if<
            detail::is_chunk_extensions<
                ChunkExtensions>::value>::type
#endif
    >
    chunk_header(
        std::size_t size,
        ChunkExtensions&& extensions);

    /** Constructor

        This constructs a buffer sequence representing a
        @em chunked-body size and terminating CRLF (`"\r\n"`)
        with provided chunk extensions.
        The specified allocator is used to provide storage for the
        extensions object.

        @param size The size of the chunk body that follows.
        The value be greater than zero.

        @param extensions The chunk extensions object. The expression
        `extensions.str()` must be valid, and the return type must
        be convertible to @ref string_view. This object will be copied
        or moved as needed to ensure that the chunk header object retains
        ownership of the buffers provided by the chunk extensions object.

        @param allocator The allocator to provide storage for the moved
        or copied extensions object.

        @note This function participates in overload resolution only
        if @b ChunkExtensions meets the requirements stated above.

        @see https://tools.ietf.org/html/rfc7230#section-4.1
    */
    template<class ChunkExtensions, class Allocator
#if ! BOOST_BEAST_DOXYGEN
        , class = typename std::enable_if<
            detail::is_chunk_extensions<
                ChunkExtensions>::value>::type
#endif
    >
    chunk_header(
        std::size_t size,
        ChunkExtensions&& extensions,
        Allocator const& allocator);

    //-----

    /// Required for <em>ConstBufferSequence</em>
#if BOOST_BEAST_DOXYGEN
    using value_type = __implementation_defined__;
#else
    using value_type = typename view_type::value_type;
#endif

    /// Required for <em>ConstBufferSequence</em>
#if BOOST_BEAST_DOXYGEN
    using const_iterator = __implementation_defined__;
#else
    using const_iterator = typename view_type::const_iterator;
#endif

    /// Required for <em>ConstBufferSequence</em>
    chunk_header(chunk_header const&) = default;

    /// Required for <em>ConstBufferSequence</em>
    const_iterator
    begin() const
    {
        return view_.begin();
    }

    /// Required for <em>ConstBufferSequence</em>
    const_iterator
    end() const
    {
        return view_.end();
    }
};

//------------------------------------------------------------------------------

/** A @em chunk

    This implements a <em>ConstBufferSequence</em> representing
    a @em chunk. The serialized format is as follows:
    @code
        chunk           = chunk-size [ chunk-ext ] CRLF chunk-data CRLF
        chunk-size      = 1*HEXDIG
        chunk-ext       = *( ";" chunk-ext-name [ "=" chunk-ext-val ] )
        chunk-ext-name  = token
        chunk-ext-val   = token / quoted-string
        chunk-data      = 1*OCTET ; a sequence of chunk-size octets
    @endcode
    The chunk extension is optional. 

    To use this class, pass an instance of it to a
    stream algorithm as the buffer sequence.

    @see https://tools.ietf.org/html/rfc7230#section-4.1
*/
template<class ConstBufferSequence>
class chunk_body
{
    using view_type = buffers_cat_view<
        detail::chunk_size,             // chunk-size
        net::const_buffer,   // chunk-extensions
        chunk_crlf,                     // CRLF
        ConstBufferSequence,            // chunk-body
        chunk_crlf>;                    // CRLF

    std::shared_ptr<
        detail::chunk_extensions> exts_;
    view_type view_;

public:
    /** Constructor

        This constructs buffers representing a complete @em chunk
        with no chunk extensions and having the size and contents
        of the specified buffer sequence.

        @param buffers A buffer sequence representing the chunk
        body. Although the buffers object may be copied as necessary,
        ownership of the underlying memory blocks is retained by the
        caller, which must guarantee that they remain valid while this
        object is in use.

        @see https://tools.ietf.org/html/rfc7230#section-4.1
    */
    explicit
    chunk_body(
        ConstBufferSequence const& buffers);

    /** Constructor

        This constructs buffers representing a complete @em chunk
        with the passed chunk extensions and having the size and
        contents of the specified buffer sequence.

        @param buffers A buffer sequence representing the chunk
        body. Although the buffers object may be copied as necessary,
        ownership of the underlying memory blocks is retained by the
        caller, which must guarantee that they remain valid while this
        object is in use.

        @param extensions The chunk extensions string. This
        string must be formatted correctly as per rfc7230,
        using this BNF syntax:
        @code
            chunk-ext       = *( ";" chunk-ext-name [ "=" chunk-ext-val ] )
            chunk-ext-name  = token
            chunk-ext-val   = token / quoted-string
        @endcode
        The data pointed to by this string view must remain
        valid for the lifetime of any operations performed on
        the object.

        @see https://tools.ietf.org/html/rfc7230#section-4.1.1
    */
    chunk_body(
        ConstBufferSequence const& buffers,
        string_view extensions);

    /** Constructor

        This constructs buffers representing a complete @em chunk
        with the passed chunk extensions and having the size and
        contents of the specified buffer sequence.
        The default allocator is used to provide storage for the
        extensions object.

        @param buffers A buffer sequence representing the chunk
        body. Although the buffers object may be copied as necessary,
        ownership of the underlying memory blocks is retained by the
        caller, which must guarantee that they remain valid while this
        object is in use.

        @param extensions The chunk extensions object. The expression
        `extensions.str()` must be valid, and the return type must
        be convertible to @ref string_view. This object will be copied
        or moved as needed to ensure that the chunk header object retains
        ownership of the buffers provided by the chunk extensions object.

        @note This function participates in overload resolution only
        if @b ChunkExtensions meets the requirements stated above.

        @see https://tools.ietf.org/html/rfc7230#section-4.1
    */
    template<class ChunkExtensions
#if ! BOOST_BEAST_DOXYGEN
        , class = typename std::enable_if<
            ! std::is_convertible<typename std::decay<
                ChunkExtensions>::type, string_view>::value>::type
#endif
    >
    chunk_body(
        ConstBufferSequence const& buffers,
        ChunkExtensions&& extensions);

    /** Constructor

        This constructs buffers representing a complete @em chunk
        with the passed chunk extensions and having the size and
        contents of the specified buffer sequence.
        The specified allocator is used to provide storage for the
        extensions object.

        @param buffers A buffer sequence representing the chunk
        body. Although the buffers object may be copied as necessary,
        ownership of the underlying memory blocks is retained by the
        caller, which must guarantee that they remain valid while this
        object is in use.

        @param extensions The chunk extensions object. The expression
        `extensions.str()` must be valid, and the return type must
        be convertible to @ref string_view. This object will be copied
        or moved as needed to ensure that the chunk header object retains
        ownership of the buffers provided by the chunk extensions object.

        @param allocator The allocator to provide storage for the moved
        or copied extensions object.

        @note This function participates in overload resolution only
        if @b ChunkExtensions meets the requirements stated above.

        @see https://tools.ietf.org/html/rfc7230#section-4.1
    */
    template<class ChunkExtensions, class Allocator
#if ! BOOST_BEAST_DOXYGEN
        , class = typename std::enable_if<
            ! std::is_convertible<typename std::decay<
                ChunkExtensions>::type, string_view>::value>::type
#endif
    >
    chunk_body(
        ConstBufferSequence const& buffers,
        ChunkExtensions&& extensions,
        Allocator const& allocator);

    //-----

    /// Required for <em>ConstBufferSequence</em>
#if BOOST_BEAST_DOXYGEN
    using value_type = __implementation_defined__;
#else
    using value_type = typename view_type::value_type;
#endif

    /// Required for <em>ConstBufferSequence</em>
#if BOOST_BEAST_DOXYGEN
    using const_iterator = __implementation_defined__;
#else
    using const_iterator = typename view_type::const_iterator;
#endif

    /// Required for <em>ConstBufferSequence</em>
    const_iterator
    begin() const
    {
        return view_.begin();
    }

    /// Required for <em>ConstBufferSequence</em>
    const_iterator
    end() const
    {
        return view_.end();
    }
};

//------------------------------------------------------------------------------

/** A chunked-encoding last chunk
*/
template<class Trailer = chunk_crlf>
class chunk_last
{
    static_assert(
        is_fields<Trailer>::value ||
        net::is_const_buffer_sequence<Trailer>::value,
        "Trailer requirements not met");

    using buffers_type = typename
        detail::buffers_or_fields<Trailer>::type;

    using view_type =
        buffers_cat_view<
            detail::chunk_size0,    // "0\r\n"
            buffers_type>;          // Trailer (includes CRLF)

    template<class Allocator>
    buffers_type
    prepare(Trailer const& trailer, Allocator const& alloc);

    buffers_type
    prepare(Trailer const& trailer, std::true_type);

    buffers_type
    prepare(Trailer const& trailer, std::false_type);

    std::shared_ptr<void> sp_;
    view_type view_;

public:
    /** Constructor

        The last chunk will have an empty trailer
    */
    chunk_last();

    /** Constructor

        @param trailer The trailer to use. This may be
        a type meeting the requirements of either Fields
        or ConstBufferSequence. If it is a ConstBufferSequence,
        the trailer must be formatted correctly as per rfc7230
        including a CRLF on its own line to denote the end
        of the trailer.
    */
    explicit
    chunk_last(Trailer const& trailer);

    /** Constructor

        @param trailer The trailer to use. This type must
        meet the requirements of Fields.

        @param allocator The allocator to use for storing temporary
        data associated with the serialized trailer buffers.
    */
#if BOOST_BEAST_DOXYGEN
    template<class Allocator>
    chunk_last(Trailer const& trailer, Allocator const& allocator);
#else
    template<class DeducedTrailer, class Allocator,
        class = typename std::enable_if<
            is_fields<DeducedTrailer>::value>::type>
    chunk_last(
        DeducedTrailer const& trailer, Allocator const& allocator);
#endif

    //-----

    /// Required for <em>ConstBufferSequence</em>
    chunk_last(chunk_last const&) = default;

    /// Required for <em>ConstBufferSequence</em>
#if BOOST_BEAST_DOXYGEN
    using value_type = __implementation_defined__;
#else
    using value_type =
        typename view_type::value_type;
#endif

    /// Required for <em>ConstBufferSequence</em>
#if BOOST_BEAST_DOXYGEN
    using const_iterator = __implementation_defined__;
#else
    using const_iterator =
        typename view_type::const_iterator;
#endif

    /// Required for <em>ConstBufferSequence</em>
    const_iterator
    begin() const
    {
        return view_.begin();
    }

    /// Required for <em>ConstBufferSequence</em>
    const_iterator
    end() const
    {
        return view_.end();
    }
};

//------------------------------------------------------------------------------

/** A set of chunk extensions

    This container stores a set of chunk extensions suited for use with
    @ref chunk_header and @ref chunk_body. The container may be iterated
    to access the extensions in their structured form.

    Meets the requirements of ChunkExtensions
*/
template<class Allocator>
class basic_chunk_extensions
{
    std::basic_string<char,
        std::char_traits<char>, Allocator> s_;

    std::basic_string<char,
        std::char_traits<char>, Allocator> range_;

    template<class FwdIt>
    FwdIt
    do_parse(FwdIt it, FwdIt last, error_code& ec);

    void
    do_insert(string_view name, string_view value);

public:
    /** The type of value when iterating.

        The first element of the pair is the name, and the second
        element is the value which may be empty. The value is
        stored in its raw representation, without quotes or escapes.
    */
    using value_type = std::pair<string_view, string_view>;

    class const_iterator;

    /// Constructor
    basic_chunk_extensions() = default;

    /// Constructor
    basic_chunk_extensions(basic_chunk_extensions&&) = default;

    /// Constructor
    basic_chunk_extensions(basic_chunk_extensions const&) = default;

    /** Constructor

        @param allocator The allocator to use for storing the serialized extension
    */
    explicit
    basic_chunk_extensions(Allocator const& allocator)
        : s_(allocator)
    {
    }

    /** Clear the chunk extensions

        This preserves the capacity of the internal string
        used to hold the serialized representation.
    */
    void
    clear()
    {
        s_.clear();
    }

    /** Parse a set of chunk extensions

        Any previous extensions will be cleared
    */
    void
    parse(string_view s, error_code& ec);

    /** Insert an extension name with an empty value

        @param name The name of the extension
    */
    void
    insert(string_view name);

    /** Insert an extension value

        @param name The name of the extension

        @param value The value to insert. Depending on the
        contents, the serialized extension may use a quoted string.
    */
    void
    insert(string_view name, string_view value);

    /// Return the serialized representation of the chunk extension
    string_view
    str() const
    {
        return s_;
    }

    const_iterator
    begin() const;

    const_iterator
    end() const;
};

//------------------------------------------------------------------------------

/// A set of chunk extensions
using chunk_extensions =
    basic_chunk_extensions<std::allocator<char>>;

/** Returns a @ref chunk_body

    This functions constructs and returns a complete
    @ref chunk_body for a chunk body represented by the
    specified buffer sequence.

    @param buffers The buffers representing the chunk body.

    @param args Optional arguments passed to the @ref chunk_body constructor.

    @note This function is provided as a notational convenience
    to omit specification of the class template arguments.
*/
template<class ConstBufferSequence, class... Args>
auto
make_chunk(
    ConstBufferSequence const& buffers,
    Args&&... args) ->
    chunk_body<ConstBufferSequence>
{
    return chunk_body<ConstBufferSequence>(
        buffers, std::forward<Args>(args)...);
}

/** Returns a @ref chunk_last

    @note This function is provided as a notational convenience
    to omit specification of the class template arguments.
*/
inline
chunk_last<chunk_crlf>
make_chunk_last()
{
    return chunk_last<chunk_crlf>{};
}

/** Returns a @ref chunk_last

    This function construct and returns a complete
    @ref chunk_last for a last chunk containing the
    specified trailers.

    @param trailer A ConstBufferSequence or 
    @note This function is provided as a notational convenience
    to omit specification of the class template arguments.

    @param args Optional arguments passed to the @ref chunk_last
    constructor.
*/
template<class Trailer, class... Args>
chunk_last<Trailer>
make_chunk_last(
    Trailer const& trailer,
    Args&&... args)
{
    return chunk_last<Trailer>{
        trailer, std::forward<Args>(args)...};
}

} // http
} // beast
} // boost

#include <boost/beast/http/impl/chunk_encode.hpp>

#endif

/* chunk_encode.hpp
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
*/