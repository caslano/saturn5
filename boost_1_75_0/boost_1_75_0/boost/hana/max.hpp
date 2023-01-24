/*!
@file
Defines `boost::hana::max`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MAX_HPP
#define BOOST_HANA_MAX_HPP

#include <boost/hana/fwd/max.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) max_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Max = BOOST_HANA_DISPATCH_IF(decltype(max_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::max(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::max(x, y) requires 'y' to be Orderable");
    #endif

        return Max::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct max_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            decltype(auto) cond = hana::less(x, y);
            return hana::if_(static_cast<decltype(cond)&&>(cond),
                static_cast<Y&&>(y),
                static_cast<X&&>(x)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MAX_HPP

/* max.hpp
uh+2vJ5ye/v4SOL7//Tv/4JWIPvzecg/RSuQ/fk+5J+nFfy//nNNm/70jGeefW7m87Nmz5k774X5C158qfTlhYsWL3nl1deWLnu9bPkbb65Y+dbbq95ZvWbtunffW//+Bx9u+OjjTzZu+vSzzVu2llds275j567dn+/Zu2//gYOHDh85euz4iZOnTp85e+78hS8ufnnp8pWr1776+pvr3373/Y0ffvzp5s+3frn962+/3/njz7/u/n3vPvPx9fOvUbNWQGDtOnXr1W+gatiocZOmzZq3aNnqkdaPPtZG3bZd+w4dOwUFd+7yeNeQ0G7de/Ts1btP3379nxjw5MCwQZpwbbZOb8jJzTOOzzcVmC3WCTa7w1lYVFwycczYcU9lZlX//F+TJk+Z+n+6/P+n8/+f5n9EZFR0TOzguPghQxMSk5JThqWmpWcMHzFy1Gjif/XP/6/g/+J8GDOBUZuYaiyYxWAugQkvgDEDmD1g/M0wXgHjAlMBRmWBsQWYCjABVhjHgDGBcVmrWyemXbfS9zFM4KP8Qpz3ivE/rxlL3x6oLoX/levV0legMF5PBdX/HFf68oP3Dmz5yvfD0FB9OhZ+GtDi3mtaeU39YehUnh91yHaCK/nV8yHSkp/9kcft/lBxq98b8DBx7UJTY6nE4X+OTz6o8fKm+p/jFjP66qnDS066P5D/Nn4+RkrDzGendi6lUhg6G/uw9NgZ
*/