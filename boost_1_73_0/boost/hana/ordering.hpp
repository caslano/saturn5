/*!
@file
Defines `boost::hana::ordering`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ORDERING_HPP
#define BOOST_HANA_ORDERING_HPP

#include <boost/hana/fwd/ordering.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F>
        struct less_by {
            F f;

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const&
            { return hana::less(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) &
            { return hana::less(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto ordering_t::operator()(F&& f) const {
        return detail::less_by<typename detail::decay<F>::type>{static_cast<F&&>(f)};
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ORDERING_HPP

/* ordering.hpp
r9Scyrk/AV6zkbOoDRqCGizw8aUrcxWogkoREjBLlpQa/rHKSsw5X6zs9XDbEcJ/QEtTakiUr4PRGfhOw1HxEtAOcjhLn/Vot+M871IWpFrYr7HZdSyR0H1BWgjB+SFgEM4MXcgguKosbnqyOJoL+uWv/BgftOILCmKtu+1Mve6nw6eZFi6hVC27RN2PpoegvXStYg+xYnu5LkJ4MjgLeieggBQcGzTSpE0dys8vrQ0alB4+
*/