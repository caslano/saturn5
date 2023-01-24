/*!
@file
Forward declares `boost::hana::empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EMPTY_HPP
#define BOOST_HANA_FWD_EMPTY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of the monadic combination `concat`.
    //! @ingroup group-MonadPlus
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{empty}_M : \emptyset \to M(T) @f$.
    //!
    //! @tparam M
    //! The tag of the monadic structure to return. This must be
    //! a model of the MonadPlus concept.
    //!
    //!
    //! Example
    //! -------
    //! @include example/empty.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto empty = []() {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct empty_impl : empty_impl<M, when<true>> { };

    template <typename M>
    struct empty_t {
        constexpr auto operator()() const;
    };

    template <typename M>
    constexpr empty_t<M> empty{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EMPTY_HPP

/* empty.hpp
DfNMuSDfJrmIxULmCh5h+TrvrOZ76EfJJol8GX2uiIa1QbnQa17U6onXpd+yft08i3k/Y2M/ugvBOrpky3vWypZPtvtmJz5c++DyPjVpUtLch1eE12wIgsEYPSVQwPqgRfetHnOdoevSCjqOK3R5z5p7qPsgdM9fXM9s6rTfbZQ97H2bbnsXT/Rcjq6TlwQLNpnC3WPC58V09GfNq8TAnvBJS6/nP4zyM1M9e6eJ37plLRc2tky7sWUZvM9CmaetJyfE87W4G/rG9y2dxePq4pHPlnhUgeXT0KE23NPG8/WbG4Gg5nP6CEfIhJpBh9g7bjoqhOb8MFX8eg7/+C57HjpbSN8gF/h9qlXT/YW3eYG/tr9Htrr3ZJkiJnFFxxAb/TJKEH++AAF97b/j5WF1BZfb51a2/ko/c1cL2Qcs2sLU98lf8z+pZ8se+z0JdIi+n8J+i4KV2nKdfa0tdvD1cfLtbeTbextWzwtaERfi+VK+vXhwhetv5Gf+Nq5mnMCYkm+vqomnd6m2F3u+HFzhDka1e8+YmiWQ0MONRxfRV3xivkgrqO8xP3h1TERtt6JiZvcVecFpCDvbjKkJC2p8FwONETuW1NAhhfLCTRL2QrW8sKM/w55mUGY1y/RyGeLZe9Yl9NDk7r4Mr7xwFzUvlrH8FqoZ7K95g17hWcte9zm4+okF9E3S+rbyJz3kW59I918uYpfJ/su5hGLX
*/