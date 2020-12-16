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
zjfDuK1fPUcZPIdacG7NeXQkbz6XaHLO7y35DTOzJL3GCw2mxBNOBC/4NPHV3vhR6zJHpteMTnz1bXzgunLHyDGOmsLEV/viPdeVp48ck14zOPFVMu5aV54xckxGzSFqUOfqn/hAjl9TGCE9gEJMB4cCGbwUiqflSZD55A8199u2Pf18/3mFbs+iaOIFi0MlVvQ3GUQkD1+m7R+Dkt3NQX6pLai9c12DQNJwJAJrcoK7K1OEFYTGTliJvxXHT7QI6wWOFGE9lTNvupQYigaAiBApEw+rt4DYaIXdwgX4lGvIgHFRajIylaP7rzVyaX8jnbQeHzrDUqHkDMutDF6d4f04Z+CLJ8kCseRki4+Ky5CGDVbI6elSmQ6hPztRc5N1lRS6wCnGpLIWq6A1qbyH67wIPi2V2ZMupbdlCGcicGlc80idjHqioH1BoyijGDZfKUESKdu6PYO0rku2Lu1eP7rFKlDYzAm0ZK1IzFzKQ58h/pggPqOU5E0AABzAGJx4Ty0CW4PEcmER+MWGVK7rKdeVyMWYauaVF5qtJ3HzcbKfU7K5ipPkpJD+BsXPbEluoyQnIElYDJiq+8bHfXN3akjovilfIPumkyMl4s5n8XpYHMrZsznrPW27tbPK+gLf1Xu8hvjvhTXc7NgSazenYcl/54mfJTSOJxgPtoX22HwJbQU+hXuiTtvPeLxt2stl2uYpdP1GN1hOWFRfmOrY31IzjPmWLlWERWiCOk/b/W7fZEVzwFhjzZ3rAFLDLZZwCzBLcjB+4Idvklo3zq1SkmK5XPgbjDkWWot19q8v0KZlVKp/IE35T/4jqzimQ5pu6VHF3Kk+S3mRltVYH+PGt7R57W9kW/5qnhYG7BeeT8PLrMNHcvv+QJyzfxCcP1vZj40P0PgEWv8It0BD7Agb4H3q/Pu7cdPwAxo+4RcAfvsB89z5342fk/LnpbxAxY7V+VOyCvMA+b2Uv0jl93L7vGrl3yvzn3T+QdqnUOXPZvxT+b9V8/+78m/O4/XvIlr/sJUwMT/hDcCPn7d+RgAPN37Z+PnwC0SxWrnqZ4xtWkAL2NIK5vqhowa5RKf6KaMLdqnV64WFFsNJZtZIFR8b2jJ2vR2GIth0i/s4nNMfc4YSANGK24OD3sCkDhob3ial0fUX6R3+pbvSqVHO7IHQWg51Ueh23skUV9mgPIwgXd6YVHkPUkrjRgY7jAHAWSyBuAER9ec5mu6nBBDnXjuPaGRont45jWNPLqxo5xnXRN6vxaTJqc1MCNnEaATozcwYCsiXAX4KOAYB0aCWWkTIab14pkTTzp6P0taNNp5NPSnnUZCYNX8YERvrLdFP/K2I+HIaPkUExReJ96Zq3AoB7Dcw17VceiSmEAhycZobXCzZlmzqRCS6NiKMmF5naMjB89Zfq3RATut+6jTNarfT5bI7Thx/AvXLJm7ALxZZ/TIG0TgbzU2LhyGBrbV1RC5iNMCHT7UAdkMwTi8mELSnGdqtKWhf0JIojyOMtxDZ7NZfH3PSdTOt7RCv3mg2JIgYX3DsXFsslSsXOGMvR56Sirxb6tXnyQQBaKbVuJLD3sIZVnOPxB4nfWynj8zksA/xjIoeOm88LvMUGc53COjX1TpiGnESePZCgqDh5di3rNjjTNnsh4aJ8Q0aAY4X6HAZ349vfjUfW7BLvhxBNXt0NL2mw2fHDoNE8MZ0VCRkXC1n9jEs2GIKLW6qpYXwp7VyGIgr9EudfMkXY05SfLRc9PL+v+hFxefMDN1ppkSs/lg/buNYlvEj2cjPn61FzdKMGtahWFT0Aw+hNQyiYvdaOujZKc5ikhFopyWJqFjA5R/ZovwSWX7AuEqWX7nf8q8=
*/