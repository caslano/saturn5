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
zzXgMvYPqG00kEaNmDdd22P7Ew2OqPgMRCIq0qbhf/NNsedUViItkpYWHmGi58U7u/OLTTCKMBnYMVzTEh5bm9ZLa+WY+Wm8D3LdQRv0+GAYWouIjDm6sYezRaFQSFxztrZsNggjGVuv3xn6RASBEBtOQRnscouaP1alv7rii2FQaeDjMWw4YzYjNoOT8aLU9CH32opVtPCNXMU4UUZ/iIeNdiR6OvcfOxKNzbblvpUa7t0ZHMmgz7FF1jHoG8+0HImG6gvTt+7LqKMxdNJyy5OotcBi64/jrM6xuKzGuOYTYwv5FfYaNqQIV+fYIlXP5iOG0MCP4fBv9jaMSedQHKb8yWR0yHMXZKZLZdIMw6H8f6/gWCgF9KRhysZKcwt24D2nfoajzlXNlHofxj0veLSY/WQqf8DtIOYXb2YZZlhk12p/8f9K72AH/2MuejQbyd6i7KjGcrkOUhi/W7Ijjy63XXz1Jrd/93zx8vqHdmbBFs5/tYN91l6sz6Bjuqfr1KU0Omsk7r6Wg8+J6t1tTqzAmAscpJrrHonDCI0Dn4t6G6hfwkh8lPjTFOkGF/mKkY+6X2dK15lm6FxCrMNkwgxN4EETUlzEL9JS+gvpfKLngydlvBElfQzPiJh3Zupkkc45To1VyJK8uqQfL5Ml4Tx40FXKKcEheMEwhsZILh0d3z+TK8hRDynuQuy6Urkg1BhGRPLcFFfljFU2X006PVJfBtP92DCdaAZZHny6FKoEIfz940Q9iwdh6nPr/Yym2nSQdEQbmrODCimflV6hW5uA19wWBUm5eba1fgyjXGLrYurHneLhxbIeTy3rQekWp9J1kceO/jD7LJXL0CqOzqZo6dNo1AoiIbuXMxCkVNQnR9GQHlg5NZnoHVvU9AuISMQtU61D1D5IFNYkKyB8q6w19RPlIkM8GdFH+ateRG6YgTiHA7ThmVg6J0vMtW5CG6QYKLswo6lI6k15w9EgWNaroynvxz+xpeqOVDEnA0piK45zeRQSVCfGIeH/GWXLYffmN9iybcPRaZia7b4ljDjDvdmW4BGpApcPaxxNl0uHe9gKvkOvxKZk8TFzXf+m+5DOWGvLuIICLqFOnoe32AVNZ9Oj2tb5MylgbKs5ITluX1OIIofKyLFNV/9PHtBG2JEXfhFx3XSekXn6xyNU/PIESav8YPs6yYNI2pQpbuzqedJ9eaTOIXqw6NN94KtA6vA02/4TjV8n2QDld9qLumG19udXCP8nWqEGTy89NYEV81ZiVIKyVc7UhoqxTWMKxpTsAaZkHSZpKusz3kCuFKFtoqMXUVwrmVwM0rd1NNiGlYiLilOwzNVligl4mHtw5FI8FJoQ6fJeQDrlPjWkPZJ/7CDGCQm197ZtFNBVBkglQ6ZD3c+2ufBDoTutQr1NxEUHRckiZVmU1B7q3U+yIvlzS731Y7NsDAJ3mFeSxXNWclcwvK9tE+YcB+kjAojzNQbSsPTYxAdZbDN1SEPQpD4Nitt/lMqctGUeqjITvSQFFUmPn4kPICscweRw8w8iIbkkdqruRvKmz5EfoluUOA6DKUiUu1K8uSep6SNdiqPddJj3acP1sBNnV1nUDxNejxgfH6CLztdozu80zheKRkWRzhA/Hhau+cOpfSATsow0kCf1ynNAs0nq13Q8XoxBDlVFNnXYfJJxiMOqc/NxRi/b19FGd9vXoUYH6+vI5h58ANbcge89aILzlfJ/skiZ2dt5heW457Ypev2TjK9f7JAvueJDvPDdJmnt1dfAl4oVndIwj1hkCUP/dda5/vl/PDbFDZfo+Z+TeI7V6Do3682IWDufpxQtPB2rZ3RuYAO51JBMo3hrJk4db63YpNo=
*/