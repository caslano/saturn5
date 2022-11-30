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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr _make_compose compose{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_COMPOSE_HPP

/* compose.hpp
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
*/