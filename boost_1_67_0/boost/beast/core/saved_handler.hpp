//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_SAVED_HANDLER_HPP
#define BOOST_BEAST_CORE_SAVED_HANDLER_HPP

#include <boost/beast/core/detail/config.hpp>

namespace boost {
namespace beast {

/** An invocable, nullary function object which holds a completion handler.

    This container can hold a type-erased instance of any completion
    handler, or it can be empty. When the container holds a value,
    the implementation maintains an instance of `net::executor_work_guard`
    for the handler's associated executor. Memory is dynamically allocated
    to store the completion handler, and the allocator may optionally
    be specified. Otherwise, the implementation uses the handler's
    associated allocator.
*/
class saved_handler
{
    class base;

    template<class, class>
    class impl;

    base* p_ = nullptr;

public:
    /// Default Constructor
    saved_handler() = default;

    /// Copy Constructor (deleted)
    saved_handler(saved_handler const&) = delete;

    /// Copy Assignment (deleted)
    saved_handler& operator=(saved_handler const&) = delete;

    /// Destructor
    BOOST_BEAST_DECL
    ~saved_handler();

    /// Move Constructor
    BOOST_BEAST_DECL
    saved_handler(saved_handler&& other) noexcept;

    /// Move Assignment
    BOOST_BEAST_DECL
    saved_handler&
    operator=(saved_handler&& other) noexcept;

    /// Returns `true` if `*this` contains a completion handler.
    bool
    has_value() const noexcept
    {
        return p_ != nullptr;
    }

    /** Store a completion handler in the container.

        Requires `this->has_value() == false`.

        @param handler The completion handler to store.
        The implementation takes ownership of the handler by performing a decay-copy.

        @param alloc The allocator to use.
    */
    template<class Handler, class Allocator>
    void
    emplace(Handler&& handler, Allocator const& alloc);

    /** Store a completion handler in the container.

        Requires `this->has_value() == false`. The
        implementation will use the handler's associated
        allocator to obtian storage.

        @param handler The completion handler to store.
        The implementation takes ownership of the handler by performing a decay-copy.
    */
    template<class Handler>
    void
    emplace(Handler&& handler);

    /** Discard the saved handler, if one exists.

        If `*this` contains an object, it is destroyed.

        @returns `true` if an object was destroyed.
    */
    BOOST_BEAST_DECL
    bool
    reset() noexcept;

    /** Unconditionally invoke the stored completion handler.

        Requires `this->has_value() == true`. Any dynamic memory
        used is deallocated before the stored completion handler
        is invoked. The executor work guard is also reset before
        the invocation.
    */
    BOOST_BEAST_DECL
    void
    invoke();

    /** Conditionally invoke the stored completion handler.

        Invokes the stored completion handler if
        `this->has_value() == true`, otherwise does nothing. Any
        dynamic memory used is deallocated before the stored completion
        handler is invoked. The executor work guard is also reset before
        the invocation.

        @return `true` if the invocation took place.
    */
    BOOST_BEAST_DECL
    bool
    maybe_invoke();
};

} // beast
} // boost

#include <boost/beast/core/impl/saved_handler.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/saved_handler.ipp>
#endif

#endif

/* saved_handler.hpp
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
*/