/*!
@file
Defines `boost::hana::union`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNION_HPP
#define BOOST_HANA_UNION_HPP

#include <boost/hana/fwd/union.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto union_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Union = BOOST_HANA_DISPATCH_IF(union_impl<S>,
            true
        );

        return Union::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct union_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNION_HPP

/* union.hpp
mWe9CF9eLhNp6ZXlS6idNHS+TL/YKEgfoiRtVL2mHxP7LPrrS6LLee52OVA9vgf0b1i97837l95/34zf15W+QY0kuydduT+N6hnyGHw1W3/SPS55P2+KjE12Drxi2W8cILovHUen1MbAq9NnR8kNHd79GqzCKaNE5ZWlb/pG+vvwtLNBq/DL3gPvypeQneqw61CTR+foLMDuM+tXPsJmnTo0fdJBCw9aRidEZ4okv+N71QhJ
*/