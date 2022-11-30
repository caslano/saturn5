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
#include <boost/beast/core/detail/work_guard.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/bind_executor.hpp>
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
        net::is_executor<Executor1>::value || net::execution::is_executor<Executor1>::value,
        "Executor type requirements not met");

    Handler h_;
    detail::select_work_guard_t<Executor1> wg1_;

public:
    /** The type of executor associated with this object.

    If a class derived from @ref async_base is a completion
    handler, then the associated executor of the derived class will
    be this type.
*/
    using executor_type =
#if BOOST_BEAST_DOXYGEN
        __implementation_defined__;
#else
        typename
        net::associated_executor<
            Handler,
            typename detail::select_work_guard_t<Executor1>::executor_type
                >::type;
#endif

private:

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
        , wg1_(detail::make_work_guard(ex1))
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
qeBAPidk6n/S1bkZKG+Hs7ChMC0payMD1ZxF9sVR8Lo/a5qd3h8hnYzujUpe17Y1bag5Z/9TKMMTGq+on4bMVJBe0tDEYNNgLCfXn8W3SHpVDwwZJq3828SR/jTVuuDeb9WZVEvlS2Y2sNJjpvb5McK2FrIe9zeEw/eWPmIV83x6WOmCLlJZ5q/3/DywGyJtFblgLYMiJy4/7sTDp0VMWZ8HzUtfwwxrjLs0f7dzHWPb24Osbw8WIc7kr8oQt8zDp36aJjE9LX2GHcvXcTeO4talTa/+hFAOdczfuN73X4fm38Od3p9sIBUnCAxAtXXok6QH2SLeFnOFYt58XoL9/jyQwR/k+5gfnFP22Q2JYmUoncc0g8YEXbOo6Fv0J56NaR6dDb8ED6kN3cRTzAnntf4R8TMjxgSEtQ7YLuc9Ys0YOlJ0LaPmJN2SrrBuzvu+fjjJAbpVNGu6FPlWD2LtzZtfkR56KKwJ+/25f77lPH97ioeJcx2cZ7FeCv53qQWPITvi6V+9V/0fH5998qHuHCWXcBsEo4pVAqBr6B6qVnYYyx0ZwTO1mK8OHWOczI+7XtsWzQcpId1glRqvSzi822OdSDjPUe/9JPIsBvCBJUuykM9MokHG4yi3TeHtHgLfnzeZVd9fQaMo9yDyB8d6bqO5LM0BEB44KUgXBt9cOCEhFhoKn4z/FKPkuE3mQ7ytxla21OjuYVHhu3fIWMYQ30klu3XaTCvavqfKMq/ZnnbqQqbY+qWGefD8YGWqfAkq/myEf/YOMyOeTwA17ZUB1u86g/Kqqmicd7NaFPyOou67WzMVkPSpJvG8OOVX7nJHBGOkv185j7xGds2Nb13tlyR5XVCPDNFU5PAfN7kgzrCsLOI4DbOcS9fXK8hnepcxwhozNiNqhswG+RMPfE1Ifcn3915yjVsxqjh230YZu/XB2n/Navd0r482q1o9jRO94nJC0FZtx/EiELFPZ7JVXMMh16AjCBEl1cE3rSBvVoxEbG5GSGTCxhrWZmxheSDIR6NS+c4o5Yqd2qh2BRW7lSUqDRHB5SlQ0tlda24ffRrjbRSHSgURlCaw+k5wlvP1r5I7NMndE0aPyMyvb+pys7vzJ3rx0QejAhnS2k3uXrwp+O4tKFW/IOATxg68X3FapnqwmCU4nZcg3L1/kOYEjcy6ftrwKvsSPbjT2ONWa7lw4dUgd2pF96oOEGiOLNHPZBSpboVsuukb6OMYqvIGbGwt2dzzuEUyWmY3SZND3DymjthY5x7axC90LpYsUXhA4eMj1fMDOKfxIxyseKxblvMPBpOnA2/ONb6IJcqntN7g0PUc7t0vWU4yhiXykORuhyrYBN4SPM5cRtLLb3z8dKeMnq0PdelwxTywPr8Iw/3UMYKA2uiN4U9JZUqMz7+Y5886g/ztNJY+3/qOdv4B2rRufVtDeeWP0I+WNAQXXV2Nx33nhbRuF3PVHWP2rPMbhEtUzEEKbs7qyiwdyKXxUYb+SWiwnLsrAlGokyic0zQh1RhnrdsCNxC8C0rsoDxipxXYj+IqDyZ4QPwNmqgaEXhaKX0IOQFXmyHYFjqSUcPsAK0z/BbnaySyzZN/mDfA3MV9J9GLS9esNehj3Yyrvkic8RkBNc82ex4YQXOmTuJRqxEgTnZoOblyeAGJ7TgIppN/HHdw4ycNNnHRmTQF76NBrtn33OyCk5HEtnGvT12B5rqmp/B0cvybVuZ1RKtqT1QuxoRLjW81Eghqs9/Kg798t8qjgICw7vCiBSYzEOCbZdup7TseQIlD5IcuAOQ8WSiw8klk4/vtdjZfUlHXeIiBo8B/lKysVsaWBaHeIVuhELIgtYuZJ5bZdyMQHU5gqEDmjMab854WJUD5Do8WaO4K7S62/KbPht5RuY3NIIsTyM7OmsHONWeF8LVEA6Yft38pCGoTUHQLTm5C4pM6gZA58AbVmzUY8DqfnF0kzdWhKgXPDbLz3esGU8LngQEWI82TAukmgXdtjXZLWHdX6uWhIvRMcnHX6/5WssP40P3vqZ20UG7/TfJ9vcmqZUBNAGG/nYPNZYaw79IBGfsTi10kRgLPZVF2y2uxnd/3foGAg8fvn7GHki0cyHssB14UqM3r+Sg+5qEJ3WE9hXXCc59ikzarHDc4XJpPmfzB8HhE/7WDtbaPC3yz1PUhwxX4Vb2tAhycwu67dhwtyt1rwvZR+lts2zswi5GvTQVMkzKtuZNMKq1mSAmFPr7H9xhFnrf+qvkQjKGhHsM2UaVlruwebr1TJpPx8G/uMO7Q0pR06xGa9IqvA/NjII0AbHGhF7yf1zXOoZewV7BJk+xTc751Vc3qKDZmY+//lDwuSZML1c8DTIFt7h1CRRlfe+ZXl6DT78rVziXMCHx/mK1eihmgOcRb7ttL6TjNAot4sobL726B4HLhF8gXWJCFim16el8aY0iHodWEo+SGgJoVUJrVMWyVAdJBtjO4INyY6/QLVe0Htl9Pi45D/N7xpZeC1omVebNwwLVLqvKCN7opVMroDRePCEmLkgj1ej8ezxbeoAi+98Chlekcjw0k1gzb0IP0HYie8XRQQGsZrhcC1v337Pj2H9lBbUII8Pyu5/1Ytxiqqi3NC/CMjn/7V8USE5gIjDYuKz7gB8f2+UMck3wRpKrGwGDQZ0dQdLAx1LQyfT8gAbLKs7gPMYzGalq/Za0n79R29TAZc10Jm+zAHjlWDWudonFQAOcMJ87/5L/+2sZ99Ff3xQWLg+TCmCrmoUYaD5HLqG7qC5u9Kb7eYguMBUfZDsC5ZciOsK893VWrLbTdMIV97vfIeCs7WjbI7jGCX4qp3RsjrEZ5Y3olDJEqZ6Oif11bavmAyZuFE5AjLixDusB7/kTPSpKvDZcyeSxXeHihZRxku2UQ0BL7AJItQRp3O0kXlhm3tTqeR31Sh7/nyhjl5NxBPtjTPIauB3KfTxNSt9TWZjywBMN5Z70nnq8Olrwqk9ZCkWQO+iLHaykpUm8XPa1WpqeSr6WCCfJBKKhi3tzhplCn2g57huROKLYPIL1llzR+biFr3nMSk3+M9fQz/BRhOmzS2W3WKT8uN8QPZ8Kq6M3YbNqV/lgk4TOuEXj4Bge0uL5tHPr+NSZJwTWZ8HlJp3s9WsU6zY9U8b7qIy+K/EN6RFMpT4/xOqDdwOfumxCScOYEW34h4XeK6z07ckIZ7R1a6DZgaRQlx8DRDdHjn7UWuNMyVLN373puC2UvXQf+Bc0QuB6Cesr7MWTAjTC/3xhB3uDZtXu7UD/RfYvVcFv9Dt60LMCLPKNf34+Eey0GP0R77862nokbLHtKah8dx3RjFjc8K0TNBbBI9buauJ/SqQmGMpZ1mGZVu3IJaN+tkvIGmX2MxTfXOsY3ub1D1hEEciaQPbUq41JXDAtJW0m/Vp1Zi+stwOX//djp4K2THQBfB9xjG0VwvWkzvRvyl0nkZK/yuT8TEvh9WrmnE6UdvweVfc/mJnwxDDxWxN7BvDugOUp/dSvZ91Lkf68FCPwI839vQxSg0m8I8nfHTs89M4ubs8a14hIIUnGMj92wZepC2GTAQwEENKDFDgMwnvd7ydDNY4bLG6YmX3xJmRU/r9hdur5iBTJiT/ISwmIcD1U6Sw2YrTj2ERcgNol17dKkP22sEYrN1d/M3h/SvoKwvIa1abafS4J+B1+N41UtVagvCE330zq+lZflQouVhP2FFz6GldyZSLaDNgraLp7uSy5IDOL9nupJ28FryfbnwSE4PeZ2YoDLpny1mNfDZC6DOw/3LI5lXd5wmb/QiE+Fl/zimkQ2WyJP8nCoGqsMctr9M7yN/1tCpGCdTkHAZln/qcdsv+1E9ZLZRf5kl3PW1WLgP38tBuzTjRO8UyOqsyQkeQlhDvzw4R0HX88NNWFRcJAqkNFPgjCBsBwVNLsHL0DYvi1L4hvSfxUCNO0/slNQraKfubzO5wIPz0wyMYSXU/pq7m0FPUGe/GzpQ34WwX1cFIjR49WG9T3tpGSOdJ73r3C6nCf1rntU8oRwxF9ODNDnE5/Zn+X/lLk3ENayi0JzP5BpXZs6StC0N8VvxTp6yYFXU7+r6sI9rocbxWok7qzJQChbzuJTVpSb7Fy8kr7Wuoa6YkPsZgGaoa6azwcnZN0bR2bT/jacaf3rCi2vEDvQSatTrnm3ecOWB8rC8s8poeeR8D/2Yw8MQZw5FQAt1dbXrNKC08zWfXedtCKvs1uPtvzS9fnvnGBupa6lA9xBVe6lhvOHpWxHVI873afPmzeYsHOK3L9frCV0PO++5mR4as6IEqNT/eXpuczuO0U5cMExIxOGWzKvXPTdYCXHv81k2bE6+ZoxFHBLuoUs1hXwgM7FAZSLylUeRw0MdBb+BF6nuv/89xCoSs6YbItoDz7JHBDtPVHMEhbLUps4IQUGU7BYzGD9ICoSJp/Oy4Jyku/Z1uVWdHU9ZeJ9uJ3xv/50dGYquebCK7cXzad5j4pgdo9//wG/axvNzPsc1fdOvGSybXEf3Tq1zrSellU2/RtkD6TLmUPFa9uqB7zAyxbc85GlnzHHGVCeszuAz+KxWTEjoBL1Pi+0IMiDW3wwfHFkvFoAV3q0FPDYYYMoa80r1asCIGLODs5T9OBLU39VGrPXhbmALTS1UVzg1XvYtD+y+7yXxua3h8fqbidmQPjiTir+8qn9svQ/L0GKG6yYxaluJ3ZBj9ignag9M2y0CUapnezPKbpXnBPyr24YYTxkOQeSXehMurXx655g3Q1aoFvH75FldoOwPlp6UujoYcDTgZuVal3Zur3QV22UadJsMo5nuzVHzXY2J5XKOCW8pRziy8WqXAo9sy4oZ09Mth00ZPb5idCm+qp0P6xrdeSg3FWHvq54ONEND91X7+6MRWcr+G+NIYdOUrOuEATSuaNm1UTeTfEnaD9nR/tJyci5w0UOo3TKHBntd9z/cAufhmQiLPD6ktvA4MPfXwfCG5pty9Z6qnqIzeqXTfmM5VsI0kWldr+FXvyg/b9T4VHlXtw5QIN266njK+GBxRI1AHoSw70Pr1VPQwyNJ+10vTuwAm/E5zpIdyW9IPIcPZpsBLz9VBF+RLAElBMchtmyO22xST7AbKNOsteasRQM2M32LzUgUDomLYcHARE6vqe2JsymS7zXru5Zt28p0svJCHFSd/dh9u/0vOeNH3r5azxR3J1cwDoT9uZToAOqMZgVmqbHzEPNiwJlo3aV2eKF15K0rzMxbeRwq8MZSRWXGoxf1hBGHELl92iGI38dShAwMZk1lAA3p4f3lsaRsb+FYJQw/o7z3l89C1RljVkttYG+ZRmKq8mOFQ7ZaMcNBfrAmzfUoTlqB6FjrUe9ldeIFVzkSbqDOTiyG/qnjAmOjzF3x+EmTw5Hr2/xrX+Xwo8laTjSb1ZCDw2ppTXKjZYtBOcmmeNR2PRmAiEX4hFZdmAr1tR3k72pkh13nVU2W9+ANIrErutJbSspvNaUJfyiH0l2T9MUgMIVVFtXXPsQ8D4Zn08dVETm6pES3PXSF2mlxx6ycc0m1tmficoJgZ10vmAgjaKwcKtfZa/FyYHSZp7LzvdaK/JwSBXxV/EdLjt45i3UeruzDQUsjOSfAmjJFGENkflmF7UT4tNgsfPIlhumhwGIFnRWBhQwWZF/F+uQx3r//Ijs3rrYcDEnwLOb4RIEbnbTPWE7wNxBiv1vbS+XibKA0SDkp0pg53JBIfk0YasSFLLrS8JRiryCNSn+vXZL+rZ5ago+PEiB4T3YR8mol4O/yKFd14j98yrGMyzcrBB32qad+D5fQqMgDnwOaesWTVLQPBkX5M0s/sRZthWLbwTvZnGShdKpt32ERZCBbz9mhJem+52vHbxz5MeUmzFrooBXkU8ZPdsps9REU7E0ipQVkXfK3p+rOXgOgX+1nIKZ0I/EM3LcNtgCOKNLWGm9YaGsCWToACCh7mIgkDarUr1SZWWt9ZAWiCWh4gApr5e+wf6DmfSPphZ1l1jFtff7DnFQOsaD/nEMOfgeriSzGugyHycQ/yLWfUA+p2H0sPjWt7P2oFD2q3dRRIub9hJXvwrWyAI97z5CyzdWT6dSz7aM0geY8F7zu+zedMnHboryWreJwpy/FhbDco67IYNtmZZaFvxErQcfv7v/M8WYUDFyDWlzsGy6upkplW86Wccl1QIybR32bZRQApmQPeAEDebmjO3tAj2jf4FGxY+tBHRpJxN7I4wUO5/umffNvX3KCEGYRw3HfDxPxv48SSrwrZgvnBPymYA5iDJplgoXJe+xWs8G+5bF8FWIFOeWqWGSkq/6dE5vLmO/GY/c78mmtNXlnaadoAZizyK08dFmIg+JQvLC6RT3nLDRKTgohXxM6BgZKi/mhQUyYulXMqOsV67veCO0PgzaSS/SSxcZ6ooda9sFuvG0vG93Xcujk9054Irp3bo9aDaXq6FCl2UIXzRNw0kVwwFQoHojIexN353RE4PBDcggDaHlZdPRMx2OEzqQSq/h1TB84k46eIjp9rWjnhVpXfwrgUKUc/yCDb5SFI5tX24rju1quKU1MIIAR5LY04eeJ/SqTVwN9R3M1A1I2OJxe7APjc7tmGedVpzoek0Q276fj8cqIvj3y0E/w2IvJE32Gnuz/LzC6Y8wBE2J1kuIKJwi21S2WK4+0pr5nynyktZX1v0Ox8eIhNYkMq/g1qBda8hlu6qqKe6neKSHFCNbOPyLIPkRmgFzwmxhvb66Wu+SMd0ezBP0exWpp95picKLnhVpF/Qn41aIiUfcpBLf4Rpv6D+hC0J2KTvIv97VwhziOFb9cEUYdoonFvuxSOVHNYPlE1EdOY0m41gq6Exu/eNFXqThQtAqZK+HeV6ZKg7pRbkxqJL3tDeaONt5jbQUIM8si2LuXobyBYSa8TX1pFp/5HPUKOgTSkO6/hWLx+PpPzO2T6XrRMWXe51B7KclxydtjpwjhPprwQiDP6Bt6Cs2u/8DttBfXVFLo2n5cbu29RB3u3U1QtLw5UV6yFArqY9GaDXFn3H0+mv6SQHkOVmmUt7bl/qqXx7nJOlxdrjNE4SKjShJbFPIhCPIJd0tfrYjEXu8SpdEOUOdT2BW8aIG8KQAAJXX1Wnpe7w/46zhnCfaqTi3GfpVvs9ZyZ3WbaxiWVG4BwhOhIsPst4B33hKXifBdoPHeWrEEjVH6Fzee6HyHhqQsvYhQiWAZ0wVdUbkFlGCvctgsN62xgYRM7MvFgOPPrgeOzICwGvvc4VtxaufCoVQb/RwCnfyKmoR7lh2bvUWF4AfqCVSC6ZWikgP0v26iuDS8jTE8W2nsymP9lyeC1hc3iLPMd22oPZS5AwVzJWZI1NLJ2cb3Pi9hxI3iZiNXe0UM8XuZk65H6ZV39OzhnpXr64JeUmmlaZlOGe0tLdNNCnhQZ4WXpOAyT4TPbCyiCYzUeUuBkukl3MKBi+VqJ7awCq8ud9chWaOeM7c6NBddN1I2p0PvpT90QgcbwLxa2aedUwIWrtlHCd4vHdW6GPU4xQ/q0DZpKZdyldeMDgaJyaNt4QYXIdZacZgxfTvOKqEfWgeCD3UNSLp2kNOCMa1MEDPp5o5qFYvR9SGoDgCnpihZqDigwXRBf5aLFEYH8fZ
*/