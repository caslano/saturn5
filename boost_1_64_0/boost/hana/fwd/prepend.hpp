/*!
@file
Forward declares `boost::hana::prepend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PREPEND_HPP
#define BOOST_HANA_FWD_PREPEND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Prepend an element to a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and an element `x`, `prepend` returns
    //! a new monadic structure which is the result of lifting `x` into the
    //! monadic structure and then combining that (to the left) with `xs`.
    //! In other words,
    //! @code
    //!     prepend(xs, x) == concat(lift<Xs>(x), xs)
    //! @endcode
    //!
    //! For sequences, this has the intuitive behavior of simply prepending
    //! an element to the beginning of the sequence, hence the name.
    //!
    //! > #### Rationale for not calling this `push_front`
    //! > While `push_front` is the de-facto name used in the standard library,
    //! > it also strongly suggests mutation of the underlying sequence, which
    //! > is not the case here. The author also finds that `push_front`
    //! > suggests too strongly the sole interpretation of putting an
    //! > element to the front of a sequence, whereas `prepend` is slightly
    //! > more nuanced and bears its name better for e.g. `hana::optional`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{prepend} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure that will be combined to the right of the element.
    //!
    //! @param x
    //! An element to combine to the left of the monadic structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/prepend.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto prepend = [](auto&& xs, auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct prepend_impl : prepend_impl<M, when<true>> { };

    struct prepend_t {
        template <typename Xs, typename X>
        constexpr auto operator()(Xs&& xs, X&& x) const;
    };

    constexpr prepend_t prepend{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PREPEND_HPP

/* prepend.hpp
EQUj1cLVcVSxPxV4PSFSkbh8lVfEsXl0N5QSEWe2fs+KbBiYzaNls3KY9A9CkzPQ8eYdNFcpjUfk5EtWasQVStdoqDbA6ORbqIE/kQ18w8kriguFseItuEDRfLmamgVuDwQ9knBBa7Z4Oik0/hFZUCXsaXL95ong2bdfrnj23R7xJAK0XFGE8HcjtCymf+ImRpaMZIGdhJ5BwCJZgVGtDXHVKucyMlGzMSFuta26CWSWJgn5ZpY2kkGmEKfL/8Sy66R65a5LpRDwBF1dehgJSg4F9jXej5em+uzAAoAsqBTn91bMaxZISDb6r1OlGHmFisymbvhspuqGQmQqRlf80CtVOXmqQVDPJ51869MNJhE98fRM1RMvULWb6q2BaQTq1waoMbb+6wgvAG0SoIVEpRg3R3nl6VIpNvU2+OPoCYZ5vQFzB8GkLsFMvQxXic+XN2LNFlR/QhjIRRfDkyvFwkulaQIYRpT3nfVrrkO0K2K0UPX06xPkodYb+BR6ljRAqbOxIHBn75IEvhS5LxSbXHw8Md/g+xF7qeY7GWaVDrMMLWiqN/v/Ln7koKznzI8zH+diy+N1WORCeCF69AeqdJHwzlasGujeiePgvncE952Yjh3WBwO4pwjkdVQrV4j9XOQPU/z+dG2FgU63xqHT5+WyQn8ANFnIZ7PiCrkb0QTPDX1Mcnur09VvH6fqWzBlMYTveRLWK4xfNfbLyND1WiXB6oPResqjRustkIAcVmgfDThajdFNC1Wt5uq16o3v4Pi6c05qUsmz/nEukTqZIyJFGO5Bo0g1ty/Uva6RWN54sYHlflvJF4H3Izi9imRyDpodWFxK6TT+NRnFtreYB8sG1rHdKeY/unq5+4vQAKI0/+u30P9zvxBtg/dudsV7fODl9bY8dSHBbvhA+DCXB6/Nrlb3EdPOM+yIQyHHnypPexJXil5lra5QtRY73f+8NN4/Me3e3KF7cux4VoYe5CcdmYKh7ipeZx34kNz3ho5Ezmlan5ONBDDBLt7MpG834Bs1L3SE569XpOh8RFLoeFUUG7BhaidzPep1c6lEbr5IQSXzibxb7O9k3PxZk+/hSK/YzViaUbI1sDg+7ZZY2rUvwZz1OZLgdSQl827MTN/oFmsrFBNSVNW0osCotgvMUNfBijKM95XGyAJXcO843WADjjsxd+5yypbfyt0S2qofg8+aSi6LqTPrpVu0F3b+S36kn4Jq2sT0S6ivk6X2cj30tKw4G4JwvRtF779SH4KDPATYgct18rTb7Z2V0sR2r7HKLivGmMzdzWNzd+TdHTcTDQo3fyP5/3IRE1iJXed5qoe7QwFpz3TFke+ZO4uzE66TppdXXFwCfkhuqneB95PSvqIS3XAQFuSfbUGesGViFL8zMnUn+enbLib44hVWZS3cA6wbzt7C1Ppzt+7/YSz3CpowSA5q/TxwkNRx0u0PG1lg+QERQV1aWYBNa47ajZ2jfabAspNcBfl3F+mQp8ZD1u5AOkgKhqlr3lbi7YDXybMZ/7zil0OV69cK9OxIRGvHjXpfo0NHX10C+JBEY/Rd2n30LUnYhlPW3Lmw8Dowrsy/SIMGW424r5dHZn0KcP9D+A6vZ6NX9JgrV54bymMrjwW81ftz580iFLBij8p1aXUn1Xgf8CE+PHlqYnh9i+/DW3y/psX3ji2+T3IlhotapM9tef41JSFc+/OUPvFyuJZtiF7wJBKIHEfMvyYi6NaKG2P5Hl59UDd3t+lfk+Vd6LH+ZOWfHcZ4SAvA4rtQc20g8xPvjGAS2NY8VvZAE8MnWw41yvN1Z8A+XFm8VFFRZeTRWoNKEI5moRKyOV19vfSKeGRFCpvaJiqqPdQ=
*/