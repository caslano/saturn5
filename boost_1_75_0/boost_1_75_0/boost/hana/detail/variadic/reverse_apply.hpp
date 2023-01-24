/*!
@file
Defines `boost::hana::detail::variadic::reverse_apply`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP
#define BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/reverse_apply/unrolled.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    BOOST_HANA_CONSTEXPR_LAMBDA auto reverse_apply =
        [](auto&& f, auto&& ...x) -> decltype(auto) {
            return detail::variadic::reverse_apply_unrolled(
                static_cast<decltype(f)>(f),
                static_cast<decltype(x)>(x)...
            );
        };
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP

/* reverse_apply.hpp
iwbnkA3R4HyyJhqcSWqiwctJVTRYRG6MBpeQpXpwy23QFlJoPqc9c8N6e1gET0Qq8Jgzah+UNyzjxJmRtcvIz+ehhGxZpd2Mu5eYuQh3MjFDvjedk4BD/sUcPJqg7GzZSljuEPO1DWKqWp69DXfOUESc5nKSvCk6fR3vgU0DU8hPp+B2FYC6qdGkm11tKMFYOTgGfDEZdbGBb7mu5nYTnu3JS5OodjaqZ6c4SRUPVWnz3TrIzClINSWTW/ukBpF1kwHqc43M5dnpBYDCIWE91oOHKT1M1NOUYFbEkbAdTkSjOopGeRSNvAQ0Ksh7+NCglh9FQ518Lho/Rn6GvGLSsZBS9Jq1aEA5Sk9HLTX/9Wcj7JY5HPecXj8VDxF87Bm1t50ETVMr0ZdIvINhC///0O1cBkZEojZP8nGUeqtlQfK7hTjgp2CocVYu+QfdJ9BaYZStQoJdpF5uVbScBculf+dyl0bLGbDcu/u+a7mv7KxcTZ2+gH7/b4rqliziGHrxSMwR9ogdHAWfxUmKpjpyH3/hzNYLZrZcOPPFF8xsuHDmSy6QeQY2Kf4YolrWX4GWLmcXUEuX+jMo61nzQ9VBnBUE3zWkGmx5qJCGh5Q6fNNH2JaeDb0QU0xTAgMn6c1XkHZOf7RzWgYOc+xNbcdIoyOMPtvQNukKpUUtI4EQrPtT5ehCkhyx6S/FjlccpxodIza/x9hYdRbKVGoT
*/