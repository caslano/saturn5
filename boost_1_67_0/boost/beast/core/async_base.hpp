//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_ASYNC_BASE_HPP
#define BOOST_BEAST_CORE_ASYNC_BASE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/detail/allocator.hpp>
#include <boost/beast/core/detail/async_base.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/handler_alloc_hook.hpp>
#include <boost/asio/handler_continuation_hook.hpp>
#include <boost/asio/handler_invoke_hook.hpp>
#include <boost/asio/post.hpp>
#include <boost/core/exchange.hpp>
#include <boost/core/empty_value.hpp>
#include <utility>

namespace boost {
namespace beast {

/** Base class to assist writing composed operations.

    A function object submitted to intermediate initiating functions during
    a composed operation may derive from this type to inherit all of the
    boilerplate to forward the executor, allocator, and legacy customization
    points associated with the completion handler invoked at the end of the
    composed operation.

    The composed operation must be typical; that is, associated with one
    executor of an I/O object, and invoking a caller-provided completion
    handler when the operation is finished. Classes derived from
    @ref async_base will acquire these properties:

    @li Ownership of the final completion handler provided upon construction.

    @li If the final handler has an associated allocator, this allocator will
        be propagated to the composed operation subclass. Otherwise, the
        associated allocator will be the type specified in the allocator
        template parameter, or the default of `std::allocator<void>` if the
        parameter is omitted.

    @li If the final handler has an associated executor, then it will be used
        as the executor associated with the composed operation. Otherwise,
        the specified `Executor1` will be the type of executor associated
        with the composed operation.

    @li An instance of `net::executor_work_guard` for the instance of `Executor1`
        shall be maintained until either the final handler is invoked, or the
        operation base is destroyed, whichever comes first.

    @li Calls to the legacy customization points
        `asio_handler_invoke`,
        `asio_handler_allocate`,
        `asio_handler_deallocate`, and
        `asio_handler_is_continuation`,
        which use argument-dependent lookup, will be forwarded to the
        legacy customization points associated with the handler.

    @par Example

    The following code demonstrates how @ref async_base may be be used to
    assist authoring an asynchronous initiating function, by providing all of
    the boilerplate to manage the final completion handler in a way that
    maintains the allocator and executor associations:

    @code

    // Asynchronously read into a buffer until the buffer is full, or an error occurs
    template<class AsyncReadStream, class ReadHandler>
    typename net::async_result<ReadHandler, void(error_code, std::size_t)>::return_type
    async_read(AsyncReadStream& stream, net::mutable_buffer buffer, ReadHandler&& handler)
    {
        using handler_type = BOOST_ASIO_HANDLER_TYPE(ReadHandler, void(error_code, std::size_t));
        using base_type = async_base<handler_type, typename AsyncReadStream::executor_type>;

        struct op : base_type
        {
            AsyncReadStream& stream_;
            net::mutable_buffer buffer_;
            std::size_t total_bytes_transferred_;

            op(
                AsyncReadStream& stream,
                net::mutable_buffer buffer,
                handler_type& handler)
                : base_type(std::move(handler), stream.get_executor())
                , stream_(stream)
                , buffer_(buffer)
                , total_bytes_transferred_(0)
            {
                (*this)({}, 0, false); // start the operation
            }

            void operator()(error_code ec, std::size_t bytes_transferred, bool is_continuation = true)
            {
                // Adjust the count of bytes and advance our buffer
                total_bytes_transferred_ += bytes_transferred;
                buffer_ = buffer_ + bytes_transferred;

                // Keep reading until buffer is full or an error occurs
                if(! ec && buffer_.size() > 0)
                    return stream_.async_read_some(buffer_, std::move(*this));

                // Call the completion handler with the result. If `is_continuation` is
                // false, which happens on the first time through this function, then
                // `net::post` will be used to call the completion handler, otherwise
                // the completion handler will be invoked directly.

                this->complete(is_continuation, ec, total_bytes_transferred_);
            }
        };

        net::async_completion<ReadHandler, void(error_code, std::size_t)> init{handler};
        op(stream, buffer, init.completion_handler);
        return init.result.get();
    }

    @endcode

    Data members of composed operations implemented as completion handlers
    do not have stable addresses, as the composed operation object is move
    constructed upon each call to an initiating function. For most operations
    this is not a problem. For complex operations requiring stable temporary
    storage, the class @ref stable_async_base is provided which offers
    additional functionality:

    @li The free function @ref allocate_stable may be used to allocate
    one or more temporary objects associated with the composed operation.

    @li Memory for stable temporary objects is allocated using the allocator
    associated with the composed operation.

    @li Stable temporary objects are automatically destroyed, and the memory
    freed using the associated allocator, either before the final completion
    handler is invoked (a Networking requirement) or when the composed operation
    is destroyed, whichever occurs first.

    @par Temporary Storage Example

    The following example demonstrates how a composed operation may store a
    temporary object.

    @code

    @endcode

    @tparam Handler The type of the completion handler to store.
    This type must meet the requirements of <em>CompletionHandler</em>.

    @tparam Executor1 The type of the executor used when the handler has no
    associated executor. An instance of this type must be provided upon
    construction. The implementation will maintain an executor work guard
    and a copy of this instance.

    @tparam Allocator The allocator type to use if the handler does not
    have an associated allocator. If this parameter is omitted, then
    `std::allocator<void>` will be used. If the specified allocator is
    not default constructible, an instance of the type must be provided
    upon construction.

    @see stable_async_base
*/
template<
    class Handler,
    class Executor1,
    class Allocator = std::allocator<void>
>
class async_base
#if ! BOOST_BEAST_DOXYGEN
    : private boost::empty_value<Allocator>
#endif
{
    static_assert(
        net::is_executor<Executor1>::value,
        "Executor type requirements not met");

    Handler h_;
    net::executor_work_guard<Executor1> wg1_;

    virtual
    void
    before_invoke_hook()
    {
    }

public:
    /** Constructor

        @param handler The final completion handler.
        The type of this object must meet the requirements of <em>CompletionHandler</em>.
        The implementation takes ownership of the handler by performing a decay-copy.

        @param ex1 The executor associated with the implied I/O object
        target of the operation. The implementation shall maintain an
        executor work guard for the lifetime of the operation, or until
        the final completion handler is invoked, whichever is shorter.

        @param alloc The allocator to be associated with objects
        derived from this class. If `Allocator` is default-constructible,
        this parameter is optional and may be omitted.
    */
#if BOOST_BEAST_DOXYGEN
    template<class Handler_>
    async_base(
        Handler&& handler,
        Executor1 const& ex1,
        Allocator const& alloc = Allocator());
#else
    template<
        class Handler_,
        class = typename std::enable_if<
            ! std::is_same<typename
                std::decay<Handler_>::type,
                async_base
            >::value>::type
    >
    async_base(
        Handler_&& handler,
        Executor1 const& ex1)
        : h_(std::forward<Handler_>(handler))
        , wg1_(ex1)
    {
    }

    template<class Handler_>
    async_base(
        Handler_&& handler,
        Executor1 const& ex1,
        Allocator const& alloc)
        : boost::empty_value<Allocator>(
            boost::empty_init_t{}, alloc)
        , h_(std::forward<Handler_>(handler))
        , wg1_(ex1)
    {
    }
#endif

    /// Move Constructor
    async_base(async_base&& other) = default;

    virtual ~async_base() = default;
    async_base(async_base const&) = delete;
    async_base& operator=(async_base const&) = delete;

    /** The type of allocator associated with this object.

        If a class derived from @ref async_base is a completion
        handler, then the associated allocator of the derived class will
        be this type.
    */
    using allocator_type =
        net::associated_allocator_t<Handler, Allocator>;

    /** The type of executor associated with this object.

        If a class derived from @ref async_base is a completion
        handler, then the associated executor of the derived class will
        be this type.
    */
    using executor_type =
        net::associated_executor_t<Handler, Executor1>;

    /** Returns the allocator associated with this object.

        If a class derived from @ref async_base is a completion
        handler, then the object returned from this function will be used
        as the associated allocator of the derived class.
    */
    allocator_type
    get_allocator() const noexcept
    {
        return net::get_associated_allocator(h_,
            boost::empty_value<Allocator>::get());
    }

    /** Returns the executor associated with this object.

        If a class derived from @ref async_base is a completion
        handler, then the object returned from this function will be used
        as the associated executor of the derived class.
    */
    executor_type
    get_executor() const noexcept
    {
        return net::get_associated_executor(
            h_, wg1_.get_executor());
    }

    /// Returns the handler associated with this object
    Handler const&
    handler() const noexcept
    {
        return h_;
    }

    /** Returns ownership of the handler associated with this object

        This function is used to transfer ownership of the handler to
        the caller, by move-construction. After the move, the only
        valid operations on the base object are move construction and
        destruction.
    */
    Handler
    release_handler()
    {
        return std::move(h_);
    }

    /** Invoke the final completion handler, maybe using post.

        This invokes the final completion handler with the specified
        arguments forwarded. It is undefined to call either of
        @ref complete or @ref complete_now more than once.

        Any temporary objects allocated with @ref beast::allocate_stable will
        be automatically destroyed before the final completion handler
        is invoked.

        @param is_continuation If this value is `false`, then the
        handler will be submitted to the executor using `net::post`.
        Otherwise the handler will be invoked as if by calling
        @ref complete_now.

        @param args A list of optional parameters to invoke the handler
        with. The completion handler must be invocable with the parameter
        list, or else a compilation error will result.
    */
    template<class... Args>
    void
    complete(bool is_continuation, Args&&... args)
    {
        this->before_invoke_hook();
        if(! is_continuation)
        {
            auto const ex = get_executor();
            net::post(net::bind_executor(
                ex,
                beast::bind_front_handler(
                    std::move(h_),
                    std::forward<Args>(args)...)));
            wg1_.reset();
        }
        else
        {
            wg1_.reset();
            h_(std::forward<Args>(args)...);
        }
    }

    /** Invoke the final completion handler.

        This invokes the final completion handler with the specified
        arguments forwarded. It is undefined to call either of
        @ref complete or @ref complete_now more than once.

        Any temporary objects allocated with @ref beast::allocate_stable will
        be automatically destroyed before the final completion handler
        is invoked.

        @param args A list of optional parameters to invoke the handler
        with. The completion handler must be invocable with the parameter
        list, or else a compilation error will result.
    */
    template<class... Args>
    void
    complete_now(Args&&... args)
    {
        this->before_invoke_hook();
        wg1_.reset();
        h_(std::forward<Args>(args)...);
    }

#if ! BOOST_BEAST_DOXYGEN
    Handler*
    get_legacy_handler_pointer() noexcept
    {
        return std::addressof(h_);
    }
#endif
};

//------------------------------------------------------------------------------

/** Base class to provide completion handler boilerplate for composed operations.

    A function object submitted to intermediate initiating functions during
    a composed operation may derive from this type to inherit all of the
    boilerplate to forward the executor, allocator, and legacy customization
    points associated with the completion handler invoked at the end of the
    composed operation.

    The composed operation must be typical; that is, associated with one
    executor of an I/O object, and invoking a caller-provided completion
    handler when the operation is finished. Classes derived from
    @ref async_base will acquire these properties:

    @li Ownership of the final completion handler provided upon construction.

    @li If the final handler has an associated allocator, this allocator will
        be propagated to the composed operation subclass. Otherwise, the
        associated allocator will be the type specified in the allocator
        template parameter, or the default of `std::allocator<void>` if the
        parameter is omitted.

    @li If the final handler has an associated executor, then it will be used
        as the executor associated with the composed operation. Otherwise,
        the specified `Executor1` will be the type of executor associated
        with the composed operation.

    @li An instance of `net::executor_work_guard` for the instance of `Executor1`
        shall be maintained until either the final handler is invoked, or the
        operation base is destroyed, whichever comes first.

    @li Calls to the legacy customization points
        `asio_handler_invoke`,
        `asio_handler_allocate`,
        `asio_handler_deallocate`, and
        `asio_handler_is_continuation`,
        which use argument-dependent lookup, will be forwarded to the
        legacy customization points associated with the handler.

    Data members of composed operations implemented as completion handlers
    do not have stable addresses, as the composed operation object is move
    constructed upon each call to an initiating function. For most operations
    this is not a problem. For complex operations requiring stable temporary
    storage, the class @ref stable_async_base is provided which offers
    additional functionality:

    @li The free function @ref beast::allocate_stable may be used to allocate
    one or more temporary objects associated with the composed operation.

    @li Memory for stable temporary objects is allocated using the allocator
    associated with the composed operation.

    @li Stable temporary objects are automatically destroyed, and the memory
    freed using the associated allocator, either before the final completion
    handler is invoked (a Networking requirement) or when the composed operation
    is destroyed, whichever occurs first.

    @par Example

    The following code demonstrates how @ref stable_async_base may be be used to
    assist authoring an asynchronous initiating function, by providing all of
    the boilerplate to manage the final completion handler in a way that maintains
    the allocator and executor associations. Furthermore, the operation shown
    allocates temporary memory using @ref beast::allocate_stable for the timer and
    message, whose addresses must not change between intermediate operations:

    @code

    // Asynchronously send a message multiple times, once per second
    template <class AsyncWriteStream, class T, class WriteHandler>
    auto async_write_messages(
        AsyncWriteStream& stream,
        T const& message,
        std::size_t repeat_count,
        WriteHandler&& handler) ->
            typename net::async_result<
                typename std::decay<WriteHandler>::type,
                void(error_code)>::return_type
    {
        using handler_type = typename net::async_completion<WriteHandler, void(error_code)>::completion_handler_type;
        using base_type = stable_async_base<handler_type, typename AsyncWriteStream::executor_type>;

        struct op : base_type, boost::asio::coroutine
        {
            // This object must have a stable address
            struct temporary_data
            {
                // Although std::string is in theory movable, most implementations
                // use a "small buffer optimization" which means that we might
                // be submitting a buffer to the write operation and then
                // moving the string, invalidating the buffer. To prevent
                // undefined behavior we store the string object itself at
                // a stable location.
                std::string const message;

                net::steady_timer timer;

                temporary_data(std::string message_, net::io_context& ctx)
                    : message(std::move(message_))
                    , timer(ctx)
                {
                }
            };

            AsyncWriteStream& stream_;
            std::size_t repeats_;
            temporary_data& data_;

            op(AsyncWriteStream& stream, std::size_t repeats, std::string message, handler_type& handler)
                : base_type(std::move(handler), stream.get_executor())
                , stream_(stream)
                , repeats_(repeats)
                , data_(allocate_stable<temporary_data>(*this, std::move(message), stream.get_executor().context()))
            {
                (*this)(); // start the operation
            }

            // Including this file provides the keywords for macro-based coroutines
            #include <boost/asio/yield.hpp>

            void operator()(error_code ec = {}, std::size_t = 0)
            {
                reenter(*this)
                {
                    // If repeats starts at 0 then we must complete immediately. But
                    // we can't call the final handler from inside the initiating
                    // function, so we post our intermediate handler first. We use
                    // net::async_write with an empty buffer instead of calling
                    // net::post to avoid an extra function template instantiation, to
                    // keep compile times lower and make the resulting executable smaller.
                    yield net::async_write(stream_, net::const_buffer{}, std::move(*this));
                    while(! ec && repeats_-- > 0)
                    {
                        // Send the string. We construct a `const_buffer` here to guarantee
                        // that we do not create an additional function template instantation
                        // of net::async_write, since we already instantiated it above for
                        // net::const_buffer.

                        yield net::async_write(stream_,
                            net::const_buffer(net::buffer(data_.message)), std::move(*this));
                        if(ec)
                            break;

                        // Set the timer and wait
                        data_.timer.expires_after(std::chrono::seconds(1));
                        yield data_.timer.async_wait(std::move(*this));
                    }
                }

                // The base class destroys the temporary data automatically,
                // before invoking the final completion handler
                this->complete_now(ec);
            }

            // Including this file undefines the macros for the coroutines
            #include <boost/asio/unyield.hpp>
        };

        net::async_completion<WriteHandler, void(error_code)> completion(handler);
        std::ostringstream os;
        os << message;
        op(stream, repeat_count, os.str(), completion.completion_handler);
        return completion.result.get();
    }

    @endcode

    @tparam Handler The type of the completion handler to store.
    This type must meet the requirements of <em>CompletionHandler</em>.

    @tparam Executor1 The type of the executor used when the handler has no
    associated executor. An instance of this type must be provided upon
    construction. The implementation will maintain an executor work guard
    and a copy of this instance.

    @tparam Allocator The allocator type to use if the handler does not
    have an associated allocator. If this parameter is omitted, then
    `std::allocator<void>` will be used. If the specified allocator is
    not default constructible, an instance of the type must be provided
    upon construction.

    @see allocate_stable, async_base
*/
template<
    class Handler,
    class Executor1,
    class Allocator = std::allocator<void>
>
class stable_async_base
    : public async_base<
        Handler, Executor1, Allocator>
{
    detail::stable_base* list_ = nullptr;

    void
    before_invoke_hook() override
    {
        detail::stable_base::destroy_list(list_);
    }

public:
    /** Constructor

        @param handler The final completion handler.
        The type of this object must meet the requirements of <em>CompletionHandler</em>.
        The implementation takes ownership of the handler by performing a decay-copy.

        @param ex1 The executor associated with the implied I/O object
        target of the operation. The implementation shall maintain an
        executor work guard for the lifetime of the operation, or until
        the final completion handler is invoked, whichever is shorter.

        @param alloc The allocator to be associated with objects
        derived from this class. If `Allocator` is default-constructible,
        this parameter is optional and may be omitted.
    */
#if BOOST_BEAST_DOXYGEN
    template<class Handler>
    stable_async_base(
        Handler&& handler,
        Executor1 const& ex1,
        Allocator const& alloc = Allocator());
#else
    template<
        class Handler_,
        class = typename std::enable_if<
            ! std::is_same<typename
                std::decay<Handler_>::type,
                stable_async_base
            >::value>::type
    >
    stable_async_base(
        Handler_&& handler,
        Executor1 const& ex1)
        : async_base<
            Handler, Executor1, Allocator>(
                std::forward<Handler_>(handler), ex1)
    {
    }

    template<class Handler_>
    stable_async_base(
        Handler_&& handler,
        Executor1 const& ex1,
        Allocator const& alloc)
        : async_base<
            Handler, Executor1, Allocator>(
                std::forward<Handler_>(handler), ex1, alloc)
    {
    }
#endif

    /// Move Constructor
    stable_async_base(stable_async_base&& other)
        : async_base<Handler, Executor1, Allocator>(
            std::move(other))
        , list_(boost::exchange(other.list_, nullptr))
    {
    }

    /** Destructor

        If the completion handler was not invoked, then any
        state objects allocated with @ref allocate_stable will
        be destroyed here.
    */
    ~stable_async_base()
    {
        detail::stable_base::destroy_list(list_);
    }

    /** Allocate a temporary object to hold operation state.

        The object will be destroyed just before the completion
        handler is invoked, or when the operation base is destroyed.
    */
    template<
        class State,
        class Handler_,
        class Executor1_,
        class Allocator_,
        class... Args>
    friend
    State&
    allocate_stable(
        stable_async_base<
            Handler_, Executor1_, Allocator_>& base,
        Args&&... args);
};

/** Allocate a temporary object to hold stable asynchronous operation state.

    The object will be destroyed just before the completion
    handler is invoked, or when the base is destroyed.

    @tparam State The type of object to allocate.

    @param base The helper to allocate from.

    @param args An optional list of parameters to forward to the
    constructor of the object being allocated.

    @see stable_async_base
*/
template<
    class State,
    class Handler,
    class Executor1,
    class Allocator,
    class... Args>
State&
allocate_stable(
    stable_async_base<
        Handler, Executor1, Allocator>& base,
    Args&&... args);

} // beast
} // boost

#include <boost/beast/core/impl/async_base.hpp>

#endif

/* async_base.hpp
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
*/