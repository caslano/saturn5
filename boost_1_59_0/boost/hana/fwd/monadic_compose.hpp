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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr monadic_compose_t monadic_compose{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_MONADIC_COMPOSE_HPP

/* monadic_compose.hpp
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
*/