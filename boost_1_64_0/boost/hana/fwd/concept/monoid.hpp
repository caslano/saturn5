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
YduWIlGemlqp34ZEY48qhUuXE8YXNYFrG63S6tLsh7qzUeMlpsO0hGh6DPtxKmCNgx8Z64DpaqDNFBAjkpuJwSYmynAQ/OLtx2WPRgGnBBo6Q4G8K8IyERo10rSwDA2h95/x2HIuLSqRIh4y4xuWM8LUHwnXd3CzfBUMqZkq8hrtpe+hC1EtxM3yXfYUVCXKYnV3qF8kLGQsSBjg3d3Rj63eeg2Hi2STrKM6i9FTiFUe285MU/ksv3RbdGotk5XVlxh0POX+GpXIpTiyq1/H75+Vt4F6Og9YZb2FeduOL8HLmtwBH0CQsXGzE5lVGvPaAQlESgM4/NFwZhsHTe696oukuCqpWSjfOJp3EmysWHVS/pY+6VLjGzXbzSiBT3q4DFfcSTzyRJyEFn5MIGFKhrfg2lsTTHQQHjgvfICWIQt39M16ARnZR7cZD3qKo2BfsM5ZZg3M/9bKq0/tTZz15UCoNt3Gxi9wtWvaAXNEyqgBdNdlBWUOtbdaX6dflM6VlUWJwdlxrzJBQCQgfvQBS0sPmzxUeO1pfsW5ukK+vI/xqzRh2m06RAaJQw==
*/