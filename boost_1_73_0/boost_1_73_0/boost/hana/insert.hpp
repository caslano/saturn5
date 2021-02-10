/*!
@file
Defines `boost::hana::insert`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INSERT_HPP
#define BOOST_HANA_INSERT_HPP

#include <boost/hana/fwd/insert.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take_front.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Set, typename ...Args>
    constexpr decltype(auto) insert_t::operator()(Set&& set, Args&& ...args) const {
        return insert_impl<typename hana::tag_of<Set>::type>::apply(
            static_cast<Set&&>(set),
            static_cast<Args&&>(args)...
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct insert_impl<T, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct insert_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename N, typename Element>
        static constexpr auto apply(Xs&& xs, N const& n, Element&& e) {
            return hana::concat(hana::append(hana::take_front(xs, n),
                                             static_cast<Element&&>(e)),
                                hana::drop_front(xs, n));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INSERT_HPP

/* insert.hpp
SqONdSKesneh2a/UbwXsZ89EL7hQkQqGMUmQxcq+KtNEIVGxiAa1PXHTTauiJt3FWMRhUwxFfGCwJIM5b3Yu2md+p9sZKcUuXsuZWm+L1/AlM9QGnPOkwDqoiLjYxkg2iaO8IgSMORNgXOEvemzCeF0GvI52clrMojmkQc4pVdx1WJQ+1hpmz6ok3awAExthIpETABT8DjTXHr8eQlvgr5nDdaVoNpXpJCT5KAtVAvvUZyUzXSuGF+c8nGdhrg7mmD9Qdt2gPGvqsKZfiFIv6nflHer41MocgyOWtTIVHRYBNVVSIfv7jDPhqibKcvNEfl8oOFYlAwoHKSRyFMyif6AcQvsFXW1JmNp1WXZyorZBSU62ayCcFj+pyY8B/Lb+v0nFDWwaBBSWqT9oNylVpPe7foamrEH7otc8EwixYNJISupUzrt75r3qFCobpkCxiKtzK0WSzJwnH99fw9FFpUEhIpcToZQPvuvmK05iZQtbPUvm3BTnp0x9PWPGNHR7dP9zWnwKMoUeFj4/7w1a7V6/3a0ANuj1Rvij+RT9xS47f2tTIdcVLPDYNV4xzxvNckX+LHuOV2e4KadXs9K6P17WgsDimmkOOWtpOUKA6BspXUGxMsWVHtmkmqKUaZ5LOmFsvq4lYGTTFTUE
*/