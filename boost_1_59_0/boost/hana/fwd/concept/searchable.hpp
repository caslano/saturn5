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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_SEARCHABLE_HPP

/* searchable.hpp
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
*/