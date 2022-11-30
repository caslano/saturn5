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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_APPLICATIVE_HPP

/* applicative.hpp
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
*/