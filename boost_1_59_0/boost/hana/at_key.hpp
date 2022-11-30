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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_AT_KEY_HPP

/* at_key.hpp
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
*/