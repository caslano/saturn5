/*!
@file
Defines `boost::hana::detail::variadic::reverse_apply_flat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP
#define BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/at.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    template <int ...i, typename F, typename ...X>
    constexpr decltype(auto)
    reverse_apply_flat_helper(std::integer_sequence<int, i...>, F&& f, X&& ...x)
    {
        return static_cast<F&&>(f)(
            detail::variadic::at<sizeof...(x) - i - 1>(
                static_cast<X&&>(x)...
            )...
        );
    }

    template <typename F, typename ...X>
    constexpr decltype(auto) reverse_apply_flat(F&& f, X&& ...x) {
        return reverse_apply_flat_helper(
            std::make_integer_sequence<int, sizeof...(x)>{},
            static_cast<F&&>(f),
            static_cast<X&&>(x)...
        );
    }
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP

/* flat.hpp
lWctgAdV5blZgK+yLaKTLWIcgbVFdHpbRLcAz8tPU0X5l4sHV0VJoVJ7PeXHyJ3KvWXN+Gu/yx93ZH2yadfJg+wHulWtyMtgXb6I/8/6rNKJtVPNqdwBJElLOQ9Opw9VYEf3+qUXkuOrvB6aCmqQKUhy0vUnUM9Cfm5vv1d4iNqfOf3q0MOrqLIp5zw25nv9Xu3wWV3b893Tz8u9B8+XOWVzRCV1erB7OFox3W4f41SSSiX4
*/