/*!
@file
Defines `boost::hana::detail::variadic::foldl1`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_FOLDL1_HPP
#define BOOST_HANA_DETAIL_VARIADIC_FOLDL1_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    //! @cond
    template <unsigned int n, typename = when<true>>
    struct foldl1_impl;

    template <>
    struct foldl1_impl<1> {
        template <typename F, typename X1>
        static constexpr X1 apply(F&&, X1&& x1)
        { return static_cast<X1&&>(x1); }
    };

    template <>
    struct foldl1_impl<2> {
        template <typename F, typename X1, typename X2>
        static constexpr decltype(auto) apply(F&& f, X1&& x1, X2&& x2) {
            return static_cast<F&&>(f)(static_cast<X1&&>(x1),
                                       static_cast<X2&&>(x2));
        }
    };

    template <>
    struct foldl1_impl<3> {
        template <typename F, typename X1, typename X2, typename X3>
        static constexpr decltype(auto) apply(F&& f, X1&& x1, X2&& x2, X3&& x3) {
            return f(f(static_cast<X1&&>(x1),
                       static_cast<X2&&>(x2)),
                       static_cast<X3&&>(x3));
        }
    };

    template <>
    struct foldl1_impl<4> {
        template <typename F, typename X1, typename X2, typename X3, typename X4>
        static constexpr decltype(auto) apply(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4) {
            return f(f(f(static_cast<X1&&>(x1),
                         static_cast<X2&&>(x2)),
                         static_cast<X3&&>(x3)),
                         static_cast<X4&&>(x4));
        }
    };

    template <>
    struct foldl1_impl<5> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5>
        static constexpr decltype(auto) apply(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5) {
            return f(f(f(f(static_cast<X1&&>(x1),
                           static_cast<X2&&>(x2)),
                           static_cast<X3&&>(x3)),
                           static_cast<X4&&>(x4)),
                           static_cast<X5&&>(x5));
        }
    };

    template <>
    struct foldl1_impl<6> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6>
        static constexpr decltype(auto) apply(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6) {
            return f(f(f(f(f(static_cast<X1&&>(x1),
                             static_cast<X2&&>(x2)),
                             static_cast<X3&&>(x3)),
                             static_cast<X4&&>(x4)),
                             static_cast<X5&&>(x5)),
                             static_cast<X6&&>(x6));
        }
    };

    template <unsigned int n>
    struct foldl1_impl<n, when<(n >= 7) && (n < 14)>> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename X7, typename ...Xn>
        static constexpr decltype(auto)
        apply(F&& f
              , X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6, X7&& x7
              , Xn&& ...xn)
        {
            return foldl1_impl<sizeof...(xn) + 1>::apply(
                f,
                f(f(f(f(f(f(static_cast<X1&&>(x1),
                            static_cast<X2&&>(x2)),
                            static_cast<X3&&>(x3)),
                            static_cast<X4&&>(x4)),
                            static_cast<X5&&>(x5)),
                            static_cast<X6&&>(x6)),
                            static_cast<X7&&>(x7)),
                static_cast<Xn&&>(xn)...
            );
        }
    };

    template <unsigned int n>
    struct foldl1_impl<n, when<(n >= 14) && (n < 28)>> {
        template <
              typename F
            , typename X1, typename X2, typename X3,  typename X4,  typename X5,  typename X6,  typename X7
            , typename X8, typename X9, typename X10, typename X11, typename X12, typename X13, typename X14
            , typename ...Xn
        >
        static constexpr decltype(auto)
        apply(F&& f
              , X1&& x1, X2&& x2, X3&& x3,   X4&& x4,   X5&& x5,   X6&& x6,   X7&& x7
              , X8&& x8, X9&& x9, X10&& x10, X11&& x11, X12&& x12, X13&& x13, X14&& x14
              , Xn&& ...xn)
        {
            return foldl1_impl<sizeof...(xn) + 1>::apply(
                f,
                f(f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X1&&>(x1),  static_cast<X2&&>(x2)), static_cast<X3&&>(x3)),   static_cast<X4&&>(x4)),   static_cast<X5&&>(x5)),   static_cast<X6&&>(x6)),   static_cast<X7&&>(x7)),
                    static_cast<X8&&>(x8)), static_cast<X9&&>(x9)), static_cast<X10&&>(x10)), static_cast<X11&&>(x11)), static_cast<X12&&>(x12)), static_cast<X13&&>(x13)), static_cast<X14&&>(x14))
                , static_cast<Xn&&>(xn)...);

        }
    };

    template <unsigned int n>
    struct foldl1_impl<n, when<(n >= 28) && (n < 56)>> {
        template <
              typename F
            , typename X1,  typename X2,  typename X3,  typename X4,  typename X5,  typename X6,  typename X7
            , typename X8,  typename X9,  typename X10, typename X11, typename X12, typename X13, typename X14
            , typename X15, typename X16, typename X17, typename X18, typename X19, typename X20, typename X21
            , typename X22, typename X23, typename X24, typename X25, typename X26, typename X27, typename X28
            , typename ...Xn
        >
        static constexpr decltype(auto)
        apply(F&& f
              , X1&& x1,   X2&& x2,   X3&& x3,   X4&& x4,   X5&& x5,   X6&& x6,   X7&& x7
              , X8&& x8,   X9&& x9,   X10&& x10, X11&& x11, X12&& x12, X13&& x13, X14&& x14
              , X15&& x15, X16&& x16, X17&& x17, X18&& x18, X19&& x19, X20&& x20, X21&& x21
              , X22&& x22, X23&& x23, X24&& x24, X25&& x25, X26&& x26, X27&& x27, X28&& x28
              , Xn&& ...xn)
        {
            return foldl1_impl<sizeof...(xn) + 1>::apply(
                f,
                f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X1&&>(x1),    static_cast<X2&&>(x2)),   static_cast<X3&&>(x3)),   static_cast<X4&&>(x4)),   static_cast<X5&&>(x5)),   static_cast<X6&&>(x6)),   static_cast<X7&&>(x7)),
                    static_cast<X8&&>(x8)),   static_cast<X9&&>(x9)),   static_cast<X10&&>(x10)), static_cast<X11&&>(x11)), static_cast<X12&&>(x12)), static_cast<X13&&>(x13)), static_cast<X14&&>(x14)),
                    static_cast<X15&&>(x15)), static_cast<X16&&>(x16)), static_cast<X17&&>(x17)), static_cast<X18&&>(x18)), static_cast<X19&&>(x19)), static_cast<X20&&>(x20)), static_cast<X21&&>(x21)),
                    static_cast<X22&&>(x22)), static_cast<X23&&>(x23)), static_cast<X24&&>(x24)), static_cast<X25&&>(x25)), static_cast<X26&&>(x26)), static_cast<X27&&>(x27)), static_cast<X28&&>(x28))
                , static_cast<Xn&&>(xn)...);
        }
    };

    template <unsigned int n>
    struct foldl1_impl<n, when<(n >= 56)>> {
        template <
              typename F
            , typename X1,  typename X2,  typename X3,  typename X4,  typename X5,  typename X6,  typename X7
            , typename X8,  typename X9,  typename X10, typename X11, typename X12, typename X13, typename X14
            , typename X15, typename X16, typename X17, typename X18, typename X19, typename X20, typename X21
            , typename X22, typename X23, typename X24, typename X25, typename X26, typename X27, typename X28
            , typename X29, typename X30, typename X31, typename X32, typename X33, typename X34, typename X35
            , typename X36, typename X37, typename X38, typename X39, typename X40, typename X41, typename X42
            , typename X43, typename X44, typename X45, typename X46, typename X47, typename X48, typename X49
            , typename X50, typename X51, typename X52, typename X53, typename X54, typename X55, typename X56
            , typename ...Xn
        >
        static constexpr decltype(auto)
        apply(F&& f
              , X1&& x1,   X2&& x2,   X3&& x3,   X4&& x4,   X5&& x5,   X6&& x6,   X7&& x7
              , X8&& x8,   X9&& x9,   X10&& x10, X11&& x11, X12&& x12, X13&& x13, X14&& x14
              , X15&& x15, X16&& x16, X17&& x17, X18&& x18, X19&& x19, X20&& x20, X21&& x21
              , X22&& x22, X23&& x23, X24&& x24, X25&& x25, X26&& x26, X27&& x27, X28&& x28
              , X29&& x29, X30&& x30, X31&& x31, X32&& x32, X33&& x33, X34&& x34, X35&& x35
              , X36&& x36, X37&& x37, X38&& x38, X39&& x39, X40&& x40, X41&& x41, X42&& x42
              , X43&& x43, X44&& x44, X45&& x45, X46&& x46, X47&& x47, X48&& x48, X49&& x49
              , X50&& x50, X51&& x51, X52&& x52, X53&& x53, X54&& x54, X55&& x55, X56&& x56
              , Xn&& ...xn)
        {
            return foldl1_impl<sizeof...(xn) + 1>::apply(
                f,
                f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X1&&>(x1),    static_cast<X2&&>(x2)),   static_cast<X3&&>(x3)),   static_cast<X4&&>(x4)),   static_cast<X5&&>(x5)),   static_cast<X6&&>(x6)),   static_cast<X7&&>(x7)),
                    static_cast<X8&&>(x8)),   static_cast<X9&&>(x9)),   static_cast<X10&&>(x10)), static_cast<X11&&>(x11)), static_cast<X12&&>(x12)), static_cast<X13&&>(x13)), static_cast<X14&&>(x14)),
                    static_cast<X15&&>(x15)), static_cast<X16&&>(x16)), static_cast<X17&&>(x17)), static_cast<X18&&>(x18)), static_cast<X19&&>(x19)), static_cast<X20&&>(x20)), static_cast<X21&&>(x21)),
                    static_cast<X22&&>(x22)), static_cast<X23&&>(x23)), static_cast<X24&&>(x24)), static_cast<X25&&>(x25)), static_cast<X26&&>(x26)), static_cast<X27&&>(x27)), static_cast<X28&&>(x28)),
                    static_cast<X29&&>(x29)), static_cast<X30&&>(x30)), static_cast<X31&&>(x31)), static_cast<X32&&>(x32)), static_cast<X33&&>(x33)), static_cast<X34&&>(x34)), static_cast<X35&&>(x35)),
                    static_cast<X36&&>(x36)), static_cast<X37&&>(x37)), static_cast<X38&&>(x38)), static_cast<X39&&>(x39)), static_cast<X40&&>(x40)), static_cast<X41&&>(x41)), static_cast<X42&&>(x42)),
                    static_cast<X43&&>(x43)), static_cast<X44&&>(x44)), static_cast<X45&&>(x45)), static_cast<X46&&>(x46)), static_cast<X47&&>(x47)), static_cast<X48&&>(x48)), static_cast<X49&&>(x49)),
                    static_cast<X50&&>(x50)), static_cast<X51&&>(x51)), static_cast<X52&&>(x52)), static_cast<X53&&>(x53)), static_cast<X54&&>(x54)), static_cast<X55&&>(x55)), static_cast<X56&&>(x56))
                , static_cast<Xn&&>(xn)...);
        }
    };
    //! @endcond

    struct foldl1_t {
        template <typename F, typename X1, typename ...Xn>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, Xn&& ...xn) const {
            return foldl1_impl<sizeof...(xn) + 1>::apply(
                static_cast<F&&>(f), static_cast<X1&&>(x1), static_cast<Xn&&>(xn)...
            );
        }
    };

    constexpr foldl1_t foldl1{};
    constexpr auto foldl = foldl1;
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_FOLDL1_HPP

/* foldl1.hpp
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
*/