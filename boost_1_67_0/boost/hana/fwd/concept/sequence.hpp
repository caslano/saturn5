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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_SEQUENCE_HPP

/* sequence.hpp
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
*/