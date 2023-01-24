/*!
@file
Forward declares `boost::hana::transform`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TRANSFORM_HPP
#define BOOST_HANA_FWD_TRANSFORM_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Map a function over a `Functor`.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor, the signature is
    //! \f$
    //!     \mathtt{transform} : F(T) \times (T \to U) \to F(U)
    //! \f$
    //!
    //! @param xs
    //! The structure to map `f` over.
    //!
    //! @param f
    //! A function called as `f(x)` on element(s) `x` of the structure,
    //! and returning a new value to replace `x` in the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/transform.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto transform = [](auto&& xs, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct transform_impl : transform_impl<Xs, when<true>> { };

    struct transform_t {
        template <typename Xs, typename F>
        constexpr auto operator()(Xs&& xs, F&& f) const;
    };

    constexpr transform_t transform{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TRANSFORM_HPP

/* transform.hpp
jaBap85oIOWh+GWt+Ei5rKnQpx7fCJW0oRrhL8VZGjHuxdMOswUPNbrnlOEe8GC6vZZAzEFna3LvHnfFDHyevQ7LE5H98YsiCxNuzKV3JZRrlOQw4ll+eyK7ag+BvJ88Swdq1g4n5dvSrfJQmD0MEnVPMQzIzfZP4t1LdrYCb0I0dyDKSAdTePuBh7cva+31fPa/Rxfz4SPqsQrNSLyhaHl6qdauKbtEpIBgvlo50tTB3J1pKGCuWamLgLUULBfNi67lJI2RYjAcbe9kX+RafkdLcfr0CpDaj9Oh6UOJxS2s3v3EX3X20X56Nqb9jGET672Tf8eYXp80+1dD94gn1/cQ5tWLixfj3btqOZE8BW8an40yCxt8ttnzsPnlh5+esw6wABLmRz0/t488r/zShwkR2YdsMXr2rYeb13Pn23NqvC8laZxf4gdAfx2+1lmRrhQ7X2EoMu18+WDtUT7fyPCLeDYpWh1Rqj/PrhPYpXqdIs+RzekxekTP0qEXL6pSjYmcbFk+o+FidHNKGItRorcCvh6C/6ygDETJU9PwDLfiAA5TFTVEWbgio+YL5BO6yOmsHM9ie5Xh/rBhL01o/kGewFBUA6ppxBFLcDJ+chGnyvjQpV5YUJ2GtTWIdlA22iUeAifPCQluo+kHEZXSuU48v7M1TzE247Gve0UuypOZlWKN9NHQVtisDuzb6uvk2GPnaWTowNaSQokt
*/