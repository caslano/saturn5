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
jhey4XQbC0kiJ0Dvfh8ODUU0oDuWst8vsvXe/Y7EIahS63QsK8QngIlxv8fZi3YNGde+PpIAHkCQ//Ftku7NDd9Kk7S2L7w9dg65bTephevtoylMl7YyiquXN9rtZ5kvsICAZ7eFWbkhzjAwxsGikCVpcjbHNBTkzf+y97+r2M/MMXt0o85E43AzE8tKJXO9HouaNSZldmS9OWN9eCqlUebmhxXJJ/y5vXFNFmTlhv9LAmKSa05voaHJAWqyGeZw4APwMME0+2YzUKFpZSOMxdiA6jpA5C+FxAsoeF0uqHG204fe9ryTYx3ol0fy2hAR8I1fW5oU8YV5pgqMVSvMxc/bZfHCm8TayuWmytRkXPYtVHE33frbaM0SMabrZMsIxkl+Oxqu1MhcjTgypSUd/KSCQyJBiYgV6jAYrJd9WmuJYORGilY2qrVEZLSgGkrsBt4I0Mm+OVsgknPZ9oBja8OYyAAMGCSEgxkipnMj07brO5eeBw6kgziZ8H7FYAe7/M2S7L3cSM0Ld+8+Vh/G9D2eVJs3vO9rbMHdx1uo+HV3emXmmpMIC7v4bQ==
*/