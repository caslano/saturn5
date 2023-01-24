/*!
@file
Forward declares `boost::hana::replicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLICATE_HPP
#define BOOST_HANA_FWD_REPLICATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Create a monadic structure by combining a lifted value with itself
    //! `n` times.
    //! @ingroup group-MonadPlus
    //!
    //! Given a value `x`, a non-negative `IntegralConstant` `n` and the tag
    //! of a monadic structure `M`, `replicate` creates a new monadic structure
    //! which is the result of combining `x` with itself `n` times inside the
    //! monadic structure. In other words, `replicate` simply `lift`s `x` into
    //! the monadic structure, and then combines that with itself `n` times:
    //! @code
    //!     replicate<M>(x, n) == cycle(lift<M>(x), n)
    //! @endcode
    //!
    //! If `n` is zero, then the identity of the `concat` operation is returned.
    //! In the case of sequences, this corresponds to creating a new sequence
    //! holding `n` copies of `x`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an `IntegralConstant` `C` and MonadPlus `M`, the signature is
    //! @f$ \mathtt{replicate}_M : T \times C \to M(T) @f$.
    //!
    //! @tparam M
    //! The tag of the returned monadic structure. It must be a
    //! model of the MonadPlus concept.
    //!
    //! @param x
    //! The value to lift into a monadic structure and then combine with
    //! itself.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of times to
    //! combine `lift<M>(x)` with itself. If `n == 0`, `replicate` returns
    //! `empty<M>()`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replicate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto replicate = [](auto&& x, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct replicate_impl : replicate_impl<M, when<true>> { };

    template <typename M>
    struct replicate_t {
        template <typename X, typename N>
        constexpr auto operator()(X&& x, N const& n) const;
    };

    template <typename M>
    constexpr replicate_t<M> replicate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REPLICATE_HPP

/* replicate.hpp
Es+X+S/6r7Pfz5b+IiuYour4n60aqqWa+E/Hlfn1IpmzQnnHbpSPVP2Hr2hSr5ucZxHLN9vU2m06aMfjbVObJtp8ma3yhOXU6g9fnz5Bi0bPIPXtQVr4H0iA/xwMlhp1vp7fzoMs5WPT1vAuknR3Q1t/X/+WLC4j/FfIcWlaH6ia7nYBSwj0ACSNy+UIfHuuvE0W4VVGBWM/LZXZ71x99js7FL+OjgeePftdwPCLB773VUBidEKiGWYX5TR0rKJDrfrf1/Nkfr5aNHoNA/yHTkL0zKyvFerNMQxCjCEYhBhFJ2L68yBPfOWtX17xcRtO3WBxkxTF7gZjzhU6b7pqME3QIm/LNIa31fH39cK/Akw1Dv6U/ilX/vSnP1Wwm+aBzecsWIVXrFTentedvAA2UkFC0z6MhH8WNBRtOQez4p9rXpTwp0DOP7IcNIPeuQNFEQWN9rUjt88huEoaPejDe+iipuRkPvKg2W6fdjpo5MB9sqh6GCWDg3G/bt+6I9yve7CPJ/RBs13n+Jgx3T5rYwhB0pWNasrL00pjeH11VbOv7m3Ou7X6BECztZ6qP+WMfRaV+3hbs/Weyhcr2W8f+2qO01P1u59ZkLOb7yXQVh97ak4fwr57kftBEn4vRtDHfppr99T/EZo0CUVtuxd0o6/3vyasXPh4yMQIbLdPeVY015SGV7Kmt+31VpQE36goie30Ow6S2u16a0o7
*/