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
hFQUdDZlMmZDqXEyaid/S7hwzvxCuA27R9mvKT8VQN5Ng2zzjfr7mlpRd1OmmiGQpg8kmW0o2yYe1tzq3q20aovpAWVrryMeFNQ4EYpKeuhSq6PJOr95Fra7kw360pIXTVhBRWuj8CTELT8/O/ryxwjdgIXHmEHQ31FEaP8atLsMM/yKoya+bwh1lA2JuzOyN9zS2spt2UoYnf6Frw3nn9gqOOKut7TA6exTGlRjeXfna5pRfwBQSwMECgAAAAgALWdKUm3l45A9HwAAA4UAAB4ACQBjdXJsLW1hc3Rlci9saWIvdnRscy9tYmVkdGxzLmNVVAUAAbZIJGDlPWt327aS3/0rkNwTV3JlW3bSbK+dpFeR5URbW/KR5DbZNoeHJiGLG4rkkpQf9yb723dmAJAgCerhpml2V/c2lojXYGYwmBfA/Z0v99liO2zlx6L/LPjAX2pxEYf/yZ3UXNuyPjHxP2j1O/xdNcg+y5t8sppsdZNPrEFNLDnKC/xuWasG+h1hw3/2seXvFn6FJ9AMW3bD6D72rmcpa3Sb7LB9cMh24c/hQYud2IHHfTZOeXDF4+sWe+HSk3/M7Lu7vYS/ajGeMtvfM/bTpn4OoJ+3obf7NmTdmR1AH7PQm4V7Dvz4x/Xc9vw9J5y/ksBM
*/