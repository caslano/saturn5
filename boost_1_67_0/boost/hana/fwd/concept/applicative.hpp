/*!
@file
Forward declares `boost::hana::Applicative`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_APPLICATIVE_HPP
#define BOOST_HANA_FWD_CONCEPT_APPLICATIVE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Applicative Applicative
    //! The `Applicative` concept represents `Functor`s with the ability
    //! to lift values and combine computations.
    //!
    //! A `Functor` can only take a normal function and map it over a
    //! structure containing values to obtain a new structure containing
    //! values. Intuitively, an `Applicative` can also take a value and
    //! lift it into the structure. In addition, an `Applicative` can take
    //! a structure containing functions and apply it to a structure
    //! containing values to obtain a new structure containing values.
    //! By currying the function(s) inside the structure, it is then
    //! also possible to apply n-ary functions to n structures containing
    //! values.
    //!
    //! @note
    //! This documentation does not go into much details about the nature
    //! of applicatives. However, the [Typeclassopedia][1] is a nice
    //! Haskell-oriented resource where such information can be found.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `lift` and `ap` satisfying the laws below. An `Applicative` must
    //! also be a `Functor`.
    //!
    //!
    //! Laws
    //! ----
    //! Given an `Applicative` `F`, the following laws must be satisfied:
    //! 1. Identity\n
    //! For all objects `xs` of tag `F(A)`,
    //! @code
    //!     ap(lift<F>(id), xs) == xs
    //! @endcode
    //!
    //! 2. Composition\n
    //! For all objects `xs` of tag `F(A)` and functions-in-an-applicative
    //! @f$ fs : F(B \to C) @f$,
    //! @f$ gs : F(A \to B) @f$,
    //! @code
    //!     ap(ap(lift<F>(compose), fs, gs), xs) == ap(fs, ap(gs, xs))
    //! @endcode
    //!
    //! 3. Homomorphism\n
    //! For all objects `x` of tag `A` and functions @f$ f : A \to B @f$,
    //! @code
    //!     ap(lift<F>(f), lift<F>(x)) == lift<F>(f(x))
    //! @endcode
    //!
    //! 4. Interchange\n
    //! For all objects `x` of tag `A` and functions-in-an-applicative
    //! @f$ fs : F(A \to B) @f$,
    //! @code
    //!     ap(fs, lift<F>(x)) == ap(lift<F>(apply(-, x)), fs)
    //! @endcode
    //! where `apply(-, x)` denotes the partial application of the `apply`
    //! function from the @ref group-functional module to the `x` argument.
    //!
    //! As a consequence of these laws, the model of `Functor` for `F` will
    //! satisfy the following for all objects `xs` of tag `F(A)` and functions
    //! @f$ f : A \to B @f$:
    //! @code
    //!     transform(xs, f) == ap(lift<F>(f), xs)
    //! @endcode
    //!
    //!
    //! Refined concept
    //! ---------------
    //! 1. `Functor` (free model)\n
    //! As a consequence of the laws, any `Applicative F` can be made a
    //! `Functor` by setting
    //! @code
    //!     transform(xs, f) = ap(lift<F>(f), xs)
    //! @endcode
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::lazy`, `hana::optional`, `hana::tuple`
    //!
    //!
    //! @anchor applicative-transformation
    //! Structure-preserving functions
    //! ------------------------------
    //! An _applicative transformation_ is a function @f$ t : F(X) \to G(X) @f$
    //! between two Applicatives `F` and `G`, where `X` can be any tag, and
    //! which preserves the operations of an Applicative. In other words, for
    //! all objects `x` of tag `X`, functions-in-an-applicative
    //! @f$ fs : F(X \to Y) @f$ and objects `xs` of tag `F(X)`,
    //! @code
    //!     t(lift<F>(x)) == lift<G>(x)
    //!     t(ap(fs, xs)) == ap(t(fs), t(xs))
    //! @endcode
    //!
    //! [1]: https://wiki.haskell.org/Typeclassopedia#Applicative
    template <typename A>
    struct Applicative;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_APPLICATIVE_HPP

/* applicative.hpp
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
*/