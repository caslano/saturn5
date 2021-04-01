/*!
@file
Defines `boost::hana::detail::fast_and`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_FAST_AND_HPP
#define BOOST_HANA_DETAIL_FAST_AND_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <bool ...b>
    struct fast_and
        : std::is_same<fast_and<b...>, fast_and<(b, true)...>>
    { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_FAST_AND_HPP

/* fast_and.hpp
9P+DG2JB0jwev+ZVQ+VPxxQxmj0SMCdA6DncWcmt1lQ+5ONQsEfEklggMz6xxX5oaJsQZBue4AIQ6VPAKzBP8ykvU5EiO8FyZy0J1qLakjd8CNLPU6K9S41T6oR+4L0m6k3uvubTxZCHfnBDtiuCD3PngIikOdpHzMeF88ibqhuSGrYGYiPQhZCUzJBhpraa9bWzfZWxbsQNc7ZWGVcWyaEifED7XyvbHpI/e04HPf8D4AF/WHcizlAHExJAKcJaDKfYUO77RgN+XiFSnk2oWPKfMgm9zdoTp58OvyKkNx3kRh/KiVr2ImfSjm/mkV92Qh6OQDfrBUSH7t+kRRHVHFqvqnIBlQKcGAZEf6UTsEOoRLwKNAfeG6iyM0SvI7DO52iUhC2avS9WTLId74eXqNAfvGQUAs6roxGT1Dh+oWQU1X0E9jKL7bk2PmK2LZI6AdY3y1/sX8akixHZC4pSeYwERmTJJrdRa7+t/BPwX0zgWBT1y9rFjlRJypo2X2jcEs+oiw5vhknZfwxwO1KNgUkHeXp7a97m0xIzKRHy149MUeNqoghJuEOzIA==
*/