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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_EUCLIDEAN_RING_HPP

/* euclidean_ring.hpp
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
*/