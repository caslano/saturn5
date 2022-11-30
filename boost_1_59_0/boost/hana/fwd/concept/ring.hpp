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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_RING_HPP

/* ring.hpp
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
*/