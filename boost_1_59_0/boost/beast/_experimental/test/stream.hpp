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
#include <boost/beast/_experimental/test/detail/stream_state.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/any_io_executor.hpp>
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
template<class Executor = net::any_io_executor>
class basic_stream;

template<class Executor>
void
teardown(
    role_type,
    basic_stream<Executor>& s,
    boost::system::error_code& ec);

template<class Executor, class TeardownHandler>
void
async_teardown(
    role_type role,
    basic_stream<Executor>& s,
    TeardownHandler&& handler);

template<class Executor>
class basic_stream
{
public:
    /// The type of the executor associated with the object.
    using executor_type =
        Executor;

      /// Rebinds the socket type to another executor.
    template <typename Executor1>
    struct rebind_executor
    {
        /// The socket type when rebound to the specified executor.
        typedef basic_stream<Executor1> other;
    };

private:
    template<class Executor2>
    friend class basic_stream;

    boost::shared_ptr<detail::stream_state> in_;
    boost::weak_ptr<detail::stream_state> out_;

    template<class Handler, class Buffers>
    class read_op;

    struct run_read_op;
    struct run_write_op;

    static
    void
    initiate_read(
        boost::shared_ptr<detail::stream_state> const& in,
        std::unique_ptr<detail::stream_read_op_base>&& op,
        std::size_t buf_size);

#if ! BOOST_BEAST_DOXYGEN
    // boost::asio::ssl::stream needs these
    // DEPRECATED
    template<class>
    friend class boost::asio::ssl::stream;
    // DEPRECATED
    using lowest_layer_type = basic_stream;
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
    ~basic_stream();

    /** Move Constructor

        Moving the stream while asynchronous operations are pending
        results in undefined behavior.
    */
    basic_stream(basic_stream&& other);

    /** Move Constructor

        Moving the stream while asynchronous operations are pending
        results in undefined behavior.
    */
    template<class Executor2>
    basic_stream(basic_stream<Executor2>&& other)
    : in_(std::move(other.in_))
    , out_(std::move(other.out_))
    {
        BOOST_ASSERT(in_->exec.template target<Executor2>() != nullptr);
        in_->exec = executor_type(*in_->exec.template target<Executor2>());
    }

    /** Move Assignment

        Moving the stream while asynchronous operations are pending
        results in undefined behavior.
    */
    basic_stream&
    operator=(basic_stream&& other);

    template<class Executor2>
    basic_stream&
    operator==(basic_stream<Executor2>&& other);

    /** Construct a stream

        The stream will be created in a disconnected state.

        @param ioc The `io_context` object that the stream will use to
        dispatch handlers for any asynchronous operations.
    */
    template <typename ExecutionContext>
    explicit basic_stream(ExecutionContext& context,
        typename std::enable_if<
            std::is_convertible<ExecutionContext&, net::execution_context&>::value
        >::type* = 0)
    : basic_stream(context.get_executor())
    {
    }

    /** Construct a stream

        The stream will be created in a disconnected state.

        @param exec The `executor` object that the stream will use to
        dispatch handlers for any asynchronous operations.
    */
    explicit
    basic_stream(executor_type exec);

    /** Construct a stream

        The stream will be created in a disconnected state.

        @param ioc The `io_context` object that the stream will use to
        dispatch handlers for any asynchronous operations.

        @param fc The @ref fail_count to associate with the stream.
        Each I/O operation performed on the stream will increment the
        fail count.  When the fail count reaches its internal limit,
        a simulated failure error will be raised.
    */
    basic_stream(
        net::io_context& ioc,
        fail_count& fc);

    /** Construct a stream

        The stream will be created in a disconnected state.

        @param ioc The `io_context` object that the stream will use to
        dispatch handlers for any asynchronous operations.

        @param s A string which will be appended to the input area, not
        including the null terminator.
    */
    basic_stream(
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
    basic_stream(
        net::io_context& ioc,
        fail_count& fc,
        string_view s);

    /// Establish a connection
    void
    connect(basic_stream& remote);

    /// Return the executor associated with the object.
    executor_type
    get_executor() noexcept;

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
    string_view
    str() const;

    /// Appends a string to the pending input data
    void
    append(string_view s);

    /// Clear the pending input area
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
    void
    close();

    /** Close the other end of the stream.

        This end of the connection will see
        `error::eof` after reading all the remaining data.
    */
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
        BOOST_ASIO_COMPLETION_TOKEN_FOR(void(error_code, std::size_t)) ReadHandler
            BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
    BOOST_ASIO_INITFN_RESULT_TYPE(ReadHandler, void(error_code, std::size_t))
    async_read_some(
        MutableBufferSequence const& buffers,
        ReadHandler&& handler BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type));

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
        BOOST_ASIO_COMPLETION_TOKEN_FOR(void(error_code, std::size_t)) WriteHandler
            BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
    BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler, void(error_code, std::size_t))
    async_write_some(
        ConstBufferSequence const& buffers,
        WriteHandler&& handler BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type)
        );

#if ! BOOST_BEAST_DOXYGEN
    friend
    void
    teardown<>(
        role_type,
        basic_stream& s,
        boost::system::error_code& ec);

    template<class Ex2, class TeardownHandler>
    friend
    void
    async_teardown(
        role_type role,
        basic_stream<Ex2>& s,
        TeardownHandler&& handler);
#endif
};

#if ! BOOST_BEAST_DOXYGEN
template<class Executor>
void
beast_close_socket(basic_stream<Executor>& s)
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
template<class Executor>
template<class... Args>
basic_stream
connect(basic_stream& to, Args&&... args);

#else
template<class Executor>
basic_stream<Executor>
connect(basic_stream<Executor>& to);

template<class Executor>
void
connect(basic_stream<Executor>& s1, basic_stream<Executor>& s2);

template<class Executor, class Arg1, class... ArgN>
basic_stream<Executor>
connect(basic_stream<Executor>& to, Arg1&& arg1, ArgN&&... argn);
#endif

using stream = basic_stream<>;

} // test
} // beast
} // boost

#include <boost/beast/_experimental/test/impl/stream.hpp>
//#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/_experimental/test/impl/stream.ipp>
//#endif

#endif

/* stream.hpp
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
*/