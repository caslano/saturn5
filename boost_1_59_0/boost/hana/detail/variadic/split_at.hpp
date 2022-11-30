/*!
@file
Defines `boost::hana::detail::variadic::split_at`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_SPLIT_AT_HPP
#define BOOST_HANA_DETAIL_VARIADIC_SPLIT_AT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/functional/reverse_partial.hpp>

#include <cstddef>


namespace boost { namespace hana { namespace detail { namespace variadic {
    template <std::size_t n>
    struct split_at_t {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename X7, typename X8, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6, X7&& x7, X8&& x8, Xs&& ...xs) const {
            return split_at_t<n - 8>{}(
                hana::partial(static_cast<F&&>(f),
                    static_cast<X1&&>(x1),
                    static_cast<X2&&>(x2),
                    static_cast<X3&&>(x3),
                    static_cast<X4&&>(x4),
                    static_cast<X5&&>(x5),
                    static_cast<X6&&>(x6),
                    static_cast<X7&&>(x7),
                    static_cast<X8&&>(x8)
                ),
                static_cast<Xs&&>(xs)...
            );
        }
    };

    template <>
    struct split_at_t<0> {
        template <typename F, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, Xs&& ...xs) const {
            return static_cast<F&&>(f)()(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<1> {
        template <typename F, typename X1, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<2> {
        template <typename F, typename X1, typename X2, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<3> {
        template <typename F, typename X1, typename X2, typename X3, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2),
                static_cast<X3&&>(x3)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<4> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2),
                static_cast<X3&&>(x3),
                static_cast<X4&&>(x4)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<5> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2),
                static_cast<X3&&>(x3),
                static_cast<X4&&>(x4),
                static_cast<X5&&>(x5)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<6> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2),
                static_cast<X3&&>(x3),
                static_cast<X4&&>(x4),
                static_cast<X5&&>(x5),
                static_cast<X6&&>(x6)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <>
    struct split_at_t<7> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename X7, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6, X7&& x7, Xs&& ...xs) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1),
                static_cast<X2&&>(x2),
                static_cast<X3&&>(x3),
                static_cast<X4&&>(x4),
                static_cast<X5&&>(x5),
                static_cast<X6&&>(x6),
                static_cast<X7&&>(x7)
            )(static_cast<Xs&&>(xs)...);
        }
    };

    template <std::size_t n>
    struct _makesplit_at_t {
        template <typename ...Xs>
        constexpr decltype(auto) operator()(Xs&& ...xs) const {
            return hana::reverse_partial(split_at_t<n>{},
                                         static_cast<Xs&&>(xs)...);
        }
    };

    template <std::size_t n>
    BOOST_HANA_INLINE_VARIABLE constexpr _makesplit_at_t<n> split_at{};
}} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_VARIADIC_SPLIT_AT_HPP

/* split_at.hpp
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
*/