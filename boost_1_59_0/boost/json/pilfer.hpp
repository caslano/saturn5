//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_PILFER_HPP
#define BOOST_JSON_PILFER_HPP

#include <boost/json/detail/config.hpp>
#include <type_traits>
#include <utility>

/*
    Implements "pilfering" from P0308R0

    @see
        http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0308r0.html
*/

namespace boost {
namespace json {

/** Tag wrapper to specify pilfer-construction.

    This wrapper is used to specify a pilfer constructor
    overload.

    @par Example

    A pilfer constructor accepts a single argument
    of type @ref pilfered and throws nothing:

    @code
    struct T
    {
        T( pilfered<T> ) noexcept;
    };
    @endcode

    @note

    The constructor should not be marked explicit.

    @see @ref pilfer, @ref is_pilfer_constructible,
    <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0308r0.html">
        Valueless Variants Considered Harmful</a>
*/
template<class T>
class pilfered
{
    T& t_;

public:
    /** Constructor

        Construct the wrapper from `t`.

        @param t The pilferable object. Ownership
        is not transferred.
    */
    explicit
    constexpr
    pilfered(T&& t) noexcept
        : t_(t)
    {
    }

    /** Return a reference to the pilferable object.

        This returns a reference to the wrapped object.
    */
    constexpr T&
    get() const noexcept
    {
        return t_;
    }

    /** Return a pointer to the pilferable object.

        This returns a pointer to the wrapped object.
    */
    constexpr T*
    operator->() const noexcept
    {
        //return std::addressof(t_);
        return reinterpret_cast<T*>(
            const_cast<char *>(
                &reinterpret_cast<
                    const volatile char &>(t_)));
    }
};

#ifndef BOOST_JSON_DOCS
// VFALCO Renamed this to work around an msvc bug
namespace detail_pilfer {
template<class>
struct not_pilfered
{
};
} // detail_pilfer
#endif

/** Metafunction returning `true` if `T` is <em>PilferConstructible</em>

    If `T` can be pilfer constructed, this metafunction is
    equal to `std::true_type`. Otherwise it is equal to
    `std::false_type`.

    @see @ref pilfer, @ref pilfered,
    <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0308r0.html">
        Valueless Variants Considered Harmful</a>
*/
template<class T>
struct is_pilfer_constructible
#ifndef BOOST_JSON_DOCS
    : std::integral_constant<bool,
        std::is_nothrow_move_constructible<T>::value ||
        (
            std::is_nothrow_constructible<
                T, pilfered<T> >::value &&
            ! std::is_nothrow_constructible<
                T, detail_pilfer::not_pilfered<T> >::value
        )>
#endif
{
};

/** Indicate that an object `t` may be pilfered from.

    A <em>pilfer</em> operation is the construction
    of a new object of type `T` from an existing
    object `t`. After the construction, the only
    valid operation on the pilfered-from object is
    destruction. This permits optimizations beyond
    those available for a move-construction, as the
    pilfered-from object is not required to be in
    a "usable" state.
\n
    This is used similarly to `std::move`.

    @par Example

    A pilfer constructor accepts a single argument
    of type @ref pilfered and throws nothing:

    @code
    struct T
    {
        T( pilfered<T> ) noexcept;
    };
    @endcode

    Pilfer construction is performed using @ref pilfer :

    @code
    {
        T t1;                       // default construction
        T t2( pilfer( t1 ) );       // pilfer-construct from t1

        // At this point, t1 may only be destroyed
    }
    @endcode

    @see @ref pilfered, @ref is_pilfer_constructible,
    <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0308r0.html">
        Valueless Variants Considered Harmful</a>
*/
template<class T>
auto
pilfer(T&& t) noexcept ->
    typename std::conditional<
        std::is_nothrow_constructible<
            typename std::remove_reference<T>::type,
            pilfered<typename
                std::remove_reference<T>::type> >::value &&
        ! std::is_nothrow_constructible<
            typename std::remove_reference<T>::type,
            detail_pilfer::not_pilfered<typename
                std::remove_reference<T>::type> >::value,
        pilfered<typename std::remove_reference<T>::type>,
        typename std::remove_reference<T>::type&&
            >::type
{
    using U =
        typename std::remove_reference<T>::type;
    static_assert(
        is_pilfer_constructible<U>::value, "");
    return typename std::conditional<
        std::is_nothrow_constructible<
            U, pilfered<U> >::value &&
        ! std::is_nothrow_constructible<
            U, detail_pilfer::not_pilfered<U> >::value,
        pilfered<U>, U&&
            >::type(std::move(t));
}

/*
template<class T>
void
relocate(T* dest, T& src) noexcept
{
    static_assert(
        is_pilfer_constructible<T>::value, "");
    ::new(dest) T(pilfer(src));
    src.~T();
}
*/

} // json
} // boost


#endif

/* pilfer.hpp
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
*/