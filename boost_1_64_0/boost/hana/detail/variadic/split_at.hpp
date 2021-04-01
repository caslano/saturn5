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


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
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
    constexpr _makesplit_at_t<n> split_at{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_SPLIT_AT_HPP

/* split_at.hpp
NtxqouWoE0gZDcBSB9YO1gBKDFpz0mSpYtvaUCCUxDEA13ZEIb1o0l2rkkqJR5z1gvtRB2BBIBivdppHmQVBWw0Gi+XwwuqIK0cCSmpxncTKwI/xgYlUxTE9IcNZtZC/RruC9NpXMmz5mhqzaQXQSD1rPAb9OXiz+IBE5JdiekFVMQGECYFMs6g+yZ+LzWc4XnCiyoV51gzCMrlREQ2I2ovzUUy1bFBsW/LnRnAeot8Ykhj5FIBNfAUh+9keakiR+QuZiTtgER6KhPlUN8NOwI+MzCAhyjDj7/T8/pnjYiGZN1bt1W3px8K3U1igzMrmqvWQccJGj9I8c/KCaFpEdN6vFk5m0F/Yb33mJfJc0qqAlrVcw/9DAc2BNnix9+THPIx0g0dYIoLchmaV+dsxKn1sMjlzs58mLxlE6Z3tAykVIWv+9pWsqF0d5umyF3EXC+8coc0xZlQtsnwg8oWo4LFBUWpxpjaYVcIEHwUew9O4IiuJqv5Pld4/iMQzFq+tD8SPxTSIFphrkrWxK9k+I8NBPYNx1sCItNeisDgqF4DsmSZQK/dVPvtD6g==
*/