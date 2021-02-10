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
Z0pSKyl04Y4CAACGBQAAGwAJAGN1cmwtbWFzdGVyL2xpYi92dGxzL25zc2cuaFVUBQABtkgkYK1UUU/bMBB+7684tS+AsobxNDY0rSoMqk0FNUWoEpLlxBfiybUj2yntxI/fXRoo05j6gqvUzvm+7zvfOTfQpVVYwtXF6PxiJsa3s59immWX4qo3ILu2+NZWevR+owdHsHeI9hE0aG4RN979wiK+7S3EE2x/hLqneZ9ICjvIkziE/ZAnOGgholM547UQ+4TuOTb+Sxl5L3hJFoIxcuzqjdcPVYSD8SF8PD39BB/g5PjkOIFzaTUayCLaHP1DAmeqtXyr5Ho9DPg1AYwgzbCjmlc6QHBlfJQegdZGF2gDKpABFIbC65xetIVYIZTaIIyvbxaT6WUCj5UuKibZuAZC5RqjoJIrBI8F6tWWo5Y+gisJTuRKh0iETdTODkkbIaJfBuZgeWmCA7mS2sichGSEKsY6fE7TovGGok+VK0JaPB9/WMXly0kWFMRSbsDVEaKDJmAC7JnA0ild8kwJIWPd5EaHKtlFQ1JWpc5DQGOYi3AawzZshKxLT8JuUFPEOvIUnA0s9Vi55V+OlEdmKRtvSYjyQE7KUZoTaOgz8q1ze/JniS6nbYL/W5pdvAqcpWCgP8pgkvUh
*/