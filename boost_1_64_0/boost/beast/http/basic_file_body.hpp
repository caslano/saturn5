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
bG9/6zBCxv3dIOXz9N8NQ0O+G6R8Mb4bXq/7bpB9SzTfl+wD1OX6bpDyJfrvhqEh3w089o74Zknmt2G57AuYq4xTwnyc+V4R7vtM2fxhluzVxij0iaTw2BNFa6x32YzI9VafKd2C3558doT5RC937XP3pcVphmyvgFJAT9jP8QJnX/K3fmBQpovqS2VSvln33CB/hvrmL3WVTeMPKbfW/qYfJPVn1z1TpLwD6235ZN0cBfnTVL89QMo14bEr7J9Tpf5axia51g9U9FWav9+CUo92n+LR7gGPdp9bTxxLNhdCWcpvz9H89swY4GzPyGvAgd/7u5O/kQOkfgDb0uZvr/vuRL2/786MAf6+OwcLX3P1zjBSyqc71uX8Z7851bxfR66TinPsBJxmz/sNcraHv3XLgjK9Vf8/Xsrj9fN+g9zP17lSPsTUPI/J302NxzlSLtc9j8HvjleZKeUy0yv+ZAFwsdQPMW82Zmvj/3bbyeK5yBiGdmzpjj9RtJnPV++6rSc+kPs841EWbIF4lHfaS1zIfS/+kTg08OSJCU/1+fq6+zZG41QixakskTiVcdPueb0wMa7D2i/Grt4cuP2R/26cirV+Fo1J8i1abb0jqzWzaN+mbao6JC6kLx5iFvYzGRcCpBy+XPVy/SmXS7k8h1xSPXJvMA7lNWACy7ZcRj1y71DuLcqhTDlQI49XWI/c+5R7l3IoK7mSRh6vtJFygXrkrmc73MB2uNHRDpX1yK3k8V7i8VY6448aKbe4kXI1jZBboGyTOF/KtQTOo1wq7sP2wA7AjsAsYCawF7APsCNwZ2An4HDuLwZmAMcDM4GTgJ2BRwC7AI8BdgVWArsB5wfluAYUbWa0A1WHrAF1vRE8jyXAfK5JNpRrklmyS4HHA5cBf+EaZtZv8j3AA4H3Ankc2l9gd/I4zgPg6wd8kHprgc8BHwOuAj4O/BH4JPBX4FPAQ628EMDJwBd4HJnL4v0t5/2NBw7hcX7nGm9gkDXeWgPzgMnAkcA2vI/teH82GZyj5vx9NWN511PfMPB1ARYCc4HDgUOBI4C7AEcC9wHuynYZDTwOOA54EnB3YBVwD+BC4J7Am4B7Ax8F7gNcBdwX+D5wP+AvwP2BLaxvB2A1cCLwZuDBwKeBhwCfB5YC3wZOAn4OPBS4CVgG3C4G9wjYBlgB7AqcDOwBnALkWnGcg7TmWlEOWStuKvj6AqcD+wNnAAcDjwKWAGcBS4GzgRXAOcBjgccALwTOBV4KPBZ4NfB44P3AeUCr/U8AvgU8EfgV8CTgxmB8HePuOE/GOcHqkLi708DXE3gWcCDwXOBuwPOARwLPB84AXshxchHwPODFwIuBZwOrgZcAOX457yPzXmHj93CuHXcEsBfXmsvjWgx7cy29CVxL7whLB7CGa8l9DpwL3MA1+JKtd21gCnAeEG0p8hXAk9Wad5yf4LxMdciad/M5rk7nuDoDOAW4APgm1+T72LoPwC+BVcC2Ju4HcAfgRcBuwIVA6JY1324CXgFcBlyk8j7yu5bf9NUheR9HcM2+kQbHA/AR4G7AJ4Bj1Pjltxhwqcf4/Yjj9xOu0fgj7+9PwJHATYyr/IX6cD/5vYA+y/vTQtqlbs2K3lyrosTiZfvsCVzBNQZfBk4Avg7cn2sZHsi1DCcCfwYeBDzYGl/AacAKYJ9muP6fkBcQFACdA1oCegK05id/eSo3gi9pE2LmQEWgcpBXfOY55QnGYlBonOaSWxKaLFbzmVsS/vZ4zU0fxNYbs1mLa9TFba4sT2hUXst1uC5d3Gbp7Qn/WOxm26UJW038ZiX63SLQctCboE2gDj8nGENAE0HzQItAtaA1oM2gDr8kGHk=
*/