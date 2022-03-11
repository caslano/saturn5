/*!
@file
Forward declares `boost::hana::Product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_PRODUCT_HPP
#define BOOST_HANA_FWD_CONCEPT_PRODUCT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Product Product
    //! Represents types that are generic containers of two elements.
    //!
    //! This concept basically represents types that are like `std::pair`.
    //! The motivation for making such a precise concept is similar to the
    //! motivation behind the `Sequence` concept; there are many different
    //! implementations of `std::pair` in different libraries, and we would
    //! like to manipulate any of them generically.
    //!
    //! Since a `Product` is basically a pair, it is unsurprising that the
    //! operations provided by this concept are getting the first and second
    //! element of a pair, creating a pair from two elements and other
    //! simmilar operations.
    //!
    //! @note
    //! Mathematically, this concept represents types that are category
    //! theoretical [products][1]. This is also where the name comes
    //! from.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `first`, `second` and `make`
    //!
    //! `first` and `second` must obviously return the first and the second
    //! element of the pair, respectively. `make` must take two arguments `x`
    //! and `y` representing the first and the second element of the pair,
    //! and return a pair `p` such that `first(p) == x` and `second(p) == y`.
    //! @include example/product/make.cpp
    //!
    //!
    //! Laws
    //! ----
    //! For a model `P` of `Product`, the following laws must be satisfied.
    //! For every data types `X` and `Y`, there must be a unique function
    //! @f$ \mathtt{make} : X \times Y \to P @f$ such that for every `x`, `y`,
    //! @code
    //!     x == first(make<P>(x, y))
    //!     y == second(make<P>(x, y))
    //! @endcode
    //!
    //! @note
    //! This law is less general than the universal property typically used to
    //! define category theoretical products, but it is vastly enough for what
    //! we need.
    //!
    //! This is basically saying that a `Product` must be the most general
    //! object able to contain a pair of objects `(P1, P2)`, but nothing
    //! more. Since the categorical product is defined by a universal
    //! property, all the models of this concept are isomorphic, and
    //! the isomorphism is unique. In other words, there is one and only
    //! one way to convert one `Product` to another.
    //!
    //! Another property that must be satisfied by `first` and `second` is
    //! that of @ref move-independence, which ensures that we can optimally
    //! decompose a `Product` into its two members without making redundant
    //! copies.
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! 1. `Comparable` (free model)\n
    //! Two products `x` and `y` are equal iff they are equal element-wise,
    //! by comparing the first element before the second element.
    //! @include example/product/comparable.cpp
    //!
    //! 2. `Orderable` (free model)\n
    //! Products are ordered using a lexicographical ordering as-if they
    //! were 2-element tuples.
    //!
    //! 3. `Foldable` (free model)\n
    //! Folding a `Product` `p` is equivalent to folding a list containing
    //! `first(p)` and `second(p)`, in that order.
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::pair`
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Product_(category_theory)
    template <typename P>
    struct Product;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_PRODUCT_HPP

/* product.hpp
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
*/