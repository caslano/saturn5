/*!
@file
Forward declares `boost::hana::monadic_compose`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MONADIC_COMPOSE_HPP
#define BOOST_HANA_FWD_MONADIC_COMPOSE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Composition of monadic functions.
    //! @ingroup group-Monad
    //!
    //! Given two monadic functions `f` and `g`, `monadic_compose` returns
    //! a new function equivalent to the composition of `f` with `g`, except
    //! the result of `g` is `chain`ed into `f` instead of simply passed to
    //! it, as with normal composition. `monadic_compose` satisfies
    //! @code
    //!     monadic_compose(f, g)(x) == chain(g(x), f)
    //! @endcode
    //!
    //!
    //! @note
    //! Unlike `compose`, `monadic_compose` does not generalize nicely to
    //! arities higher than one. Hence, only unary functions may be used
    //! with `monadic_compose`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Monad` `M` and two functions @f$ f : B \to M(C) @f$ and
    //! @f$ g : A \to M(B) @f$, the signature is
    //! @f$
    //!     \mathtt{monadic\_compose}
    //!         : (B \to M(C)) \times (A \to M(B)) \to (A \to M(C))
    //! @f$.
    //!
    //! @param f
    //! A monadic function with signature @f$ B \to M(C) @f$.
    //!
    //! @param g
    //! A monadic function with signature @f$ A \to M(B) @f$.
    //!
    //!
    //! @note
    //! This method is not tag-dispatched, so it can't be customized directly.
    //!
    //!
    //! Example
    //! -------
    //! @include example/monadic_compose.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto monadic_compose = [](auto&& f, auto&& g) {
        return [perfect-capture](auto&& x) -> decltype(auto) {
            return hana::chain(forwarded(g)(forwarded(x)), forwarded(f));
        };
    };
#else
    struct monadic_compose_t {
        template <typename F, typename G>
        constexpr auto operator()(F&& f, G&& g) const;
    };

    constexpr monadic_compose_t monadic_compose{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MONADIC_COMPOSE_HPP

/* monadic_compose.hpp
pYEShRZsm52TYeJuZd1XIrBzNEGjG/BUFMxO8mb7zM3CWlRZh3DS4HzuTW6G0wl5gzv67AWBN5jcneG0SkWliD0yi8VXesMlBM9klKsNHDDit37QvYGM999evze5035c9SYDfzymq2FAHo28YNLrTvteQKNpMBqOfZfGjH0dYgP2VZgXJlWIJJYVRnfZuK5XPHpdb7QUdYYsxwzsKDHLsdj8PwnULW6wtKN2ddWxNDscO6BDJaw8f4mfZRalPLpoLPKwGagsWMyhiz3FrLBp12ZIpl8oGEhezefott4D8bb6xRqGGqwlTmJD5BnHvodThd7TpSkb0AQt0dlLtiEmdT2bvdYsI4Nlt1G9znVN6iPIa4HUIkpbe9Yp0owAxKwsGw5hbDR8ykDljFkCYffzd/WLgTcUzta23DmgtZUVtnptaqcpOUPACgx0OL7VoUDn6u+2+gxxjIqCRbKueiRw8vfWONejftvu+qVAV1n+CIZDwjQpOqTRt9Kdp3NqAhjrjc4Vol5ajvEsnc8a85tasBQPdo362l7NFvWjuqm3DjaQe95J0AywnGbQ7LR69lKg+RcipkfeKnqwBbFfH5Z46ArR/dtMoK/0WV2dGsXQZuxn2xi1L5aDvuSPMinQVEqYAfatNgzMNcsyt9U6
*/