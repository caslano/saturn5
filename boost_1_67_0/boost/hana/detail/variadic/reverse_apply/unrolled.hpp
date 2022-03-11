/*!
@file
Defines `boost::hana::detail::variadic::reverse_apply_unrolled`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_UNROLLED_HPP
#define BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_UNROLLED_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/functional/reverse_partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    struct reverse_apply_unrolled_impl {
        template <typename F>
        constexpr decltype(auto) operator()(F&& f) const {
            return static_cast<F&&>(f)();
        }

        template <typename F, typename X1>
        constexpr decltype(auto) operator()(F&& f, X1&& x1) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2) const {
            return static_cast<F&&>(f)(
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3) const {
            return static_cast<F&&>(f)(
                static_cast<X3&&>(x3),
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3, typename X4>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4) const {
            return static_cast<F&&>(f)(
                static_cast<X4&&>(x4),
                static_cast<X3&&>(x3),
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5) const {
            return static_cast<F&&>(f)(
                static_cast<X5&&>(x5),
                static_cast<X4&&>(x4),
                static_cast<X3&&>(x3),
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename ...Xn>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6, Xn&& ...xn) const {
            return (*this)(hana::reverse_partial(
                  static_cast<F&&>(f)
                , static_cast<X6&&>(x6)
                , static_cast<X5&&>(x5)
                , static_cast<X4&&>(x4)
                , static_cast<X3&&>(x3)
                , static_cast<X2&&>(x2)
                , static_cast<X1&&>(x1)
            ), static_cast<Xn&&>(xn)...);
        }
    };

    constexpr reverse_apply_unrolled_impl reverse_apply_unrolled{};

}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_UNROLLED_HPP

/* unrolled.hpp
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
*/