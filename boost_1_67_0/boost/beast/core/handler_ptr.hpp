//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HANDLER_PTR_HPP
#define BOOST_BEAST_HANDLER_PTR_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/allocator.hpp>
#include <boost/assert.hpp>
#include <boost/config/pragma_message.hpp>
#include <type_traits>
#include <utility>

#ifndef BOOST_BEAST_DOXYGEN

BOOST_PRAGMA_MESSAGE("<boost/beast/core/handler_ptr.hpp> is DEPRECATED and will be removed in a future release.")

namespace boost {
namespace beast {

/** A smart pointer container with associated completion handler.

    This is a smart pointer that retains unique ownership of an
    object through a pointer. Memory is managed using the allocator
    associated with a completion handler stored in the object. The
    managed object is destroyed and its memory deallocated when one
    of the following occurs:

    @li The function @ref invoke is called.

    @li The function @ref release_handler is called.

    @li The container is destroyed.

    Objects of this type are used in the implementation of composed
    operations with states that are expensive or impossible to move.
    This container manages that non-trivial state on behalf of the
    composed operation.

    @par Thread Safety
    @e Distinct @e objects: Safe.@n
    @e Shared @e objects: Unsafe.

    @tparam T The type of the owned object. Must be noexcept destructible.

    @tparam Handler The type of the completion handler.
*/
template<class T, class Handler>
class handler_ptr
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(T) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif

    T* t_ = nullptr;
    union
    {
        Handler h_;
    };

    void clear();

public:
    /// The type of element stored
    using element_type = T;

    /// The type of handler stored
    using handler_type = Handler;

    /// Default constructor (deleted).
    handler_ptr() = delete;

    /// Copy assignment (deleted).
    handler_ptr& operator=(handler_ptr const&) = delete;

    /// Move assignment (deleted).
    handler_ptr& operator=(handler_ptr &&) = delete;

    /** Destructor

        If `*this` owns an object the object is destroyed and
        the memory deallocated using the allocator associated
        with the handler.
    */
    ~handler_ptr();

    /** Move constructor.

        When this call returns, the moved-from container
        will have no owned object.
    */
    handler_ptr(handler_ptr&& other);

    /// Copy constructor (deleted).
    handler_ptr(handler_ptr const& other) = delete;

    /** Constructor

        This creates a new container with an owned object of
        type `T`. The allocator associated with the handler will
        be used to allocate memory for the owned object. The
        constructor for the owned object will be called with the
        following equivalent signature:

        @code
            T::T(Handler const&, Args&&...)
        @endcode

        @esafe
        Strong guarantee.

        @param handler The handler to associate with the owned object.
        The implementation takes ownership of the handler by performing a decay-copy.

        @param args Optional arguments forwarded to
        the owned object's constructor.
    */
    template<class DeducedHandler, class... Args>
    explicit
    handler_ptr(DeducedHandler&& handler, Args&&... args);

    /// Return a reference to the handler
    handler_type const&
    handler() const noexcept
    {
        return h_;
    }

    /// Return a reference to the handler
    handler_type&
    handler() noexcept
    {
        return h_;
    }

    /// Return `true` if `*this` owns an object
    bool
    has_value() const noexcept
    {
        return t_ != nullptr;
    }

    /** Return a pointer to the owned object.

        @par Preconditions:
        `has_value() == true`
    */
    T*
    get() const
    {
        BOOST_ASSERT(t_);
        return t_;
    }

    /** Return a reference to the owned object.

        @par Preconditions:
        `has_value() == true`
    */
    T&
    operator*() const
    {
        BOOST_ASSERT(t_);
        return *t_;
    }

    /// Return a pointer to the owned object.
    T*
    operator->() const
    {
        BOOST_ASSERT(t_);
        return t_;
    }

    /** Returns ownership of the handler

        Before this function returns, the owned object is
        destroyed, satisfying the deallocation-before-invocation
        Asio guarantee.

        @return The released handler.

        @par Preconditions:
        `has_value() == true`

        @par Postconditions:
        `has_value() == false`
    */
    handler_type
    release_handler();

    /** Invoke the handler in the owned object.

        This function invokes the handler in the owned object
        with a forwarded argument list. Before the invocation,
        the owned object is destroyed, satisfying the
        deallocation-before-invocation Asio guarantee.

        @par Preconditions:
        `has_value() == true`

        @par Postconditions:
        `has_value() == false`

        @note Care must be taken when the arguments are themselves
        stored in the owned object. Such arguments must first be
        moved to the stack or elsewhere, and then passed, or else
        undefined behavior will result.
    */
    template<class... Args>
    void
    invoke(Args&&... args);
};

} // beast
} // boost

#include <boost/beast/core/impl/handler_ptr.hpp>

#endif

#endif

/* handler_ptr.hpp
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
*/