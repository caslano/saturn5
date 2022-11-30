/*!
@file
Forward declares `boost::hana::Sequence`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_SEQUENCE_HPP
#define BOOST_HANA_FWD_CONCEPT_SEQUENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! @ingroup group-concepts
    //! @defgroup group-Sequence Sequence
    //! The `Sequence` concept represents generic index-based sequences.
    //!
    //! Compared to other abstract concepts, the Sequence concept is very
    //! specific. It represents generic index-based sequences. The reason
    //! why such a specific concept is provided is because there are a lot
    //! of models that behave exactly the same while being implemented in
    //! wildly different ways. It is useful to regroup all those data types
    //! under the same umbrella for the purpose of generic programming.
    //!
    //! In fact, models of this concept are not only _similar_. They are
    //! actually _isomorphic_, in a sense that we define below, which is
    //! a fancy way of rigorously saying that they behave exactly the same
    //! to an external observer.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `Iterable`, `Foldable`, and `make`
    //!
    //! The `Sequence` concept does not provide basic methods that could be
    //! used as a minimal complete definition; instead, it borrows methods
    //! from other concepts and add laws to them. For this reason, it is
    //! necessary to specialize the `Sequence` metafunction in Hana's
    //! namespace to tell Hana that a type is indeed a `Sequence`. Explicitly
    //! specializing the `Sequence` metafunction can be seen like a seal
    //! saying "this data type satisfies the additional laws of a `Sequence`",
    //! since those can't be checked by Hana automatically.
    //!
    //!
    //! Laws
    //! ----
    //! The laws for being a `Sequence` are simple, and their goal is to
    //! restrict the semantics that can be associated to the functions
    //! provided by other concepts. First, a `Sequence` must be a finite
    //! `Iterable` (thus a `Foldable` too). Secondly, for a `Sequence` tag
    //! `S`, `make<S>(x1, ..., xn)` must be an object of tag `S` and whose
    //! linearization is `[x1, ..., xn]`. This basically ensures that objects
    //! of tag `S` are equivalent to their linearization, and that they can
    //! be created from such a linearization (with `make`).
    //!
    //! While it would be possible in theory to handle infinite sequences,
    //! doing so complicates the implementation of many algorithms. For
    //! simplicity, the current version of the library only handles finite
    //! sequences. However, note that this does not affect in any way the
    //! potential for having infinite `Searchable`s and `Iterable`s.
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! 1. `Comparable` (definition provided automatically)\n
    //! Two `Sequence`s are equal if and only if they contain the same number
    //! of elements and their elements at any given index are equal.
    //! @include example/sequence/comparable.cpp
    //!
    //! 2. `Orderable` (definition provided automatically)\n
    //! `Sequence`s are ordered using the traditional lexicographical ordering.
    //! @include example/sequence/orderable.cpp
    //!
    //! 3. `Functor` (definition provided automatically)\n
    //! `Sequence`s implement `transform` as the mapping of a function over
    //! each element of the sequence. This is somewhat equivalent to what
    //! `std::transform` does to ranges of iterators. Also note that mapping
    //! a function over an empty sequence returns an empty sequence and never
    //! applies the function, as would be expected.
    //! @include example/sequence/functor.cpp
    //!
    //! 4. `Applicative` (definition provided automatically)\n
    //! First, `lift`ing a value into a `Sequence` is the same as creating a
    //! singleton sequence containing that value. Second, applying a sequence
    //! of functions to a sequence of values will apply each function to
    //! all the values in the sequence, and then return a list of all the
    //! results. In other words,
    //! @code
    //!     ap([f1, ..., fN], [x1, ..., xM]) == [
    //!         f1(x1), ..., f1(xM),
    //!         ...
    //!         fN(x1), ..., fN(xM)
    //!     ]
    //! @endcode
    //! Example:
    //! @include example/sequence/applicative.cpp
    //!
    //! 5. `Monad` (definition provided automatically)\n
    //! First, `flaten`ning a `Sequence` takes a sequence of sequences and
    //! concatenates them to get a larger sequence. In other words,
    //! @code
    //!     flatten([[a1, ..., aN], ..., [z1, ..., zM]]) == [
    //!         a1, ..., aN, ..., z1, ..., zM
    //!     ]
    //! @endcode
    //! This acts like a `std::tuple_cat` function, except it receives a
    //! sequence of sequences instead of a variadic pack of sequences to
    //! flatten.\n
    //! __Example__:
    //! @include example/sequence/monad.ints.cpp
    //! Also note that the model of `Monad` for `Sequence`s can be seen as
    //! modeling nondeterminism. A nondeterministic computation can be
    //! modeled as a function which returns a sequence of possible results.
    //! In this line of thought, `chain`ing a sequence of values into such
    //! a function will return a sequence of all the possible output values,
    //! i.e. a sequence of all the values applied to all the functions in
    //! the sequences.\n
    //! __Example__:
    //! @include example/sequence/monad.types.cpp
    //!
    //! 6. `MonadPlus` (definition provided automatically)\n
    //! `Sequence`s are models of the `MonadPlus` concept by considering the
    //! empty sequence as the unit of `concat`, and sequence concatenation
    //! as `concat`.
    //! @include example/sequence/monad_plus.cpp
    //!
    //! 7. `Foldable`\n
    //! The model of `Foldable` for `Sequence`s is uniquely determined by the
    //! model of `Iterable`.
    //! @include example/sequence/foldable.cpp
    //!
    //! 8. `Iterable`\n
    //! The model of `Iterable` for `Sequence`s corresponds to iteration over
    //! each element of the sequence, in order. This model is not provided
    //! automatically, and it is in fact part of the minimal complete
    //! definition for the `Sequence` concept.
    //! @include example/sequence/iterable.cpp
    //!
    //! 9. `Searchable` (definition provided automatically)\n
    //! Searching through a `Sequence` is equivalent to just searching through
    //! a list of the values it contains. The keys and the values on which
    //! the search is performed are both the elements of the sequence.
    //! @include example/sequence/searchable.cpp
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::tuple`
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Isomorphism#Isomorphism_vs._bijective_morphism
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename S>
    struct Sequence;
#else
    template <typename S, typename = void>
    struct Sequence : Sequence<S, when<true>> { };
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_SEQUENCE_HPP

/* sequence.hpp
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
*/