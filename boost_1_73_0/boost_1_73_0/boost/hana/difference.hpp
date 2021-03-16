/*!
@file
Defines `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DIFFERENCE_HPP
#define BOOST_HANA_DIFFERENCE_HPP

#include <boost/hana/fwd/difference.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/erase_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto difference_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Difference = BOOST_HANA_DISPATCH_IF(difference_impl<S>,
            true
        );

        return Difference::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct difference_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DIFFERENCE_HPP

/* difference.hpp
/r6mUnxNpUBzLlJ8hmNN0KTgNpXiNpViJE+BsvcVjnWOluIOleIOleIQK4WQG79Wqm+oFN9QKcZ6VM3bOdY4LY9vqhTfVCkmUYpZs9bA/zm321fh4Vqz4p33Rws8H36Iiaq6YtH0LK8Xv5ZzyKzOZKwjvSGGmWG++Z58Zv/pFxDnEc4UvXV0nDA+5xPOoB2F6RceFxAOqtAo+PvJyJd/xfPX8xpBOO8LbJ5qhI3OSMJBk4Ce34g/fq/XSWcU4Vw=
*/