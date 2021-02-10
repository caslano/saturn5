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
SX44Joe+m/ORw6vw+UzD5k1+xj+L/yokMMOHwkZGf2Y+O3mfbCj1eR/ZtBZocpvTp1rl++fIBndgd6Y0xrOLck1YMXuhF2TfoqHmQ9yn/lyZ7wpIYfb/4wCFRlFYurLBnzUAE067H5Rwd298tvmU9K4KckxEnc8zOao8niuhwt9ZA02GV9t9hcNLPjtJXh2jXY/nA2ng76xhvbcLgzA4Anv73HUfRq4Gb20k4l6eyudAXx0+nU1PJjNmdtYCPkffE2YP1tS5Zfv4dXiPxosRsw2o59zCFy9gB59B99oPeUlhnFT41K5k1Ss00A+s08F0OVHcythwPBvs0VD0v19za9D/MmrUx2K0RBKwaNn6BfybxIm1ARwI3eNWGrDcV+tAhxbNlL0JXcqgItsqPrzEokHLubNWaeBYKydIfCu0gIoRsf3hQymnqQrFCMgsmym0SOqb2HuhA+xXYNXXXljLm7Ump4CqJ+NZA8Z82PuxF6rauxMHFu3mIxkj5WKPrmAesSNAACveYzZyMrIozglL9JahISctGoXygnUpLU/pVbDCGKt96dgB2x5RvO7qBbTk4XzcnF+P9QTSlIBoNj0dfzyfj54tSTpkG1N2nh7sn/w80OE7Dxiy1cuxt7ZIu+AhviMOPVg6mcSps2ZM
*/