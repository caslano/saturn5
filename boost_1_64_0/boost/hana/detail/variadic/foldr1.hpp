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
b/3r1QXdXdJotnDiu17LaZTb3mDZseApDpzrQ8a+L83Jqw41kO2I+Eu6k2cR4HrHRlPRLn1bGLszv0Om3/lObq/iC4KmfVCOHdXqKWzs53Vh78p5/BxFBizp5ZYZK7u78tGqO71a+d6P9KeEy9SsjWXGq1KeWzy+OLooHI8ZE1ogH/QhnHXHd82K/EgD7J1ebvnRA7BlGbWR1ppIjGgT+y3A+rvlxDYod7wN29Ph+wMsWAmsdRGb9/ZE+TkDVDmBegegrWLp/CqZrNmo5LPbACu92FwcPyBQa/HZWuKz1j7bx/7u5jP3xTa/SGJfLHGdnuXI90sI19sZ7c90nQ/0NmAmqRK/BHepCS/FwsIMRGJzhc1HdZMvVzZJim8V9n7fZ+7jbdWJ9vwW3GXj7IP2Usg+gGqAT3Pf2h3V92X4SU2CHza51mMBmudrx16P0UbO6wmeRn2Qi8bKVvOkFRXf2DazDM5HtoCdocBbDkgbfH4trq5Uu1Q4DzjZKvpnmTLhN7aHtu3ZVQ3Clnsee/t0ZW/v7EmLW+UZeLgVj10Y0yjY3rQWHtqhtjKy70hb1ghrH0qcTcI/Mc6Iy4PRue1olkQQ43kTBMEkogn+utT1RSkICSaOWnkI78wl3ptqgJtZGY5nl/C5LBcl4UgkR+LTuCs5kM1TVRfx6WWnG5DlttMNQpruJ6CMmf9upvt+wuAsnob9b3thy8rFBkxu1BrlBnG9BUuzYNh37SxtHfhuCBtLuihsNacCa4bqkv0UXnKF5iVNmZcCsqFk8nq5XKjCc7m22dcDnohuu1iHpNvsLPfdmaGEs76Es2FIy3LDqdz0BO3OxIIypHYAD4LgZn0VtC1q2ivL1qVGUL1R17qR2wPOJ8ALGQ32smWOzRcBky6ZTnpbRZ6p5zfTSTaP5HOwmeM4ynU+V+Y6o9IVXm/KlsLmYDQaihCM9OvQIkAc3do8rqK66ByrFidCXIfeN9Sx2KS1KcS/R3mNRx2KCk0U+60L38u5HE1zKf++j9lbcwDn54HZqU56km7ibgzJQJxvYZta6D6TNvLINkLpNJke46TTZTrXSQ8UZBuhtF+QbYTSIwTZRiidI9Pj7TT4ItlGKJ0nyDZC6VJBthFKVwmyjVB6tpEeY6fnGOlcO90syDZC6RZBthFKLxGObSQ3S+KKrhsQauw9UyryyAZHaWlza+Bp2NwaeRo2t3qeXkk2OCt9NfJ5+maywVnpu1AfTz9ANjgr/QS3waWaNrccVv41boNLNW1uuSz9MbfBpZo2t3EsvYFscAeAZoEafSz+Z//TAvsijOzMyvL8WtyctqSKwg69inDOiLo918OWqVuujz0dvmusG43gexGceLPL12+iIs8mIW3l7UJ5+G3k7UN8e3KWeudffadEF1OpbB7rU7Zw3r4tyHLsUJbMzaKfZTu4ZW4R6xNkn6u/JdTONGqH6pJ1G/P6OpVfk2nWVUblp2exd6So3Wz6QVm047w9Mp7wAL3HtDJQHTOyHH6ELNtuxtMZSEdd/gihAJS1cAP3RQAMr5q2cL6cImEtgvFppOORBl4mzSgTjDc3OucB28j6w1F6r5H7H8h2lyhwjAtwqMh2Ol2mWbt9ZRut7QtcfgiAhVmZ/rIMq2Mg0pGmIHrrwAYBFlsUtc8JK4G7wYBBQbf7PlSWCS0Icz+N4QSDOm+Uq5J81vzOtn/1leccZpvR0GLskcn+tR9bw3mWXl9UCYtAcX5RMckdFUpvB5r3UwLGtcUFpidMoCVmvL8YaG0ON0k5EoUvjka+ODVoy7ZzhHAzY/dOvp1i+uckX9702Zli+yC1R8MwG4aDkfBS+06iDYGss+6PsVLobwW7p1mH/gY=
*/