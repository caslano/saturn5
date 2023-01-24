/*!
@file
Defines `boost::hana::IntegralConstant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP
#define BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP

#include <boost/hana/fwd/concept/integral_constant.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename C, typename Tag = typename tag_of<C>::type>
        struct integral_constant_dispatch
            : hana::integral_constant<bool,
                hana::IntegralConstant<Tag>::value
            >
        { };

        template <typename C>
        struct integral_constant_dispatch<C, C>
            : hana::integral_constant<bool, false>
        { };
    }

    //! @cond
    template <typename C>
    struct IntegralConstant
        : detail::integral_constant_dispatch<C>
    { };
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
9nNpEen7KE5gWjT4RG0hDZ2mQNR1amt0jl4QJsNJ18PjLLzJ5zeoeYeTFlOiHn/BgN3RbXcM2BtgEqdR4i5+c9mnOW/sgVEYzjroM9cekC5hj2NFW7IOSgm7lsPH4Ch4O3zk6CUGQ0OHbUSLQjn7D61WRtoy8JxjUJ1guCb9AErh9+zJZGK/Be8AoHyzbElT8s3MoT8Z4amxvq6Ub2Kq7sbDuF3eceEkD/cxigMt8t1LvSZ2GmU5c9p+CnOHZzzjDqqXE/kpJrUPYQhGfx1en6jB69NVFJTxfrz+dTMGu3voiefoh0J5lj/0tI9+atfRz/O3088fPfDz1CO1FJjUYVYocqgfbzBCZDOVKxhAqs4Z8DqV2kfp6wtYk7RE7F4zVKbZ8UKSwZDT7HgJyUhxvBpOWglt8Rr8K8P9RyE5ht0nSBcehX4abAwn3YQR8ii48Y3c79cKkqQFGo2jrAS4qTzVBqg0NLrcezZbBdsbeMk6tWF8sXo1SDDDgf74VHhEbjJnnVrfBfSEaaswbdX3SBsd/x5Do2DTWIm6OM2m3J5m88Pf9A5gKMRMgJKIDbGwFFIdAxox01kCPeeylFgij/DbvTTnBkciPW/t5ZOgiA8XaLLDp6WNMCOHxZo2wEDXy1zEkacmIxLk7jR5ZCoek+AdrpOJWPN7lMNu6wGtD+ppb/VXHHOJv1VPrVISlE1mZbnF3qoUW0GfBXlV
*/