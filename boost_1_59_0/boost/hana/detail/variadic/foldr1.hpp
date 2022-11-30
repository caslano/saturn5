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


namespace boost { namespace hana { namespace detail { namespace variadic {
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

    BOOST_HANA_INLINE_VARIABLE constexpr foldr1_t foldr1{};

    struct foldr_t {
        template <typename F, typename State, typename ...Xn>
        constexpr decltype(auto) operator()(F&& f, State&& state, Xn&& ...xn) const {
            return foldr1_impl<sizeof...(xn) + 1>::apply(
                static_cast<F&&>(f), static_cast<Xn&&>(xn)..., static_cast<State&&>(state)
            );
        }
    };

    BOOST_HANA_INLINE_VARIABLE constexpr foldr_t foldr{};
}} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_VARIADIC_FOLDR1_HPP

/* foldr1.hpp
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
*/