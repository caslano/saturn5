/*!
@file
Defines `boost::hana::not_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NOT_EQUAL_HPP
#define BOOST_HANA_NOT_EQUAL_HPP

#include <boost/hana/fwd/not_equal.hpp>

#include <boost/hana/concept/comparable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_to.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto not_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using NotEqual = not_equal_impl<T, U>;
        return NotEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct not_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_(hana::equal(static_cast<X&&>(x),
                                          static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct not_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Comparable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_equal(hana::to<C>(static_cast<X&&>(x)),
                                   hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NOT_EQUAL_HPP

/* not_equal.hpp
eXL1sKzFPFgtNBOVzrOtAVGvM0j4U8+EIlWjs7BLtE2eP/eChRiec0usxoHD8AAUzW2ECfamdoxegG5tXSPMAxGD8t8TKJh/Vw8jHLQzx/BZTec2xg0aMeCsrmMP4+ZBTX6qwrYtvfTnRi3fVdudErk/ufsw729aDGHzdiuHBWYFWLH2Xiicmn9/lL9iNamgQlQztiBDIUCmPfLHkjh5iHpABYKhqyDZGG59FW2Om/Um0Q1HsMM6iZw2o/GTyHriKzcI8fjKICFwpnTy0P86tF6k8m00Ofjopf3py6JkQTQzeP+ctUHI+3+LY/PiwK/FtcH74rNCMEL7yIHUMvVaDgFOxkOOWHHy9tQ9Gw7eUlRBJQNm04iODUsdnACXC1sD1cECNBziNouXXuSK44zODAy3BrzZku36eftltjew0C1+CiDB+S2xDRr9oTI5C6dm3XZBKpq3SMopIVevkVKkTvrytYtzYs+M/f3jjjmKhwZhCYLLGR26An+o0WHoSRdkcpygmtmwSK92HwsCZTCzOyvqHN3sNbqNEV29ZXK8YzzkRy0Bo7gVIva4vJRpvlIfoJfTiL1aFInIHczEsQfn/GzOPM+9EOc0jRclKGw6G4l30wI8yNRwhW4xTOVn3eBbTg1vEsoo0CGIeJa6
*/