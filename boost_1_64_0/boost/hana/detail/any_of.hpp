/*!
@file
Defines `boost::hana::detail::any_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_ANY_OF_HPP
#define BOOST_HANA_DETAIL_ANY_OF_HPP

#include <boost/hana/config.hpp>

#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    std::false_type expand(...);

    template <template <typename ...> class Predicate, typename ...T>
    decltype(expand(
        typename std::enable_if<!Predicate<T>::value, void*>::type{}...
    )) any_of_impl(int);

    template <template <typename ...> class Predicate, typename ...T>
    std::true_type any_of_impl(...);

    //! @ingroup group-details
    //! Returns whether the `Predicate` is satisfied by any of the `T...`.
    //!
    //! This metafunction will short-circuit the evaluation at the first
    //! type satisfying the predicate, if such a type exists.
    //!
    //!
    //! @note
    //! The implementation technique used here was originally shown to
    //! me by Eric Fiselier. All credits where due.
    template <template <typename ...> class Predicate, typename ...T>
    struct any_of
        : decltype(any_of_impl<Predicate, T...>(int{}))
    { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_ANY_OF_HPP

/* any_of.hpp
+glzJaszdfIm6ad2v37HnWR+6TBHtnqRdZTlwCzI7GPvyWdxHsyJbF+h4kekn0OQQbIct7IdpJ8wnkNikVp/SAZhPIe9fZOnKwuC8bNUzBzVV1kozIXs/O8R4cqiYe5kt0cPl7wkwJzJvB80nqYsBeZANrj2TH/pGYxn+9OABTbKcrVniYjc90T6MtS4hrCrPZcqM8D4WTYMRCtUlmDeZId3RYxWFgkrSRa7s8dWqR1Wk6zqx9i/lCXDGn6z8G928acnv8psYRXo3MDTDZorsx8mvxP4Zu0dh9eX+cECeTcXOw6SzMMCyNZfQ3nqXQerw3OIayDn0mFVyYa0f7ZWWYF2LtPv3k+Slxi8X8jMh3vJ/CJhwWQmg9/9rSwJ5kd2qsZnO2UZMH6WGYfer5XZDjeufVOjvyfJ/GCcl24NSzlLX2D8nB77XCsqi4FxJhpd72cl+w7j/btzfO42yS6MM9E98rW8X9JgvmS7AuaOl+zCrDi7cVmyY/na/Q6HlzFTZjYCP1uQjWra94IyX5gr2Ym5rT7L3sJ8yGouS34ttcOaUD6TP9tWkxpgXnQuKLXcDKkBZs31bWk1WGqAmZGdqTdY9q8A5sjvz883dsluxn7/c+VfZ7y3blgLmR/Mi2z30x+/f8eElSV7tmn3WMkZzIOsYIGv9CwdZka2PiPZTTKoWZOoS72UZcPqkC07G5QvNYzEd1qyETNSmkoNsBJkYZG3WimLggWSvRlusU4yCLMnO7cjSDKfol3zWOn5H2R+MGeyZr37dFaWA+P6Hof99U5mC3Mk22paubbMD+ZAlmBf319qH2X8LAN3JQcrc4dVIQt1mvRWWaRmK1+OlBoSYTXINjVLOywzgnENc4b1lH5ma7ajWKUQqV17ziJ3LpdUlgezIpvk8Gax1A7jnNncuGZQ5jQaPz+Q/av5z+1kN2HlyFpU/H2bZAKm3iFfe7A0IWO2ZAJW6JsFfjNv8787KouGGehcry+zL8s+wNzI2oddKiT7AHMke3rx2V5lqdr9PDI3fH8XwErTuSEjPcYpO6edix7T95b0GuZF595mh9kpMxmDz3Ayc+9mkgl3mANZn3m5Q5QFwVzJHk5fX0GyBLMlu7Pqzn5lMbASZPPHr1moLB6mfs6p+jWD606nyY7B1H/37mtDmryuv1Z2BVaDbH+J+oMlE3H4DCAbEPb+D2UhMGeyN/nVpYYomBVZiUf/MJcaYKXJ5jdMbSy7ArMku7SwzD5lyTAnsooPan9/T2jPUr/XXxdkfjAbsvb53eW99DhOvmPCMM4BbarLrmj3ezfg1TNlhrF4n5EV+cOjiewKzI5syfzXftIzWFmysItTDNIzGD/LtOJ9lsquwFzpXMm/W/oqS4CVIhuR2am59AzmSRZo7yg7dlS7n9OoRpKlbBjPKPTk2OLK8mGOZCmVPWOUmY0zfha3X34pIfsAK8699m4cJT2D1aVzn7ddc5PaYeZk9Vq8KqksDsZ9McydmKgsSTt3tNrqYrIPMDeyOoO2d1aWoZ3bZ/39O18OzIXMMW5gJ2WvtPqupVTroszkJ3yG07nCq1f0lNphfL8Ji+5UVRYEK0+WMDcsXPICsyBzfjZhsewYzIcsYtsPKdIX7X7Pshtck77AeH7B69s8UZYO4xmNqj78uNQ33viaP9hkyhwMsFpkU0ZemaosFMZZKpi25ozUB+P9Sz2UaCpzh3Ht/qNOS84SYNyz0YfNbytLhQWSefbsOE1ZLqwS2bTOv3ops5xgvCutti9NVeYEq0LnzGys9ygLh1mT/dOt4WKpDxZANmvE7CRliTDu50if/COy0zBLshVH39eU+mDlyP522fNWsgvjXru9PhQhO60=
*/