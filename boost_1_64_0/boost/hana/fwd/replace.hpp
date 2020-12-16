/*!
@file
Forward declares `boost::hana::replace`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLACE_HPP
#define BOOST_HANA_FWD_REPLACE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Replace all the elements of a structure that compare equal
    //! to some `value` with some new fixed value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `U` a type that can be compared with `T`,
    //! the signature is
    //! \f$
    //!     \mathtt{replace} : F(T) \times U \times T \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to replace elements of.
    //!
    //! @param oldval
    //! An object compared with each element of the structure. Elements
    //! of the structure that compare equal to `oldval` are replaced
    //! by `newval` in the new structure.
    //!
    //! @param newval
    //! A value by which every element `x` of the structure that compares
    //! equal to `oldval` is replaced.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replace.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto replace = [](auto&& xs, auto&& oldval, auto&& newval) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct replace_impl : replace_impl<Xs, when<true>> { };

    struct replace_t {
        template <typename Xs, typename OldVal, typename NewVal>
        constexpr auto operator()(Xs&& xs, OldVal&& oldval, NewVal&& newval) const;
    };

    constexpr replace_t replace{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REPLACE_HPP

/* replace.hpp
/P+zCEqr44cxQGHUBetGg+IUbVX383da1/8me5hjb0PsKGdRYByb0iqledMBRbAn5oUu8fvPJSwHjCYasAJzAAezf+Ue7jeKuQT4lB9dmhldivhXsZaBcyr0inW7meohhd+A2hNENDuKxchQC4MJsBrnmMI9wTVjkmx31BNwsQ6zkaflcrxgM/SoFAntWdGb5MSDvqRhmFgCKdPqbmSSrPG7WLmU6C5TOuv6DxtrUPzupfBaUAtqieEUs3GU6RuuB7PFFArm6cF8MZaC+XrQIkZQ8BwOesRAPgQd0yZ1ivF/IVd2TRc6aGvzewZ9t7f9PZ++F7T6vbQogd+Gz4hA9roVuZZAb9um0mHkZTo9KJICGbW9QQJADpPwV+3pWoVX3IJfd4Rm8BRX38e0eZ7I/K2ZpIFDQDw6FG4ZVWaBRdz64MoMk7/bdBF6S18IlFeL0+wtfQ7uaqi2jvtEnTU4fH1kZJnvGuwMbG+rTWpDaVEUvwYT/a1ve/zZw6Ax3nNeVHxCBuQqrDXhzMG8MLXF/1uZEychaP9gNNsPD4QMC5W5FtVZhxYqN3A+j4Fkh1/gUvhyyRqSOXHz9WKQ9FT4yv7fDYR86IW4+ubL+hacur7aXfENXhCrSoMz28TVyDHFaoPBKddlPyXaT1VOL+TFB5T0ic84SFdVDcQStPw7b3LL1ZHsWVg/b6N/r1T9u5TO/+NK8V1j9O+du+MalSFbY09s1Cg06AKfT7UGIgZD/AcvJgtUU6iQv+yJb4r9rJoS3/+PxA/g/l1xVc2XdSxoq/9r4/q/OqLXWFppfSKu//2odGpCpQvOqtKK3jSUoirsfHV5h5pJRboHmsmyuPn473xx5xvtEA7RXvccIjj+kUGxxt9Hq1GVxmS5DlCmG1Co6PkNpbmWZL1wLjQWbU6Ibqs8Y39d3FDGyYn8daQ/vfAHK3VZEcXyRwULcWYVoA/tgu+Q+/esxAzsX9zv8BVzG9FCDW1c+Hp8G+Wd6fY0Jo6eD2F6ng2LasOCjWZ/SrAxKdA1uCLf5M8IrigwLWudmir5wTQIgdwsIZO8jpVrgPrrPI/fpnidLVLlsDK6jPdpxO0E4OGjXnE7DuJ25ujsjkzrFQ8/oNidPyKWz/OOfmywOw9ujrE73zPYnbePG2zKWmJ1SkITE9icb7jEtojB5mgGjMB0yebc/qKRf1w0kBkNIO5z8Fik+W2CDmWD4nECD4G1mdh0Otbm/g911uYevGBn+CAXGKqHaPRfufFuXP9R4v5hRSQx3LuxVXmdG/I6PwgYVPeEzpn8YAeCQ/VghvgOBXP1YKZYTsFhejBLaBQcjiCLU3j/VNoeUuHx9eJMvgLxMDoqpt+RhWimRGuA8KteaVO/g8/vn94n5QVZdJMRKqiK59Zqk7ELMnwoQtcO/3JFBfpAd9S7omelTCTOb1RamjX3EhYfjwayR0ET1FZ1B4J84OwWSS8wlkjEXbHGB/PtnPkL0azUH1f08eqRe4UOcWUlonGytnJKMBq1TTiO0Cq3WP3bZuOCe5HXI95D97tE8YOMN8Ue0QVApAJbD/Zj5RGz5XG33IGsHcUWGbibGNHe3w6xwlNGFDX0RUR5xIp9SrVJ96DtEdciKoQUvJAYY3ovkofQWXymp4a2xpnJlm2dDhGU3wsADEdZeMMjW9nG/c84oOat3U/uRb0uy7GGJ9unhydn4CSatkkn1UfR23CZ3RUuy5D6Sj/mlBkqpUdqIj3ZHO/F2st6ZRVQ6q2wSNWQa2Uu6bF6TKNxSlWPs61zGvWzLb1n2uyURPqfK+l/fnxyRW/fAUuq+1ff42GFAfLPGRoJzKGjl+ylvfnkW06ZbHFonzGT/Fcx5vI=
*/