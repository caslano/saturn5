/*!
@file
Defines `boost::hana::count`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_COUNT_HPP
#define BOOST_HANA_COUNT_HPP

#include <boost/hana/fwd/count.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/count_if.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto count_t::operator()(Xs&& xs, Value&& value) const {
        using S = typename hana::tag_of<Xs>::type;
        using Count = BOOST_HANA_DISPATCH_IF(count_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::count(xs, value) requires 'xs' to be Foldable");
    #endif

        return Count::apply(static_cast<Xs&&>(xs), static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename T, bool condition>
    struct count_impl<T, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& value) {
            return hana::count_if(static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<Value&&>(value)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_COUNT_HPP

/* count.hpp
MemBnIl4fsOqA8cD3RRnE8Wmyut5Kv8UNccelzqdstcmdDXW+motLTZGjyoSk27v5X26lIT6Op2NywjLnd7gVyhQA8zZvw4iuIcg83/+vviKUZi/VzlVFCQTaW7XJZz0nZTn5ra0J+VaG/MaKj8cGF2tRCrhFahPXYqfpsZZZ0gSFWBqe7aHxSwiz+cHl4Yhq4Z+ymLpC35Mxo8A6FwQdVipMFM5734PintozpRsBJCavMFUyWoUujx25JIQN6BlwLLsq06xpjQx8M+a0f1TWz73GhtdtX1Ft5gg46+7Vz1dW40IuA7e00CuDrY961SQ6vKBnSoaFVj1T1KA4TgVeIgZzXxKvkuQuZYDGfUmTXh+f8cZvVgeMMFnYwgQerhfZobWMA/7VTVbYMdP/XYchXXT0g4wdsWfpynBq7SxVl9z4txbo7bzVN6BiXsvILd/jHl/UU0xilfJQ4ugKN/HzFsVcBSzw0ehRywk3oekt0RcHPMg6iCYVa01P9rjd5NFB4bO59xtifOPxsRCdyGJCqdlbGTAjW5RRpYsdxubMPvez/vygfcTGRolew==
*/