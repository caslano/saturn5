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
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
*/