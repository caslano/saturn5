/*!
@file
Defines `boost::hana::contains` and `boost::hana::in`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONTAINS_HPP
#define BOOST_HANA_CONTAINS_HPP

#include <boost/hana/fwd/contains.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Key>
    constexpr auto contains_t::operator()(Xs&& xs, Key&& key) const {
        using S = typename hana::tag_of<Xs>::type;
        using Contains = BOOST_HANA_DISPATCH_IF(contains_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::contains(xs, key) requires 'xs' to be a Searchable");
    #endif

        return Contains::apply(static_cast<Xs&&>(xs),
                               static_cast<Key&&>(key));
    }
    //! @endcond

    template <typename S, bool condition>
    struct contains_impl<S, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::any_of(static_cast<Xs&&>(xs),
                    hana::equal.to(static_cast<X&&>(x)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONTAINS_HPP

/* contains.hpp
khGP6YyM4s1xNky5TrwpGgwloqpUoFmaki+040znsBn0C3o82gZjRMwNnbQUmkJdJnI0txF5JC9xpgQGQh5wUySRZg8yETFlN9vMJyEKTi3BlcdKM8UbgRQIBkq1PrT7JRgGmmsPTtqDVu94ACe1o6Nad3AKvX2odU/J2Zd2t4Ha4RhMAbsaK6YxuAI+GqecRUXM1zuqzioXYZpFDEpUPF8zk40rScnBhRiVFXPBIve43/QPPjUbg06/DGtrT4+HSXM5AK4762HQOmrWGn3/sNdvf7V+Jqut2h9N/zBf91tlbPmbwgMs9HDS7n7YWuDhqFdv9vvkofwwge8O76wCTFjZHZtEsSCqJHt0O7eAggv/4HjQ/OoPoNjkj7DoV75xVln6SPClyOeDKxmiAp4O3qp1G50mxhTYP85MQUc4Ekyq/RxcKsN/qLD3Cj5WXJh4wcKIjaS6poXqup0BaaAN3G2yM6aYJkO2DXNSQtuIDbNzKyQ0FxliUXkXERYgMNraFEl1jw8Gi1S05eThsa8CpXBuXPI0BW2knUPppDEt8TgKplMJe/kgz79CcbQJDA8fcLeeV2yYxfAbYuh0dhwH+YC6ZSC3n9JXMJk3iXsheVR2vjlULwMcLQFm3YWIT4auzWwdNP+Xydi9B6Ds
*/