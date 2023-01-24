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
8h6j9rXHpH01Sm/CgXL+Uj5eXjRc09Qco38F9C4gx3bYG7nPqJxRkJfqikgzG6eQp2cDQ7U0rdBhXZdJ+i9FArHKN59MgdDAZpQ5w+Q3Ktfz+BJ4ABowA9u0CP9IN9oPSzcAYcyrcMeUTFw3EgVLhXBrj4jJjVMGfoymJHe4yAPZBp2XmF+VKzwWCHfUHeurC9zdaGlcYVLODCyAfAx9pQUawLcmzSqBitF2K9dTIDzW0uY4FYGe/qHNL3/chzmDG+WWS9MCvqr+FdLUxqQS5RpeSZ1Be7RdMk8rO6VlQJkwqoYCtCtLlM4SXxkB3trcauA0QXG8q9ThG24K18Q1GqA0LetzBNelyAs44cE9OL3hBLwDOCs0CMNjZVnQG9lQAV1yIz/dMTL9gFIWqv8Iiwlvd5D2TAPkq6w2BdBsOFS41ojuYYPQh4idY0R4uZ2nqhahwAAvE/6/fPjQeqja67/vRfhzr/tb4N4NcKvlkGXtPE+BWhK5pclSN1wtmuuGSyRzY3ap9pVS1W93EDETEwql5LqWBY3ZWko40GjRTOGiCKBsdUMDnC7iTaN7gWkI1c3m4yVpsK42l3t1DiBJXcTm9fF3NyZRREhoPKo52g7XH8MBzy87dfHhe4WNvLdjdUpriSFfbjVqYyAwCwJDPVQHUQlDNY1J3sPrF28n0PEbeXv76gkezllRThZAK/gC3/J+6Az7kJQGmS7a
*/