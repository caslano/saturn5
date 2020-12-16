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
sz1/dXCxa34yHDsCZTGfFJYXgq0wqNgmBjv58uZJ1FC6mO3Pb+th7HOmP2fZ+fxzp89DPewQJSSnTmZzOMJ7fkhR80b7eJc8qGruaA3D/Yz5hal2Cok+wEEXMs5X6qlSFvzJdDHctW4rpGqwns7cMffOWfsBRNen8/3oFuI/1rrqx9cVpdNoXY2m9s90tx/hC4sSRp066jTudeCbszkPJhtrE4yDsAjK48nGQLQ9Emlpi1M9iQtQ3XaMNna/WqP71VNkjDayp5zr2DzNO6ABzIlt6lTh5nx47uc3g/Ykbz6feDPZTV3nMBfSGcMsOmu5SKbpfGX+EOd9YfMsWxeXsDORuBKHcSXp1n6h3O3PknWZZS/IMuu5nMqib/b7Tz7h7tuV1Lccqv8qpL3vM3n4PqG+a2jcso5rsyyZzet0v+98ntLeDVkUq1zZTyyiv8m/wI5VfhONKeqcdcFtis7DaM/h4EWpg/B7O9Ked/2StE3LdlYpfhB38jYAv4vNIcbqGvM9Cg7O5nEyKV+OK4fGZY0lh9dFY7mftbOB4qPjt/Hlg4SrcRkMJ9RXKmvj5BEqO4rKShsVypj+FXTuBbq20yXuOJTwnY7GFkcDwZYWweNPNkBCIAoewZ14k3PbwyYsl51b/DOLakMOX74cJPXq/k7bgbbmUMCIMAM8XSbPbKBvS9w8ZfCDRfgU2YFIWD4d1oqTJVxvBqMJ7dMASeSXvWvzjzR/Q99WD23syulQJ3F+3tShnbSWt19xQRHJAIp/8TT6l7g6M46FBrn4DOenXR2RQb9J9Wz9TLYv4PEKWlLd8QryDVkAfXmMkx4o07lO2g850oaBWPuKbpjf59zyPWQprUYXnaTBVx7qwjyaAkRqI6AyOlhr/c9MKfrt1Xge/gl7np/fxDyfQfP8QtLz7Nlo16a8s55jzq7sAv4Xg+wgq/+jSykwy72WXtoEjuOE45eTxjGNarOWk9G79fd1AYcJZvTPxGJVZzTAcfvqJnC7gnD7WtK4TTDaZLBb1fmaY/6dpEe4fU3eIBn3Jsnuks7tstEFwXCU2wzUHG63eBJ1/qsTu8XbyJsbYqJN6p9kt1jDcbcZ7Rd0Ng6PShSwqWfTGN7tZAxrPcZQQGN4j4+hi21f0oW14lqZf/YawVrmvPyDJGX2h0mvBddokl0DNv8jWrZ1+4/pb0nzN+zozKG1LtoEvU2vvLn2Ga0L6Hsu368vsvCj6M5fsr0L9jP4cceNX0d1fcz2BV/jb3Uf8Jbim/Yt02OfVPK+R9r7DKZzPcIYk6Kn/6jo6T9Rf39Wyv2i9OFXWU5z9E54GATyZ+LxCuOG3OwJ4+29qZoHl4Nc0n298sbl0htESh7+mm3HDFPziitKsLmfRvndvL6lNsXGedUz8PqHd18riisrqK+eefJjnJjJ+EDMl+F34IaVLSsvq93fXHsq1KRbuZfAd7aPoOU/6JO+0a4znIZ6Wd6JTxSxzhMbOTwd8KJQ6/y2WIuwYAMBqw23RfiZqV80Lp7N7VFI78/SI2Q+2YUs2ChZRoHlyHLGtRppz2pl57go6wGfALi87aDEQKRzXOTReadzb39xTXNsMQ6FG2OLGbwA+LA90gnul/dhGV5ymV22SjTXtOG2TEt7G7sTK2GV7W0AchvwHANuxDEy7jr2xdz6sp2V1izMB2DqquRVnlnmcuMQ226unhMVlyo3HSZNKi5l1+JkTRyQt9EHkgev+h+6xydlQTfghvea2jLgftEi4YCRnz1kQirDZd7GOCEsKNDE905bA7XNOLiQN6GMTznAen87PS3bsYv0yDb52zwXHg1vVXOADB9posXuSGX9vFAD2Qi3yZa4anFa5mcIBLc=
*/