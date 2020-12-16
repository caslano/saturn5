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
Euvot2JOc2eYtxoRrslGpDtE9bHJ31luux372B8kbBtV3zuI/97mamOo6mOj5Dli3f59bCX8Txe39a5TjBDMKb0KbZdzjWtckapeLhT36x372M/k/vGqXdsv/ivMV41U1ad+I3666H2qWoP5nKT3QfRQ82kH7dqDll0p8uck1aa8Kv5yTKd+9gK57wrpZxe4mjm2AU3FX4x7oPGEqxPbgIli94BrAOrwIrQBG9DP3mdONJLQc+a6Rvxq6p1Vf4Z/59vvRR/0NV9z0L4f/IJfkx5nP3gf+8E9/7StX43qB5t9b4W92bVU9YOMz7kfpPtA1ad1kzjOd01zfo9lmH5KxjIlzHmuYleYUx1jmE5qjJRohYFktzAvNM5x1devzEPSD5s2faPaB+0rCbsLc2t5ev+IezSuf4yW8G2UXmO23PMcJdutxX2lbX95rri1d+Ubbsxt1/eXl4t9gm1/ebfEP9Wxv1wpYaOlruxtoL9sJ/6uQn/ZX/WXc8Quy3UCamwV6spr6JcnmQOMe82Rhl3f95ik5TTV90X+IPn9q6lTDfVlQw/59l0v+plT8Cx2OlsPUnFjGs8BOZlzBFN+DKxr+pqSJTZrSlZJmEST9Ytx5DqtKaF7jpK1q8Xcw3TaI3C5uPfkHoHe8BmaTBRLgDTeP/Mny304pBF6hbha4eqAq7sRq8b8V0ocNweM+dOYxl3ivtQmDpjZr14qfiZS17VeTrKSjsa431lvTC/Hac35fd/SGwdN8CrEmfKzfzlyHYnzXA/DdKs/b03M7wae/cJyP1HcP2C5esO3DzzvhOWYJ+7fss30+k/RyqC0DP+pcnxb3Ic5lAHDYL2ahGGcKyXMerswSsfj5V84L+N//kmezb6G5UiHra4k1/2chaslv+9HZOHdEqECyquipKGzdximnZLHW8Tc1zb/Ryj/rVV53CjmIZSHwPMst9C/zGlRlzvyCHQi/fMp1y+f9HfrFB7el85v+cm4IrMsgbbJF861NjBvyXDpLHPZg6FRe2P6l7ledou4lmCBy/P+Xw7+Hn7zbNJI3XDHNnO6hDmH6fXG0Umt+dwh5tfNnkaMw7mqDIOcSmR5Fop5ttkVqXvQyFLn/aS4PGdiphibHdftjZewl7JueuNuxXlfb3q2SXr2GW0d55Iu9+S7KwHaCR+Z4Vo9xf2y6/djuVP8PW62NpbDbojoJt8ldlGuUiNG10NU/cQN8hyZHEeYxtViTjUjxO7EuAquJxwr8eQbSWLnsbxF7Jq75iPuQ/Cvtdm8GicfBTZtwjgbXe0pNu/Fy9z2+tObWxnyG8M2YRCu5VZfHBIgV9SfdparSyRMO8qVN45O9rrTdNfbkAvEnOm4X++54t6TcuIN31rVM/cRtA9LfqHO9FLqnb+AG1t/3gv2tsbjnnxDhhXOKC2aV8rPJJ5nkjwYV6bpddJ/bzGPgTks1DJfJ+/bOZLH+dVFohqqjcO9+UB5dkuYS0x9TFFF/wXKfx7NGOmK/3SnsQH9Z6s1+ob4v1Hi57r58krtGTqJexOVvsViTpN6dIasu50ga8chI/KbIO4ZeCPOEPsC2ueK/WqEHGm009Zc5In9JNw/HDl1CmqtW+rccLoPEHe3xDWKdgvEDntccP3GyayLfHau6cDqD2UXamjPV1qm5UcXcY9U+tQ3iDlE84/vYVp+LBP32So/ThRzFt0xQ8n0irsyR1KnsWHZTQfbi5xCjrR1FDkiz5SVgPc5yEMjZLqK6wDKeJZPJtgT8caG18v0bBzrfRiZpv+yhmSYfjqqun28mP9i2MiYyEG6uB+nwi8VcxdHGSsT9zeNwWyfvTK20bKn3Sja5Ytdqscf5efU8ECZulLsjjc=
*/