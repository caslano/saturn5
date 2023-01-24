/*!
@file
Defines `boost::hana::at_key`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AT_KEY_HPP
#define BOOST_HANA_AT_KEY_HPP

#include <boost/hana/fwd/at_key.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/at.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/find.hpp>
#include <boost/hana/find_if.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/functional/on.hpp>
#include <boost/hana/index_if.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/second.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Key>
    constexpr decltype(auto) at_key_t::operator()(Xs&& xs, Key const& key) const {
        using S = typename hana::tag_of<Xs>::type;
        using AtKey = BOOST_HANA_DISPATCH_IF(at_key_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::at_key(xs, key) requires 'xs' to be Searchable");
    #endif

        return AtKey::apply(static_cast<Xs&&>(xs), key);
    }
    //! @endcond

    template <typename S, bool condition>
    struct at_key_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Key>
        static constexpr auto apply(Xs&& xs, Key const& key) {
            return hana::find(static_cast<Xs&&>(xs), key).value();
        }
    };

    namespace at_key_detail {
        template <typename T>
        struct equal_to {
            T const& t;
            template <typename U>
            constexpr auto operator()(U const& u) const {
                return hana::equal(t, u);
            }
        };
    }

    template <typename S>
    struct at_key_impl<S, when<hana::Sequence<S>::value>> {
        template <typename Xs, typename Key>
        static constexpr decltype(auto) apply(Xs&& xs, Key const& key) {
            using Result = decltype(hana::index_if(
                static_cast<Xs&&>(xs), at_key_detail::equal_to<Key>{key}));

            return hana::at(static_cast<Xs&&>(xs), Result{}.value());
        }
    };

    template <typename S>
    struct at_key_impl<S, when<hana::Struct<S>::value>> {
        template <typename X, typename Key>
        static constexpr decltype(auto) apply(X&& x, Key const& key) {
            auto accessor = hana::second(*hana::find_if(hana::accessors<S>(),
                hana::equal.to(key) ^hana::on^ hana::first
            ));
            return accessor(static_cast<X&&>(x));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AT_KEY_HPP

/* at_key.hpp
aptD0od4zUnnokmqHcjHY/Y3V0qiGvLqnDrNirnQOhvxiEt7pjNsJksTvJ9U8rgMI7nUe94NFUVB5TEh08TIYdz7qwIN5kkR3HWEH9jfFeV/fNEINjTAMgi4NqTsxCpiK1o9h8ox5X9QZn7TOOmkXpeGR1vzzpPuKp3tw41kHhPR/uoU1DiLpg3j45jTcoxA+F2+pIlqgrUmcslEaL9Q0qGbMq4cpCpV3HHw5Ber88o7NJN4LbbFiKKRhQCTOuO9D0PCGB2XMZ7Sm70Nfz6SBgJ3lHCj2OQ55An/OGGPe/ZHG2KLNy82pH5kmjup07vQ33/SPRvU2s/nWkmTj6okFxvIvA0IQ3HM33OTiAipgKdmPqM4grq0qO1R9BgXw8kGnUvrNSoJx9/8KteWjg5/FZhL8T3o/hnvZ5Ks9VaI82sO5414eoWZAd2NSXrqSKea5YfN55BlRr9AWs0Xr7ZZbdbBHT3nfkx6ToWCnpZ6Or+9gYHN89C59KVujzXR/WHIx7knPvCTjbAAMcs59DkAL74d3zNtnqKXtjwdqHQM/G2u4vGnBfENet63bh7vPhy/GvV88xDzeOsGcdQqfQ7FCM0HKZY+h9+Ib8gIccx3DbCKD54nx05UvLzIKWF5eIUe7E85NkKAlDdnMUOOSbFauGU+GN2an9/F0E+E1/DkHGKtdQfwfawLE3xzVzZX87c8NCkvAXBL89AmJtJ7
*/