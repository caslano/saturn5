/*!
@file
Defines logical operators.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP
#define BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/and.hpp>
#include <boost/hana/fwd/not.hpp>
#include <boost/hana/fwd/or.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct logical_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value ||
            detail::logical_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator||(X&& x, Y&& y)
        { return hana::or_(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value ||
            detail::logical_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator&&(X&& x, Y&& y)
        { return hana::and_(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value
        >::type>
        constexpr auto operator!(X&& x)
        { return hana::not_(static_cast<X&&>(x)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP

/* logical.hpp
fhBNCOUnmgL4SYFRfqJ8BPxE+YrxU0y1cKoxkZ9iSsUtKpTyE+Uj4CfmooPxk+qlQ+EnkIDyxfxUFOcnJ4vC1aFfTltNeuVmUjTA5si2oAivzmjFQsJHqk22QxVW2yGQ6vYelOoSlfU13VWTYfYMEcNzGRtSXx+Nqq+P8C9dBTLfJfMnpScW0os7jchj0dFNTNwRZw9IOtzys6eFXlG1EGpVxj6wg+ohnVTmo0uOXlITLQSh//imuNC/f+VQlxxU6B+QqUcOEPrvxIT+O4rQH6F45DhFPXLU1hzTcXVr8HSivVUV+refU4S+nNxgN5NkKCg9R++1SFFnTLzPhdf4ho9+EFfPSTLu6owpz8W4B+NxE7RxC/AsakEB2UcP3Lmk9r/Tynh0UnKE3TKKHbUZFvNXsZi7/z40ptAzW7s4aS4kbubyUhL5CC5QijU9gFkq9PUkayCUg7Y+ZD5DmhXH8Z47qPQJTaKnQdP9zmPS7hIgg1PCC7I/was6RZ25f8QVYX4+XkLAW6Jv49GE8txx3FPobqchqd40t5zglKocb/Wj92OH7UzFx6EtqNI/ZtLz98J4NIO0iO6e8txsGJkCBuHhHj1/Opfv8aYBiE8inVmnjpxf7LdHXMWFBYUlxXKFWR5jusdkIRG8X34BNXJQKDnfGdrmUu3j2TJ8TYYiVoao1x6W1CNr00Z9sndULh/hfO9iz6yWQ3+HJwW8
*/