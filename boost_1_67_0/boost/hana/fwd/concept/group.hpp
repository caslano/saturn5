/*!
@file
Forward declares `boost::hana::Group`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_GROUP_HPP
#define BOOST_HANA_FWD_CONCEPT_GROUP_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Group Group
    //! The `Group` concept represents `Monoid`s where all objects have
    //! an inverse w.r.t. the `Monoid`'s binary operation.
    //!
    //! A [Group][1] is an algebraic structure built on top of a `Monoid`
    //! which adds the ability to invert the action of the `Monoid`'s binary
    //! operation on any element of the set. Specifically, a `Group` is a
    //! `Monoid` `(S, +)` such that every element `s` in `S` has an inverse
    //! (say `s'`) which is such that
    //! @code
    //!     s + s' == s' + s == identity of the Monoid
    //! @endcode
    //!
    //! There are many examples of `Group`s, one of which would be the
    //! additive `Monoid` on integers, where the inverse of any integer
    //! `n` is the integer `-n`. The method names used here refer to
    //! exactly this model.
    //!
    //!
    //! Minimal complete definitions
    //! ----------------------------
    //! 1. `minus`\n
    //! When `minus` is specified, the `negate` method is defaulted by setting
    //! @code
    //!     negate(x) = minus(zero<G>(), x)
    //! @endcode
    //!
    //! 2. `negate`\n
    //! When `negate` is specified, the `minus` method is defaulted by setting
    //! @code
    //!     minus(x, y) = plus(x, negate(y))
    //! @endcode
    //!
    //!
    //! Laws
    //! ----
    //! For all objects `x` of a `Group` `G`, the following laws must be
    //! satisfied:
    //! @code
    //!     plus(x, negate(x)) == zero<G>() // right inverse
    //!     plus(negate(x), x) == zero<G>() // left inverse
    //! @endcode
    //!
    //!
    //! Refined concept
    //! ---------------
    //! `Monoid`
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
    //! true. For a non-boolean arithmetic data type `T`, a model of `Group`
    //! is automatically defined by setting
    //! @code
    //!     minus(x, y) = (x - y)
    //!     negate(x) = -x
    //! @endcode
    //!
    //! @note
    //! The rationale for not providing a Group model for `bool` is the same
    //! as for not providing a `Monoid` model.
    //!
    //!
    //! Structure-preserving functions
    //! ------------------------------
    //! Let `A` and `B` be two `Group`s. A function `f : A -> B` is said to
    //! be a [Group morphism][2] if it preserves the group structure between
    //! `A` and `B`. Rigorously, for all objects `x, y` of data type `A`,
    //! @code
    //!     f(plus(x, y)) == plus(f(x), f(y))
    //! @endcode
    //! Because of the `Group` structure, it is easy to prove that the
    //! following will then also be satisfied:
    //! @code
    //!     f(negate(x)) == negate(f(x))
    //!     f(zero<A>()) == zero<B>()
    //! @endcode
    //! Functions with these properties interact nicely with `Group`s, which
    //! is why they are given such a special treatment.
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Group_(mathematics)
    //! [2]: http://en.wikipedia.org/wiki/Group_homomorphism
    template <typename G>
    struct Group;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_GROUP_HPP

/* group.hpp
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
*/