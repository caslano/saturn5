/*!
@file
Forward declares `boost::hana::Foldable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_FOLDABLE_HPP
#define BOOST_HANA_FWD_CONCEPT_FOLDABLE_HPP

#include <boost/hana/config.hpp>


namespace boost { namespace hana {
    //! @ingroup group-concepts
    //! @defgroup group-Foldable Foldable
    //! The `Foldable` concept represents data structures that can be reduced
    //! to a single value.
    //!
    //! Generally speaking, folding refers to the concept of summarizing a
    //! complex structure as a single value, by successively applying a
    //! binary operation which reduces two elements of the structure to a
    //! single value. Folds come in many flavors; left folds, right folds,
    //! folds with and without an initial reduction state, and their monadic
    //! variants. This concept is able to express all of these fold variants.
    //!
    //! Another way of seeing `Foldable` is as data structures supporting
    //! internal iteration with the ability to accumulate a result. By
    //! internal iteration, we mean that the _loop control_ is in the hand
    //! of the structure, not the caller. Hence, it is the structure who
    //! decides when the iteration stops, which is normally when the whole
    //! structure has been consumed. Since C++ is an eager language, this
    //! requires `Foldable` structures to be finite, or otherwise one would
    //! need to loop indefinitely to consume the whole structure.
    //!
    //! @note
    //! While the fact that `Foldable` only works for finite structures may
    //! seem overly restrictive in comparison to the Haskell definition of
    //! `Foldable`, a finer grained separation of the concepts should
    //! mitigate the issue. For iterating over possibly infinite data
    //! structures, see the `Iterable` concept. For searching a possibly
    //! infinite data structure, see the `Searchable` concept.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `fold_left` or `unpack`
    //!
    //! However, please note that a minimal complete definition provided
    //! through `unpack` will be much more compile-time efficient than one
    //! provided through `fold_left`.
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::map`, `hana::optional`, `hana::pair`, `hana::set`,
    //! `hana::range`, `hana::tuple`
    //!
    //!
    //! @anchor Foldable-lin
    //! The linearization of a `Foldable`
    //! ---------------------------------
    //! Intuitively, for a `Foldable` structure `xs`, the _linearization_ of
    //! `xs` is the sequence of all the elements in `xs` as if they had been
    //! put in a list:
    //! @code
    //!     linearization(xs) = [x1, x2, ..., xn]
    //! @endcode
    //!
    //! Note that it is always possible to produce such a linearization
    //! for a finite `Foldable` by setting
    //! @code
    //!     linearization(xs) = fold_left(xs, [], flip(prepend))
    //! @endcode
    //! for an appropriate definition of `[]` and `prepend`. The notion of
    //! linearization is useful for expressing various properties of
    //! `Foldable` structures, and is used across the documentation. Also
    //! note that `Iterable`s define an [extended version](@ref Iterable-lin)
    //! of this allowing for infinite structures.
    //!
    //!
    //! Compile-time Foldables
    //! ----------------------
    //! A compile-time `Foldable` is a `Foldable` whose total length is known
    //! at compile-time. In other words, it is a `Foldable` whose `length`
    //! method returns a `Constant` of an unsigned integral type. When
    //! folding a compile-time `Foldable`, the folding can be unrolled,
    //! because the final number of steps of the algorithm is known at
    //! compile-time.
    //!
    //! Additionally, the `unpack` method is only available to compile-time
    //! `Foldable`s. This is because the return _type_ of `unpack` depends
    //! on the number of objects in the structure. Being able to resolve
    //! `unpack`'s return type at compile-time hence requires the length of
    //! the structure to be known at compile-time too.
    //!
    //! __In the current version of the library, only compile-time `Foldable`s
    //! are supported.__ While it would be possible in theory to support
    //! runtime `Foldable`s too, doing so efficiently requires more research.
    //!
    //!
    //! Provided conversion to `Sequence`s
    //! ----------------------------------
    //! Given a tag `S` which is a `Sequence`, an object whose tag is a model
    //! of the `Foldable` concept can be converted to an object of tag `S`.
    //! In other words, a `Foldable` can be converted to a `Sequence` `S`, by
    //! simply taking the linearization of the `Foldable` and creating the
    //! sequence with that. More specifically, given a `Foldable` `xs` with a
    //! linearization of `[x1, ..., xn]` and a `Sequence` tag `S`, `to<S>(xs)`
    //! is equivalent to `make<S>(x1, ..., xn)`.
    //! @include example/foldable/to.cpp
    //!
    //!
    //! Free model for builtin arrays
    //! -----------------------------
    //! Builtin arrays whose size is known can be folded as-if they were
    //! homogeneous tuples. However, note that builtin arrays can't be
    //! made more than `Foldable` (e.g. `Iterable`) because they can't
    //! be empty and they also can't be returned from functions.
    //!
    //!
    //! @anchor monadic-folds
    //! Primer on monadic folds
    //! -----------------------
    //! A monadic fold is a fold in which subsequent calls to the binary
    //! function are chained with the monadic `chain` operator of the
    //! corresponding Monad. This allows a structure to be folded in a
    //! custom monadic context. For example, performing a monadic fold with
    //! the `hana::optional` monad would require the binary function to return
    //! the result as a `hana::optional`, and the fold would abort and return
    //! `nothing` whenever one of the accumulation step would fail (i.e.
    //! return `nothing`). If, however, all the reduction steps succeed,
    //! then `just` the result would be returned. Different monads will of
    //! course result in different effects.
    template <typename T>
    struct Foldable;
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_FOLDABLE_HPP

/* foldable.hpp
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
*/