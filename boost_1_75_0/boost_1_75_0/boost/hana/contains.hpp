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
3H1qZOfOi12dtx70Qn7CE8QBsRux+VAcYFZljSTuqPudZtpUvqBsV5ykTjtxfytwlb+fdi1Qjig610ucmlO8pvoq/rYJ4/Tznnr4gBp9Ob3e85B+l04rk4soEz/7z9TlzG0ni7TDtE8AzeQP1tHQ+YmXrPxDCXRMKsSJCubTMzGnFMB5ix3gYAWK0WA63IEXpJLVGJory3pcyOE1TV9Fxq+eXHRMVkzssLcviQ8lMi3c4+DuoXi1jyulbXhgLajco86gwmpWal5EeQBoj0x/lCS5q/xKm3C/isDMLFw8INwnPBhDDCGwnjgDc55juuXgP2VKe/J7fvYU9BT3FIELwUpkKPYuJVSoD4r4KR30Afhu4/FL118f7zULLkun75Ou9ku96AOV9iDwmaP7xWvkM1w8HrJ4f54/Gc6ZQ/jwFSRVc+VUdnVUKd7znDtZY75wf+1kxWbeuXhpD3CtdG7IFV/Vz/LawA5wdcD89Ots/pvpt0lPTvKcrHGBvPuFirOuOovuapEFmqMY/EGWQbai+SUOyIxtHUlPEA8S23K6ZpoAgR+VMyi3AojRVZSMoF/dF9oaHFNO09HGPqhwX/aJsjWSfHYvGvIBwGbujRb3SbEM5soP3cmzuPDcYr5pMnPtHEb4dE5ICRztHD/qIZ8t9B+1HqPrOjx3OlJ2AsD8silwmc70O8tLjTHkzV/HPLrBB5iPDybIHFChUDff
*/