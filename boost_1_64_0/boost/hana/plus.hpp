/*!
@file
Defines `boost::hana::plus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PLUS_HPP
#define BOOST_HANA_PLUS_HPP

#include <boost/hana/fwd/plus.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/monoid.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) plus_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Plus = BOOST_HANA_DISPATCH_IF(decltype(plus_impl<T, U>{}),
            hana::Monoid<T>::value &&
            hana::Monoid<U>::value &&
            !is_default<plus_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monoid<T>::value,
        "hana::plus(x, y) requires 'x' to be a Monoid");

        static_assert(hana::Monoid<U>::value,
        "hana::plus(x, y) requires 'y' to be a Monoid");

        static_assert(!is_default<plus_impl<T, U>>::value,
        "hana::plus(x, y) requires 'x' and 'y' to be embeddable "
        "in a common Monoid");
    #endif

        return Plus::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct plus_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct plus_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Monoid, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::plus(hana::to<C>(static_cast<X&&>(x)),
                              hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for non-boolean arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct plus_impl<T, T, when<
        std::is_arithmetic<T>::value &&
        !std::is_same<T, bool>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) + static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Monoid
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_plus {
            static constexpr auto value = hana::plus(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct plus_impl<C, C, when<
        hana::Constant<C>::value &&
        Monoid<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_plus<C, X, Y>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PLUS_HPP

/* plus.hpp
fRU3SGXlztom00MvVqPxEUfI41Gu4u68IZaYXdc2+LF5baoyG8rx5MPfhq4VcznwTNKvFnNIatOzTS1oXAjxjXqU2mi8KOFjhTW1LvvScj4cw5MPD+fz1hvM7OLrAlJgDz5+hY4h7tI2TZsKO7+/nbRngCyZFyprDOEP7ofRPbuEk8hwV77hDPunarpqaKzYgJ126hewHox7/bmNDH8vpD2a8xlEa50VXdULqDZiSLD0Bsj29+GGs9guZauLFh8twBa4iGhes89o4/w4ldZrB9sXQz2Is6BjZZHuTEoHwawqdakjXXY2uqeldE1RNTkUO5Fu+Wx0L5rXV+g60zbSnZzT3TLKxpzu9n1X2r5RFaEyk96M/BdQPsFgVkVTNkNs4NHSC4tb+tkUe7TEooEgUgTs0dmwYJlGum+ndG0LLQ70JYHunmelW7rRrD5rO5UNge7kAh3J1jdK9y2lTVOb8iisa/AA4uWo76PxorhCN0rnj+wLfNDQ38XRSnWCnPZ2ONVLLESD83n3gKYqt5Gs0rqquuibctDCoywApyFbxQ7F7hEklyZ9rYRWZTFoUxNy4qJ99sL82+M8bl8pXde2GPfRczDQc3DoU5HuCZzuRCFzidkuA2zuVkrlQyXG+Z60WTtcaKhwbUX73RH42STbJrRYZKaue1tLD/zoXtbOCvu4eFb+4kYz+2sF9W9eNDR2mYcRcNRHgUomvK594/Q+1/Y5FmSniVd/NmBKmXlfL8FknBun31RCMLVFPX1TZ3pGrmnT6bjFbi5cx3Aq4ddiPVRY9zn0cu7Qnmwg8KkpziT/dly+eTLndVxjR+27ohAomSB17tCdkpdXVvS2bNtBZtQX74fCoh8gzHp8APCvTdunvTaZ3ppuMsMPhC5V1kVBc2fvNPQADwpqGFItelPLOQbg6qMTn9gGQnQvWzSx17HfD4x755DUm4u27OrCmlbI6en5iHGjveQUpx+camWoVdcKHV+jF4kFyStJ3YXAbaqUhUZLoQpgCt7bMEFp9NFM38Sed5PZ/l/KaqgKncbp5PDWk/7u5Qmti5mTZbbOau+75ulJ1uH7W039v2lad12ZdqgwAM5siIl6rG4Rac/cdI5VWTfDkDlrznko1Fgz6Q2eN8P2NpDIjeqNiHRkz7nJ0cHrV8Qz9qazeIttCRG49jMee///669f37GNX03aCJm/kYPKXPyaf4PT//KvYD4YN3NtXFs78/CHi2Puz22PnfUPSqvLBqyRpREbA7ZjE17JZ//ocVYW8FC+GNLJAZVhlnz1j/8cs+R59z8Ss4SwWb79x4jN8iDCbHF0Pwh1BkwVasuFRzySdVgYBJNM5IW2vMjXxT0RJqycpTlWTmVXVhntL/64gCfp854K2ku7OhmOQ8RZejrxdQgea+5dc81jZwTMw2deI2BPhsqu6NMifuTJbhjS9Ev49BWQr9m7s/RLUjrqWIrphPe4rE+aVd+mkH7liLkW0JrWRhNDoruWz79nxL6j9BuOdJW9p0MnAoZXSL8J4csZBXbQ+0w0N+N4cozXzWP6CEdJvG4R0x3yFNq1Wk15t6S8NlvVniH16VaU19llXS7buw8rvO15wIMLoiilNz49XuqofMCPQx0et2xKH8by3er4bahtn/E4UkXWtnkmG+dfOdF81uf1VnbKtYm+/ed8OiDRTt6L+vF5n+b0s2tOPbumbJeZfqL5gs+Xq5zPFyN/1p4vhXKtLdcC7CHV8eVZHcvLCkBwU/5XpnytwdeDcwUMxGf7Oe3nDmAos9aA1GHcDHq5M4C7uUfAo3yuL+fx4dZsARzDkHaekOZGEAUo/bwhfbDDbXj6+UK66TKUn3ifP6QXYBPLXiA=
*/