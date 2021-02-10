/*!
@file
Defines `boost::hana::on`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ON_HPP
#define BOOST_HANA_FUNCTIONAL_ON_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>
#include <boost/hana/functional/infix.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Invoke a function with the result of invoking another function on
    //! each argument.
    //!
    //! Specifically, `on(f, g)` is a function such that
    //! @code
    //!     on(f, g)(x...) == f(g(x)...)
    //! @endcode
    //!
    //! For convenience, `on` also supports infix application as provided
    //! by `infix`.
    //!
    //!
    //! @note
    //! `on` is associative, i.e. `on(f, on(g, h))` is equivalent to
    //! `on(on(f, g), h)`.
    //!
    //! @internal
    //! ### Proof of associativity
    //!
    //! @code
    //!     on(f, on(g, h))(xs...) == f(on(g, h)(xs)...)
    //!                            == f(g(h(xs))...)
    //!
    //!     on(on(f, g), h)(xs...) == on(f, g)(h(xs)...)
    //!                            == f(g(h(xs))...)
    //! @endcode
    //! @endinternal
    //!
    //!
    //! ### Example
    //! @include example/functional/on.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto on = infix([](auto&& f, auto&& g) {
        return [perfect-capture](auto&& ...x) -> decltype(auto) {
            return forwarded(f)(g(forwarded(x))...);
        };
    });
#else
    template <typename F, typename G>
    struct on_t {
        F f; G g;
        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const& {
            return f(g(static_cast<X&&>(x))...);
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) & {
            return f(g(static_cast<X&&>(x))...);
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) && {
            return std::move(f)(g(static_cast<X&&>(x))...);
        }
    };

    constexpr auto on = infix(detail::create<on_t>{});
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ON_HPP

/* on.hpp
xJQlpKNsO83T0Tn/zUjXNiMdiBYRs5XGktA5E6UA3UIMOh8Nf6oTg2igZoDGxpsYmxayLezKSydSiUs6dTy94UTgUI5ODk9pwRlm1sKZR5tNgO1DCFMzMeVnnAZr2N35cAw2JPllooYPDWF//kk9xkjOg+GPKECMR/BgxDENT88v6Kwez7q2UnXY5XwR9kAYIapjdXEn0UT18cx83FPuMzu9puEUhcG1BIXdnsqjG0ahB1Prgzhp+1Df/VQ7P6QK08Bzw9XSUgcvmfBLYV/OHyfa68hI+7k66nisUEteZsGX+VrSD6HYFPqJSyeFXCX9nKeXr6S/zFdkq7INfbit08sC+oCXTfiUcCIi4fayYRVfFtDCq64E/cKt1F5Hd/vs5evoL/UjYyAfdFqBFyXDFG/zbRpso1esk70s9Ba3RytJEoHhVdBIOsvqZIkvXLzPWlYLPaXz5KI5ORRmXn+Zby6BEXBo+Xx7VFG+LK82ETtEz1ZNvsxX57fJBAMDF7qrv8yPU7Oh9wrd1V4Wl5Ow2dvmInuJ16qzsHYTmAw3vJpM1P18+g2ik3sVRgluMstoqfy4MraG8fAUa0Og/xdQSwMECgAAAAgALWdKUgP3RBlOAgAAIQUAACAACQBjdXJsLW1hc3Rlci9saWIv
*/