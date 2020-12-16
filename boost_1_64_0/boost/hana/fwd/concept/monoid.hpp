/*!
@file
Forward declares `boost::hana::Monoid`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_MONOID_HPP
#define BOOST_HANA_FWD_CONCEPT_MONOID_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Monoid Monoid
    //! The `Monoid` concept represents data types with an associative
    //! binary operation that has an identity.
    //!
    //! Specifically, a [Monoid][1] is a basic algebraic structure typically
    //! used in mathematics to construct more complex algebraic structures
    //! like `Group`s, `Ring`s and so on. They are useful in several contexts,
    //! notably to define the properties of numbers in a granular way. At its
    //! core, a `Monoid` is a set `S` of objects along with a binary operation
    //! (let's say `+`) that is associative and that has an identity in `S`.
    //! There are many examples of `Monoid`s:
    //! - strings with concatenation and the empty string as the identity
    //! - integers with addition and `0` as the identity
    //! - integers with multiplication and `1` as the identity
    //! - many others...
    //!
    //! As you can see with the integers, there are some sets that can be
    //! viewed as a monoid in more than one way, depending on the choice
    //! of the binary operation and identity. The method names used here
    //! refer to the monoid of integers under addition; `plus` is the binary
    //! operation and `zero` is the identity element of that operation.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `plus` and `zero` satisfying the laws
    //!
    //!
    //! Laws
    //! ----
    //! For all objects `x`, `y` and `z` of a `Monoid` `M`, the following
    //! laws must be satisfied:
    //! @code
    //!     plus(zero<M>(), x) == x                    // left zero
    //!     plus(x, zero<M>()) == x                    // right zero
    //!     plus(x, plus(y, z)) == plus(plus(x, y), z) // associativity
    //! @endcode
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
    //! true. For a non-boolean arithmetic data type `T`, a model of `Monoid`
    //! is automatically defined by setting
    //! @code
    //!     plus(x, y) = (x + y)
    //!     zero<T>() = static_cast<T>(0)
    //! @endcode
    //!
    //! > #### Rationale for not making `bool` a `Monoid` by default
    //! > First, it makes no sense whatsoever to define an additive `Monoid`
    //! > over the `bool` type. Also, it could make sense to define a `Monoid`
    //! > with logical conjunction or disjunction. However, C++ allows `bool`s
    //! > to be added, and the method names of this concept really suggest
    //! > addition. In line with the principle of least surprise, no model
    //! > is provided by default.
    //!
    //!
    //! Structure-preserving functions
    //! ------------------------------
    //! Let `A` and `B` be two `Monoid`s. A function `f : A -> B` is said
    //! to be a [Monoid morphism][2] if it preserves the monoidal structure
    //! between `A` and `B`. Rigorously, for all objects `x, y` of data
    //! type `A`,
    //! @code
    //!     f(plus(x, y)) == plus(f(x), f(y))
    //!     f(zero<A>()) == zero<B>()
    //! @endcode
    //! Functions with these properties interact nicely with `Monoid`s, which
    //! is why they are given such a special treatment.
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Monoid
    //! [2]: http://en.wikipedia.org/wiki/Monoid#Monoid_homomorphisms
    template <typename M>
    struct Monoid;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_MONOID_HPP

/* monoid.hpp
K1/95StbvvLla9ihFTwa7w/BJNnXUYs2S4i21cSKdnr/MHXthk+sx7yTLO9DTsHwssoRZG2YpvqmnfHrwfPa1Vv/Oeqt/0AXG5+fwXV09W/nCwl5GAeuwRh+AJJO87bKhbw5OUTvRU9ZqblngLHUmSf/Z0b6azn9FUhvZp5e/jzGTPh3GJEnc+SzVGYtn7dpfWbH/rbb380awzwAYGKvDmy0mWU60KbeHIOUJxopczjlk7GUPsU2vU6qeWctRQJekAav1PcrtLYtVM8jg17a9PGo5E01J2NVbAt2FdPayUvOsJqpq2mHbZV7bVyT2s81ieAz9KwjEKtLncC5fyHBJikiapWHp//oKGMx3FIUMtrh4tuoC776CD78BMwxZI+4elsdT6+su0FKjSlf0AA9p05JVq5UCo13c8BxRsAFUD3w21kelmx4noXYrlpD/bH2JxXgNlQfcTrb8E0qwhyN2hYJmyFl9RrtEeT2OA4LTK/fXcvLR8G1AS3X31YP90gfU9d6wF6/ax2HEwVG1/JXylnR87PeuwydomswT5r7lqnty1nwDkFcSweECZ/2jeBznwmf1yQ+FXX18fnwAOFzZ2P4HNh1mPgo/Sq3/1kTZZmGfPORbz3lqvGUcfH4BrnejFwLxRebeKbkiylbkN8GU35B5Lftpwb51e6n/MY0yO9Yzm96S/JjAu/jC0+QZ60pz5uQ5wSV5zi1pzQLWbLM49OEGNH8KUY0OVlPPVmdKv/OFtc6zRN8GdvYGDlkkTXAbv1RtbQ+q4N3C1d4RuJonXgNNM8Q6TUHX93HloDZKNcWycHNbPZIjl3LTYnkpGi5zkiOU8tNjeSkarmuSI5Ly3VHctxablokJ03LTY/kpGu5PSI5PbTc3pGc3lpun0hOHy23bySnr5bbP5LTX8vNjuRka7n5kZx8LXdYJGdYM9io+SvzDV4xZ6mqn4HCVv9gVH2hNoAGF5aPwcWYTGEuXnMsaHeuU6ebI63nekA3QTTDFfF0U5s9nnWblq5Dj3odSTsvo1FBRi365Y8P2SNTxkfyxtT4Ar6a9MBgmfvVnPukH2IzWb+jKVGwc+ACvY05xvmmGH6nJ9kZYQoQGT5GuKXOKvqjlB1HeCxW5Y23tJhNavJZRpn4tFraI9B711doep/wWlR/dDXoj/dIpT0l/8B2FIMBjgQotLoZnKivoOJcgcmqcW4AwGHfGyuDDgRJWw/9FwfJi7PW4Rxw9nhA/SkQkkmu4SSdjCRA/TOfdj2mUihJ5YxBC2jXj5EfaI7x47LeDdnhXE6AZd3T95jl5ApYRopWb/G4PmRXb/QhXVTzT/wZbD/Zbu0d7fDgUqoTVxxMkJptnVFADHmfuB/U3Gyw4ayPEeQTiz83vFdRzW/x0kbN4I/YV83dYtfGuqgHwvODhneEvPvUsPdKm9q1mS46J/1MXhd/yjFp7hZ3fsCxigwvj3i4mr0ur1NeA/xTOOPuu5RPhr/3xeTzXoXy6eSfwz5PchyzqvURrKUbPrz/ZZf7X8GOSj/M5iN7puKLDUwFsWUYSCK2c+sGfRtJvFoXbRpeWxO8ayU8gINY/Q4JjxBvmrLqR5WN5n6pXbPNrfQhQm05NqmHIAulJdMKSus3YcM4kqS2qfZcDq87E0xeVUk0ypvRV6+guf1FkPLoWfcTWWhFHpRGbEykXc8H2fN+5flcorTz0OpB3adBv28J/qR9mg1U37a1HNUYvEIcvGLuLdrhca40m0esAtXxr6k6Bp3pLz8barOhRJBDXZ9V9EiSFr8/l/OWtqEFy4LwgJd5PT5d0PVLdHzfI5a/D/hHr5EUK2IrfwSunAh7CLeVY3XziFkUq4MR63aKlRs=
*/