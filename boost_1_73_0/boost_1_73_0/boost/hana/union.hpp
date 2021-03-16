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
GOpLi1YRWw6tMupbKVpF7JZ8/vjbHuwO0SqirzlJsr59S7c8/sFjj7xmX3/JzPx+iye9cn7eofyuEvWnRrHI6ERjA/sG2d6l1xFZ73v+wnv9VXCAz/7V18HOj7nk/+f8qF2W8xeB2hfCxyVsAChEng2f3HQEK+pmK7Dl2Qry8/L5Zb3F5X8BffAxvp5XtfY2rf2a1n5da2+HdkK039Dab2rtt6C9VLR3aO238/ij+LD9V639Th5vYPtdrb1ZzIs=
*/