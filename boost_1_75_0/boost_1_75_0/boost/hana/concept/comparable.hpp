/*!
@file
Defines `boost::hana::Comparable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMPARABLE_HPP
#define BOOST_HANA_CONCEPT_COMPARABLE_HPP

#include <boost/hana/fwd/concept/comparable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Comparable
        : hana::integral_constant<bool,
            !is_default<equal_impl<typename tag_of<T>::type,
                                   typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_COMPARABLE_HPP

/* comparable.hpp
4D5ljO7g6HGeG2WCrRrkBomU2j7p8kxHj6+Q4lc8NgJX0ApS6eHbLUiWqUTv7NeVNHazguma+T/VkzwfCQOnIFTsUj31mG4jT3eBvQ9VGY7PJnbHOIpJjNSPZ5cVDUBlZydTaHFVsuGJZdILbPkpgdYhjuEpCJEI4+88P2R7zO7nyWd8P1Af++GHggF4tL6eoIceX4b0xQf6wMnoQF92Whvozz5PAz0AnFsLHt4GuQ51Cdy7chWMJYoouAAye40sce4Q/7zRc9GyGcCoT9a5UZ/hTpYyV3fQe3sOurNn8QNJjoT4VGOiisNkwWYMR0nrBbiHcf0O+1mFxlPgft4WzhFEPC4Cq1HPN/uwW6Euamm91qypMc3aFNKatf85ZIGn5E+Fhk/NfY1Gn0k+IPQ1mvHXqDbaw1Px+JPpzb7JMsvxjcPLSA+OLObBnMER8gFzML76gAH3/+iU6GbPhHHOewFIsb9dPRBDioZIvQ+wqgpe72K0PTemWcQdgf52r21CwDt5KkziVRhiO8fD8y0PUxBb9cAQwv7L/VFoszVowyxYE7WxgZm9k/vb5A5BA2H9ThB3xYD46n4OoimBg/BObmBxUQB87e9sAJfHAHhZA4Ae4vUGmIWmtIs1P4ORq/ZXn8EjFHyT4BdQ5Rub1a4j8uJnEZEWe19e0OQ1liEW30TQ9qPFblbMy+QlTmlWK15wAtm9fp9e5kE2Xytz
*/