/*!
@file
Forward declares `boost::hana::Searchable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_SEARCHABLE_HPP
#define BOOST_HANA_FWD_CONCEPT_SEARCHABLE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Searchable Searchable
    //! The `Searchable` concept represents structures that can be searched.
    //!
    //! Intuitively, a `Searchable` is any structure, finite or infinite,
    //! containing elements that can be searched using a predicate. Sometimes,
    //! `Searchable`s will associate keys to values; one can search for a key
    //! with a predicate, and the value associated to it is returned. This
    //! gives rise to map-like data structures. Other times, the elements of
    //! the structure that are searched (i.e. those to which the predicate is
    //! applied) are the same that are returned, which gives rise to set-like
    //! data structures. In general, we will refer to the _keys_ of a
    //! `Searchable` structure as those elements that are used for searching,
    //! and to the _values_ of a `Searchable` as those elements that are
    //! returned when a search is successful. As was explained, there is no
    //! requirement that both notions differ, and it is often useful to have
    //! keys and values coincide (think about `std::set`).
    //!
    //! Some methods like `any_of`, `all_of` and `none_of` allow simple queries
    //! to be performed on the keys of the structure, while other methods like
    //! `find` and `find_if` make it possible to find the value associated
    //! to a key. The most specific method should always be used if one
    //! cares about performance, because it is usually the case that heavy
    //! optimizations can be performed in more specific methods. For example,
    //! an associative data structure implemented as a hash table will be much
    //! faster to access using `find` than `find_if`, because in the second
    //! case it will have to do a linear search through all the entries.
    //! Similarly, using `contains` will likely be much faster than `any_of`
    //! with an equivalent predicate.
    //!
    //! > __Insight__\n
    //! > In a lazy evaluation context, any `Foldable` can also become a model
    //! > of `Searchable` because we can search lazily through the structure
    //! > with `fold_right`. However, in the context of C++, some `Searchable`s
    //! > can not be folded; think for example of an infinite set.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `find_if` and `any_of`
    //!
    //! When `find_if` and `any_of` are provided, the other functions are
    //! implemented according to the laws explained below.
    //!
    //! @note
    //! We could implement `any_of(xs, pred)` by checking whether
    //! `find_if(xs, pred)` is an empty `optional` or not, and then reduce
    //! the minimal complete definition to `find_if`. However, this is not
    //! done because that implementation requires the predicate of `any_of`
    //! to return a compile-time `Logical`, which is more restrictive than
    //! what we have right now.
    //!
    //!
    //! Laws
    //! ----
    //! In order for the semantics of the methods to be consistent, some
    //! properties must be satisfied by any model of the `Searchable` concept.
    //! Rigorously, for any `Searchable`s  `xs` and `ys` and any predicate `p`,
    //! the following laws should be satisfied:
    //! @code
    //!     any_of(xs, p) <=> !all_of(xs, negated p)
    //!                   <=> !none_of(xs, p)
    //!
    //!     contains(xs, x) <=> any_of(xs, equal.to(x))
    //!
    //!     find(xs, x) == find_if(xs, equal.to(x))
    //!     find_if(xs, always(false_)) == nothing
    //!
    //!     is_subset(xs, ys) <=> all_of(xs, [](auto x) { return contains(ys, x); })
    //!     is_disjoint(xs, ys) <=> none_of(xs, [](auto x) { return contains(ys, x); })
    //! @endcode
    //!
    //! Additionally, if all the keys of the `Searchable` are `Logical`s,
    //! the following laws should be satisfied:
    //! @code
    //!     any(xs)  <=> any_of(xs, id)
    //!     all(xs)  <=> all_of(xs, id)
    //!     none(xs) <=> none_of(xs, id)
    //! @endcode
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::map`, `hana::optional`, `hana::range`, `hana::set`,
    //! `hana::string`, `hana::tuple`
    //!
    //!
    //! Free model for builtin arrays
    //! -----------------------------
    //! Builtin arrays whose size is known can be searched as-if they were
    //! homogeneous tuples. However, since arrays can only hold objects of
    //! a single type and the predicate to `find_if` must return a compile-time
    //! `Logical`, the `find_if` method is fairly useless. For similar reasons,
    //! the `find` method is also fairly useless. This model is provided mainly
    //! because of the `any_of` method & friends, which are both useful and
    //! compile-time efficient.
    //!
    //!
    //! Structure preserving functions
    //! ------------------------------
    //! Given two `Searchables` `S1` and `S2`, a function
    //! @f$ f : S_1(X) \to S_2(X) @f$ is said to preserve the `Searchable`
    //! structure if for all `xs` of data type `S1(X)` and predicates
    //! @f$ \mathtt{pred} : X \to Bool @f$ (for a `Logical` `Bool`),
    //! @code
    //!     any_of(xs, pred)  if and only if  any_of(f(xs), pred)
    //!     find_if(xs, pred) == find_if(f(xs), pred)
    //! @endcode
    //!
    //! This is really just a generalization of the following, more intuitive
    //! requirements. For all `xs` of data type `S1(X)` and `x` of data type
    //! `X`,
    //! @code
    //!     x ^in^ xs  if and only if  x ^in^ f(xs)
    //!     find(xs, x) == find(f(xs), x)
    //! @endcode
    //!
    //! These requirements can be understood as saying that `f` does not
    //! change the content of `xs`, although it may reorder elements.
    //! As usual, such a structure-preserving transformation is said to
    //! be an embedding if it is also injective, i.e. if it is a lossless
    //! transformation.
    template <typename S>
    struct Searchable;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_SEARCHABLE_HPP

/* searchable.hpp
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
*/