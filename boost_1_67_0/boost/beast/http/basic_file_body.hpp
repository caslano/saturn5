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