//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_BASIC_STREAM_HPP
#define BOOST_BEAST_CORE_BASIC_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/stream_base.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/rate_policy.hpp>
#include <boost/beast/core/role.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/config/workaround.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <chrono>
#include <limits>
#include <memory>

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

/** A stream socket wrapper with timeouts, an executor, and a rate limit policy.

    This stream wraps a `net::basic_stream_socket` to provide
    the following features:

    @li An <em>Executor</em> may be associated with the stream, which will
    be used to invoke any completion handlers which do not already have
    an associated executor. This achieves support for
    <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1322r0.html">[P1322R0] Networking TS enhancement to enable custom I/O executors</a>.

    @li Timeouts may be specified for each logical asynchronous operation
    performing any reading, writing, or connecting.

    @li A <em>RatePolicy</em> may be associated with the stream, to implement
    rate limiting through the policy's interface.

    Although the stream supports multiple concurrent outstanding asynchronous
    operations, the stream object is not thread-safe. The caller is responsible
    for ensuring that the stream is accessed from only one thread at a time.
    This includes the times when the stream, and its underlying socket, are
    accessed by the networking implementation. To meet this thread safety
    requirement, all asynchronous operations must be performed by the stream
    within the same implicit strand (only one thread `net::io_context::run`)
    or within the same explicit strand, such as an instance of `net::strand`.

    Completion handlers with explicit associated executors (such as those
    arising from use of `net::bind_executor`) will be invoked by the stream
    using the associated executor. Otherwise, the completion handler will
    be invoked by the executor associated with the stream upon construction.
    The type of executor used with this stream must meet the following
    requirements:

    @li Function objects submitted to the executor shall never run
        concurrently with each other.

    The executor type `net::strand` meets these requirements. Use of a
    strand as the executor in the stream class template offers an additional
    notational convenience: the strand does not need to be specified in
    each individual initiating function call.

    Unlike other stream wrappers, the underlying socket is accessed
    through the @ref socket member function instead of `next_layer`.
    This causes the @ref basic_stream to be returned in calls
    to @ref get_lowest_layer.

    @par Usage

    To use this stream declare an instance of the class. Then, before
    each logical operation for which a timeout is desired, call
    @ref expires_after with a duration, or call @ref expires_at with a
    time point. Alternatively, call @ref expires_never to disable the
    timeout for subsequent logical operations. A logical operation
    is any series of one or more direct or indirect calls to the timeout
    stream's asynchronous read, asynchronous write, or asynchronous connect
    functions.

    When a timeout is set and a mixed operation is performed (one that
    includes both reads and writes, for example) the timeout applies
    to all of the intermediate asynchronous operations used in the
    enclosing operation. This allows timeouts to be applied to stream
    algorithms which were not written specifically to allow for timeouts,
    when those algorithms are passed a timeout stream with a timeout set.

    When a timeout occurs the socket will be closed, canceling any
    pending I/O operations. The completion handlers for these canceled
    operations will be invoked with the error @ref beast::error::timeout.

    @par Examples

    This function reads an HTTP request with a timeout, then sends the
    HTTP response with a different timeout.

    @code
    void process_http_1 (tcp_stream& stream, net::yield_context yield)
    {
        flat_buffer buffer;
        http::request<http::empty_body> req;

        // Read the request, with a 15 second timeout
        stream.expires_after(std::chrono::seconds(15));
        http::async_read(stream, buffer, req, yield);

        // Calculate the response
        http::response<http::string_body> res = make_response(req);

        // Send the response, with a 30 second timeout.
        stream.expires_after (std::chrono::seconds(30));
        http::async_write (stream, res, yield);
    }
    @endcode

    The example above could be expressed using a single timeout with a
    simple modification. The function that follows first reads an HTTP
    request then sends the HTTP response, with a single timeout that
    applies to the entire combined operation of reading and writing:

    @code
    void process_http_2 (tcp_stream& stream, net::yield_context yield)
    {
        flat_buffer buffer;
        http::request<http::empty_body> req;

        // Require that the read and write combined take no longer than 30 seconds
        stream.expires_after(std::chrono::seconds(30));

        http::async_read(stream, buffer, req, yield);

        http::response<http::string_body> res = make_response(req);
        http::async_write (stream, res, yield);
    }
    @endcode

    Some stream algorithms, such as `ssl::stream::async_handshake` perform
    both reads and writes. A timeout set before calling the initiating function
    of such composite stream algorithms will apply to the entire composite
    operation. For example, a timeout may be set on performing the SSL handshake
    thusly:

    @code
    void do_ssl_handshake (net::ssl::stream<tcp_stream>& stream, net::yield_context yield)
    {
        // Require that the SSL handshake take no longer than 10 seconds
        stream.expires_after(std::chrono::seconds(10));

        stream.async_handshake(net::ssl::stream_base::client, yield);
    }
    @endcode

    @par Blocking I/O

    Synchronous functions behave identically as that of the wrapped
    `net::basic_stream_socket`. Timeouts are not available when performing
    blocking calls.

    @tparam Protocol A type meeting the requirements of <em>Protocol</em>
    representing the protocol the protocol to use for the basic stream socket.
    A common choice is `net::ip::tcp`.

    @tparam Executor A type meeting the requirements of <em>Executor</em> to
    be used for submitting all completion handlers which do not already have an
    associated executor. If this type is omitted, the default of `net::executor`
    will be used.

    @par Thread Safety
    <em>Distinct objects</em>: Safe.@n
    <em>Shared objects</em>: Unsafe. The application must also ensure
    that all asynchronous operations are performed within the same
    implicit or explicit strand.

    @see

    @li <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1322r0.html">[P1322R0] Networking TS enhancement to enable custom I/O executors</a>.
*/
template<
    class Protocol,
    class Executor = net::executor,
    class RatePolicy = unlimited_rate_policy
>
class basic_stream
#if ! BOOST_BEAST_DOXYGEN
    : private detail::stream_base
#endif
{
public:
    /// The type of the underlying socket.
    using socket_type =
        net::basic_stream_socket<Protocol, Executor>;

    /** The type of the executor associated with the stream.

        This will be the type of executor used to invoke completion
        handlers which do not have an explicit associated executor.
    */
    using executor_type = beast::executor_type<socket_type>;

    /// Rebinds the stream type to another executor.
    template<class Executor1>
    struct rebind_executor
    {
        /// The stream type when rebound to the specified executor.
        using other = basic_stream<
            Protocol, Executor1, RatePolicy>;
    };

    /// The protocol type.
    using protocol_type = Protocol;

    /// The endpoint type.
    using endpoint_type = typename Protocol::endpoint;

private:
    static_assert(net::is_executor<Executor>::value,
        "Executor type requirements not met");

    struct impl_type
        : boost::enable_shared_from_this<impl_type>
        , boost::empty_value<RatePolicy>
    {
        // must come first
        net::basic_stream_socket<
            Protocol, Executor> socket;

        op_state read;
        op_state write;
#if 0
        net::basic_waitable_timer<
            std::chrono::steady_clock,
            net::wait_traits<
                std::chrono::steady_clock>,
            Executor> timer; // rate timer;
#else
        net::steady_timer timer;
#endif
        int waiting = 0;

        impl_type(impl_type&&) = default;

        template<class... Args>
        explicit
        impl_type(std::false_type, Args&&...);

        template<class RatePolicy_, class... Args>
        explicit
        impl_type(std::true_type,
            RatePolicy_&& policy, Args&&...);

        impl_type& operator=(impl_type&&) = delete;

        beast::executor_type<socket_type>
        ex() noexcept
        {
            return this->socket.get_executor();
        }

        RatePolicy&
        policy() noexcept
        {
            return this->boost::empty_value<RatePolicy>::get();
        }

        RatePolicy const&
        policy() const noexcept
        {
            return this->boost::empty_value<RatePolicy>::get();
        }

        template<class Executor2>
        void on_timer(Executor2 const& ex2);

        void reset();           // set timeouts to never
        void close() noexcept;  // cancel everything
    };

    // We use shared ownership for the state so it can
    // outlive the destruction of the stream_socket object,
    // in the case where there is no outstanding read or write
    // but the implementation is still waiting on a timer.
    boost::shared_ptr<impl_type> impl_;

    template<class Executor2>
    struct timeout_handler;

    struct ops;

#if ! BOOST_BEAST_DOXYGEN
    // boost::asio::ssl::stream needs these
    // DEPRECATED
    template<class>
    friend class boost::asio::ssl::stream;
    // DEPRECATED
    using lowest_layer_type = socket_type;
    // DEPRECATED
    lowest_layer_type&
    lowest_layer() noexcept
    {
        return impl_->socket;
    }
    // DEPRECATED
    lowest_layer_type const&
    lowest_layer() const noexcept
    {
        return impl_->socket;
    }
#endif

public:
    /** Destructor

        This function destroys the stream, cancelling any outstanding
        asynchronous operations associated with the socket as if by
        calling cancel.
    */
    ~basic_stream();

    /** Constructor

        This constructor creates the stream by forwarding all arguments
        to the underlying socket. The socket then needs to be open and
        connected or accepted before data can be sent or received on it.

        @param args A list of parameters forwarded to the constructor of
        the underlying socket.
    */
#if BOOST_BEAST_DOXYGEN
    template<class... Args>
    explicit
    basic_stream(Args&&... args);
#else
    template<class Arg0, class... Args,
        class = typename std::enable_if<
        ! std::is_constructible<RatePolicy, Arg0>::value>::type>
    explicit
    basic_stream(Arg0&& argo, Args&&... args);
#endif

    /** Constructor

        This constructor creates the stream with the specified rate
        policy, and forwards all remaining arguments to the underlying
        socket. The socket then needs to be open and connected or
        accepted before data can be sent or received on it.

        @param policy The rate policy object to use. The stream will
        take ownership of this object by decay-copy.

        @param args A list of parameters forwarded to the constructor of
        the underlying socket.
    */
#if BOOST_BEAST_DOXYGEN
    template<class RatePolicy_, class... Args>
    explicit
    basic_stream(RatePolicy_&& policy, Args&&... args);
#else
    template<class RatePolicy_, class Arg0, class... Args,
        class = typename std::enable_if<
            std::is_constructible<
                RatePolicy, RatePolicy_>::value>::type>
    basic_stream(
        RatePolicy_&& policy, Arg0&& arg, Args&&... args);
#endif

    /** Move constructor

        @param other The other object from which the move will occur.

        @note Following the move, the moved-from object is in the
        same state as if newly constructed.
    */
    basic_stream(basic_stream&& other);

    /// Move assignment (deleted).
    basic_stream& operator=(basic_stream&&) = delete;

    /// Return a reference to the underlying socket
    socket_type&
    socket() noexcept
    {
        return impl_->socket;
    }

    /// Return a reference to the underlying socket
    socket_type const&
    socket() const noexcept
    {
        return impl_->socket;
    }

    /** Release ownership of the underlying socket.

        This function causes all outstanding asynchronous connect,
        read, and write operations to be canceled as if by a call
        to @ref cancel. Ownership of the underlying socket is then
        transferred to the caller.
    */
    socket_type
    release_socket();

    //--------------------------------------------------------------------------

    /// Returns the rate policy associated with the object
    RatePolicy&
    rate_policy() noexcept
    {
        return impl_->policy();
    }

    /// Returns the rate policy associated with the object
    RatePolicy const&
    rate_policy() const noexcept
    {
        return impl_->policy();
    }

    /** Set the timeout for the next logical operation.

        This sets either the read timer, the write timer, or
        both timers to expire after the specified amount of time
        has elapsed. If a timer expires when the corresponding
        asynchronous operation is outstanding, the stream will be
        closed and any outstanding operations will complete with the
        error @ref beast::error::timeout. Otherwise, if the timer
        expires while no operations are outstanding, and the expiraton
        is not set again, the next operation will time out immediately.

        The timer applies collectively to any asynchronous reads
        or writes initiated after the expiration is set, until the
        expiration is set again. A call to @ref async_connect
        counts as both a read and a write.

        @param expiry_time The amount of time after which a logical
        operation should be considered timed out.
    */
    void
    expires_after(
        std::chrono::nanoseconds expiry_time);

    /** Set the timeout for the next logical operation.

        This sets either the read timer, the write timer, or both
        timers to expire at the specified time point. If a timer
        expires when the corresponding asynchronous operation is
        outstanding, the stream will be closed and any outstanding
        operations will complete with the error @ref beast::error::timeout.
        Otherwise, if the timer expires while no operations are outstanding,
        and the expiraton is not set again, the next operation will time out
        immediately.

        The timer applies collectively to any asynchronous reads
        or writes initiated after the expiration is set, until the
        expiration is set again. A call to @ref async_connect
        counts as both a read and a write.

        @param expiry_time The time point after which a logical
        operation should be considered timed out.
    */
    void
    expires_at(net::steady_timer::time_point expiry_time);

    /// Disable the timeout for the next logical operation.
    void
    expires_never();

    /** Cancel all asynchronous operations associated with the socket.

        This function causes all outstanding asynchronous connect,
        read, and write operations to finish immediately. Completion
        handlers for cancelled operations will receive the error
        `net::error::operation_aborted`. Completion handlers not
        yet invoked whose operations have completed, will receive
        the error corresponding to the result of the operation (which
        may indicate success).
    */
    void
    cancel();

    /** Close the timed stream.

        This cancels all of the outstanding asynchronous operations
        as if by calling @ref cancel, and closes the underlying socket.
    */
    void
    close();

    //--------------------------------------------------------------------------

    /** Get the executor associated with the object.

        This function may be used to obtain the executor object that the
        stream uses to dispatch completion handlers without an assocaited
        executor.

        @return A copy of the executor that stream will use to dispatch handlers.
    */
    executor_type
    get_executor() noexcept
    {
        return impl_->ex();
    }

    /** Connect the stream to the specified endpoint.

        This function is used to connect the underlying socket to the
        specified remote endpoint. The function call will block until
        the connection is successfully made or an error occurs.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        @param ep The remote endpoint to connect to.

        @throws system_error Thrown on failure.

        @see connect
    */
    void
    connect(endpoint_type const& ep)
    {
        socket().connect(ep);
    }

    /** Connect the stream to the specified endpoint.

        This function is used to connect the underlying socket to the
        specified remote endpoint. The function call will block until
        the connection is successfully made or an error occurs.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        @param ep The remote endpoint to connect to.

        @param ec Set to indicate what error occurred, if any.

        @see connect
    */
    void
    connect(endpoint_type const& ep, error_code& ec)
    {
        socket().connect(ep, ec);
    }

    /** Establishes a connection by trying each endpoint in a sequence.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        The algorithm, known as a <em>composed operation</em>, is implemented
        in terms of calls to the underlying socket's `connect` function.

        @param endpoints A sequence of endpoints.

        @returns The successfully connected endpoint.

        @throws system_error Thrown on failure. If the sequence is
        empty, the associated error code is `net::error::not_found`.
        Otherwise, contains the error from the last connection attempt.
    */
    template<class EndpointSequence
    #if ! BOOST_BEAST_DOXYGEN
        ,class = typename std::enable_if<
            net::is_endpoint_sequence<
                EndpointSequence>::value>::type
    #endif
    >
    typename Protocol::endpoint
    connect(EndpointSequence const& endpoints)
    {
        return net::connect(socket(), endpoints);
    }

    /** Establishes a connection by trying each endpoint in a sequence.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        The algorithm, known as a <em>composed operation</em>, is implemented
        in terms of calls to the underlying socket's `connect` function.

        @param endpoints A sequence of endpoints.

        @param ec Set to indicate what error occurred, if any. If the sequence is
        empty, set to `net::error::not_found`. Otherwise, contains the error
        from the last connection attempt.

        @returns On success, the successfully connected endpoint. Otherwise, a
        default-constructed endpoint.
    */
    template<class EndpointSequence
    #if ! BOOST_BEAST_DOXYGEN
        ,class = typename std::enable_if<
            net::is_endpoint_sequence<
                EndpointSequence>::value>::type
    #endif
    >
    typename Protocol::endpoint
    connect(
        EndpointSequence const& endpoints,
        error_code& ec
    )
    {
        return net::connect(socket(), endpoints, ec);
    }

    /** Establishes a connection by trying each endpoint in a sequence.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        The algorithm, known as a <em>composed operation</em>, is implemented
        in terms of calls to the underlying socket's `connect` function.

        @param begin An iterator pointing to the start of a sequence of endpoints.

        @param end An iterator pointing to the end of a sequence of endpoints.

        @returns An iterator denoting the successfully connected endpoint.

        @throws system_error Thrown on failure. If the sequence is
        empty, the associated error code is `net::error::not_found`.
        Otherwise, contains the error from the last connection attempt.
    */
    template<class Iterator>
    Iterator
    connect(
        Iterator begin, Iterator end)
    {
        return net::connect(socket(), begin, end);
    }

    /** Establishes a connection by trying each endpoint in a sequence.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        The algorithm, known as a <em>composed operation</em>, is implemented
        in terms of calls to the underlying socket's `connect` function.

        @param begin An iterator pointing to the start of a sequence of endpoints.

        @param end An iterator pointing to the end of a sequence of endpoints.

        @param ec Set to indicate what error occurred, if any. If the sequence is
        empty, set to boost::asio::error::not_found. Otherwise, contains the error
        from the last connection attempt.

        @returns On success, an iterator denoting the successfully connected
        endpoint. Otherwise, the end iterator.
    */
    template<class Iterator>
    Iterator
    connect(
        Iterator begin, Iterator end,
        error_code& ec)
    {
        return net::connect(socket(), begin, end, ec);
    }

    /** Establishes a connection by trying each endpoint in a sequence.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        The algorithm, known as a <em>composed operation</em>, is implemented
        in terms of calls to the underlying socket's `connect` function.

        @param endpoints A sequence of endpoints.

        @param connect_condition A function object that is called prior to each
        connection attempt. The signature of the function object must be:
        @code
        bool connect_condition(
            error_code const& ec,
            typename Protocol::endpoint const& next);
        @endcode
        The @c ec parameter contains the result from the most recent connect
        operation. Before the first connection attempt, @c ec is always set to
        indicate success. The @c next parameter is the next endpoint to be tried.
        The function object should return true if the next endpoint should be tried,
        and false if it should be skipped.

        @returns The successfully connected endpoint.

        @throws boost::system::system_error Thrown on failure. If the sequence is
        empty, the associated error code is `net::error::not_found`.
        Otherwise, contains the error from the last connection attempt.
    */
    template<
        class EndpointSequence, class ConnectCondition
    #if ! BOOST_BEAST_DOXYGEN
        ,class = typename std::enable_if<
            net::is_endpoint_sequence<
                EndpointSequence>::value>::type
    #endif
    >
    typename Protocol::endpoint
    connect(
        EndpointSequence const& endpoints,
        ConnectCondition connect_condition
    )
    {
        return net::connect(socket(), endpoints, connect_condition);
    }

    /** Establishes a connection by trying each endpoint in a sequence.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        The algorithm, known as a <em>composed operation</em>, is implemented
        in terms of calls to the underlying socket's `connect` function.

        @param endpoints A sequence of endpoints.

        @param connect_condition A function object that is called prior to each
        connection attempt. The signature of the function object must be:
        @code
        bool connect_condition(
            error_code const& ec,
            typename Protocol::endpoint const& next);
        @endcode
        The @c ec parameter contains the result from the most recent connect
        operation. Before the first connection attempt, @c ec is always set to
        indicate success. The @c next parameter is the next endpoint to be tried.
        The function object should return true if the next endpoint should be tried,
        and false if it should be skipped.

        @param ec Set to indicate what error occurred, if any. If the sequence is
        empty, set to `net::error::not_found`. Otherwise, contains the error
        from the last connection attempt.

        @returns On success, the successfully connected endpoint. Otherwise, a
        default-constructed endpoint.
    */
    template<
        class EndpointSequence, class ConnectCondition
    #if ! BOOST_BEAST_DOXYGEN
        ,class = typename std::enable_if<
            net::is_endpoint_sequence<
                EndpointSequence>::value>::type
    #endif
    >
    typename Protocol::endpoint
    connect(
        EndpointSequence const& endpoints,
        ConnectCondition connect_condition,
        error_code& ec)
    {
        return net::connect(socket(), endpoints, connect_condition, ec);
    }

    /** Establishes a connection by trying each endpoint in a sequence.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        The algorithm, known as a <em>composed operation</em>, is implemented
        in terms of calls to the underlying socket's `connect` function.

        @param begin An iterator pointing to the start of a sequence of endpoints.

        @param end An iterator pointing to the end of a sequence of endpoints.

        @param connect_condition A function object that is called prior to each
        connection attempt. The signature of the function object must be:
        @code
        bool connect_condition(
            error_code const& ec,
            typename Protocol::endpoint const& next);
        @endcode
        The @c ec parameter contains the result from the most recent connect
        operation. Before the first connection attempt, @c ec is always set to
        indicate success. The @c next parameter is the next endpoint to be tried.
        The function object should return true if the next endpoint should be tried,
        and false if it should be skipped.

        @returns An iterator denoting the successfully connected endpoint.

        @throws boost::system::system_error Thrown on failure. If the sequence is
        empty, the associated @c error_code is `net::error::not_found`.
        Otherwise, contains the error from the last connection attempt.
    */
    template<
        class Iterator, class ConnectCondition>
    Iterator
    connect(
        Iterator begin, Iterator end,
        ConnectCondition connect_condition)
    {
        return net::connect(socket(), begin, end, connect_condition);
    }

    /** Establishes a connection by trying each endpoint in a sequence.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        The algorithm, known as a <em>composed operation</em>, is implemented
        in terms of calls to the underlying socket's `connect` function.

        @param begin An iterator pointing to the start of a sequence of endpoints.

        @param end An iterator pointing to the end of a sequence of endpoints.

        @param connect_condition A function object that is called prior to each
        connection attempt. The signature of the function object must be:
        @code
        bool connect_condition(
            error_code const& ec,
            typename Protocol::endpoint const& next);
        @endcode
        The @c ec parameter contains the result from the most recent connect
        operation. Before the first connection attempt, @c ec is always set to
        indicate success. The @c next parameter is the next endpoint to be tried.
        The function object should return true if the next endpoint should be tried,
        and false if it should be skipped.

        @param ec Set to indicate what error occurred, if any. If the sequence is
        empty, set to `net::error::not_found`. Otherwise, contains the error
        from the last connection attempt.

        @returns On success, an iterator denoting the successfully connected
        endpoint. Otherwise, the end iterator.
    */
    template<
        class Iterator, class ConnectCondition>
    Iterator
    connect(
        Iterator begin, Iterator end,
        ConnectCondition connect_condition,
        error_code& ec)
    {
        return net::connect(socket(), begin, end, connect_condition, ec);
    }

    /** Connect the stream to the specified endpoint asynchronously.

        This function is used to asynchronously connect the underlying
        socket to the specified remote endpoint. The function call always
        returns immediately.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        If the timeout timer expires while the operation is outstanding,
        the operation will be canceled and the completion handler will be
        invoked with the error @ref error::timeout.

        @param ep The remote endpoint to which the underlying socket will be
        connected. Copies will be made of the endpoint object as required.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
            error_code ec         // Result of operation
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.

        @see async_connect
    */
    template<
        BOOST_BEAST_ASYNC_TPARAM1 ConnectHandler =
            net::default_completion_token_t<executor_type>
    >
    BOOST_BEAST_ASYNC_RESULT1(ConnectHandler)
    async_connect(
        endpoint_type const& ep,
        ConnectHandler&& handler =
            net::default_completion_token_t<
                executor_type>{});

    /** Establishes a connection by trying each endpoint in a sequence asynchronously.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        The algorithm, known as a <em>composed asynchronous operation</em>, is
        implemented in terms of calls to the underlying socket's `async_connect`
        function.

        If the timeout timer expires while the operation is outstanding,
        the current connection attempt will be canceled and the completion
        handler will be invoked with the error @ref error::timeout.

        @param endpoints A sequence of endpoints. This this object must meet
        the requirements of <em>EndpointSequence</em>.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
            // Result of operation. if the sequence is empty, set to
            // net::error::not_found. Otherwise, contains the
            // error from the last connection attempt.
            error_code const& error,

            // On success, the successfully connected endpoint.
            // Otherwise, a default-constructed endpoint.
            typename Protocol::endpoint const& endpoint
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.
    */
    template<
        class EndpointSequence,
        BOOST_ASIO_COMPLETION_TOKEN_FOR(
            void(error_code, typename Protocol::endpoint))
            RangeConnectHandler =
                net::default_completion_token_t<executor_type>
    #if ! BOOST_BEAST_DOXYGEN
        ,class = typename std::enable_if<
            net::is_endpoint_sequence<
                EndpointSequence>::value>::type
    #endif
    >
    BOOST_ASIO_INITFN_RESULT_TYPE(
        RangeConnectHandler,
        void(error_code, typename Protocol::endpoint))
    async_connect(
        EndpointSequence const& endpoints,
        RangeConnectHandler&& handler =
            net::default_completion_token_t<executor_type>{});

    /** Establishes a connection by trying each endpoint in a sequence asynchronously.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        The algorithm, known as a <em>composed asynchronous operation</em>, is
        implemented in terms of calls to the underlying socket's `async_connect`
        function.

        If the timeout timer expires while the operation is outstanding,
        the current connection attempt will be canceled and the completion
        handler will be invoked with the error @ref error::timeout.

        @param endpoints A sequence of endpoints. This this object must meet
        the requirements of <em>EndpointSequence</em>.

        @param connect_condition A function object that is called prior to each
        connection attempt. The signature of the function object must be:
        @code
        bool connect_condition(
            error_code const& ec,
            typename Protocol::endpoint const& next);
        @endcode
        The @c ec parameter contains the result from the most recent connect
        operation. Before the first connection attempt, @c ec is always set to
        indicate success. The @c next parameter is the next endpoint to be tried.
        The function object should return true if the next endpoint should be tried,
        and false if it should be skipped.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
            // Result of operation. if the sequence is empty, set to
            // net::error::not_found. Otherwise, contains the
            // error from the last connection attempt.
            error_code const& error,

            // On success, the successfully connected endpoint.
            // Otherwise, a default-constructed endpoint.
            typename Protocol::endpoint const& endpoint
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.

        @par Example
        The following connect condition function object can be used to output
        information about the individual connection attempts:
        @code
        struct my_connect_condition
        {
            bool operator()(
                error_code const& ec,
                net::ip::tcp::endpoint const& next)
            {
                if (ec)
                    std::cout << "Error: " << ec.message() << std::endl;
                std::cout << "Trying: " << next << std::endl;
                return true;
            }
        };
        @endcode
    */
    template<
        class EndpointSequence,
        class ConnectCondition,
        BOOST_ASIO_COMPLETION_TOKEN_FOR(
            void(error_code, typename Protocol::endpoint))
            RangeConnectHandler =
                net::default_completion_token_t<executor_type>
    #if ! BOOST_BEAST_DOXYGEN
        ,class = typename std::enable_if<
            net::is_endpoint_sequence<
                EndpointSequence>::value>::type
    #endif
    >
    BOOST_ASIO_INITFN_RESULT_TYPE(
        RangeConnectHandler,
        void(error_code, typename Protocol::endpoint))
    async_connect(
        EndpointSequence const& endpoints,
        ConnectCondition connect_condition,
        RangeConnectHandler&& handler =
            net::default_completion_token_t<
                executor_type>{});

    /** Establishes a connection by trying each endpoint in a sequence asynchronously.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The underlying socket is automatically opened if needed.
        An automatically opened socket is not returned to the
        closed state upon failure.

        The algorithm, known as a <em>composed asynchronous operation</em>, is
        implemented in terms of calls to the underlying socket's `async_connect`
        function.

        If the timeout timer expires while the operation is outstanding,
        the current connection attempt will be canceled and the completion
        handler will be invoked with the error @ref error::timeout.

        @param begin An iterator pointing to the start of a sequence of endpoints.

        @param end An iterator pointing to the end of a sequence of endpoints.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
            // Result of operation. if the sequence is empty, set to
            // net::error::not_found. Otherwise, contains the
            // error from the last connection attempt.
            error_code const& error,

            // On success, an iterator denoting the successfully
            // connected endpoint. Otherwise, the end iterator.
            Iterator iterator
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.
    */
    template<
        class Iterator,
        BOOST_ASIO_COMPLETION_TOKEN_FOR(
            void(error_code, Iterator))
            IteratorConnectHandler =
                net::default_completion_token_t<executor_type>>
    BOOST_ASIO_INITFN_RESULT_TYPE(
        IteratorConnectHandler,
        void(error_code, Iterator))
    async_connect(
        Iterator begin, Iterator end,
        IteratorConnectHandler&& handler =
            net::default_completion_token_t<executor_type>{});

    /** Establishes a connection by trying each endpoint in a sequence asynchronously.

        This function attempts to connect the stream to one of a sequence of
        endpoints by trying each endpoint until a connection is successfully
        established.
        The algorithm, known as a <em>composed asynchronous operation</em>, is
        implemented in terms of calls to the underlying socket's `async_connect`
        function.

        If the timeout timer expires while the operation is outstanding,
        the current connection attempt will be canceled and the completion
        handler will be invoked with the error @ref error::timeout.

        @param begin An iterator pointing to the start of a sequence of endpoints.

        @param end An iterator pointing to the end of a sequence of endpoints.

        @param connect_condition A function object that is called prior to each
        connection attempt. The signature of the function object must be:
        @code
        bool connect_condition(
            error_code const& ec,
            Iterator next);
        @endcode

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
            // Result of operation. if the sequence is empty, set to
            // net::error::not_found. Otherwise, contains the
            // error from the last connection attempt.
            error_code const& error,

            // On success, an iterator denoting the successfully
            // connected endpoint. Otherwise, the end iterator.
            Iterator iterator
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.
    */
    template<
        class Iterator,
        class ConnectCondition,
        BOOST_ASIO_COMPLETION_TOKEN_FOR(
            void(error_code, Iterator))
            IteratorConnectHandler =
                net::default_completion_token_t<executor_type>>
    BOOST_ASIO_INITFN_RESULT_TYPE(
        IteratorConnectHandler,
        void(error_code, Iterator))
    async_connect(
        Iterator begin, Iterator end,
        ConnectCondition connect_condition,
        IteratorConnectHandler&& handler =
            net::default_completion_token_t<executor_type>{});

    //--------------------------------------------------------------------------

    /** Read some data.

        This function is used to read some data from the stream.

        The call blocks until one of the following is true:

        @li One or more bytes are read from the stream.

        @li An error occurs.

        @param buffers The buffers into which the data will be read. If the
        size of the buffers is zero bytes, the call always returns
        immediately with no error.

        @returns The number of bytes read.

        @throws system_error Thrown on failure.

        @note The `read_some` operation may not receive all of the requested
        number of bytes. Consider using the function `net::read` if you need
        to ensure that the requested amount of data is read before the
        blocking operation completes.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(MutableBufferSequence const& buffers)
    {
        return impl_->socket.read_some(buffers);
    }

    /** Read some data.

        This function is used to read some data from the underlying socket.

        The call blocks until one of the following is true:

        @li One or more bytes are read from the stream.

        @li An error occurs.

        @param buffers The buffers into which the data will be read. If the
        size of the buffers is zero bytes, the call always returns
        immediately with no error.

        @param ec Set to indicate what error occurred, if any.

        @returns The number of bytes read.

        @note The `read_some` operation may not receive all of the requested
        number of bytes. Consider using the function `net::read` if you need
        to ensure that the requested amount of data is read before the
        blocking operation completes.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(
        MutableBufferSequence const& buffers,
        error_code& ec)
    {
        return impl_->socket.read_some(buffers, ec);
    }

    /** Read some data asynchronously.

        This function is used to asynchronously read data from the stream.

        This call always returns immediately. The asynchronous operation
        will continue until one of the following conditions is true:

        @li One or more bytes are read from the stream.

        @li An error occurs.

        The algorithm, known as a <em>composed asynchronous operation</em>,
        is implemented in terms of calls to the next layer's `async_read_some`
        function. The program must ensure that no other calls to @ref read_some
        or @ref async_read_some are performed until this operation completes.

        If the timeout timer expires while the operation is outstanding,
        the operation will be canceled and the completion handler will be
        invoked with the error @ref error::timeout.

        @param buffers The buffers into which the data will be read. If the size
        of the buffers is zero bytes, the operation always completes immediately
        with no error.
        Although the buffers object may be copied as necessary, ownership of the
        underlying memory blocks is retained by the caller, which must guarantee
        that they remain valid until the handler is called.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
            error_code error,               // Result of operation.
            std::size_t bytes_transferred   // Number of bytes read.
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.

        @note The `async_read_some` operation may not receive all of the requested
        number of bytes. Consider using the function `net::async_read` if you need
        to ensure that the requested amount of data is read before the asynchronous
        operation completes.
    */
    template<
        class MutableBufferSequence,
        BOOST_BEAST_ASYNC_TPARAM2 ReadHandler =
            net::default_completion_token_t<executor_type>
    >
    BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
    async_read_some(
        MutableBufferSequence const& buffers,
        ReadHandler&& handler =
            net::default_completion_token_t<executor_type>{}
    );

    /** Write some data.

        This function is used to write some data to the stream.

        The call blocks until one of the following is true:

        @li One or more bytes are written to the stream.

        @li An error occurs.

        @param buffers The buffers from which the data will be written. If the
        size of the buffers is zero bytes, the call always returns immediately
        with no error.

        @returns The number of bytes written.

        @throws system_error Thrown on failure.

        @note The `write_some` operation may not transmit all of the requested
        number of bytes. Consider using the function `net::write` if you need
        to ensure that the requested amount of data is written before the
        blocking operation completes.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(ConstBufferSequence const& buffers)
    {
        return impl_->socket.write_some(buffers);
    }

    /** Write some data.

        This function is used to write some data to the stream.

        The call blocks until one of the following is true:

        @li One or more bytes are written to the stream.

        @li An error occurs.

        @param buffers The buffers from which the data will be written. If the
        size of the buffers is zero bytes, the call always returns immediately
        with no error.

        @param ec Set to indicate what error occurred, if any.

        @returns The number of bytes written.

        @throws system_error Thrown on failure.

        @note The `write_some` operation may not transmit all of the requested
        number of bytes. Consider using the function `net::write` if you need
        to ensure that the requested amount of data is written before the
        blocking operation completes.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(
        ConstBufferSequence const& buffers,
        error_code& ec)
    {
        return impl_->socket.write_some(buffers, ec);
    }

    /** Write some data asynchronously.

        This function is used to asynchronously write data to the underlying socket.

        This call always returns immediately. The asynchronous operation
        will continue until one of the following conditions is true:

        @li One or more bytes are written to the stream.

        @li An error occurs.

        The algorithm, known as a <em>composed asynchronous operation</em>,
        is implemented in terms of calls to the next layer's `async_write_some`
        function. The program must ensure that no other calls to @ref async_write_some
        are performed until this operation completes.

        If the timeout timer expires while the operation is outstanding,
        the operation will be canceled and the completion handler will be
        invoked with the error @ref error::timeout.

        @param buffers The buffers from which the data will be written. If the
        size of the buffers is zero bytes, the operation  always completes
        immediately with no error.
        Although the buffers object may be copied as necessary, ownership of the
        underlying memory blocks is retained by the caller, which must guarantee
        that they remain valid until the handler is called.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
            error_code error,               // Result of operation.
            std::size_t bytes_transferred   // Number of bytes written.
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.

        @note The `async_write_some` operation may not transmit all of the requested
        number of bytes. Consider using the function `net::async_write` if you need
        to ensure that the requested amount of data is sent before the asynchronous
        operation completes.
    */
    template<
        class ConstBufferSequence,
        BOOST_BEAST_ASYNC_TPARAM2 WriteHandler =
            net::default_completion_token_t<Executor>
    >
    BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
    async_write_some(
        ConstBufferSequence const& buffers,
        WriteHandler&& handler =
            net::default_completion_token_t<Executor>{});
};

} // beast
} // boost

#include <boost/beast/core/impl/basic_stream.hpp>

#endif

/* basic_stream.hpp
+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
*/