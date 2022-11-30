//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_STREAM_TRAITS_HPP
#define BOOST_BEAST_STREAM_TRAITS_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/static_const.hpp>
#include <boost/beast/core/detail/stream_traits.hpp>
#include <boost/asio/basic_socket.hpp>

namespace boost {
namespace beast {

/** A trait to determine the lowest layer type of a stack of stream layers.

    If `t.next_layer()` is well-defined for an object `t` of type `T`,
    then `lowest_layer_type<T>` will be an alias for
    `lowest_layer_type<decltype(t.next_layer())>`,
    otherwise it will be the type
    `std::remove_reference<T>`.

    @param T The type to determine the lowest layer type of.

    @return The type of the lowest layer.
*/
template<class T>
#if BOOST_BEAST_DOXYGEN
using lowest_layer_type = __see_below__;
#else
using lowest_layer_type = detail::lowest_layer_type<T>;
#endif

/** Return the lowest layer in a stack of stream layers.

    If `t.next_layer()` is well-defined, returns
    `get_lowest_layer(t.next_layer())`. Otherwise, it returns `t`.

    A stream layer is an object of class type which wraps another object through
    composition, and meets some or all of the named requirements of the wrapped
    type while optionally changing behavior. Examples of stream layers include
    `net::ssl::stream` or @ref beast::websocket::stream. The owner of a stream
    layer can interact directly with the wrapper, by passing it to stream
    algorithms. Or, the owner can obtain a reference to the wrapped object by
    calling `next_layer()` and accessing its members. This is necessary when it is
    desired to access functionality in the next layer which is not available
    in the wrapper. For example, @ref websocket::stream permits reading and
    writing, but in order to establish the underlying connection, members
    of the wrapped stream (such as `connect`) must be invoked directly.

    Usually the last object in the chain of composition is the concrete socket
    object (for example, a `net::basic_socket` or a class derived from it).
    The function @ref get_lowest_layer exists to easily obtain the concrete
    socket when it is desired to perform an action that is not prescribed by
    a named requirement, such as changing a socket option, cancelling all
    pending asynchronous I/O, or closing the socket (perhaps by using
    @ref close_socket).

    @par Example
    @code
    // Set non-blocking mode on a stack of stream
    // layers with a regular socket at the lowest layer.
    template <class Stream>
    void set_non_blocking (Stream& stream)
    {
        error_code ec;
        // A compile error here means your lowest layer is not the right type!
        get_lowest_layer(stream).non_blocking(true, ec);
        if(ec)
            throw system_error{ec};
    }
    @endcode

    @param t The layer in a stack of layered objects for which the lowest layer is returned.

    @see close_socket, lowest_layer_type
*/
template<class T>
lowest_layer_type<T>&
get_lowest_layer(T& t) noexcept
{
    return detail::get_lowest_layer_impl(
        t, detail::has_next_layer<T>{});
}

//------------------------------------------------------------------------------

/** A trait to determine the return type of get_executor.

    This type alias will be the type of values returned by
    by calling member `get_exector` on an object of type `T&`.

    @param T The type to query

    @return The type of values returned from `get_executor`.
*/
// Workaround for ICE on gcc 4.8
#if BOOST_BEAST_DOXYGEN
template<class T>
using executor_type = __see_below__;
#elif BOOST_WORKAROUND(BOOST_GCC, < 40900)
template<class T>
using executor_type =
    typename std::decay<T>::type::executor_type;
#else
template<class T>
using executor_type =
    decltype(std::declval<T&>().get_executor());
#endif

/** Determine if `T` has the `get_executor` member function.

    Metafunctions are used to perform compile time checking of template
    types. This type will be `std::true_type` if `T` has the member
    function with the correct signature, else type will be `std::false_type`. 

    @par Example

    Use with tag dispatching:

    @code
    template<class T>
    void maybe_hello(T const& t, std::true_type)
    {
        net::post(
            t.get_executor(),
            []
            {
                std::cout << "Hello, world!" << std::endl;
            });
    }

    template<class T>
    void maybe_hello(T const&, std::false_type)
    {
        // T does not have get_executor
    }

    template<class T>
    void maybe_hello(T const& t)
    {
        maybe_hello(t, has_get_executor<T>{});
    }
    @endcode

    Use with `static_assert`:

    @code
    struct stream
    {
        using executor_type = net::io_context::executor_type;
        executor_type get_executor() noexcept;
    };

    static_assert(has_get_executor<stream>::value, "Missing get_executor member");
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using has_get_executor = __see_below__;
#else
template<class T, class = void>
struct has_get_executor : std::false_type {};

template<class T>
struct has_get_executor<T, boost::void_t<decltype(
    std::declval<T&>().get_executor())>> : std::true_type {};
#endif

//------------------------------------------------------------------------------

/** Determine if at type meets the requirements of <em>SyncReadStream</em>.

    Metafunctions are used to perform compile time checking of template
    types. This type will be `std::true_type` if `T` meets the requirements,
    else the type will be `std::false_type`. 

    @par Example
    Use with `static_assert`:
    @code
    template<class SyncReadStream>
    void f(SyncReadStream& stream)
    {
        static_assert(is_sync_read_stream<SyncReadStream>::value,
            "SyncReadStream type requirements not met");
    ...
    @endcode

    Use with `std::enable_if` (SFINAE):
    @code
    template<class SyncReadStream>
    typename std::enable_if<is_sync_read_stream<SyncReadStream>::value>::type
    f(SyncReadStream& stream);
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_sync_read_stream = __see_below__;
#else
template<class T, class = void>
struct is_sync_read_stream : std::false_type {};

template<class T>
struct is_sync_read_stream<T, boost::void_t<decltype(
    std::declval<std::size_t&>() = std::declval<T&>().read_some(
        std::declval<detail::MutableBufferSequence>()),
    std::declval<std::size_t&>() = std::declval<T&>().read_some(
        std::declval<detail::MutableBufferSequence>(),
        std::declval<boost::system::error_code&>())
            )>> : std::true_type {};
#endif

/** Determine if `T` meets the requirements of <em>SyncWriteStream</em>.

    Metafunctions are used to perform compile time checking of template
    types. This type will be `std::true_type` if `T` meets the requirements,
    else the type will be `std::false_type`. 

    @par Example

    Use with `static_assert`:

    @code
    template<class SyncReadStream>
    void f(SyncReadStream& stream)
    {
        static_assert(is_sync_read_stream<SyncReadStream>::value,
            "SyncReadStream type requirements not met");
    ...
    @endcode

    Use with `std::enable_if` (SFINAE):

    @code
    template<class SyncReadStream>
    typename std::enable_if<is_sync_read_stream<SyncReadStream>::value>::type
    f(SyncReadStream& stream);
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_sync_write_stream = __see_below__;
#else
template<class T, class = void>
struct is_sync_write_stream : std::false_type {};

template<class T>
struct is_sync_write_stream<T, boost::void_t<decltype(
    (
    std::declval<std::size_t&>() = std::declval<T&>().write_some(
        std::declval<detail::ConstBufferSequence>()))
    ,std::declval<std::size_t&>() = std::declval<T&>().write_some(
        std::declval<detail::ConstBufferSequence>(),
        std::declval<boost::system::error_code&>())
            )>> : std::true_type {};
#endif

/** Determine if `T` meets the requirements of @b SyncStream.

    Metafunctions are used to perform compile time checking of template
    types. This type will be `std::true_type` if `T` meets the requirements,
    else the type will be `std::false_type`. 

    @par Example

    Use with `static_assert`:

    @code
    template<class SyncStream>
    void f(SyncStream& stream)
    {
        static_assert(is_sync_stream<SyncStream>::value,
            "SyncStream type requirements not met");
    ...
    @endcode

    Use with `std::enable_if` (SFINAE):

    @code
    template<class SyncStream>
    typename std::enable_if<is_sync_stream<SyncStream>::value>::type
    f(SyncStream& stream);
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_sync_stream = __see_below__;
#else
template<class T>
using is_sync_stream = std::integral_constant<bool,
    is_sync_read_stream<T>::value && is_sync_write_stream<T>::value>;
#endif

//------------------------------------------------------------------------------

/** Determine if `T` meets the requirements of <em>AsyncReadStream</em>.

    Metafunctions are used to perform compile time checking of template
    types. This type will be `std::true_type` if `T` meets the requirements,
    else the type will be `std::false_type`. 

    @par Example
    
    Use with `static_assert`:
    
    @code
    template<class AsyncReadStream>
    void f(AsyncReadStream& stream)
    {
        static_assert(is_async_read_stream<AsyncReadStream>::value,
            "AsyncReadStream type requirements not met");
    ...
    @endcode
    
    Use with `std::enable_if` (SFINAE):
    
    @code
        template<class AsyncReadStream>
        typename std::enable_if<is_async_read_stream<AsyncReadStream>::value>::type
        f(AsyncReadStream& stream);
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_async_read_stream = __see_below__;
#else
template<class T, class = void>
struct is_async_read_stream : std::false_type {};

template<class T>
struct is_async_read_stream<T, boost::void_t<decltype(
    std::declval<T&>().async_read_some(
        std::declval<detail::MutableBufferSequence>(),
        std::declval<detail::ReadHandler>())
            )>> : std::integral_constant<bool,
    has_get_executor<T>::value
        > {};
#endif

/** Determine if `T` meets the requirements of <em>AsyncWriteStream</em>.

    Metafunctions are used to perform compile time checking of template
    types. This type will be `std::true_type` if `T` meets the requirements,
    else the type will be `std::false_type`. 

    @par Example

    Use with `static_assert`:

    @code
    template<class AsyncWriteStream>
    void f(AsyncWriteStream& stream)
    {
        static_assert(is_async_write_stream<AsyncWriteStream>::value,
            "AsyncWriteStream type requirements not met");
    ...
    @endcode

    Use with `std::enable_if` (SFINAE):

    @code
    template<class AsyncWriteStream>
    typename std::enable_if<is_async_write_stream<AsyncWriteStream>::value>::type
    f(AsyncWriteStream& stream);
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_async_write_stream = __see_below__;
#else
template<class T, class = void>
struct is_async_write_stream : std::false_type {};

template<class T>
struct is_async_write_stream<T, boost::void_t<decltype(
    std::declval<T&>().async_write_some(
        std::declval<detail::ConstBufferSequence>(),
        std::declval<detail::WriteHandler>())
            )>> : std::integral_constant<bool,
    has_get_executor<T>::value
        > {};
#endif

/** Determine if `T` meets the requirements of @b AsyncStream.

    Metafunctions are used to perform compile time checking of template
    types. This type will be `std::true_type` if `T` meets the requirements,
    else the type will be `std::false_type`. 

    @par Example

    Use with `static_assert`:

    @code
    template<class AsyncStream>
    void f(AsyncStream& stream)
    {
        static_assert(is_async_stream<AsyncStream>::value,
            "AsyncStream type requirements not met");
    ...
    @endcode

    Use with `std::enable_if` (SFINAE):

    @code
    template<class AsyncStream>
    typename std::enable_if<is_async_stream<AsyncStream>::value>::type
    f(AsyncStream& stream);
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_async_stream = __see_below__;
#else
template<class T>
using is_async_stream = std::integral_constant<bool,
    is_async_read_stream<T>::value && is_async_write_stream<T>::value>;
#endif

//------------------------------------------------------------------------------

/** Default socket close function.

    This function is not meant to be called directly. Instead, it
    is called automatically when using @ref close_socket. To enable
    closure of user-defined types or classes derived from a particular
    user-defined type, this function should be overloaded in the
    corresponding namespace for the type in question.

    @see close_socket
*/
template<
    class Protocol,
    class Executor>
void
beast_close_socket(
    net::basic_socket<
        Protocol, Executor>& sock)
{
    boost::system::error_code ec;
    sock.close(ec);
}

namespace detail {

struct close_socket_impl
{
    template<class T>
    void
    operator()(T& t) const
    {
        using beast::beast_close_socket;
        beast_close_socket(t);
    }
};

} // detail

/** Close a socket or socket-like object.

    This function attempts to close an object representing a socket.
    In this context, a socket is an object for which an unqualified
    call to the function `void beast_close_socket(Socket&)` is
    well-defined. The function `beast_close_socket` is a
    <em>customization point</em>, allowing user-defined types to
    provide an algorithm for performing the close operation by
    overloading this function for the type in question.

    Since the customization point is a function call, the normal
    rules for finding the correct overload are applied including
    the rules for argument-dependent lookup ("ADL"). This permits
    classes derived from a type for which a customization is provided
    to inherit the customization point.

    An overload for the networking class template `net::basic_socket`
    is provided, which implements the close algorithm for all socket-like
    objects (hence the name of this customization point). When used
    in conjunction with @ref get_lowest_layer, a generic algorithm
    operating on a layered stream can perform a closure of the underlying
    socket without knowing the exact list of concrete types.

    @par Example 1
    The following generic function synchronously sends a message
    on the stream, then closes the socket.
    @code
    template <class WriteStream>
    void hello_and_close (WriteStream& stream)
    {
        net::write(stream, net::const_buffer("Hello, world!", 13));
        close_socket(get_lowest_layer(stream));
    }
    @endcode

    To enable closure of user defined types, it is necessary to provide
    an overload of the function `beast_close_socket` for the type.

    @par Example 2
    The following code declares a user-defined type which contains a
    private socket, and provides an overload of the customization
    point which closes the private socket.
    @code
    class my_socket
    {
        net::ip::tcp::socket sock_;

    public:
        my_socket(net::io_context& ioc)
            : sock_(ioc)
        {
        }

        friend void beast_close_socket(my_socket& s)
        {
            error_code ec;
            s.sock_.close(ec);
            // ignore the error
        }
    };
    @endcode

    @param sock The socket to close. If the customization point is not
    defined for the type of this object, or one of its base classes,
    then a compiler error results.

    @see beast_close_socket
*/
#if BOOST_BEAST_DOXYGEN
template<class Socket>
void
close_socket(Socket& sock);
#else
BOOST_BEAST_INLINE_VARIABLE(close_socket, detail::close_socket_impl)
#endif

} // beast
} // boost

#endif

/* stream_traits.hpp
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
*/