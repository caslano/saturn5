/*!
@file
Defines `boost::hana::all`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ALL_HPP
#define BOOST_HANA_ALL_HPP

#include <boost/hana/fwd/all.hpp>

#include <boost/hana/all_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto all_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using All = BOOST_HANA_DISPATCH_IF(all_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::all(xs) requires 'xs' to be a Searchable");
    #endif

        return All::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct all_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::all_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ALL_HPP

/* all.hpp
32ggeyCv72miwpBgCY2BzwFfjHBqCVupSjEW431jefsM8YSQviNlBET3MuSSWCFn9VrkEni+s0JdDWTv1TAim0b+LnCy/hZENP3WFZmjF8cTyf6H78yq3QGc9yUsICzQjwHSVyBz5c/zIvOAavHwfg7x8UXMCPOz2fXLJeKvRxkWaPwJk6n3vdEbYjS1ba5PZilkwZAlCfYq9p9+0HOcKGYMlDAJ2RrCqNCPsaSY1rQYxUMELYSR0aHCsmZamsMF5YTnpAdKLYS45UK1hktDBMJf7kYKMBaMXOdLSmkLZqqt1DTxhvNl9wK4Sc40UGbSqh9gR2JSmv20HHzk0yXoKHnENlRkS32yn48vZqVNTDHD5d+6K/35/W1pOzf5wi0zon9s/lXU9aNC+LHOH/wLDkMvPtTTJSFDk5752RrtRz6x+bJXcft+9m+kTtA/5KHa8BZq7berC39ooqHc/+MToazkRuBl7QfujnQrRzPRGdq4TsZ3lBFoX5OEbeiOZxn2kTj3Eq4oY49iQ/iEtfHhx39oza8RYZZnsBJG2xjHkpLgoRWHTE1vvB6q/XGEi82aNVMD/OVWfBR0olIQbyqBChd+3fQHgT6RX8EKbKV1+B2+3wfnRPXA67e4MCnQTfuVDV6+SfgZmjZ/sGOaCfpgycABn7tJhWRNqp+sbPlC4XpHaxQNGJYASDvpsb62ufajCulBWnYrr/PB6fp0
*/