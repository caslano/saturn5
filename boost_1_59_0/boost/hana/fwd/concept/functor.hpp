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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_FUNCTOR_HPP

/* functor.hpp
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
*/