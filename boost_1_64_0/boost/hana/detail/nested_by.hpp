/*!
@file
Defines `boost::hana::detail::nested_by`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_BY_HPP
#define BOOST_HANA_DETAIL_NESTED_BY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>

#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename Predicate, typename Object>
    constexpr decltype(auto) nested_by_t<Algorithm>::
    operator()(Predicate&& predicate, Object&& object) const {
        return Algorithm{}(static_cast<Object&&>(object),
                           static_cast<Predicate&&>(predicate));
    }

    template <typename Algorithm>
    template <typename Predicate>
    constexpr decltype(auto)
    nested_by_t<Algorithm>::operator()(Predicate&& predicate) const {
        return hana::partial(hana::flip(Algorithm{}),
                             static_cast<Predicate&&>(predicate));
    }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_BY_HPP

/* nested_by.hpp
tJqjLfgA+kAQquvQpZjl7JtbKCULCIaNrAWmamTA2Y+dDPHCwYH31RwTzzyYZsRvEtsqVASQrlg2aEqsfqlhHch+ylf47w4stXfQXI99TXCeOALiyVjeFTfbOOucxHeM2KjICjB+gWfFf9x8Ab6T0lriFughN5ZkAwLeUUXbIvW0r+5I7+/67GucrRKGI8/RSmRkbSlUxAiRlunXoMWWt5pfrQp5j2+OpAr/MtBlQH9alR3Ud9ltmi8xMIvz7qsRlVeyNzkOWxaB7TWCHujzov0leXOSh+uFE6Crfnhx2WjVWFHKzjktopoNZuaoWUTqLD7QgNR1EW6sJ80m/NvPO810MtB0vkRtAjf6QwKRiZasi4Th8tyKvWCQfJcEXXv1rtHvC4KJ2xGh0FGHHSieI2xxjYRJlxwZ5fTOIYIepnLhnh1CxCOJZNturC0m3KTvqQ9PCsbmVfWAZCjGF6UPVPBRAGeLxcVYBske6w6WTEFzl1yeGnCE4dvX+uCNDJ1dmgOxXQgahI2zBgw2YpiAOIEwQgsBCymOIHnxO6oA5ZqtGoUNx9ShNHbzIg==
*/