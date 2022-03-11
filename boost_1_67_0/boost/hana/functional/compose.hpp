/*!
@file
Defines `boost::hana::compose`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_COMPOSE_HPP
#define BOOST_HANA_FUNCTIONAL_COMPOSE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>
#include <boost/hana/detail/variadic/foldl1.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Return the composition of two functions or more.
    //!
    //! `compose` is defined inductively. When given more than two functions,
    //! `compose(f, g, h...)` is equivalent to `compose(f, compose(g, h...))`.
    //! When given two functions, `compose(f, g)` is a function such that
    //! @code
    //!     compose(f, g)(x, y...) == f(g(x), y...)
    //! @endcode
    //!
    //! If you need composition of the form `f(g(x, y...))`, use `demux` instead.
    //!
    //! @note
    //! `compose` is an associative operation; `compose(f, compose(g, h))`
    //! is equivalent to `compose(compose(f, g), h)`.
    //!
    //! @internal
    //! ### Proof of associativity
    //!
    //! @code
    //!     compose(f, compose(g, h))(x, xs...) == f(compose(g, h)(x), xs...)
    //!                                         == f(g(h(x)), xs...)
    //!
    //!     compose(compose(f, g), h)(x, xs...) == compose(f, g)(h(x), xs...)
    //!                                         == f(g(h(x)), xs...)
    //! @endcode
    //! @endinternal
    //!
    //! ### Example
    //! @include example/functional/compose.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto compose = [](auto&& f1, auto&& f2, ..., auto&& fn) {
        return [perfect-capture](auto&& x, auto&& ...xs) -> decltype(auto) {
            return forwarded(f1)(
                    forwarded(f2)(
                     ...
                      forwarded(fn)(forwarded(x))
                    ),
                    forwarded(xs)...
                );
        }
    };
#else
    template <typename F, typename G>
    struct _compose {
        F f; G g;

        template <typename X, typename ...Xs>
        constexpr decltype(auto) operator()(X&& x, Xs&& ...xs) const& {
            return f(
                g(static_cast<X&&>(x)),
                static_cast<Xs&&>(xs)...
            );
        }

        template <typename X, typename ...Xs>
        constexpr decltype(auto) operator()(X&& x, Xs&& ...xs) & {
            return f(
                g(static_cast<X&&>(x)),
                static_cast<Xs&&>(xs)...
            );
        }

        template <typename X, typename ...Xs>
        constexpr decltype(auto) operator()(X&& x, Xs&& ...xs) && {
            return std::move(f)(
                std::move(g)(static_cast<X&&>(x)),
                static_cast<Xs&&>(xs)...
            );
        }
    };

    struct _make_compose {
        template <typename F, typename G, typename ...H>
        constexpr decltype(auto) operator()(F&& f, G&& g, H&& ...h) const {
            return detail::variadic::foldl1(detail::create<_compose>{},
                static_cast<F&&>(f),
                static_cast<G&&>(g),
                static_cast<H&&>(h)...
            );
        }
    };

    constexpr _make_compose compose{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_COMPOSE_HPP

/* compose.hpp
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
*/