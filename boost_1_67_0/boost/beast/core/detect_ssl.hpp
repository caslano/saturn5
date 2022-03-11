//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETECT_SSL_HPP
#define BOOST_BEAST_CORE_DETECT_SSL_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/read_size.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/coroutine.hpp>
#include <type_traits>

namespace boost {
namespace beast {

//------------------------------------------------------------------------------
//
// Example: Detect TLS client_hello
//
//  This is an example and also a public interface. It implements
//  an algorithm for determining if a "TLS client_hello" message
//  is received. It can be used to implement a listening port that
//  can handle both plain and TLS encrypted connections.
//
//------------------------------------------------------------------------------

//[example_core_detect_ssl_1

// By convention, the "detail" namespace means "not-public."
// Identifiers in a detail namespace are not visible in the documentation,
// and users should not directly use those identifiers in programs, otherwise
// their program may break in the future.
//
// Using a detail namespace gives the library writer the freedom to change
// the interface or behavior later, and maintain backward-compatibility.

namespace detail {

/** Return `true` if the buffer contains a TLS Protocol client_hello message.

    This function analyzes the bytes at the beginning of the buffer
    and compares it to a valid client_hello message. This is the
    message required to be sent by a client at the beginning of
    any TLS (encrypted communication) session, including when
    resuming a session.

    The return value will be:

    @li `true` if the contents of the buffer unambiguously define
    contain a client_hello message,

    @li `false` if the contents of the buffer cannot possibly
    be a valid client_hello message, or

    @li `boost::indeterminate` if the buffer contains an
    insufficient number of bytes to determine the result. In
    this case the caller should read more data from the relevant
    stream, append it to the buffers, and call this function again.

    @param buffers The buffer sequence to inspect.
    This type must meet the requirements of <em>ConstBufferSequence</em>.

    @return `boost::tribool` indicating whether the buffer contains
    a TLS client handshake, does not contain a handshake, or needs
    additional bytes to determine an outcome.

    @see

    <a href="https://tools.ietf.org/html/rfc2246#section-7.4">7.4. Handshake protocol</a>
    (RFC2246: The TLS Protocol)
*/
template <class ConstBufferSequence>
boost::tribool
is_tls_client_hello (ConstBufferSequence const& buffers);

} // detail

//]

//[example_core_detect_ssl_2

namespace detail {

template <class ConstBufferSequence>
boost::tribool
is_tls_client_hello (ConstBufferSequence const& buffers)
{
    // Make sure buffers meets the requirements
    static_assert(
        net::is_const_buffer_sequence<ConstBufferSequence>::value,
        "ConstBufferSequence type requirements not met");

/*
    The first message on a TLS connection must be the client_hello,
    which is a type of handshake record, and it cannot be compressed
    or encrypted. A plaintext record has this format:

         0      byte    record_type      // 0x16 = handshake
         1      byte    major            // major protocol version
         2      byte    minor            // minor protocol version
       3-4      uint16  length           // size of the payload
         5      byte    handshake_type   // 0x01 = client_hello
         6      uint24  length           // size of the ClientHello
         9      byte    major            // major protocol version
        10      byte    minor            // minor protocol version
        11      uint32  gmt_unix_time
        15      byte    random_bytes[28]
                ...
*/

    // Flatten the input buffers into a single contiguous range
    // of bytes on the stack to make it easier to work with the data.
    unsigned char buf[9];
    auto const n = net::buffer_copy(
        net::mutable_buffer(buf, sizeof(buf)), buffers);

    // Can't do much without any bytes
    if(n < 1)
        return boost::indeterminate;

    // Require the first byte to be 0x16, indicating a TLS handshake record
    if(buf[0] != 0x16)
        return false;

    // We need at least 5 bytes to know the record payload size
    if(n < 5)
        return boost::indeterminate;

    // Calculate the record payload size
    std::uint32_t const length = (buf[3] << 8) + buf[4];

    // A ClientHello message payload is at least 34 bytes.
    // There can be multiple handshake messages in the same record.
    if(length < 34)
        return false;

    // We need at least 6 bytes to know the handshake type
    if(n < 6)
        return boost::indeterminate;

    // The handshake_type must be 0x01 == client_hello
    if(buf[5] != 0x01)
        return false;

    // We need at least 9 bytes to know the payload size
    if(n < 9)
        return boost::indeterminate;

    // Calculate the message payload size
    std::uint32_t const size =
        (buf[6] << 16) + (buf[7] << 8) + buf[8];

    // The message payload can't be bigger than the enclosing record
    if(size + 4 > length)
        return false;

    // This can only be a TLS client_hello message
    return true;
}

} // detail

//]

//[example_core_detect_ssl_3

/** Detect a TLS client handshake on a stream.

    This function reads from a stream to determine if a client
    handshake message is being received.
    
    The call blocks until one of the following is true:

    @li A TLS client opening handshake is detected,

    @li The received data is invalid for a TLS client handshake, or

    @li An error occurs.

    The algorithm, known as a <em>composed operation</em>, is implemented
    in terms of calls to the next layer's `read_some` function.

    Bytes read from the stream will be stored in the passed dynamic
    buffer, which may be used to perform the TLS handshake if the
    detector returns true, or be otherwise consumed by the caller based
    on the expected protocol.

    @param stream The stream to read from. This type must meet the
    requirements of <em>SyncReadStream</em>.

    @param buffer The dynamic buffer to use. This type must meet the
    requirements of <em>DynamicBuffer</em>.

    @param ec Set to the error if any occurred.

    @return `true` if the buffer contains a TLS client handshake and
    no error occurred, otherwise `false`.
*/
template<
    class SyncReadStream,
    class DynamicBuffer>
bool
detect_ssl(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    error_code& ec)
{
    namespace beast = boost::beast;

    // Make sure arguments meet the requirements

    static_assert(
        is_sync_read_stream<SyncReadStream>::value,
        "SyncReadStream type requirements not met");
    
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");

    // Loop until an error occurs or we get a definitive answer
    for(;;)
    {
        // There could already be data in the buffer
        // so we do this first, before reading from the stream.
        auto const result = detail::is_tls_client_hello(buffer.data());

        // If we got an answer, return it
        if(! boost::indeterminate(result))
        {
            // A definite answer is a success
            ec = {};
            return static_cast<bool>(result);
        }

        // Try to fill our buffer by reading from the stream.
        // The function read_size calculates a reasonable size for the
        // amount to read next, using existing capacity if possible to
        // avoid allocating memory, up to the limit of 1536 bytes which
        // is the size of a normal TCP frame.

        std::size_t const bytes_transferred = stream.read_some(
            buffer.prepare(beast::read_size(buffer, 1536)), ec);

        // Commit what we read into the buffer's input area.
        buffer.commit(bytes_transferred);

        // Check for an error
        if(ec)
            break;
    }

    // error
    return false;
}

//]

//[example_core_detect_ssl_4

/** Detect a TLS/SSL handshake asynchronously on a stream.

    This function reads asynchronously from a stream to determine
    if a client handshake message is being received.

    This call always returns immediately. The asynchronous operation
    will continue until one of the following conditions is true:

    @li A TLS client opening handshake is detected,

    @li The received data is invalid for a TLS client handshake, or

    @li An error occurs.

    The algorithm, known as a <em>composed asynchronous operation</em>,
    is implemented in terms of calls to the next layer's `async_read_some`
    function. The program must ensure that no other calls to
    `async_read_some` are performed until this operation completes.

    Bytes read from the stream will be stored in the passed dynamic
    buffer, which may be used to perform the TLS handshake if the
    detector returns true, or be otherwise consumed by the caller based
    on the expected protocol.

    @param stream The stream to read from. This type must meet the
    requirements of <em>AsyncReadStream</em>.

    @param buffer The dynamic buffer to use. This type must meet the
    requirements of <em>DynamicBuffer</em>.

    @param token The completion token used to determine the method
    used to provide the result of the asynchronous operation. If
    this is a completion handler, the implementation takes ownership
    of the handler by performing a decay-copy, and the equivalent
    function signature of the handler must be:
    @code
    void handler(
        error_code const& error,    // Set to the error, if any
        bool result                 // The result of the detector
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.
*/
template<
    class AsyncReadStream,
    class DynamicBuffer,
    class CompletionToken =
        net::default_completion_token_t<beast::executor_type<AsyncReadStream>>
>
#if BOOST_BEAST_DOXYGEN
BOOST_ASIO_INITFN_RESULT_TYPE(CompletionToken, void(error_code, bool))
#else
auto
#endif
async_detect_ssl(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    CompletionToken&& token = net::default_completion_token_t<
            beast::executor_type<AsyncReadStream>>{}) ->
        typename net::async_result<
            typename std::decay<CompletionToken>::type, /*< `async_result` customizes the return value based on the completion token >*/
            void(error_code, bool)>::return_type; /*< This is the signature for the completion handler >*/
//]

//[example_core_detect_ssl_5

// These implementation details don't need to be public

namespace detail {

// The composed operation object
template<
    class DetectHandler,
    class AsyncReadStream,
    class DynamicBuffer>
class detect_ssl_op;

// This is a function object which `net::async_initiate` can use to launch
// our composed operation. This is a relatively new feature in networking
// which allows the asynchronous operation to be "lazily" executed (meaning
// that it is launched later). Users don't need to worry about this, but
// authors of composed operations need to write it this way to get the
// very best performance, for example when using Coroutines TS (`co_await`).

struct run_detect_ssl_op
{
    // The implementation of `net::async_initiate` captures the
    // arguments of the initiating function, and then calls this
    // function object later with the captured arguments in order
    // to launch the composed operation. All we need to do here
    // is take those arguments and construct our composed operation
    // object.
    //
    // `async_initiate` takes care of transforming the completion
    // token into the "real handler" which must have the correct
    // signature, in this case `void(error_code, boost::tri_bool)`.

    template<
        class DetectHandler,
        class AsyncReadStream,
        class DynamicBuffer>
    void operator()(
        DetectHandler&& h,
        AsyncReadStream* s, // references are passed as pointers
        DynamicBuffer& b)
    {
        detect_ssl_op<
            typename std::decay<DetectHandler>::type,
            AsyncReadStream,
            DynamicBuffer>(
                std::forward<DetectHandler>(h), *s, b);
    }
};

} // detail

//]

//[example_core_detect_ssl_6

// Here is the implementation of the asynchronous initiation function
template<
    class AsyncReadStream,
    class DynamicBuffer,
    class CompletionToken>
#if BOOST_BEAST_DOXYGEN
BOOST_ASIO_INITFN_RESULT_TYPE(CompletionToken, void(error_code, bool))
#else
auto
#endif
async_detect_ssl(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    CompletionToken&& token)
        -> typename net::async_result<
            typename std::decay<CompletionToken>::type,
            void(error_code, bool)>::return_type
{
    // Make sure arguments meet the type requirements

    static_assert(
        is_async_read_stream<AsyncReadStream>::value,
        "SyncReadStream type requirements not met");

    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");

    // The function `net::async_initate` uses customization points
    // to allow one asynchronous initiating function to work with
    // all sorts of notification systems, such as callbacks but also
    // fibers, futures, coroutines, and user-defined types.
    //
    // It works by capturing all of the arguments using perfect
    // forwarding, and then depending on the specialization of
    // `net::async_result` for the type of `CompletionToken`,
    // the `initiation` object will be invoked with the saved
    // parameters and the actual completion handler. Our
    // initiating object is `run_detect_ssl_op`.
    //
    // Non-const references need to be passed as pointers,
    // since we don't want a decay-copy.

    return net::async_initiate<
        CompletionToken,
        void(error_code, bool)>(
            detail::run_detect_ssl_op{},
            token,
            &stream, // pass the reference by pointer
            buffer);
}

//]

//[example_core_detect_ssl_7

namespace detail {

// Read from a stream, calling is_tls_client_hello on the data
// data to determine if the TLS client handshake is present.
//
// This will be implemented using Asio's "stackless coroutines"
// which are based on macros forming a switch statement. The
// operation is derived from `coroutine` for this reason.
//
// The library type `async_base` takes care of all of the
// boilerplate for writing composed operations, including:
//
//  * Storing the user's completion handler
//  * Maintaining the work guard for the handler's associated executor
//  * Propagating the associated allocator of the handler
//  * Propagating the associated executor of the handler
//  * Deallocating temporary storage before invoking the handler
//  * Posting the handler to the executor on an immediate completion
//
// `async_base` needs to know the type of the handler, as well
// as the executor of the I/O object being used. The metafunction
// `executor_type` returns the type of executor used by an
// I/O object.
//
template<
    class DetectHandler,
    class AsyncReadStream,
    class DynamicBuffer>
class detect_ssl_op
    : public boost::asio::coroutine
    , public async_base<
        DetectHandler, executor_type<AsyncReadStream>>
{
    // This composed operation has trivial state,
    // so it is just kept inside the class and can
    // be cheaply copied as needed by the implementation.

    AsyncReadStream& stream_;

    // The callers buffer is used to hold all received data
    DynamicBuffer& buffer_;

    // We're going to need this in case we have to post the handler
    error_code ec_;

    boost::tribool result_ = false;

public:
    // Completion handlers must be MoveConstructible.
    detect_ssl_op(detect_ssl_op&&) = default;

    // Construct the operation. The handler is deduced through
    // the template type `DetectHandler_`, this lets the same constructor
    // work properly for both lvalues and rvalues.
    //
    template<class DetectHandler_>
    detect_ssl_op(
        DetectHandler_&& handler,
        AsyncReadStream& stream,
        DynamicBuffer& buffer)
        : beast::async_base<
            DetectHandler,
            beast::executor_type<AsyncReadStream>>(
                std::forward<DetectHandler_>(handler),
                stream.get_executor())
        , stream_(stream)
        , buffer_(buffer)
    {
        // This starts the operation. We pass `false` to tell the
        // algorithm that it needs to use net::post if it wants to
        // complete immediately. This is required by Networking,
        // as initiating functions are not allowed to invoke the
        // completion handler on the caller's thread before
        // returning.
        (*this)({}, 0, false);
    }

    // Our main entry point. This will get called as our
    // intermediate operations complete. Definition below.
    //
    // The parameter `cont` indicates if we are being called subsequently
    // from the original invocation
    //
    void operator()(
        error_code ec,
        std::size_t bytes_transferred,
        bool cont = true);
};

} // detail

//]

//[example_core_detect_ssl_8

namespace detail {

// This example uses the Asio's stackless "fauxroutines", implemented
// using a macro-based solution. It makes the code easier to write and
// easier to read. This include file defines the necessary macros and types.
#include <boost/asio/yield.hpp>

// detect_ssl_op is callable with the signature void(error_code, bytes_transferred),
// allowing `*this` to be used as a ReadHandler
//
template<
    class AsyncStream,
    class DynamicBuffer,
    class Handler>
void
detect_ssl_op<AsyncStream, DynamicBuffer, Handler>::
operator()(error_code ec, std::size_t bytes_transferred, bool cont)
{
    namespace beast = boost::beast;

    // This introduces the scope of the stackless coroutine
    reenter(*this)
    {
        // Loop until an error occurs or we get a definitive answer
        for(;;)
        {
            // There could already be a hello in the buffer so check first
            result_ = is_tls_client_hello(buffer_.data());

            // If we got an answer, then the operation is complete
            if(! boost::indeterminate(result_))
                break;

            // Try to fill our buffer by reading from the stream.
            // The function read_size calculates a reasonable size for the
            // amount to read next, using existing capacity if possible to
            // avoid allocating memory, up to the limit of 1536 bytes which
            // is the size of a normal TCP frame.
            //
            // `async_read_some` expects a ReadHandler as the completion
            // handler. The signature of a read handler is void(error_code, size_t),
            // and this function matches that signature (the `cont` parameter has
            // a default of true). We pass `std::move(*this)` as the completion
            // handler for the read operation. This transfers ownership of this
            // entire state machine back into the `async_read_some` operation.
            // Care must be taken with this idiom, to ensure that parameters
            // passed to the initiating function which could be invalidated
            // by the move, are first moved to the stack before calling the
            // initiating function.

            yield stream_.async_read_some(buffer_.prepare(
                read_size(buffer_, 1536)), std::move(*this));

            // Commit what we read into the buffer's input area.
            buffer_.commit(bytes_transferred);

            // Check for an error
            if(ec)
                break;
        }

        // If `cont` is true, the handler will be invoked directly.
        //
        // Otherwise, the handler cannot be invoked directly, because
        // initiating functions are not allowed to call the handler
        // before returning. Instead, the handler must be posted to
        // the I/O context. We issue a zero-byte read using the same
        // type of buffers used in the ordinary read above, to prevent
        // the compiler from creating an extra instantiation of the
        // function template. This reduces compile times and the size
        // of the program executable.

        if(! cont)
        {
            // Save the error, otherwise it will be overwritten with
            // a successful error code when this read completes
            // immediately.
            ec_ = ec;

            // Zero-byte reads and writes are guaranteed to complete
            // immediately with succcess. The type of buffers and the
            // type of handler passed here need to exactly match the types
            // used in the call to async_read_some above, to avoid
            // instantiating another version of the function template.

            yield stream_.async_read_some(buffer_.prepare(0), std::move(*this));

            // Restore the saved error code
            ec = ec_;
        }

        // Invoke the final handler.
        // At this point, we are guaranteed that the original initiating
        // function is no longer on our stack frame.

        this->complete_now(ec, static_cast<bool>(result_));
    }
}

// Including this file undefines the macros used by the stackless fauxroutines.
#include <boost/asio/unyield.hpp>

} // detail

//]

} // beast
} // boost

#endif

/* detect_ssl.hpp
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
*/