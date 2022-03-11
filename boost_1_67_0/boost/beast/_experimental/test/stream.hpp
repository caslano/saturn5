//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_STREAM_HPP
#define BOOST_BEAST_TEST_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/role.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/_experimental/test/fail_count.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>
#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/throw_exception.hpp>
#include <condition_variable>
#include <limits>
#include <memory>
#include <mutex>
#include <utility>

#if ! BOOST_BEAST_DOXYGEN
namespace boost {
namespace asio {
namespace ssl {
template<typename> class stream;
} // ssl
} // asio
} // boost
#endif

namespace boost {
namespace beast {
namespace test {

/** A two-way socket useful for unit testing

    An instance of this class simulates a traditional socket,
    while also providing features useful for unit testing.
    Each endpoint maintains an independent buffer called
    the input area. Writes from one endpoint append data
    to the peer's pending input area. When an endpoint performs
    a read and data is present in the input area, the data is
    delivered to the blocking or asynchronous operation. Otherwise
    the operation is blocked or deferred until data is made
    available, or until the endpoints become disconnected.

    These streams may be used anywhere an algorithm accepts a
    reference to a synchronous or asynchronous read or write
    stream. It is possible to use a test stream in a call to
    `net::read_until`, or in a call to
    @ref boost::beast::http::async_write for example.

    As with Boost.Asio I/O objects, a @ref stream constructs
    with a reference to the `net::io_context` to use for
    handling asynchronous I/O. For asynchronous operations, the
    stream follows the same rules as a traditional asio socket
    with respect to how completion handlers for asynchronous
    operations are performed.

    To facilitate testing, these streams support some additional
    features:

    @li The input area, represented by a @ref beast::basic_flat_buffer,
    may be directly accessed by the caller to inspect the contents
    before or after the remote endpoint writes data. This allows
    a unit test to verify that the received data matches.

    @li Data may be manually appended to the input area. This data
    will delivered in the next call to
    @ref stream::read_some or @ref stream::async_read_some.
    This allows predefined test vectors to be set up for testing
    read algorithms.

    @li The stream may be constructed with a fail count. The
    stream will eventually fail with a predefined error after a
    certain number of operations, where the number of operations
    is controlled by the test. When a test loops over a range of
    operation counts, it is possible to exercise every possible
    point of failure in the algorithm being tested. When used
    correctly the technique allows the tests to reach a high
    percentage of code coverage.

    @par Thread Safety
        @e Distinct @e objects: Safe.@n
        @e Shared @e objects: Unsafe.
        The application must also ensure that all asynchronous
        operations are performed within the same implicit or explicit strand.

    @par Concepts
        @li <em>SyncReadStream</em>
        @li <em>SyncWriteStream</em>
        @li <em>AsyncReadStream</em>
        @li <em>AsyncWriteStream</em>
*/
class stream
{
    struct state;

    boost::shared_ptr<state> in_;
    boost::weak_ptr<state> out_;

    enum class status
    {
        ok,
        eof,
    };

    class service;
    struct service_impl;

    struct read_op_base
    {
        virtual ~read_op_base() = default;
        virtual void operator()(error_code ec) = 0;
    };

    struct state
    {
        friend class stream;

        net::io_context& ioc;
        boost::weak_ptr<service_impl> wp;
        std::mutex m;
        flat_buffer b;
        std::condition_variable cv;
        std::unique_ptr<read_op_base> op;
        status code = status::ok;
        fail_count* fc = nullptr;
        std::size_t nread = 0;
        std::size_t nread_bytes = 0;
        std::size_t nwrite = 0;
        std::size_t nwrite_bytes = 0;
        std::size_t read_max =
            (std::numeric_limits<std::size_t>::max)();
        std::size_t write_max =
            (std::numeric_limits<std::size_t>::max)();

        BOOST_BEAST_DECL
        state(
            net::io_context& ioc_,
            boost::weak_ptr<service_impl> wp_,
            fail_count* fc_);


        BOOST_BEAST_DECL
        ~state();

        BOOST_BEAST_DECL
        void
        remove() noexcept;

        BOOST_BEAST_DECL
        void
        notify_read();

        BOOST_BEAST_DECL
        void
        cancel_read();
    };

    template<class Handler, class Buffers>
    class read_op;

    struct run_read_op;
    struct run_write_op;

    BOOST_BEAST_DECL
    static
    void
    initiate_read(
        boost::shared_ptr<state> const& in,
        std::unique_ptr<read_op_base>&& op,
        std::size_t buf_size);

#if ! BOOST_BEAST_DOXYGEN
    // boost::asio::ssl::stream needs these
    // DEPRECATED
    template<class>
    friend class boost::asio::ssl::stream;
    // DEPRECATED
    using lowest_layer_type = stream;
    // DEPRECATED
    lowest_layer_type&
    lowest_layer() noexcept
    {
        return *this;
    }
    // DEPRECATED
    lowest_layer_type const&
    lowest_layer() const noexcept
    {
        return *this;
    }
#endif

public:
    using buffer_type = flat_buffer;

    /** Destructor

        If an asynchronous read operation is pending, it will
        simply be discarded with no notification to the completion
        handler.

        If a connection is established while the stream is destroyed,
        the peer will see the error `net::error::connection_reset`
        when performing any reads or writes.
    */
    BOOST_BEAST_DECL
    ~stream();

    /** Move Constructor

        Moving the stream while asynchronous operations are pending
        results in undefined behavior.
    */
    BOOST_BEAST_DECL
    stream(stream&& other);

    /** Move Assignment

        Moving the stream while asynchronous operations are pending
        results in undefined behavior.
    */
    BOOST_BEAST_DECL
    stream&
    operator=(stream&& other);

    /** Construct a stream

        The stream will be created in a disconnected state.

        @param ioc The `io_context` object that the stream will use to
        dispatch handlers for any asynchronous operations.
    */
    BOOST_BEAST_DECL
    explicit
    stream(net::io_context& ioc);

    /** Construct a stream

        The stream will be created in a disconnected state.

        @param ioc The `io_context` object that the stream will use to
        dispatch handlers for any asynchronous operations.

        @param fc The @ref fail_count to associate with the stream.
        Each I/O operation performed on the stream will increment the
        fail count.  When the fail count reaches its internal limit,
        a simulated failure error will be raised.
    */
    BOOST_BEAST_DECL
    stream(
        net::io_context& ioc,
        fail_count& fc);

    /** Construct a stream

        The stream will be created in a disconnected state.

        @param ioc The `io_context` object that the stream will use to
        dispatch handlers for any asynchronous operations.

        @param s A string which will be appended to the input area, not
        including the null terminator.
    */
    BOOST_BEAST_DECL
    stream(
        net::io_context& ioc,
        string_view s);

    /** Construct a stream

        The stream will be created in a disconnected state.

        @param ioc The `io_context` object that the stream will use to
        dispatch handlers for any asynchronous operations.

        @param fc The @ref fail_count to associate with the stream.
        Each I/O operation performed on the stream will increment the
        fail count.  When the fail count reaches its internal limit,
        a simulated failure error will be raised.

        @param s A string which will be appended to the input area, not
        including the null terminator.
    */
    BOOST_BEAST_DECL
    stream(
        net::io_context& ioc,
        fail_count& fc,
        string_view s);

    /// Establish a connection
    BOOST_BEAST_DECL
    void
    connect(stream& remote);

    /// The type of the executor associated with the object.
    using executor_type =
        net::io_context::executor_type;

    /// Return the executor associated with the object.
    executor_type
    get_executor() noexcept
    {
        return in_->ioc.get_executor();
    };

    /// Set the maximum number of bytes returned by read_some
    void
    read_size(std::size_t n) noexcept
    {
        in_->read_max = n;
    }

    /// Set the maximum number of bytes returned by write_some
    void
    write_size(std::size_t n) noexcept
    {
        in_->write_max = n;
    }

    /// Direct input buffer access
    buffer_type&
    buffer() noexcept
    {
        return in_->b;
    }

    /// Returns a string view representing the pending input data
    BOOST_BEAST_DECL
    string_view
    str() const;

    /// Appends a string to the pending input data
    BOOST_BEAST_DECL
    void
    append(string_view s);

    /// Clear the pending input area
    BOOST_BEAST_DECL
    void
    clear();

    /// Return the number of reads
    std::size_t
    nread() const noexcept
    {
        return in_->nread;
    }

    /// Return the number of bytes read
    std::size_t
    nread_bytes() const noexcept
    {
        return in_->nread_bytes;
    }

    /// Return the number of writes
    std::size_t
    nwrite() const noexcept
    {
        return in_->nwrite;
    }

    /// Return the number of bytes written
    std::size_t
    nwrite_bytes() const noexcept
    {
        return in_->nwrite_bytes;
    }

    /** Close the stream.

        The other end of the connection will see
        `error::eof` after reading all the remaining data.
    */
    BOOST_BEAST_DECL
    void
    close();

    /** Close the other end of the stream.

        This end of the connection will see
        `error::eof` after reading all the remaining data.
    */
    BOOST_BEAST_DECL
    void
    close_remote();

    /** Read some data from the stream.

        This function is used to read data from the stream. The function call will
        block until one or more bytes of data has been read successfully, or until
        an error occurs.

        @param buffers The buffers into which the data will be read.

        @returns The number of bytes read.

        @throws boost::system::system_error Thrown on failure.

        @note The `read_some` operation may not read all of the requested number of
        bytes. Consider using the function `net::read` if you need to ensure
        that the requested amount of data is read before the blocking operation
        completes.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(MutableBufferSequence const& buffers);

    /** Read some data from the stream.

        This function is used to read data from the stream. The function call will
        block until one or more bytes of data has been read successfully, or until
        an error occurs.

        @param buffers The buffers into which the data will be read.

        @param ec Set to indicate what error occurred, if any.

        @returns The number of bytes read.

        @note The `read_some` operation may not read all of the requested number of
        bytes. Consider using the function `net::read` if you need to ensure
        that the requested amount of data is read before the blocking operation
        completes.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(MutableBufferSequence const& buffers,
        error_code& ec);

    /** Start an asynchronous read.

        This function is used to asynchronously read one or more bytes of data from
        the stream. The function call always returns immediately.

        @param buffers The buffers into which the data will be read. Although the
        buffers object may be copied as necessary, ownership of the underlying
        buffers is retained by the caller, which must guarantee that they remain
        valid until the handler is called.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
            error_code const& ec,           // Result of operation.
            std::size_t bytes_transferred   // Number of bytes read.
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.

        @note The `async_read_some` operation may not read all of the requested number of
        bytes. Consider using the function `net::async_read` if you need
        to ensure that the requested amount of data is read before the asynchronous
        operation completes.
    */
    template<
        class MutableBufferSequence,
        BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
    BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
    async_read_some(
        MutableBufferSequence const& buffers,
        ReadHandler&& handler);

    /** Write some data to the stream.

        This function is used to write data on the stream. The function call will
        block until one or more bytes of data has been written successfully, or
        until an error occurs.

        @param buffers The data to be written.

        @returns The number of bytes written.

        @throws boost::system::system_error Thrown on failure.

        @note The `write_some` operation may not transmit all of the data to the
        peer. Consider using the function `net::write` if you need to
        ensure that all data is written before the blocking operation completes.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(ConstBufferSequence const& buffers);

    /** Write some data to the stream.

        This function is used to write data on the stream. The function call will
        block until one or more bytes of data has been written successfully, or
        until an error occurs.

        @param buffers The data to be written.

        @param ec Set to indicate what error occurred, if any.

        @returns The number of bytes written.

        @note The `write_some` operation may not transmit all of the data to the
        peer. Consider using the function `net::write` if you need to
        ensure that all data is written before the blocking operation completes.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(
        ConstBufferSequence const& buffers, error_code& ec);

    /** Start an asynchronous write.

        This function is used to asynchronously write one or more bytes of data to
        the stream. The function call always returns immediately.

        @param buffers The data to be written to the stream. Although the buffers
        object may be copied as necessary, ownership of the underlying buffers is
        retained by the caller, which must guarantee that they remain valid until
        the handler is called.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
            error_code const& ec,           // Result of operation.
            std::size_t bytes_transferred   // Number of bytes written.
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.

        @note The `async_write_some` operation may not transmit all of the data to
        the peer. Consider using the function `net::async_write` if you need
        to ensure that all data is written before the asynchronous operation completes.
    */
    template<
        class ConstBufferSequence,
        BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
    BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
    async_write_some(
        ConstBufferSequence const& buffers,
        WriteHandler&& handler);

#if ! BOOST_BEAST_DOXYGEN
    friend
    BOOST_BEAST_DECL
    void
    teardown(
        role_type,
        stream& s,
        boost::system::error_code& ec);

    template<class TeardownHandler>
    friend
    BOOST_BEAST_DECL
    void
    async_teardown(
        role_type role,
        stream& s,
        TeardownHandler&& handler);
#endif
};

#if ! BOOST_BEAST_DOXYGEN
inline
void
beast_close_socket(stream& s)
{
    s.close();
}
#endif

#if BOOST_BEAST_DOXYGEN
/** Return a new stream connected to the given stream

    @param to The stream to connect to.

    @param args Optional arguments forwarded to the new stream's constructor.

    @return The new, connected stream.
*/
template<class... Args>
stream
connect(stream& to, Args&&... args);

#else
BOOST_BEAST_DECL
stream
connect(stream& to);

BOOST_BEAST_DECL
void
connect(stream& s1, stream& s2);

template<class Arg1, class... ArgN>
stream
connect(stream& to, Arg1&& arg1, ArgN&&... argn);
#endif

} // test
} // beast
} // boost

#include <boost/beast/_experimental/test/impl/stream.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/_experimental/test/impl/stream.ipp>
#endif

#endif

/* stream.hpp
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
*/