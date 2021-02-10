/*!
@file
Forward declares `boost::hana::prefix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PREFIX_HPP
#define BOOST_HANA_FWD_PREFIX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Inserts a value before each element of a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a value `z` called the prefix,
    //! `prefix` returns a new monadic structure. `prefix` satisfies
    //! @code
    //!     prefix(xs, z) == flatten(transform(xs, [](auto x) {
    //!         return concat(lift<M>(z), lift<M>(x));
    //!     }))
    //! @endcode
    //!
    //! For sequences, this simply corresponds to inserting the prefix before
    //! each element of the sequence. For example, given a sequence
    //! `[x1, ..., xn]`, `prefix` will return
    //! @code
    //!     [z, x1, z, x2, ..., z, xn]
    //! @endcode
    //! As explained above, this can be generalized to other MonadPlus models,
    //! with various levels of interest.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathrm{prefix} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure.
    //!
    //! @param pref
    //! A value (the prefix) to insert before each element of a monadic
    //! structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/prefix.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto prefix = [](auto&& xs, auto&& pref) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct prefix_impl : prefix_impl<M, when<true>> { };

    struct prefix_t {
        template <typename Xs, typename Pref>
        constexpr auto operator()(Xs&& xs, Pref&& pref) const;
    };

    constexpr prefix_t prefix{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PREFIX_HPP

/* prefix.hpp
1GIv55h5+oA3ni1PGvs3dNcMf/tkiptA5O2dV0Bteup480V0/OFy6yP8v39P3OJFbyL/V+7RVV5JwfgeLyXOJLEa+LTAptrdSqAuJSHLKSj+Yku1xFUnYi1N3UC8jz/ole7FV/rs3fsj/x5S+ErZAzfLHyBuosokC0glCsBNepHiiDIFaFeLCJ8cXWmBgkqRR5aWZQBXaQYFO4TIEa170mRYUCAcJQAH2DJ/0gx4KYCnsKSgcDc5wbKRJZv0RB4kXG/vitMdtnAiuM6Q4IAdOFw4QHCLWDey0C9DAaDOMLAAth/IV1NLbF1wsebxYYoXGxe0MiViiJu6REFR3+HxYQdGAZsYMgr1ZkPfzblkJTNKOekSfsBLoJ5f9PunNfMeSCxCMx6a1EVdmZk/LpQ39Wu7MoKmpuizDEnXrj1npQWL8jQJPSuRY6maSlW2Yo2a1y+VxiebCzFBg8a5Cr56wXr4Us3N8N1aLixQyabHSWpk6KzukY/7l/TwZmS6ERQERjVBPkzPN2MOxYoPsL8PMhZfGfZLFElJAl7RxYW7rFggYirpOZfon/s1eTTXZipWHKAwUE9IFaEu8iweBDEGaMLlUSTOdpTNrLVceOmC4uLWilkPsNeOrxV3M6FvmoAZDlRWQuEt1q9PTi/M
*/