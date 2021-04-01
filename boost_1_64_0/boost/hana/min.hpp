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
+Yp58CVVV923gg1ieotmNjl+WUo/Bh8UTkJYWvWggC5zpUIfEHwVmAJXKkuy8hen1NRqyNvR6sJXI5Dd0LYg4YNuWej3m0F6k2VSK/XDcCmYO+BgRp+/rsMC3EHSPCROMoX4xzP9+9oR4AyPhtaOfRYyC62DcU243jJKD8nUL84QV9w/AhQkDMSUUYbieFCTEGu7emjZ4DX/0mVNY3b+t+YuEJ2Hj3qvCJ5n2mgrrRT6bM43SIdfxqYXM7SFLsb4kBxI0JImYs3UyGIitAfkWz983/Vjpj5gyDC6MTZBimLFzOegfXecaTqJT2+AiL73AZp7XXJLjhBD0xLVmF/wAS1VfbBf1MRRH8s7KutycxOXeUCBBlGAQ3j4r3G/CtyCX+8xyoGsjaUe++mpqNl1UXjkOEybKFNfWZFJrBV8At32GmF/86ADX2+H9TebEfdqwMfMKrMxaTsmbYyf8YKdXUGPfR8clEs+CZ9mf6esTkj7jXn4jrzUbycCFEHzi6R0NorIp/Qx+JtZah/vyM3bAxsH+5+OTw7bzoarWadfX/qM2Z+ZYiAfT9+WPw==
*/