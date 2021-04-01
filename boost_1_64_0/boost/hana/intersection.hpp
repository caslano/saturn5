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
1DfDeS8qeWMIRycjxfjs151hx0rLiyr58CJbYUydaH2TFR8rDFKtD5LehavY99s3Z1bdjtzy4sFe6Kq+ML9lZm4PDDeZxrnunQsN/WDPsPqLxsnidDPAkG78UjldFbezGBzJJG9WeYljLt4eCNeMb4uyGUzvhEQnDMond/OJ+1ZeuaMlZpWGg9qRPB1Ok2jPJw/VIv38mma9hzMgSMj9h082DudgV1ExeQgGOerIMVoddPFIreeQ61FH/jixsqlbQYAkfUAA+3pP05hHpNPBo77rdG1KHzy8sWBrRkOjvl3Ed6pjXLfU1cpxxamjwJZDerEg9pZ6HjI+zJi0dbYst/NP871S1MWSIM0Cno+omWbU36ithX+3po7s61N/Qn40bvfQZLCwpgXitjyr0vjBqiALSqFz57Y+gYEAffTAnNJw5X3H0O8zHC8epttQqThNz0tLDC/3XkPQOmf3xdnI4u919ASRy2qCEOWVy8TOYOXIiO9bPQ89Ak8PTgmlAn20lWrf0PJE10TNC1uuSP5bixmptUboKSyrXpKE3txUwZDk7MI01mrKBeNHrQ==
*/