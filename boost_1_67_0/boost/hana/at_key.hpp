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
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
*/