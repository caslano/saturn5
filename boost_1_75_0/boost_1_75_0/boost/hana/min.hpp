/*!
@file
Defines `boost::hana::min`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MIN_HPP
#define BOOST_HANA_MIN_HPP

#include <boost/hana/fwd/min.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) min_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Min = BOOST_HANA_DISPATCH_IF(decltype(min_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::min(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::min(x, y) requires 'y' to be Orderable");
    #endif

        return Min::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct min_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            decltype(auto) cond = hana::less(x, y);
            return hana::if_(static_cast<decltype(cond)&&>(cond),
                static_cast<X&&>(x),
                static_cast<Y&&>(y)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MIN_HPP

/* min.hpp
ZVfAQMD+gLUBowFbAaZgOMA8DAcdZjGGA5yB4QDn43PA1/A5dJhr8TngRnwOuBOfAx7B58FADz4HvIHPAe+gP3SY/tPBH1AFWBuwNaAPvMCC0R+wN/oDhqN/b2if6A84Ev0B9egPHaoV3YCT0D0Q+IVuwFJ0Q4dahm7AtYjQkW5EjAM6EROATkToIC8AQp/BrgO2ArwzHedZpJ/P5qsOjM8FmOxdHCc06jqhZ9eL53qxfmDgKwqkfyeUvtlrFEjp54nwtFLD+HotIa01jBfp4nsff2aRrlm4rcJtFeFtwt8m0ssT+djFu9/OJggs5Ch929QhwjkFGsWZxmxBn91dHsrHJOJLZ+dyBJ2Fonx5Yu1CCxyjeERPgaBDy1d3GR/RUnyLiGcU4ezieb7AEkFHkaBzoqDbIcpP6eSKfKRvp0r3wuSLeihw80Mr3GYRzyTCWXiOOI7HkDhGppIyvmoUAvUewUguQlgk/46Vjo/VYrhE6Pg4OYqNZiQTISyaDWUkFyH8tg0mZuiD+Rguh88qYlk8I5kI4d80IbkI4SeBSTZCQOIyGMlHCP/2AMlICF8dJ7kIgRFiArdnc3syI/kIgVFkAiMZQZoxfRsfR6byMDaefipPP4/TEMfDoMyE8NtBSG5C+LfySHZCxDfzHGIMGsdIhkL41+JJjjDfoUKWQvjX92gMiutREUK2kJ5RQr5C+DeKScZC+NfYSc5C
*/