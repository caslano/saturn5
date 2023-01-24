/*!
@file
Forward declares `boost::hana::then`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_THEN_HPP
#define BOOST_HANA_FWD_THEN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Sequentially compose two monadic actions, discarding any value
    //! produced by the first but not its effects.
    //! @ingroup group-Monad
    //!
    //!
    //! @param before
    //! The first `Monad` in the monadic composition chain. The result of
    //! this monad is ignored, but its effects are combined with that of the
    //! second monad.
    //!
    //! @param xs
    //! The second `Monad` in the monadic composition chain.
    //!
    //!
    //! Example
    //! -------
    //! @include example/then.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto then = [](auto&& before, auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct then_impl : then_impl<M, when<true>> { };

    struct then_t {
        template <typename Before, typename Xs>
        constexpr decltype(auto) operator()(Before&& before, Xs&& xs) const;
    };

    constexpr then_t then{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_THEN_HPP

/* then.hpp
4cfknPWnfBt6KpCu2aR5h8O6/nGVgPEvsiwdHNENpvSgATx9oihb3oZU/krAR1fS6KRcc0kslixM4iTk/Czyf4qivKac97qCkOxOexMnKaViKyVWd71vpNzucKEW/UitcyLHSyK/vLotIO1prZGo3+skL1d4NvfDK9hrnhCWDhWpMe5IUUa3en9CKXtScXj1bEmbHApRCZek9Ot2uDrnwfkNKfyAW7YTBY2VA+WWMoBHtvTiLV3x2QexR4e0ER8bV5ARKUQMuMhSJtL2HKtEzu/CDDo2pE/kpbcnyux3ntHVtODbVwLJKGSuC32/j4zSFSHKSEOSyNxGll/6i+SfYg6FWIcz2AMa+zXAT59wJ0mwbpWLaWGhgU1KfqLgieBTYZCvWZ7Et21zRCy1Wii/gDkTmAfcLlnON/EsQpKsopR5IOLOtiEruEmpbL+Qh2WekWF5LmQxTP0crfbTsNlgm4TKnPnUyXKfjWyMaO2vCTHYS9+bq4zLDoM0Vclh0h2C6E137+D83LdgqQZKd3gntmpg52uH50Pql3xT1vPBWZ57iJIru0Xyly1oH5uwMutx/y1ZRNlN8cP2I+Wc5ZDR5pvzv7zpeHr6JaT1QYw/2zdEWec93y74A5eJRvsAmH3IkkXJ51OL1sAJpks6PUhalsr9X89BF9LRJ48dBojEP1qF8OpXS8Qc5LJDqng855N4FmGeBIys8EiChbHm
*/