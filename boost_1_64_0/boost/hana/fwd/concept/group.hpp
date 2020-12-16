/*!
@file
Forward declares `boost::hana::Group`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_GROUP_HPP
#define BOOST_HANA_FWD_CONCEPT_GROUP_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Group Group
    //! The `Group` concept represents `Monoid`s where all objects have
    //! an inverse w.r.t. the `Monoid`'s binary operation.
    //!
    //! A [Group][1] is an algebraic structure built on top of a `Monoid`
    //! which adds the ability to invert the action of the `Monoid`'s binary
    //! operation on any element of the set. Specifically, a `Group` is a
    //! `Monoid` `(S, +)` such that every element `s` in `S` has an inverse
    //! (say `s'`) which is such that
    //! @code
    //!     s + s' == s' + s == identity of the Monoid
    //! @endcode
    //!
    //! There are many examples of `Group`s, one of which would be the
    //! additive `Monoid` on integers, where the inverse of any integer
    //! `n` is the integer `-n`. The method names used here refer to
    //! exactly this model.
    //!
    //!
    //! Minimal complete definitions
    //! ----------------------------
    //! 1. `minus`\n
    //! When `minus` is specified, the `negate` method is defaulted by setting
    //! @code
    //!     negate(x) = minus(zero<G>(), x)
    //! @endcode
    //!
    //! 2. `negate`\n
    //! When `negate` is specified, the `minus` method is defaulted by setting
    //! @code
    //!     minus(x, y) = plus(x, negate(y))
    //! @endcode
    //!
    //!
    //! Laws
    //! ----
    //! For all objects `x` of a `Group` `G`, the following laws must be
    //! satisfied:
    //! @code
    //!     plus(x, negate(x)) == zero<G>() // right inverse
    //!     plus(negate(x), x) == zero<G>() // left inverse
    //! @endcode
    //!
    //!
    //! Refined concept
    //! ---------------
    //! `Monoid`
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`
    //!
    //!
    //! Free model for non-boolean arithmetic data types
    //! ------------------------------------------------
    //! A data type `T` is arithmetic if `std::is_arithmetic<T>::%value` is
    //! true. For a non-boolean arithmetic data type `T`, a model of `Group`
    //! is automatically defined by setting
    //! @code
    //!     minus(x, y) = (x - y)
    //!     negate(x) = -x
    //! @endcode
    //!
    //! @note
    //! The rationale for not providing a Group model for `bool` is the same
    //! as for not providing a `Monoid` model.
    //!
    //!
    //! Structure-preserving functions
    //! ------------------------------
    //! Let `A` and `B` be two `Group`s. A function `f : A -> B` is said to
    //! be a [Group morphism][2] if it preserves the group structure between
    //! `A` and `B`. Rigorously, for all objects `x, y` of data type `A`,
    //! @code
    //!     f(plus(x, y)) == plus(f(x), f(y))
    //! @endcode
    //! Because of the `Group` structure, it is easy to prove that the
    //! following will then also be satisfied:
    //! @code
    //!     f(negate(x)) == negate(f(x))
    //!     f(zero<A>()) == zero<B>()
    //! @endcode
    //! Functions with these properties interact nicely with `Group`s, which
    //! is why they are given such a special treatment.
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Group_(mathematics)
    //! [2]: http://en.wikipedia.org/wiki/Group_homomorphism
    template <typename G>
    struct Group;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_GROUP_HPP

/* group.hpp
R0lsc0UcOkaW3cxk3n+AsqMig8t7ZJ29vDxd3gOyvLeM/ZV31Dx7fa+YIMtceP73qe/mq/gYaEHqfHZlzgaahytz6HwBxqdC5nU517GVjLtzaIZGzE05t+NJDGa1MoFurudMOBp8BUN7xW8JaANAbMIzCh2TY35DBKek0TNxD1mpisYCQXHe1o5pUXzl4txnUalWv+hYsKWJzlPBRxqb1vbAFawBcUWjln6IlWGHvL3PxQ4BaSd6v7lu7dq1uz8yn8JdKPPZre85hzw7ZGvNkPoK51MorBNtsftRiXu34JypokNQFZqhC11qkl+Kh392eg/22pDxesYTJU9u3olFDSb6PQ+mV4EiXkmoXLXAoohhkMvyki/nJ2IOLH8UuamEfKVJanoDHKWhTagFaWajXR6t0e3Sjk75AX9sjyYi/rhIqQJXSvOcQW1uZ//yi3cv0Pvt7IJtWnBB5+/J2krR2ySdp2BddaV4EemwKOXTMlcdxIFOL9HxeF5S3aag64FKHoDZd5E+faWBEZZDtONiyxCP9Nvhe5c3x4/JUb7rTLk1OU2srZS6c/EIFqnVoPLorsUnaKnaaAKXV7e0siBJL8CkYBu9RPQmRG3a+hD2U9dZ2HcH9hJz3GLDO9Po34ynU+GCdZZTtB/swqhtfxAeL9UxHqpHxGrM3YjqF3FFoTbA+N35L2+Zf9aFtvx7Vx44f5QABFsCGAAAfA3AgnKtXu/jJyWWVabF/eJYpKkrr0RIcXJhZVDML9J2bnubFUE8BgfFAycq3T181/Smgv681j72fqj9LbYHVcnWgn9jDZnzjYS6/3mG5qOpM1uq8jwLofxBJY92+M/a4K+U8M+ww/cqCTRDn9se6C3hv2aDv1rCz2gJ3/JJdVk590XDAeFtt8FbJeHdf/r+4b0z7YDwggyv2QbvJVV/C55UgxpzHo8AMvW9+839nofkgoVqaOsPyBwzuW70ZOtS0FAsE/ttL0mFAgU7Craxu4w7RxIlMD8nPVpMTFKJPOJiSyUyKoZMpNVz4wgt1+9CXdRYNtnhS/M2L42KoRx/WZv4/j0RXw2SxPHnt4m/vgfiR0XFH0+m+FPaxD9L8f2jYi3HH23FD1DxVyI+Yi3OQXEDHRmL5mxoWRRu7+mVjrGe5UZmjQUWvzcX0W3lo0ZLgcuT7bPI9v3+lP7bOUTvybUbro9Op9tD2IzMp0bFtiZGhBCT+3QSwOH85FQTvDE6o7foV0z7CBJvQ79sGiWjJBGysXNHuSYeY83xkyPJmpxoVDvoOobGIitciaoyy7baDLjkiy1Fa/CpwdOyKT6XHD1lEIfZ0v7d7vtkfZOx/dT3TFXfGaq+YRLfo549xLAiWz2nU3QEVexwkdbxOaFNFUekqnje8S3QZu1/riXPeeMZdf/PVtHS4//+im6egPna0FofyoP6kh5gQOsaWh4vkzAq2Y/Ebwa1++zYWcBlabXmLkkThixehyOeB48xP0n8yZH4aF+8b2JferxbYp+T/suMZ7HPyuazEFDTedUOfB9J3ySLGJRIOvCdT98V1h3S4LnSVcsMhk8CXPg5FR2maw1Yu3jYTWWlZ2wpK9kTP9Q4zsJ0DmP6qlRXqp6hccXldFTJIxLD5U7f3IPO2I7bek5IPLBBHIb/2alOx2HWvT7PyrfkkV0eqppH5HF0lfjDWdZO+HFl+QlI8iZtUoH2hdnPCLZCaKxEqIl4UmBe0zNKvEkh5eO8vbHBaz5N3aX3jg4FM7YGxbm6rHhElRMSO47VhWSx6Z/mn6Cpa3ywQCDVmUoE2vU0ilgeDbUoIj6FUVDuc7KlDcObCpWGy/ZSzdi4pqED/u1UneT5+cyzpD5Sjh6vUE0=
*/