/*!
@file
Defines `boost::hana::less_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LESS_EQUAL_HPP
#define BOOST_HANA_LESS_EQUAL_HPP

#include <boost/hana/fwd/less_equal.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/less.hpp>
#include <boost/hana/not.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto less_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using LessEqual = BOOST_HANA_DISPATCH_IF(
            decltype(less_equal_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::less_equal(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::less_equal(x, y) requires 'y' to be Orderable");
    #endif

        return LessEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct less_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_(hana::less(static_cast<Y&&>(y),
                                         static_cast<X&&>(x)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct less_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less_equal(hana::to<C>(static_cast<X&&>(x)),
                                    hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LESS_EQUAL_HPP

/* less_equal.hpp
2IVSY3aSzEqudqZNwIMyvuevVHdKcZ1wpmb6/aqf92TtdqzaWAj23eVCIABe4CawlmXGrwMnScVvIhJHJo0aJRNL2/q2C4gwIHWU8mybZiU8jJ0CPOm95X899MuKxtLR0hinjGrAg2mrl0REu6NUTqEcYkFYVzi1h7FzQ4vzVSvxf9yh7OaxIIx/2U59/zqiG9gD1wvEUhA3LR3rWyY3P8gk+nPAZ4nATbsetCiuGEIWvXpKM/DeE9N3wZrxjiyIovAwRNWoIy/FrnrPmuHf5FyfW2TkrDmpmmG5y3J+NkYsnj/dY4XIFVbcJib0FmU1opQP2hOgKSQdf590rxtdr4eAeZ0XGhLb6w7W1tZgEwlqPZXjNDFfQYqGDRLshuGX2Kt3I+IUXAbeDk88/0fG3dtWi0xO90e1Iux2yNmXWGHqGoRyhmPM9vz+rCxWahKMQEm2hB8pm4vaDH8H27R/I05DCeAgecZ3ufNCa/o0y/CRsgyfGdGww2VOsTtD171rWVMHyfBk9Hvy1niX8838GaIB4sTq0/omXIiHJw3TztP1hFRxpqWqG9wNhw==
*/