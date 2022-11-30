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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_ORDERABLE_HPP

/* orderable.hpp
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
*/