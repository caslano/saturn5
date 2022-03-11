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
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
*/