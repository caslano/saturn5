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
a/H7CX534/cYfjvwe/6/7I90Mx/5MVrU3Boifnxd9shDYD9zG+xnTnGMPJXsZ25JTzyRvnJbC/uZNeeyNY6IGPEjPfKOi4htp+sPWGGaeQZ/8FyZ7Wgx+56ScyWyQVN+MlUTNIjaxDLZUwzzCmNOo/hsxD5yD2PoGdBe/DyrTCm48z6yhbO2M1+8YPPzSN9OK6I1A3nEEe7pLXD3i9WzGPdpDTwTUIO3GI0N7cSjZhLfGwifp9twoBG32vAaWxt2v8xyg4WlyOjgRVQatmgpTPbO1Jh83P6aeVaNA9psaKRnzpV9vVTFjNawA+JGhu0/+LH2v+yPzm+jIJaJ49Po+rijBc3epvQf6lNaRMK3Wnk6ywD3Sbbdj0hIDes9EUine+m6Z4uPmea6zUakE5+ykM/JHwfmP1ixgxwEmef5cGK1JC0N8+Palng1SryGa7zIo5y4eJXyIOPUXuKyQ4wNXNIAFTh8ADZ8vB8Vp19t2TSfSamTNdgsz7pEB3bgQDKfN+tyxvvv9yMXOwp484n+Dde3viw9p3G0O+mApv4B9PkjKQDV11tbB2k3hGjTnMZywIjWXeDjHe2FPjOLDPsFhXdF6gwgaFaQCj17VY7jmGrBpXrxoxm9rqIL1iF9V8yPBQY3xhAxIDZRriULs+GBlEUVXmm0wT1TXktmWxryYplck76XaaQD6C/P82F7NBQcx0c/352kpXYjmITYDGtpe3YZPqv5MyIeY6WkwP7LZQUPAoqBZfig6QLYNb1BfWewVCWbVPuVz20MGhxfz9BGYZ3FWQv6x86TrT/b+KMcc0+sU2OOueDxfEkgKN6U3ERzh81lSBbRZhH8+OXRLygmVCuLH0s78wVzKU/6/mypbJ8JqibmaIVAtCUC2taGVjoMio+Ad3t2YAo+AYcIar68v3aOWeuiGQ+WF+0Jn3u5oANg5ILik7myGaWVDZf2gGZ5MQ8Rz/ZXsOHE1cVgIjNZQPiIF69XzbGswzQaMnUZnIH0/H9q8Y3r6e0Pst1PrPu+nh8UPeHtTFRkrVHe2JzsjS0vfeu3Gat2sL2vGdC7OdJwvgV3J6LumtT2vH8EVymu0DShV+xoThMRJy+RO3HOSp1JLKsfhAeKQ1PPSzHVrtiw5iHmN3yyz56AsbcKis+utYzLl3xDLvtuOYu7LjZKgf9kMYPHioW7tg2xMSr4DRlsNiL4+w6aNvZDZqLzgBH5b3Q24pfGMsuGy3Vl01l/1dpDuukpfNWcyQfrppOk4NJ86qB6rLK8T9GMBIPKC9o3p+Ke0xmSrUx55+1h4BLzc90pEGW+zuLGbC7zYOUtQ3kRVaCrET+uYAshzYjTZU/7aGADZDgWqXfWkKiRCw2KpZhS2pV8n9gUjYpXnMyIuNH7yGa+xsYVSHksZPZ7E9YFPA966pfBtEXiPc9W4fQ86Mxem47/+6wd4wAfk/jEUfP2tNjsp9JlObwV++YifZ4/46ANerD+nc71R+vd5Dyhr7fgt3S0CKMvcQSXYSDOwjermtCgXYwPHz7iUbz4SWFAG0jyrFni4O333BVJyulZQ5JjhsNfM/kmfZ9zFS/QHSYMQQamFDwvxlxFdZlOJxb9wXvFmBEyxaPymvnFN1lS2L0ImLMBsYvNBrh47E10YatwrR2Xc4jZsFV48dKHXrIjePOLjj+nnJax3ZiT5QQR8dlNVjgZeEluylmJh3Tk8Foq7lLmQ0u+nV/Fyv/i2NNUVHzhkG/j5zggyxgrxXjwPHCjzraKLjnDF/1l2oSbc0aqplOulDUFInlAZPssDfGwKAfxMPvr2x3T8FUYDornmOH30fGPbIzb9gvWocDicxYpgiHokys46IeNjH/Mn/Q=
*/