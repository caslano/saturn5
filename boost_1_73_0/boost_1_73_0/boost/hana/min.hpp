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
TgDpTqmDCpYMuYXdgUZhac2D0J/VseV3vf7RoXsyfH8xHjSM5m+lQewAtH8ZciVHPYcmwjms1xTbTO6Xk2iREBZfRjE80s0hzc2dX78/+NHtd952rQfdX8cw7N6gP1KPL96cjH5we6PRZXfodvqn7qg77HXO7dej3qs+vO71zwbqxeBkdOEOu/9x2R2Nc89GFwAf2vVDWIjmbMBkzLzUw6nIHiZQbG4/gkEtpaADmFCUMomgGS++1/PN2DWg5yokyYKQFlw502t/+qGiIiA5dVcp8CirFxHMIUCwHwK4EDaY3BCAweQf+YtCMaJl68kH/34RXeVqpvHUS3z74XWUpDQE+/FyvUiDYF4A4MdxFOc6jithBYSSzmUpKLqTce7TWF+UvIiBD5a/uQOaujnid3MmAV5Wbn/gno46JVVmiUflmThK3l+XNwVDKn+xnH1f/gJnvvzNJKwYqPStWCGIKl6s53O/omOrD9OkfUjsxOA7nbc9ZDvZxHjL4MqLmDD0ipk7dYXJX7pDXLBu//Lty+7QefHcObg7OPjx4OnB0/l5w3n82HmkuIuBfFyKjZJOwYa6MvC/XVM/HBxIU7C4Dlo/tn5A/rvwYE+DlcQSzI5T2o9u/1Wv363s5mXPPQFmMTjvQmeF3xncWaqX
*/