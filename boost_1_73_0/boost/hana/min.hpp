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
A7lIHRUdb9QR5dcYbvZXJjf2S7EOyIh2gy60bDJtsvdwcza2cW+89SnFnaM4svv3DqO/6IiA34Uv/dYpFwtMc9wvuZYc0T+dxlKVuhRciKyARR+Hr1uH99pd6HvGr8Te0Pahp4MRjEYER0E47+Jr6S16UV0TdAr75NpN7BQpfQONmJdqsUiwh0G8hcfWnnGyuF9rT6tXophc79uL9Ew5QH7QXJSo4kVWsg//SAWDT2DZr1Ub
*/