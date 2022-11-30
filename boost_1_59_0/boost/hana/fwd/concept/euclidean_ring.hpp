/*!
@file
Forward declares `boost::hana::EuclideanRing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_EUCLIDEAN_RING_HPP
#define BOOST_HANA_FWD_CONCEPT_EUCLIDEAN_RING_HPP

#include <boost/hana/config.hpp>


namespace boost { namespace hana {
    //! @ingroup group-concepts
    //! @defgroup group-EuclideanRing Euclidean Ring
    //! The `EuclideanRing` concept represents a commutative `Ring` that
    //! can also be endowed with a division algorithm.
    //!
    //! A Ring defines a binary operation often called _multiplication_ that
    //! can be used to combine two elements of the ring into a new element of
    //! the ring. An [Euclidean ring][1], also called an Euclidean domain, adds
    //! the ability to define a special function that generalizes the Euclidean
    //! division of integers.
    //!
    //! However, an Euclidean ring must also satisfy one more property, which
    //! is that of having no non-zero zero divisors. In a Ring `(R, +, *)`, it
    //! follows quite easily from the axioms that `x * 0 == 0` for any ring
    //! element `x`. However, there is nothing that mandates `0` to be the
    //! only ring element sending other elements to `0`. Hence, in some Rings,
    //! it is possible to have elements `x` and `y` such that `x * y == 0`
    //! while not having `x == 0` nor `y == 0`. We call these elements divisors
    //! of zero, or zero divisors. For example, this situation arises in the
    //! Ring of integers modulo 4 (the set `{0, 1, 2, 3}`) with addition and
    //! multiplication `mod 4` as binary operations. In this case, we have that
    //! @code
    //!     2 * 2 == 4
    //!           == 0 (mod 4)
    //! @endcode
    //! even though `2 != 0 (mod 4)`.
    //!
    //! Following this line of thought, an Euclidean ring requires its only
    //! zero divisor is zero itself. In other words, the multiplication in an
    //! Euclidean won't send two non-zero elements to zero. Also note that
    //! since multiplication in a `Ring` is not necessarily commutative, it
    //! is not always the case that
    //! @code
    //!     x * y == 0  implies  y * x == 0
    //! @endcode
    //! To be rigorous, we should then distinguish between elements that are
    //! zero divisors when multiplied to the right and to the left.
    //! Fortunately, the concept of an Euclidean ring requires the Ring
    //! multiplication to be commutative. Hence,
    //! @code
    //!     x * y == y * x
    //! @endcode
    //! and we do not have to distinguish between left and right zero divisors.
    //!
    //! Typical examples of Euclidean rings include integers and polynomials
    //! over a field. The method names used here refer to the Euclidean ring
    //! of integers under the usual addition, multiplication and division
    //! operations.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `div` and `mod` satisfying the laws below
    //!
    //!
    //! Laws
    //! ----
    //! To simplify the reading, we will use the `+`, `*`, `/` and `%`
    //! operators with infix notation to denote the application of the
    //! corresponding methods in Monoid, Group, Ring and EuclideanRing.
    //! For all objects `a` and `b` of an `EuclideanRing` `R`, the
    //! following laws must be satisfied:
    //! @code
    //!     a * b == b * a // commutativity
    //!     (a / b) * b + a % b == a    if b is non-zero
    //!     zero<R>() % b == zero<R>()  if b is non-zero
    //! @endcode
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! `Monoid`, `Group`, `Ring`
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`
    //!
    //!
    //! Free model for non-boolean integral data types
    //! ----------------------------------------------
    //! A data type `T` is integral if `std::is_integral<T>::%value` is true.
    //! For a non-boolean integral data type `T`, a model of `EuclideanRing`
    //! is automatically defined by using the `Ring` model provided for
    //! arithmetic data types and setting
    //! @code
    //!     div(x, y) = (x / y)
    //!     mod(x, y)  = (x % y)
    //! @endcode
    //!
    //! @note
    //! The rationale for not providing an EuclideanRing model for `bool` is
    //! the same as for not providing Monoid, Group and Ring models.
    //!
    //!
    //! [1]: https://en.wikipedia.org/wiki/Euclidean_domain
    template <typename R>
    struct EuclideanRing;
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_EUCLIDEAN_RING_HPP

/* euclidean_ring.hpp
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
*/