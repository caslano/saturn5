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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_ITERABLE_HPP

/* iterable.hpp
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
*/