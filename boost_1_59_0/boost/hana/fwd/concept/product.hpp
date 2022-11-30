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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_PRODUCT_HPP

/* product.hpp
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
*/