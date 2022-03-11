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