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
4O8XhOmpwG8DfH4EEZnskUaNXYj4Tuw395NdmHOFmhmfhmKfHIhxsZ/RhO+h7EpP6nJC3G4sPvxb0pHJUXIaNa2PVyn2C9cw84nbhkpSifeaNe9bdalGJIkXAoeHQ6G9+obYLcFdAlGuCbj/mUI0xntXxesh200hgGh5r9fFWI18+P3JEIskBzL1W44IHf4YpEC8Z7A6blP5fBtkTGjROwx9biC8GpCGN77Db8a1a/uqQQ8N3AdFNkVUGYf7BrCHv1X1YqBKC2Q+UT7rXBPR0Gy/O0WHagq2yH41fSD2AmlhaUtijhY41OfNNG26V7+3MeoSHhuTOwWL/hnE9b09Qcyzhc9bgSLqHW+mFDndo8oaq3uL4MnohLkA30MLSHAe/iAamJ0RpwEc36ETHggngCgLDxhI+h875XUlLo30Vdl/hdqXnWgxyE1HU38onoxmxHZLbmYaY3hCmtGFVMV6PxV0jEl536uzrVdD5K2/YTwkL9KwwUxyxmj+hxjf3pkABOXmi1ARq6GpLzNL1H7M34P2QVtWedsYR8jNJ3Fo4POYylb3GXK+1aNErg==
*/