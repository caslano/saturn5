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
5qJymV0LxSXNXIbUFxTxxOO7d4bBXWMUCUmX7/ZeOXnez6jSp/2x2b6JEOw8EOc41KJYl9/irqL6F1A9mvilRrHvWbPK2Fr85E26sSQQ9EGE6+70Y0IADPmpPN2yIT0sggFNLOxEkkSCwe3O8nzPePuNVP+Ip5m9wVia9DYoUagObSJNb3vgMU2/79l30+3d5a52LmgVzTGP01pr5qPN94z3pKdJGsTvc/Kx+NDEawJ/kdo4Xs/7wn4nwlAtXyuJS+54LkLo07vX6f0GSgEAish0fniUHx2vblZd+kOt/v7WheZeG7jHakh4yD/+4m7VcZvTl7FfzSvatpRfPap1tFxgSJuBqloeRWYQoWx79qiaWNYLT4/W+fPUSW4Hjzf2/jg5SK1kB/e072iOLiv1Y7vhRvYosYpRJ9cgu1rP9B0XZbkD4PxEuHXUFRno16XTgnrDOZRDIXFt+4dQzDstFn7iYOJhxgIi+3GX5RuZmyKJzIfczzyl29cIW8krs471gOGU6wO7m9QjUao8PJth/gad5gIXxBJQ6LtLtJtf2yrzNraJjAmrSYRKMANY6b3rOa08cghE8cCpFvIzn8IasKfxh7bs0N1NdS8TJVvZ3svr6XMqSN5MQIR0BvEuO0lHM0iYj8U6bOEXYS3GEYrfk/5zJUhaCNQ1LxJv/KIH3lR0RX5fQOBTC24CVAGkD/deHrtB0m/NoK8Xbgsh
*/