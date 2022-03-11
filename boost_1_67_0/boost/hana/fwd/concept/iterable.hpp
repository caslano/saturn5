/*!
@file
Forward declares `boost::hana::Iterable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_ITERABLE_HPP
#define BOOST_HANA_FWD_CONCEPT_ITERABLE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Iterable Iterable
    //! The `Iterable` concept represents data structures supporting external
    //! iteration.
    //!
    //! Intuitively, an `Iterable` can be seen as a kind of container whose
    //! elements can be pulled out one at a time. An `Iterable` also provides
    //! a way to know when the _container_ is empty, i.e. when there are no
    //! more elements to pull out.
    //!
    //! Whereas `Foldable` represents data structures supporting internal
    //! iteration with the ability to accumulate a result, the `Iterable`
    //! concept allows inverting the control of the iteration. This is more
    //! flexible than `Foldable`, since it allows iterating over only some
    //! part of the structure. This, in turn, allows `Iterable` to work on
    //! infinite structures, while trying to fold such a structure would
    //! never finish.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `at`, `drop_front` and `is_empty`
    //!
    //!
    //! @anchor Iterable-lin
    //! The linearization of an `Iterable`
    //! ----------------------------------
    //! Intuitively, for an `Iterable` structure `xs`, the _linearization_ of
    //! `xs` is the sequence of all the elements in `xs` as if they had been
    //! put in a (possibly infinite) list:
    //! @code
    //!     linearization(xs) = [x1, x2, x3, ...]
    //! @endcode
    //!
    //! The `n`th element of the linearization of an `Iterable` can be
    //! accessed with the `at` function. In other words, `at(xs, n) == xn`.
    //!
    //! Note that this notion is precisely the extension of the [linearization]
    //! (@ref Foldable-lin) notion of `Foldable`s to the infinite case. This
    //! notion is useful for expressing various properties of `Iterable`s,
    //! and is used for that elsewhere in the documentation.
    //!
    //!
    //! Compile-time `Iterable`s
    //! ------------------------
    //! A _compile-time_ `Iterable` is an `Iterable` for which `is_empty`
    //! returns a compile-time `Logical`. These structures allow iteration
    //! to be done at compile-time, in the sense that the "loop" doing the
    //! iteration can be unrolled because the total length of the structure
    //! is kown at compile-time.
    //!
    //! In particular, note that being a compile-time `Iterable` has nothing
    //! to do with being finite or infinite. For example, it would be possible
    //! to create a sequence representing the Pythagorean triples as
    //! `integral_constant`s. Such a sequence would be infinite, but iteration
    //! on the sequence would still be done at compile-time. However, if one
    //! tried to iterate over _all_ the elements of the sequence, the compiler
    //! would loop indefinitely, in contrast to your program looping
    //! indefinitely if the sequence was a runtime one.
    //!
    //! __In the current version of the library, only compile-time `Iterable`s
    //! are supported.__ While it would be possible in theory to support
    //! runtime `Iterable`s, doing it efficiently is the subject of some
    //! research. In particular, follow [this issue][1] for the current
    //! status of runtime `Iterable`s.
    //!
    //!
    //! Laws
    //! ----
    //! First, we require the equality of two `Iterable`s to be related to the
    //! equality of the elements in their linearizations. More specifically,
    //! if `xs` and `ys` are two `Iterable`s of data type `It`, then
    //! @code
    //!     xs == ys  =>  at(xs, i) == at(ys, i)   for all i
    //! @endcode
    //!
    //! This conveys that two `Iterable`s must have the same linearization
    //! in order to be considered equal.
    //!
    //! Secondly, since every `Iterable` is also a `Searchable`, we require
    //! the models of `Iterable` and `Searchable` to be consistent. This is
    //! made precise by the following laws. For any `Iterable` `xs` with a
    //! linearization of `[x1, x2, x3, ...]`,
    //! @code
    //!     any_of(xs, equal.to(z))  <=>  xi == z
    //! @endcode
    //! for some _finite_ index `i`. Furthermore,
    //! @code
    //!     find_if(xs, pred) == just(the first xi such that pred(xi) is satisfied)
    //! @endcode
    //! or `nothing` if no such `xi` exists.
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! 1. `Searchable` (free model)\n
    //! Any `Iterable` gives rise to a model of `Searchable`, where the keys
    //! and the values are both the elements in the structure. Searching for
    //! a key is just doing a linear search through the elements of the
    //! structure.
    //! @include example/iterable/searchable.cpp
    //!
    //! 2. `Foldable` for finite `Iterable`s\n
    //! Every finite `Iterable` gives rise to a model of  `Foldable`. For
    //! these models to be consistent, we require the models of both `Foldable`
    //! and `Iterable` to have the same linearization.
    //!
    //! @note
    //! As explained above, `Iterable`s are also `Searchable`s and their
    //! models have to be consistent. By the laws presented here, it also
    //! means that the `Foldable` model for finite `Iterable`s has to be
    //! consistent with the `Searchable` model.
    //!
    //! For convenience, finite `Iterable`s must only provide a definition of
    //! `length` to model the `Foldable` concept; defining the more powerful
    //! `unpack` or `fold_left` is not necessary (but still possible). The
    //! default implementation of `unpack` derived from `Iterable` + `length`
    //! uses the fact that `at(xs, i)` denotes the `i`th element of `xs`'s
    //! linearization, and that the linearization of a finite `Iterable` must
    //! be the same as its linearization as a `Foldable`.
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::tuple`, `hana::string`, `hana::range`
    //!
    //!
    //! [1]: https://github.com/boostorg/hana/issues/40
    template <typename It>
    struct Iterable;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_ITERABLE_HPP

/* iterable.hpp
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
*/