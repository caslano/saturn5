/*!
@file
Forward declares `boost::hana::Orderable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_ORDERABLE_HPP
#define BOOST_HANA_FWD_CONCEPT_ORDERABLE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Orderable Orderable
    //! The `Orderable` concept represents totally ordered data types.
    //!
    //! Intuitively, `Orderable` objects must define a binary predicate named
    //! `less` returning whether the first argument is to be considered less
    //! than the second argument. The word "total" means that _distinct_
    //! objects must always be ordered; if `a` and `b` are not equal, then
    //! exactly one of `less(a, b)` and `less(b, a)` must be true. This is
    //! a contrast with weaker kinds of orders that would allow some objects
    //! to be incomparable (neither less than nor greater than). Also note
    //! that a non-strict total order may always be obtained from a strict
    //! total order (and vice-versa) by setting
    //! @code
    //!     a <= b  =  !(b < a)
    //!     a <  b  =  !(b <= a)
    //! @endcode
    //! The non-strict version is used in the description of the laws because
    //! it makes them easier to parse for humans, but they could be formulated
    //! equivalently using the strict order.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `less`
    //!
    //! When `less` is defined, the other methods are defined from it using
    //! the same definition as mandated in the laws below.
    //!
    //!
    //! Laws
    //! ----
    //! Rigorously speaking, a [total order][1] `<=` on a set `S` is a binary
    //! predicate @f$ <= \;: S \times S \to bool @f$ such that for all
    //! `a`, `b`, `c` in `S`,
    //! @code
    //!     if  a <= b  and  b <= a  then  a == b // Antisymmetry
    //!     if  a <= b  and  b <= c  then  a <= c // Transitivity
    //!     either  a <= b  or  b <= a            // Totality
    //! @endcode
    //! Additionally, the `less`, `greater` and `greater_equal` methods should
    //! have the following intuitive meanings:
    //! @code
    //!     a <  b  if and only if  !(b <= a)
    //!     a >  b  if and only if    b < a
    //!     a >= b  if and only if  !(a < b)
    //! @endcode
    //!
    //!
    //! Refined concept
    //! ---------------
    //! 1. `Comparable` (free model)\n
    //! Since `Orderable` requires `less_equal` to be a total order, a model
    //! of `Comparable` may always be obtained by setting
    //! @code
    //!     equal(x, y) = less_equal(x, y) && less_equal(y, x)
    //! @endcode
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`, `hana::optional`, `hana::pair`,
    //! `hana::string`, `hana::tuple`
    //!
    //!
    //! Free model for `LessThanComparable` data types
    //! ----------------------------------------------
    //! Two data types `T` and `U` that model the cross-type version of the
    //! usual [LessThanComparable][2] C++ concept are automatically a model
    //! of `Orderable` by setting
    //! @code
    //!     less(x, y) = (x < y)
    //! @endcode
    //! The cross-type version of the LessThanComparable concept is analogous
    //! to the cross-type version of the EqualityComparable concept presented
    //! in [N3351][3], which is compatible with the usual single type
    //! definition.
    //! However, note that the LessThanComparable concept only requires `<`
    //! to be a [strict weak ordering][4], which is a weaker requirement
    //! than being a total order. Hence, if `less` is used with objects
    //! of a LessThanComparable data type that do not define a total order,
    //! some algorithms may have an unexpected behavior. It is the author's
    //! opinion that defining `operator<` as a non-total order is a bad idea,
    //! but this is debatable and so the design choice of providing a model
    //! for LessThanComparable data types is open to debate. Waiting for
    //! some user input.
    //!
    //!
    //! Order-preserving functions
    //! --------------------------
    //! Let `A` and `B` be two `Orderable` data types. A function
    //! @f$ f : A \to B@f$ is said to be order-preserving (also called
    //! monotone) if it preserves the structure of the `Orderable` concept,
    //! which can be rigorously stated as follows. For all objects `x`, `y`
    //! of data type `A`,
    //! @code
    //!     if  less(x, y)  then  less(f(x), f(y))
    //! @endcode
    //! Another important property is that of being order-reflecting, which
    //! can be stated as
    //! @code
    //!     if  less(f(x), f(y))  then  less(x, y)
    //! @endcode
    //! We say that a function is an order-embedding if it is both
    //! order-preserving and order-reflecting, i.e. if
    //! @code
    //!     less(x, y)  if and only if  less(f(x), f(y))
    //! @endcode
    //!
    //!
    //! Cross-type version of the methods
    //! ---------------------------------
    //! The comparison methods (`less`, `less_equal`, `greater` and
    //! `greater_equal`) are "overloaded" to handle distinct data types
    //! with certain properties. Specifically, they are defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Orderable` when taken individually
    //! 3. @f$\mathrm{to<C>} : A \to C@f$ and @f$\mathrm{to<C>} : B \to C@f$
    //!    are both order-embeddings as determined by the `is_embedding`
    //!    metafunction.
    //!
    //! The method definitions for data types satisfying the above
    //! properties are
    //! @code
    //!     less(x, y)          = less(to<C>(x), to<C>(y))
    //!     less_equal(x, y)    = less_equal(to<C>(x), to<C>(y))
    //!     greater_equal(x, y) = greater_equal(to<C>(x), to<C>(y))
    //!     greater(x, y)       = greater(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Partial application of the methods
    //! ----------------------------------
    //! The `less`, `greater`, `less_equal` and `greater_equal` methods can
    //! be called in two different ways. First, they can be called like
    //! normal functions:
    //! @code
    //!     less(x, y)
    //!     greater(x, y)
    //!
    //!     less_equal(x, y)
    //!     greater_equal(x, y)
    //! @endcode
    //!
    //! However, they may also be partially applied to an argument as follows:
    //! @code
    //!     less.than(x)(y)    == less(y, x)
    //!     greater.than(x)(y) == greater(y, x)
    //!
    //!     less_equal.than(x)(y)    == less_equal(y, x)
    //!     greater_equal.than(x)(y) == greater_equal(y, x)
    //! @endcode
    //!
    //! Take good note that the order of the arguments is reversed, so
    //! for example `less.than(x)(y)` is equivalent to `less(y, x)`, not
    //! `less(x, y)`. This is because those variants are meant to be used
    //! with higher order algorithms, where the chosen application order
    //! makes sense.
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Total_order
    //! [2]: http://en.cppreference.com/w/cpp/named_req/LessThanComparable
    //! [3]: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3351.pdf
    //! [4]: http://en.wikipedia.org/wiki/Strict_weak_ordering
    template <typename Ord>
    struct Orderable;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_ORDERABLE_HPP

/* orderable.hpp
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
*/