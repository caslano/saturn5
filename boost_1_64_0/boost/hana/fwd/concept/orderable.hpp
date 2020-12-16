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
YY+aJBnAE9/6Kg6T68xWlJuVXFbyq5TLU3IuQ4IjOFkdHrCF8feIKxIVZhfsIcw2GZi9xpjBgzHjt8IMYQqzLQZm8FOYkXPZpsPAbNmD8rTFLF+gFXZ8WoleGPlKDncxSWM3KKIWHBLAztuEoxUhOtufdgnRij4HVYR0/85C8jn9HeXT3u9Cj8ISslL3oVNGFivPfzi2xp25JWyP8cj+L16RW2axXq8gLLvfKI+TyzNuZ73y1O2KK8/SlPrlmXCgfnmK3q5fnkfWm8rT22KU5/7DLw8lEd9EmVbFxrWCQKcpTHd14EBwa84Mar8e8d2Hh2TqfP78+iPTTUeQAMonvuH0KR4CjDJhOHKEbwclo4h/5E+nBz2Ao9ngmpsUy3wvd4SUw5Dt6OWxiZtfwdTEpXm2TsnezOFXI1xaSLFVD1qniL8KT1E/cR7iMcaztzUlwltG1JM0BP9I6kIQAGSLkS/FlsJTA6k+8dc6YyINZOMIwyb9E/1lgk+MMjr8EOo+VavqjP6ypUF/qWWftNWx/vI0+yxcZeovn3xbp/pLxeH3F54f/iRBxCYHCUHJ4/vXk89n1/serL6N/Sg3DlmvqeXVxB1yNTFf1F/bLNvNmdLGifQJHS82gaoGcmXSkEp6ESd1UVLxGJHdvP48KyOXfBl1lop6QiwXs1EGZfIFO0DDOYWfpCEq0TdfHql431Te0aq8f9DP/31Zv7zPfNuwvB+/h/JerpdXJR2LpKq8L71H5c1W5Z2ol1dFPfPLQ5V3MqdgGb5KdOCL36C8N6ryrpdAH/mifnnXfVO/vOni63frooyLXmSVOvBFrMgb36UiD0ZSqUFjxJ6lYvf/wlzq9KZ+XAtph19I4zHvZ/Q/xH5K9iHCBzcaXv972U452ZrTL9f9zPA0S4YVXg3205SoYsjXTJRTaM2VBMLRxW+5guT774J3gobSmbyESJEcmZ5k5BZuruaqS9mX7FbLp05hjzgdr1QirHin8CmGlPSRfg/nVbWTM2lmt0KdR98MSuDVUTdu//x9DZ+BTKciZKLL9fDfPxbH2p/GH7Fzj7Gq2Ye4kUSEp7DJ32qmlTY6X9KnkOxS0s3yANOb7uSbuFhrfRGwTeXTSmT5ClaPH7cbZnhCw6D7X4uuRrdUf29M9I4yOmwJbXwrG+uKJIlkSJ5hwI1vv5JHnrtX5fHGgg8QR0juxEt21Npi0LOj4yeGBBTccX8CR/GDp3qF7QOlDTQatsjxOgr7SeKZ7xlKZJxdzxlGklGguf2gpaOsdRWN1Rtv6TvUItze8qK5wCQuiE/c+1duhZoPArPgw6qoa+QoqmNOLLXmxU3/ukfaT9oByuBjA4uZdf3OwUVuug0i0RHtqpcoXF0nDZuR7ZfV+h3ZukklO8xN/ZQk9fshvdOPBQy1S5vOz7+nqrOVVmyvKe5XnBKq85INUpuo+UGfrPnydNp4J/I0O7muFQ0yK63zpqvkoQ5eSrJGJRmEDvJuzSn9iu3BE3xihJFLB+SsGm1/rWy0YvvoqqHcanpxftjE0UUxluWQXv9Wt3fq0H2Cm99OY8VCtUB8nn8LD8Ns7ngpesxJwKMZxSm1n9ebuuw5FUSICagqXldZPD4cpPevgX+pa8bIEtEqtsF5vU0eQI721qw8OVU2nX94IDTSeUNR6m2ZBv6XhjrqF5GkFvCKDI96mrOQSnTrq3ryGSdL++Ue8t3+Wl1UH44ca/Kr+lC9YWe/EnuoPS0uT9zNKWmUN2eWsHoKRq35e/32+O9n630/siP++5hX47/rfoj/PpgYvz/X7bX48Hur47/vXxv/fWW97/N+iv++blv894u1pm9lj6k7Nqs7Uxcrv5jML47yKHM=
*/