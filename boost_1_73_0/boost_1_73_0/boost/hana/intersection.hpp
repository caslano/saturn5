/*!
@file
Defines `boost::hana::intersection`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INTERSECTION_HPP
#define BOOST_HANA_INTERSECTION_HPP

#include <boost/hana/fwd/intersection.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto intersection_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Intersection = BOOST_HANA_DISPATCH_IF(intersection_impl<S>,
            true
        );

        return Intersection::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct intersection_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INTERSECTION_HPP

/* intersection.hpp
As76Xz8H+ucGXw1upaSs30aKoDCyXsUi6xp/c5ivFcV8Z5wovmjw8n3sNizRBw7JMPHl4T+1gQl5/wBJBuhSbSToWyX2yxzoXU0oWFdNwI82dcDK/9QmJxSif0ktIRlqONAbn1BwA37+2bPWBzqEH3g+LjuhsBUWi7X8YtnIJxuj3DZG0YqQRsbPlCB7jdD/uu1SaC7vkJVPD2Idsev5PJn4SKgpWF+zKuKH/p1M8H/D5ipcr/Jwg+g+hbEFHxA=
*/