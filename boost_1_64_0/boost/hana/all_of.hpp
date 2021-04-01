/*!
@file
Defines `boost::hana::all_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ALL_OF_HPP
#define BOOST_HANA_ALL_OF_HPP

#include <boost/hana/fwd/all_of.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto all_of_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using AllOf = BOOST_HANA_DISPATCH_IF(all_of_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::all_of(xs, pred) requires 'xs' to be a Searchable");
    #endif

        return AllOf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct all_of_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::not_(hana::any_of(static_cast<Xs&&>(xs),
                    hana::compose(hana::not_, static_cast<Pred&&>(pred))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ALL_OF_HPP

/* all_of.hpp
OiUt2aZOlaKTYIdSj/yRKAdZe2L1AyDpiZ0cbtueh21EUCKbjYMhaKA1A6jffmQxO8d+fs61q/zeXWYs/+ilCbjoY4mi5llGaWD+3Noukoqd3aDzIP9WsFUubqcU+9g+GHp4/1v1vBsZ7A6+WBOMEplnoG6egRzGqy86XrpFUe/8igpfocod4VGIoDFA4Sfg6+J9ebRpz4+4KzPtPXDl/SB1i6XdxftyI84J1KGV4XrLlhwApRcWa6Hs4US7HDaIRigfGwAhg/JXVpzBpY3CSvxVUrLzYz3bhu0aXm2mrvPg7/r5dIUdZPFN0ubLTr0zVh6PQQDmldnJ2o/hCYriiy3f8WaxDei1i6TRWQfEdRz0a6puFs1DoCoQ6U53bsZ4ys5I28WvrlGyVvphJzk5E3FiFcbTqiKWkLSxzetfzPeil0vQLiT6+NDch155ECpK/KkRXEgYgDOrJK2GMgAbp5a6YbUm2kbGgEN728aa6VIlUCie1QmANOyl/q/K9qTIuTcBVxyKY7wWg6AXgg53rKcP0FUwHZN+0xtzQyAGzOK4DuKD5Nqhu0RkTA==
*/