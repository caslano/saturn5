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
yIN/BAAAuQsAAB8ACQBjdXJsLW1hc3Rlci9tNC9jdXJsLW92ZXJyaWRlLm00VVQFAAG2SCRg7VZtT+NGEP7uXzEiqITKJIBO7VHQqbnw0giaoBB6QoCsxV7j7a29vt11gJb+9z6zCS9HQVxVPtZRYmc9M8/sM/OM3fr+7Y6oRa8eSfgmOHBmh0Nrfpepf944SW5p9oHTGc6vQHTpweM2WaZXPW6pHTySOcYWXyfJKzBnnBj/dNnxLOFLrEQt+PVNfWPVZeGp3V+mtY2N97RC66vrqzFti0pJTUdeVhfSXsa0lYWVnwtxfd1x8kNM0pPQnRBoUihHzuT+SlhJuNYqlZWTGQlHmXSpVRf4oyryhaRcaUn90eHJYLgX01Wh0gIxbkxDrjCNzqgQU0lWplJNZyFqYT2ZHN6InSnnEa/xylQdQEvy0pYOIRhcaGdITIXS4gIwwlPhfe1+6nbTxmpk3s1M6rrp3dY7hS/nuzhBBqW4IVN78oYaJ2Niu5hKk6mcz6ACi3VzoZUr4odUAFRlXWPJSa0RCm5KulnKko7mzMRsRTWyVZ5PzlSOka4KU35lCAoRJG9sBRhQAJvMgOCYmiqTNtiGTd8hzNkM1L5QkodcMzIVMqGF3hENjhboQjjlYvo0mPwyOp7Qp954
*/