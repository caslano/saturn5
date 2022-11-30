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


namespace boost { namespace hana { namespace detail { namespace variadic {
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

    BOOST_HANA_INLINE_VARIABLE constexpr foldl1_t foldl1{};
    BOOST_HANA_INLINE_VARIABLE constexpr auto foldl = foldl1;
}} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_VARIADIC_FOLDL1_HPP

/* foldl1.hpp
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
*/