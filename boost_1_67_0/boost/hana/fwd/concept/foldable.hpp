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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_FOLDABLE_HPP

/* foldable.hpp
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
*/