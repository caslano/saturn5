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