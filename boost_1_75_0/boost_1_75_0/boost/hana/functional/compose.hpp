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
Us9deUktL9LX7pLo3Gs5Ynai2JGG8U02FGsuorJNU68RY+TjqbAfRjb6luQl0SffhOfb0wLH0uCb96XnHb48T96d+iK9I7qGb1GW5FkSYBhoRIsuOjX1XJ53cwsVOS6CzynVcl+umAXrgQbSt1NHoz0cyi9pTlwCmXkKJf4MqpZ5fpy4iNW1Kgb4+whPmhYFnE0By6cni8nkAQqdVMUr6TWvx7nagT2G6/7I5LvgGxfpdh4vcduOZDwMEdrbvWbxnIy3RzPiC+Vrnz6S0YAZfxvlD3b34TN+jmz0e+zIAVZGS4lF91aFfGX99D42E98nKjuuInvX5yy/kRxMpsfNXkeour7WQvvt55aOC7xFIS9qRxmwyy1aI3MfrkJvbhzVadPMb6cdMVpRLBS6SPgVvl8sNAh4jAuNEX6FZgpCwy+pSLEyPyDeiycvj0zMoosev55A9xyOvscfo6+0K/sVCR9eQnrVi8/T91b193Kq40hv1fHeJGdv1amYSzGvX/BWojZh6hvIMk7DM/t1aEpZdkSHN8Az2I9hR/2RxWN4APUZoRIT/el7BqNwIshEEMvR79e1FDMDK/38aMz4f4/ZQHMcvrZer0H7ew+BEejNHniRVnWxeAv2xPUyyRILsdKZMjGJE2e9hPo/KRSBOqp8bOnltFYAspmiCRwAhLdg+B8svB3DARZGXAe20vARI3ce+v+2R6U08tZW7M3v
*/