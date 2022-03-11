/*!
@file
Forward declares `boost::hana::Monoid`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_MONOID_HPP
#define BOOST_HANA_FWD_CONCEPT_MONOID_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Monoid Monoid
    //! The `Monoid` concept represents data types with an associative
    //! binary operation that has an identity.
    //!
    //! Specifically, a [Monoid][1] is a basic algebraic structure typically
    //! used in mathematics to construct more complex algebraic structures
    //! like `Group`s, `Ring`s and so on. They are useful in several contexts,
    //! notably to define the properties of numbers in a granular way. At its
    //! core, a `Monoid` is a set `S` of objects along with a binary operation
    //! (let's say `+`) that is associative and that has an identity in `S`.
    //! There are many examples of `Monoid`s:
    //! - strings with concatenation and the empty string as the identity
    //! - integers with addition and `0` as the identity
    //! - integers with multiplication and `1` as the identity
    //! - many others...
    //!
    //! As you can see with the integers, there are some sets that can be
    //! viewed as a monoid in more than one way, depending on the choice
    //! of the binary operation and identity. The method names used here
    //! refer to the monoid of integers under addition; `plus` is the binary
    //! operation and `zero` is the identity element of that operation.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `plus` and `zero` satisfying the laws
    //!
    //!
    //! Laws
    //! ----
    //! For all objects `x`, `y` and `z` of a `Monoid` `M`, the following
    //! laws must be satisfied:
    //! @code
    //!     plus(zero<M>(), x) == x                    // left zero
    //!     plus(x, zero<M>()) == x                    // right zero
    //!     plus(x, plus(y, z)) == plus(plus(x, y), z) // associativity
    //! @endcode
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
    //! true. For a non-boolean arithmetic data type `T`, a model of `Monoid`
    //! is automatically defined by setting
    //! @code
    //!     plus(x, y) = (x + y)
    //!     zero<T>() = static_cast<T>(0)
    //! @endcode
    //!
    //! > #### Rationale for not making `bool` a `Monoid` by default
    //! > First, it makes no sense whatsoever to define an additive `Monoid`
    //! > over the `bool` type. Also, it could make sense to define a `Monoid`
    //! > with logical conjunction or disjunction. However, C++ allows `bool`s
    //! > to be added, and the method names of this concept really suggest
    //! > addition. In line with the principle of least surprise, no model
    //! > is provided by default.
    //!
    //!
    //! Structure-preserving functions
    //! ------------------------------
    //! Let `A` and `B` be two `Monoid`s. A function `f : A -> B` is said
    //! to be a [Monoid morphism][2] if it preserves the monoidal structure
    //! between `A` and `B`. Rigorously, for all objects `x, y` of data
    //! type `A`,
    //! @code
    //!     f(plus(x, y)) == plus(f(x), f(y))
    //!     f(zero<A>()) == zero<B>()
    //! @endcode
    //! Functions with these properties interact nicely with `Monoid`s, which
    //! is why they are given such a special treatment.
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Monoid
    //! [2]: http://en.wikipedia.org/wiki/Monoid#Monoid_homomorphisms
    template <typename M>
    struct Monoid;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_MONOID_HPP

/* monoid.hpp
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
*/