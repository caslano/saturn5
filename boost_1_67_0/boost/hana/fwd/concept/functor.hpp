/*!
@file
Forward declares `boost::hana::Functor`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_FUNCTOR_HPP
#define BOOST_HANA_FWD_CONCEPT_FUNCTOR_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Functor Functor
    //! The `Functor` concept represents types that can be mapped over.
    //!
    //! Intuitively, a [Functor][1] is some kind of box that can hold generic
    //! data and map a function over this data to create a new, transformed
    //! box. Because we are only interested in mapping a function over the
    //! contents of a black box, the only real requirement for being a functor
    //! is to provide a function which can do the mapping, along with a couple
    //! of guarantees that the mapping is well-behaved. Those requirements are
    //! made precise in the laws below. The pattern captured by `Functor` is
    //! very general, which makes it widely useful. A lot of objects can be
    //! made `Functor`s in one way or another, the most obvious example being
    //! sequences with the usual mapping of the function on each element.
    //! While this documentation will not go into much more details about
    //! the nature of functors, the [Typeclassopedia][2] is a nice
    //! Haskell-oriented resource for such information.
    //!
    //! Functors are parametric data types which are parameterized over the
    //! data type of the objects they contain. Like everywhere else in Hana,
    //! this parametricity is only at the documentation level and it is not
    //! enforced.
    //!
    //! In this library, the mapping function is called `transform` after the
    //! `std::transform` algorithm, but other programming languages have given
    //! it different names (usually `map`).
    //!
    //! @note
    //! The word _functor_ comes from functional programming, where the
    //! concept has been used for a while, notably in the Haskell programming
    //! language. Haskell people borrowed the term from [category theory][3],
    //! which, broadly speaking, is a field of mathematics dealing with
    //! abstract structures and transformations between those structures.
    //!
    //!
    //! Minimal complete definitions
    //! ----------------------------
    //! 1. `transform`\n
    //! When `transform` is specified, `adjust_if` is defined analogously to
    //! @code
    //!     adjust_if(xs, pred, f) = transform(xs, [](x){
    //!         if pred(x) then f(x) else x
    //!     })
    //! @endcode
    //!
    //! 2. `adjust_if`\n
    //! When `adjust_if` is specified, `transform` is defined analogously to
    //! @code
    //!     transform(xs, f) = adjust_if(xs, always(true), f)
    //! @endcode
    //!
    //!
    //! Laws
    //! ----
    //! Let `xs` be a Functor with tag `F(A)`,
    //!     \f$ f : A \to B \f$ and
    //!     \f$ g : B \to C \f$.
    //! The following laws must be satisfied:
    //! @code
    //!     transform(xs, id) == xs
    //!     transform(xs, compose(g, f)) == transform(transform(xs, f), g)
    //! @endcode
    //! The first line says that mapping the identity function should not do
    //! anything, which precludes the functor from doing something nasty
    //! behind the scenes. The second line states that mapping the composition
    //! of two functions is the same as mapping the first function, and then
    //! the second on the result. While the usual functor laws are usually
    //! restricted to the above, this library includes other convenience
    //! methods and they should satisfy the following equations.
    //! Let `xs` be a Functor with tag `F(A)`,
    //!     \f$ f : A \to A \f$,
    //!     \f$ \mathrm{pred} : A \to \mathrm{Bool} \f$
    //! for some `Logical` `Bool`, and `oldval`, `newval`, `value` objects
    //! of tag `A`. Then,
    //! @code
    //!     adjust(xs, value, f) == adjust_if(xs, equal.to(value), f)
    //!     adjust_if(xs, pred, f) == transform(xs, [](x){
    //!         if pred(x) then f(x) else x
    //!     })
    //!     replace_if(xs, pred, value) == adjust_if(xs, pred, always(value))
    //!     replace(xs, oldval, newval) == replace_if(xs, equal.to(oldval), newval)
    //!     fill(xs, value)             == replace_if(xs, always(true), value)
    //! @endcode
    //! The default definition of the methods will satisfy these equations.
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::lazy`, `hana::optional`, `hana::tuple`
    //!
    //!
    //! Structure-preserving functions for Functors
    //! -------------------------------------------
    //! A mapping between two functors which also preserves the functor
    //! laws is called a natural transformation (the term comes from
    //! category theory). A natural transformation is a function `f`
    //! from a functor `F` to a functor `G` such that for every other
    //! function `g` with an appropriate signature and for every object
    //! `xs` of tag `F(X)`,
    //! @code
    //!     f(transform(xs, g)) == transform(f(xs), g)
    //! @endcode
    //!
    //! There are several examples of such transformations, like `to<tuple_tag>`
    //! when applied to an optional value. Indeed, for any function `g` and
    //! `hana::optional` `opt`,
    //! @code
    //!     to<tuple_tag>(transform(opt, g)) == transform(to<tuple_tag>(opt), g)
    //! @endcode
    //!
    //! Of course, natural transformations are not limited to the `to<...>`
    //! functions. However, note that any conversion function between Functors
    //! should be natural for the behavior of the conversion to be intuitive.
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Functor
    //! [2]: https://wiki.haskell.org/Typeclassopedia#Functor
    //! [3]: http://en.wikipedia.org/wiki/Category_theory
    template <typename F>
    struct Functor;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_FUNCTOR_HPP

/* functor.hpp
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
*/