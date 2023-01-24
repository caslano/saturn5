/*!
@file
Forward declares `boost::hana::Ring`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_RING_HPP
#define BOOST_HANA_FWD_CONCEPT_RING_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Ring Ring
    //! The `Ring` concept represents `Group`s that also form a `Monoid`
    //! under a second binary operation that distributes over the first.
    //!
    //! A [Ring][1] is an algebraic structure built on top of a `Group`
    //! which requires a monoidal structure with respect to a second binary
    //! operation. This second binary operation must distribute over the
    //! first one. Specifically, a `Ring` is a triple `(S, +, *)` such that
    //! `(S, +)` is a `Group`, `(S, *)` is a `Monoid` and `*` distributes
    //! over `+`, i.e.
    //! @code
    //!     x * (y + z) == (x * y) + (x * z)
    //! @endcode
    //!
    //! The second binary operation is often written `*` with its identity
    //! written `1`, in reference to the `Ring` of integers under
    //! multiplication. The method names used here refer to this exact ring.
    //!
    //!
    //! Minimal complete definintion
    //! ----------------------------
    //! `one` and `mult` satisfying the laws
    //!
    //!
    //! Laws
    //! ----
    //! For all objects `x`, `y`, `z` of a `Ring` `R`, the following laws must
    //! be satisfied:
    //! @code
    //!     mult(x, mult(y, z)) == mult(mult(x, y), z)          // associativity
    //!     mult(x, one<R>()) == x                              // right identity
    //!     mult(one<R>(), x) == x                              // left identity
    //!     mult(x, plus(y, z)) == plus(mult(x, y), mult(x, z)) // distributivity
    //! @endcode
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! `Monoid`, `Group`
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`
    //!
    //!
    //! Free model for non-boolean arithmetic data types
    //! ------------------------------------------------
    //! A data type `T` is arithmetic if `std::is_arithmetic<T>::%value` is
    //! true. For a non-boolean arithmetic data type `T`, a model of `Ring` is
    //! automatically defined by using the provided `Group` model and setting
    //! @code
    //!     mult(x, y) = (x * y)
    //!     one<T>() = static_cast<T>(1)
    //! @endcode
    //!
    //! @note
    //! The rationale for not providing a Ring model for `bool` is the same
    //! as for not providing Monoid and Group models.
    //!
    //!
    //! Structure-preserving functions
    //! ------------------------------
    //! Let `A` and `B` be two `Ring`s. A function `f : A -> B` is said to
    //! be a [Ring morphism][2] if it preserves the ring structure between
    //! `A` and `B`. Rigorously, for all objects `x, y` of data type `A`,
    //! @code
    //!     f(plus(x, y)) == plus(f(x), f(y))
    //!     f(mult(x, y)) == mult(f(x), f(y))
    //!     f(one<A>()) == one<B>()
    //! @endcode
    //! Because of the `Ring` structure, it is easy to prove that the
    //! following will then also be satisfied:
    //! @code
    //!     f(zero<A>()) == zero<B>()
    //!     f(negate(x)) == negate(f(x))
    //! @endcode
    //! which is to say that `f` will then also be a `Group` morphism.
    //! Functions with these properties interact nicely with `Ring`s,
    //! which is why they are given such a special treatment.
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Ring_(mathematics)
    //! [2]: http://en.wikipedia.org/wiki/Ring_homomorphism
    template <typename R>
    struct Ring;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_RING_HPP

/* ring.hpp
xhYxbwXLG+406LnmZe/+JH033WIu7Pv+zg2yuQrCdxUJZ7ZMJ5gVaJ9gSWFzEdBCsFPLkKqgtMLI4JbCUU820XK/Ltb0W+HH+PZ2V5QGiPuoo3gtqAkoqHWGbO6PPlDYzHvcCxkV6VchyFDxoYdYsPWE+flpddMa42vsMe1VtdPWSq6vDGXvFdiwCkrhOhWwNOeSFX18KrEWkMDyj1OeT7nnEpbEW0stcsOOlgvN+JQsm8yYjnuuRgVJ8kmhsAvaa8p+8ER0WmibfhhajHRnm8UQUrDwxKo5t+XcKu5AnzdD1iA5JNtFgdpIO1wmubrhb4AKJGNevIKHO1xWRXMq6rLDuCyG4lZj8pot9gxTniMUUJHkkpBzP2kzZ3Eq6bLlFVZE+1QkU5ErcMonLK4yx09UYkZUitriF9jtWSsxIiN8ySgi/34w0cR98LqesvcCQ9lF1qfIec8KwNGM/Kjio9wWX7TPRjJXgiv3c/qm00FXl/t4+ipUR3efT1HVyTzqMxjCbCx+hVydn3x+IzNRczh/qXNO6K2IXztyZ+XuI23HKKKVwa5q0q6fETqSDd8jA1eOPL/svWpzEH/6mDkQB0Kos9/BpQKVm7JmTChv8+p9S0rXIByV8W/W2V+YMZwyYjE1CXsPNDvLrCQZGaZiUqw2WQGPyEnd7eN2jSldyHNeo1eQcpyV93TF5n96KTlKPyV9tfBHeeb0z3ae
*/