/*!
@file
Defines `boost::hana::extract`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXTRACT_HPP
#define BOOST_HANA_EXTRACT_HPP

#include <boost/hana/fwd/extract.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_>
    constexpr decltype(auto) extract_t::operator()(W_&& w) const {
        using W = typename hana::tag_of<W_>::type;
        using Extract = BOOST_HANA_DISPATCH_IF(extract_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::extract(w) requires 'w' to be a Comonad");
    #endif

        return Extract::apply(static_cast<W_&&>(w));
    }
    //! @endcond

    template <typename W, bool condition>
    struct extract_impl<W, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXTRACT_HPP

/* extract.hpp
kj1RItYwHf+haP77Pd/aYILAmd+wvP3XMhqxDYXur0HoLELGPbsJa1ZiZqWBHszbZac7Cv0Kb2eGLXlZ82Xx5wt1oWLyUkS00B48vhe2wERobF+i6wujj0ERy0ZvROPSKWuckegLN1T9MgOgmX1L32q+ngI4nuvgXh5XaqD0Lme4VO1c6tnKnbCq8X7UuwwDcKtal20rzJd6fC14V7Zv4mV1v62khxCLTjBaCgNeS1sgHZRqwAhxqTM03vyjrQozbQdiffTalQVeB7juNG3JWzfeyKlPjqV+6ZW+hjHJijozaVzZCnTG5Xd65NomZuym7tcG0+UCxr1EqFxT6yJtUTNW7uuSfH1QUj08+w8ppqrffvXUlzasw+/9aY/LhNwEb0AlG07fbc8kPXTUoQaDq9aEWQ9Tf6YOOaVJ24HcgkkmaGgc8d4YaS9ANYuP018X3kN8Bt8lNGTipVulPZNITzAkarcltBuTyycqlNClNTWTvR3zts4UlEn6beo8M3b7w5CjlWpbAuobfI22n/iAxEIQb0GCowWp+Krcn17h2plRjqm44Ipcvl08cbbpXyCqNx6oxabO1mqMB9HPYNIcPnabGE0mr1HS04nd11MqGb9PsEK0KYWNFEGrAQf27337yMo7/tdvP97kd6JFlG+xjnCTvRnnfvSovbBNCKfa0YE1zjN7hG+4fYFNkRP+PzczeqwFx48gk6HKt4CJ
*/