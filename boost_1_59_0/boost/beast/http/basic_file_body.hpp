//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_BASIC_FILE_BODY_HPP
#define BOOST_BEAST_HTTP_BASIC_FILE_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/file_base.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <algorithm>
#include <cstdio>
#include <cstdint>
#include <utility>

namespace boost {
namespace beast {
namespace http {

//[example_http_file_body_1

/** A message body represented by a file on the filesystem.

    Messages with this type have bodies represented by a
    file on the file system. When parsing a message using
    this body type, the data is stored in the file pointed
    to by the path, which must be writable. When serializing,
    the implementation will read the file and present those
    octets as the body content. This may be used to serve
    content from a directory as part of a web service.

    @tparam File The implementation to use for accessing files.
    This type must meet the requirements of <em>File</em>.
*/
template<class File>
struct basic_file_body
{
    // Make sure the type meets the requirements
    static_assert(is_file<File>::value,
        "File type requirements not met");

    /// The type of File this body uses
    using file_type = File;

    // Algorithm for storing buffers when parsing.
    class reader;

    // Algorithm for retrieving buffers when serializing.
    class writer;

    // The type of the @ref message::body member.
    class value_type;

    /** Returns the size of the body

        @param body The file body to use
    */
    static
    std::uint64_t
    size(value_type const& body);
};

//]

//[example_http_file_body_2

/** The type of the @ref message::body member.

    Messages declared using `basic_file_body` will have this type for
    the body member. This rich class interface allow the file to be
    opened with the file handle maintained directly in the object,
    which is attached to the message.
*/
template<class File>
class basic_file_body<File>::value_type
{
    // This body container holds a handle to the file
    // when it is open, and also caches the size when set.

    friend class reader;
    friend class writer;
    friend struct basic_file_body;

    // This represents the open file
    File file_;

    // The cached file size
    std::uint64_t file_size_ = 0;

public:
    /** Destructor.

        If the file is open, it is closed first.
    */
    ~value_type() = default;

    /// Constructor
    value_type() = default;

    /// Constructor
    value_type(value_type&& other) = default;

    /// Move assignment
    value_type& operator=(value_type&& other) = default;

    /// Return the file
    File& file()
    {
        return file_;
    }

    /// Returns `true` if the file is open
    bool
    is_open() const
    {
        return file_.is_open();
    }

    /// Returns the size of the file if open
    std::uint64_t
    size() const
    {
        return file_size_;
    }

    /// Close the file if open
    void
    close();

    /** Open a file at the given path with the specified mode

        @param path The utf-8 encoded path to the file

        @param mode The file mode to use

        @param ec Set to the error, if any occurred
    */
    void
    open(char const* path, file_mode mode, error_code& ec);

    /** Set the open file

        This function is used to set the open file. Any previously
        set file will be closed.

        @param file The file to set. The file must be open or else
        an error occurs

        @param ec Set to the error, if any occurred
    */
    void
    reset(File&& file, error_code& ec);
};

template<class File>
void
basic_file_body<File>::
value_type::
close()
{
    error_code ignored;
    file_.close(ignored);
}

template<class File>
void
basic_file_body<File>::
value_type::
open(char const* path, file_mode mode, error_code& ec)
{
    // Open the file
    file_.open(path, mode, ec);
    if(ec)
        return;

    // Cache the size
    file_size_ = file_.size(ec);
    if(ec)
    {
        close();
        return;
    }
}

template<class File>
void
basic_file_body<File>::
value_type::
reset(File&& file, error_code& ec)
{
    // First close the file if open
    if(file_.is_open())
    {
        error_code ignored;
        file_.close(ignored);
    }

    // Take ownership of the new file
    file_ = std::move(file);

    // Cache the size
    file_size_ = file_.size(ec);
}

// This is called from message::payload_size
template<class File>
std::uint64_t
basic_file_body<File>::
size(value_type const& body)
{
    // Forward the call to the body
    return body.size();
}

//]

//[example_http_file_body_3

/** Algorithm for retrieving buffers when serializing.

    Objects of this type are created during serialization
    to extract the buffers representing the body.
*/
template<class File>
class basic_file_body<File>::writer
{
    value_type& body_;      // The body we are reading from
    std::uint64_t remain_;  // The number of unread bytes
    char buf_[4096];        // Small buffer for reading

public:
    // The type of buffer sequence returned by `get`.
    //
    using const_buffers_type =
        net::const_buffer;

    // Constructor.
    //
    // `h` holds the headers of the message we are
    // serializing, while `b` holds the body.
    //
    // Note that the message is passed by non-const reference.
    // This is intentional, because reading from the file
    // changes its "current position" which counts makes the
    // operation logically not-const (although it is bitwise
    // const).
    //
    // The BodyWriter concept allows the writer to choose
    // whether to take the message by const reference or
    // non-const reference. Depending on the choice, a
    // serializer constructed using that body type will
    // require the same const or non-const reference to
    // construct.
    //
    // Readers which accept const messages usually allow
    // the same body to be serialized by multiple threads
    // concurrently, while readers accepting non-const
    // messages may only be serialized by one thread at
    // a time.
    //
    template<bool isRequest, class Fields>
    writer(header<isRequest, Fields>& h, value_type& b);

    // Initializer
    //
    // This is called before the body is serialized and
    // gives the writer a chance to do something that might
    // need to return an error code.
    //
    void
    init(error_code& ec);

    // This function is called zero or more times to
    // retrieve buffers. A return value of `boost::none`
    // means there are no more buffers. Otherwise,
    // the contained pair will have the next buffer
    // to serialize, and a `bool` indicating whether
    // or not there may be additional buffers.
    boost::optional<std::pair<const_buffers_type, bool>>
    get(error_code& ec);
};

//]

//[example_http_file_body_4

// Here we just stash a reference to the path for later.
// Rather than dealing with messy constructor exceptions,
// we save the things that might fail for the call to `init`.
//
template<class File>
template<bool isRequest, class Fields>
basic_file_body<File>::
writer::
writer(header<isRequest, Fields>& h, value_type& b)
    : body_(b)
{
    boost::ignore_unused(h);

    // The file must already be open
    BOOST_ASSERT(body_.file_.is_open());

    // Get the size of the file
    remain_ = body_.file_size_;
}

// Initializer
template<class File>
void
basic_file_body<File>::
writer::
init(error_code& ec)
{
    // The error_code specification requires that we
    // either set the error to some value, or set it
    // to indicate no error.
    //
    // We don't do anything fancy so set "no error"
    ec = {};
}

// This function is called repeatedly by the serializer to
// retrieve the buffers representing the body. Our strategy
// is to read into our buffer and return it until we have
// read through the whole file.
//
template<class File>
auto
basic_file_body<File>::
writer::
get(error_code& ec) ->
    boost::optional<std::pair<const_buffers_type, bool>>
{
    // Calculate the smaller of our buffer size,
    // or the amount of unread data in the file.
    auto const amount =  remain_ > sizeof(buf_) ?
        sizeof(buf_) : static_cast<std::size_t>(remain_);

    // Handle the case where the file is zero length
    if(amount == 0)
    {
        // Modify the error code to indicate success
        // This is required by the error_code specification.
        //
        // NOTE We use the existing category instead of calling
        //      into the library to get the generic category because
        //      that saves us a possibly expensive atomic operation.
        //
        ec = {};
        return boost::none;
    }

    // Now read the next buffer
    auto const nread = body_.file_.read(buf_, amount, ec);
    if(ec)
        return boost::none;

    if (nread == 0)
    {
        ec = error::short_read;
        return boost::none;
    }

    // Make sure there is forward progress
    BOOST_ASSERT(nread != 0);
    BOOST_ASSERT(nread <= remain_);

    // Update the amount remaining based on what we got
    remain_ -= nread;

    // Return the buffer to the caller.
    //
    // The second element of the pair indicates whether or
    // not there is more data. As long as there is some
    // unread bytes, there will be more data. Otherwise,
    // we set this bool to `false` so we will not be called
    // again.
    //
    ec = {};
    return {{
        const_buffers_type{buf_, nread},    // buffer to return.
        remain_ > 0                         // `true` if there are more buffers.
        }};
}

//]

//[example_http_file_body_5

/** Algorithm for storing buffers when parsing.

    Objects of this type are created during parsing
    to store incoming buffers representing the body.
*/
template<class File>
class basic_file_body<File>::reader
{
    value_type& body_;  // The body we are writing to

public:
    // Constructor.
    //
    // This is called after the header is parsed and
    // indicates that a non-zero sized body may be present.
    // `h` holds the received message headers.
    // `b` is an instance of `basic_file_body`.
    //
    template<bool isRequest, class Fields>
    explicit
    reader(header<isRequest, Fields>&h, value_type& b);

    // Initializer
    //
    // This is called before the body is parsed and
    // gives the reader a chance to do something that might
    // need to return an error code. It informs us of
    // the payload size (`content_length`) which we can
    // optionally use for optimization.
    //
    void
    init(boost::optional<std::uint64_t> const&, error_code& ec);

    // This function is called one or more times to store
    // buffer sequences corresponding to the incoming body.
    //
    template<class ConstBufferSequence>
    std::size_t
    put(ConstBufferSequence const& buffers,
        error_code& ec);

    // This function is called when writing is complete.
    // It is an opportunity to perform any final actions
    // which might fail, in order to return an error code.
    // Operations that might fail should not be attempted in
    // destructors, since an exception thrown from there
    // would terminate the program.
    //
    void
    finish(error_code& ec);
};

//]

//[example_http_file_body_6

// We don't do much in the reader constructor since the
// file is already open.
//
template<class File>
template<bool isRequest, class Fields>
basic_file_body<File>::
reader::
reader(header<isRequest, Fields>& h, value_type& body)
    : body_(body)
{
    boost::ignore_unused(h);
}

template<class File>
void
basic_file_body<File>::
reader::
init(
    boost::optional<std::uint64_t> const& content_length,
    error_code& ec)
{
    // The file must already be open for writing
    BOOST_ASSERT(body_.file_.is_open());

    // We don't do anything with this but a sophisticated
    // application might check available space on the device
    // to see if there is enough room to store the body.
    boost::ignore_unused(content_length);

    // The error_code specification requires that we
    // either set the error to some value, or set it
    // to indicate no error.
    //
    // We don't do anything fancy so set "no error"
    ec = {};
}

// This will get called one or more times with body buffers
//
template<class File>
template<class ConstBufferSequence>
std::size_t
basic_file_body<File>::
reader::
put(ConstBufferSequence const& buffers, error_code& ec)
{
    // This function must return the total number of
    // bytes transferred from the input buffers.
    std::size_t nwritten = 0;

    // Loop over all the buffers in the sequence,
    // and write each one to the file.
    for(auto it = net::buffer_sequence_begin(buffers);
        it != net::buffer_sequence_end(buffers); ++it)
    {
        // Write this buffer to the file
        net::const_buffer buffer = *it;
        nwritten += body_.file_.write(
            buffer.data(), buffer.size(), ec);
        if(ec)
            return nwritten;
    }

    // Indicate success
    // This is required by the error_code specification
    ec = {};

    return nwritten;
}

// Called after writing is done when there's no error.
template<class File>
void
basic_file_body<File>::
reader::
finish(error_code& ec)
{
    // This has to be cleared before returning, to
    // indicate no error. The specification requires it.
    ec = {};
}

//]

#if ! BOOST_BEAST_DOXYGEN
// operator<< is not supported for file_body
template<bool isRequest, class File, class Fields>
std::ostream&
operator<<(std::ostream&, message<
    isRequest, basic_file_body<File>, Fields> const&) = delete;
#endif

} // http
} // beast
} // boost

#endif

/* basic_file_body.hpp
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
*/