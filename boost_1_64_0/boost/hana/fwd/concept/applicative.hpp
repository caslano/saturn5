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
X8WUyMOK5SzpTRrgO2Wig1yaGH9AnvN5R85a5c43eUd+r+zyuc8ccEeu5IdSettdL2NTE3pZBriJhdM7xbum5s0Uv/01jwmWvymNFTMJaPHs39GOhQ5Wg4SIwK2XFcsCCtPSbe1UmwILe5dH+ejAQ5r1Z78pd4Fn4BtdSCkQHICaIp8vRBfJPDDSuZTz5H+DdZF/pn2vl8CnktJYgHXO84q2611NHa3eMIUzqswBC/IZD3XrlbyZ108mKR2uo8ff222zxTqz1rB6gKaQDizFGzfRLJMPbI/jA8upb5NoXluB//mottZw5YvTDFexmGi4SkWp4SoUI+CCuizc/jCx7qQcygevucZlhxLs8tMvAd/CN5HCRpwfcfgU15jxi2X2fD6SG3mv2h/MVq+JicFm2BTTankPM6w8LN/miYiae9TBZKF+ihNye32RS59GRHw8+mgcuJut95iia+ztX1C+mMnl4xme39ANh0G3m2pbUMSWPSme5qhcRFEwP9f0LzT49vzzB8FP5SQuAAfq15ZazPkUjWIy5TWYRJMFPqNysc1JmonO5ESpteYupWFUS9ypJJx65fRkxfTEoumdYp2N6dPcPTV/phjxniFLnZlYNMUSG5pYOAUyVtaXSlZMQT/ivvkUzDmx9jrVz4egbAo5GRdXmIRM4SvVixyW2FGJhQ6c14TFUXcZxbJ0H0NJdGf1raqI3sxsUliCwxQd0nNJQJvHysdOcdiLajA3YmNBk9VthjyFWUIC4EovcemVvmSFj+/f1GqbVZfQXL4YW0LtZTNkfkAkeNuI9KygEEvhx1dxYPuvHzNtFDwDoXplIFkR0HMiYQjwWK5FquRvZpY+kDblOciDFUG+PhygD9IbUrd/gmh8hz9DX4Xk4zAfjiulC//Y9tin32sZxz4RefLL9sNJMalhf/J4abuR1pUOCfXnV7cj1Id9mEGoB+m5emkmha5QFBoGk3jv6KLBf+A5SZ/vxjd6ttnlKx+CdzZ7w+JmTh74Z3u54/MWR5bf+TXnLd6G7P2QOpKQz8ZMe07hbDO1J1euY4bl9A7XUz+vp09mrKcr5Xp62Ors9fQA+e/IyP9zY//z1AHzq/Ol7PICXF5jRnn3Gfb/Dqa8Kdn9idJI2BZkLfYxz6re+YhPj8R16e5RGQ98vhVo63cmLlxgiUsBfx1JeJMk+cCCkUNBqXcPcBan+Nns+dMnOkA2fDb+ecRvnlQ0tiGxyGlB9CCjXzh6QTo6DO5TshHi4hfTDHHfaL4MLuMMJ6sMmHPJsbtzbfF/sHcl8FEWVzybLMkCC7vAAkEWWCFKlIjRBEhIxHAlqBE3LLsLAgEV8XNFRdgEVE6XK3xE8aqt1aqtt7Z4oKJWC6Yar9b7aPHAo3bSiGJVQEW2//dm5tsvCUKs7a9n+C3f983x5s315s2bN+9li1d+oS5MxQeLRn6nuda3sdznYDqT7UxjmyUWu3kYzZklT8s5U4NnbJSaJBfdq8HTvG6vL4ADrk85tNOfoMeDUYT/xOvXy51+JshlTqs9/nf1T8911D/LW/SPVtw44H7J12Afn9k8Pu+zjc975Pj87NF2zRfK39e4LpU/di7pf7fKfCB85Jzhw25AyrIgjY2dT/qfFiRuQb1GdrzJtkZOkn7Z4Y7wWj0hjleinO5B6ltfo6bVHjIZQUE3ScGr8knu4zPPHU/pZN2kbQkKXCQTUp5PHtei3864wLiNP+Ryvvhd+3Lerg3A888fnL7q8zFLfmUsc9iW0Ld+xYLKQJtFFCvFSDQolEcKjNU6B+7/PK0EbH51rBtltTkxpwcv3nVLAyzCatfJbgL45TbthODd/r3rbnzvfz2ALCFippvzptM=
*/