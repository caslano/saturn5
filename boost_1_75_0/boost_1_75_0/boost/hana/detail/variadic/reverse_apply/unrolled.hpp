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
aJaHb18NJz7P7ZAj+1typNIcqZBjcHw8B9RkbLdFGhEF4A2O0M21K84bjHpcHMUAsH5z9KmqbjA4YdW4I3ejLHkrvr3VgWpRhWV0ZVvRY/OpWdAhKNH1Dgp/gACyQKiAWG7rYIkBPcm03xRwkqb8qMcGc2syp+XA+oIS0HRYIREpF83W3SSFXiPnrhrtY4ZZ8m9Au2H0Fe1PKXSkr5tIludF9+tfTUcBXMwqJA/Ztn5g/5qW58LZAF3X01fcvRHAxgkQChF1UwuKPyoIDydbyIiCCEeO8rU8f5aU1Gqapa4xQJ1ZTSUGOjlPJayFJJu/4SBCaDMF5fYIYCMmKy35rSZHes3dKzkrzCO/RufRLUCR16o3GOc7MlGTzaEsz1GusdTNLxB/ABNI/txwX9LQBzhFPLevsr+/3qI0/34owpUYPamJnybOxcu12UYps66wQBI8JrXY4CwnlabEs50jqJ8NbP4B1L+IXhHK34t5sjiebvO7cITV2lMwyC+99BKMABC+hKHe+/3EoR4zeqgVJi2C9Wlqc7L4cuyGVid5+bL46CZx2gQYUTa6bqR6+rhmjx5X6q0A0nPIfGBjleXorgNdy1/PX1dXm82JmcByYPUL6GgFqtv47AIOvpSvowMENMnr35jlMbjoSCKJBCRakwpKNKMJKdGN0aSpRuroAAc5YRxL0F8IGmzfdxnWCNxTYKjb3lbLK8NDR92s
*/