/*!
@file
Defines `boost::hana::detail::variadic::foldr1`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_FOLDR1_HPP
#define BOOST_HANA_DETAIL_VARIADIC_FOLDR1_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    //! @cond
    template <unsigned int n, typename = when<true>>
    struct foldr1_impl;

    template <>
    struct foldr1_impl<1> {
        template <typename F, typename X1>
        static constexpr X1 apply(F&&, X1&& x1)
        { return static_cast<X1&&>(x1); }
    };

    template <>
    struct foldr1_impl<2> {
        template <typename F, typename X1, typename X2>
        static constexpr decltype(auto) apply(F&& f, X1&& x1, X2&& x2) {
            return static_cast<F&&>(f)(static_cast<X1&&>(x1),
                                       static_cast<X2&&>(x2));
        }
    };

    template <>
    struct foldr1_impl<3> {
        template <typename F, typename X1, typename X2, typename X3>
        static constexpr decltype(auto) apply(F&& f, X1&& x1, X2&& x2, X3&& x3) {
            return f(static_cast<X1&&>(x1),
                   f(static_cast<X2&&>(x2),
                     static_cast<X3&&>(x3)));
        }
    };

    template <>
    struct foldr1_impl<4> {
        template <typename F, typename X1, typename X2, typename X3, typename X4>
        static constexpr decltype(auto) apply(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4) {
            return f(static_cast<X1&&>(x1),
                   f(static_cast<X2&&>(x2),
                   f(static_cast<X3&&>(x3),
                     static_cast<X4&&>(x4))));
        }
    };

    template <>
    struct foldr1_impl<5> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5>
        static constexpr decltype(auto) apply(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5) {
            return f(static_cast<X1&&>(x1),
                   f(static_cast<X2&&>(x2),
                   f(static_cast<X3&&>(x3),
                   f(static_cast<X4&&>(x4),
                     static_cast<X5&&>(x5)))));
        }
    };

    template <>
    struct foldr1_impl<6> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6>
        static constexpr decltype(auto) apply(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6) {
            return f(static_cast<X1&&>(x1),
                   f(static_cast<X2&&>(x2),
                   f(static_cast<X3&&>(x3),
                   f(static_cast<X4&&>(x4),
                   f(static_cast<X5&&>(x5),
                     static_cast<X6&&>(x6))))));
        }
    };

    template <unsigned int n>
    struct foldr1_impl<n, when<(n >= 7) && (n < 14)>> {
        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename X7, typename ...Xn>
        static constexpr decltype(auto)
        apply(F&& f
              , X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6, X7&& x7
              , Xn&& ...xn)
        {
            return f(static_cast<X1&&>(x1),
                   f(static_cast<X2&&>(x2),
                   f(static_cast<X3&&>(x3),
                   f(static_cast<X4&&>(x4),
                   f(static_cast<X5&&>(x5),
                   f(static_cast<X6&&>(x6),
                     foldr1_impl<sizeof...(xn) + 1>::apply(f, static_cast<X7&&>(x7), static_cast<Xn&&>(xn)...)))))));
        }
    };

    template <unsigned int n>
    struct foldr1_impl<n, when<(n >= 14) && (n < 28)>> {
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
            return f(static_cast<X1&&>(x1), f(static_cast<X2&&>(x2), f(static_cast<X3&&>(x3),   f(static_cast<X4&&>(x4),   f(static_cast<X5&&>(x5),   f(static_cast<X6&&>(x6),   f(static_cast<X7&&>(x7),
                   f(static_cast<X8&&>(x8), f(static_cast<X9&&>(x9), f(static_cast<X10&&>(x10), f(static_cast<X11&&>(x11), f(static_cast<X12&&>(x12), f(static_cast<X13&&>(x13),
                     foldr1_impl<sizeof...(xn) + 1>::apply(f, static_cast<X14&&>(x14), static_cast<Xn&&>(xn)...))))))))))))));
        }
    };

    template <unsigned int n>
    struct foldr1_impl<n, when<(n >= 28) && (n < 56)>> {
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
            return f(static_cast<X1&&>(x1),   f(static_cast<X2&&>(x2),   f(static_cast<X3&&>(x3),   f(static_cast<X4&&>(x4),   f(static_cast<X5&&>(x5),   f(static_cast<X6&&>(x6),   f(static_cast<X7&&>(x7),
                   f(static_cast<X8&&>(x8),   f(static_cast<X9&&>(x9),   f(static_cast<X10&&>(x10), f(static_cast<X11&&>(x11), f(static_cast<X12&&>(x12), f(static_cast<X13&&>(x13), f(static_cast<X14&&>(x14),
                   f(static_cast<X15&&>(x15), f(static_cast<X16&&>(x16), f(static_cast<X17&&>(x17), f(static_cast<X18&&>(x18), f(static_cast<X19&&>(x19), f(static_cast<X20&&>(x20), f(static_cast<X21&&>(x21),
                   f(static_cast<X22&&>(x22), f(static_cast<X23&&>(x23), f(static_cast<X24&&>(x24), f(static_cast<X25&&>(x25), f(static_cast<X26&&>(x26), f(static_cast<X27&&>(x27),
                     foldr1_impl<sizeof...(xn) + 1>::apply(f, static_cast<X28&&>(x28), static_cast<Xn&&>(xn)...))))))))))))))))))))))))))));
        }
    };

    template <unsigned int n>
    struct foldr1_impl<n, when<(n >= 56)>> {
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
            return f(static_cast<X1&&>(x1),   f(static_cast<X2&&>(x2),   f(static_cast<X3&&>(x3),   f(static_cast<X4&&>(x4),   f(static_cast<X5&&>(x5),   f(static_cast<X6&&>(x6),   f(static_cast<X7&&>(x7),
                   f(static_cast<X8&&>(x8),   f(static_cast<X9&&>(x9),   f(static_cast<X10&&>(x10), f(static_cast<X11&&>(x11), f(static_cast<X12&&>(x12), f(static_cast<X13&&>(x13), f(static_cast<X14&&>(x14),
                   f(static_cast<X15&&>(x15), f(static_cast<X16&&>(x16), f(static_cast<X17&&>(x17), f(static_cast<X18&&>(x18), f(static_cast<X19&&>(x19), f(static_cast<X20&&>(x20), f(static_cast<X21&&>(x21),
                   f(static_cast<X22&&>(x22), f(static_cast<X23&&>(x23), f(static_cast<X24&&>(x24), f(static_cast<X25&&>(x25), f(static_cast<X26&&>(x26), f(static_cast<X27&&>(x27), f(static_cast<X28&&>(x28),
                   f(static_cast<X29&&>(x29), f(static_cast<X30&&>(x30), f(static_cast<X31&&>(x31), f(static_cast<X32&&>(x32), f(static_cast<X33&&>(x33), f(static_cast<X34&&>(x34), f(static_cast<X35&&>(x35),
                   f(static_cast<X36&&>(x36), f(static_cast<X37&&>(x37), f(static_cast<X38&&>(x38), f(static_cast<X39&&>(x39), f(static_cast<X40&&>(x40), f(static_cast<X41&&>(x41), f(static_cast<X42&&>(x42),
                   f(static_cast<X43&&>(x43), f(static_cast<X44&&>(x44), f(static_cast<X45&&>(x45), f(static_cast<X46&&>(x46), f(static_cast<X47&&>(x47), f(static_cast<X48&&>(x48), f(static_cast<X49&&>(x49),
                   f(static_cast<X50&&>(x50), f(static_cast<X51&&>(x51), f(static_cast<X52&&>(x52), f(static_cast<X53&&>(x53), f(static_cast<X54&&>(x54), f(static_cast<X55&&>(x55),
                     foldr1_impl<sizeof...(xn) + 1>::apply(f, static_cast<X56&&>(x56), static_cast<Xn&&>(xn)...))))))))))))))))))))))))))))))))))))))))))))))))))))))));
        }
    };
    //! @endcond

    struct foldr1_t {
        template <typename F, typename X1, typename ...Xn>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, Xn&& ...xn) const {
            return foldr1_impl<sizeof...(xn) + 1>::apply(
                static_cast<F&&>(f), static_cast<X1&&>(x1), static_cast<Xn&&>(xn)...
            );
        }
    };

    constexpr foldr1_t foldr1{};

    struct foldr_t {
        template <typename F, typename State, typename ...Xn>
        constexpr decltype(auto) operator()(F&& f, State&& state, Xn&& ...xn) const {
            return foldr1_impl<sizeof...(xn) + 1>::apply(
                static_cast<F&&>(f), static_cast<Xn&&>(xn)..., static_cast<State&&>(state)
            );
        }
    };

    constexpr foldr_t foldr{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_FOLDR1_HPP

/* foldr1.hpp
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
*/