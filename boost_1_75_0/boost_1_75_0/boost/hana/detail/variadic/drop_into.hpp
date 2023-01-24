/*!
@file
Defines `boost::hana::detail::variadic::drop_into`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_DROP_INTO_HPP
#define BOOST_HANA_DETAIL_VARIADIC_DROP_INTO_HPP

#include <boost/hana/config.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    template <std::size_t n, typename F, typename = std::make_index_sequence<n>>
    struct dropper;

    template <std::size_t n, typename F, std::size_t ...ignore>
    struct dropper<n, F, std::index_sequence<ignore...>> {
        F f;

        template <typename ...Rest>
        constexpr auto go(decltype(ignore, (void*)0)..., Rest ...rest) const
        { return f(*rest...); }

        template <typename ...Xs>
        constexpr auto operator()(Xs ...xs) const
        { return go(&xs...); }
    };

    template <std::size_t n>
    struct make_dropper {
        template <typename F>
        constexpr auto operator()(F f) const
        { return dropper<n, decltype(f)>{f}; }
    };

    template <std::size_t n>
    constexpr make_dropper<n> drop_into{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_DROP_INTO_HPP

/* drop_into.hpp
khxVgCiGBeLhfAV0Qo6QD6xUjFlpCtUt5qQXtbEV5DJchhzxW3Eztx2G4FYMAufK7nij2hN/ujqqPYEjQZ82SHID9w+MQAMUUDfySjL2T9BFRAbgQuzHCbe6gdfGAqfrinIvlkpkPYYkLcp3HE6jlCzxfSjObsauFpOd5D58biVBGQKSLHrSSpZUc/pJo5WOD0HTjZqsp+CTx8+7UAA8lw7abBrEkuRS+oBLy8A36PIhvaYRd9FGoKbyHf0cvpVVQE5com9f6F0jlZIqn9Qf3Zoy6MmLEmDUbQM2zGHF95YuxT0IAG5GgFeNAvhMIkDcfy8E8KZzAL6GhWJUGgCpZREm4cWNhBpbnnISJZKwD/yLfOMS89EhkvvoHo9vZMAmb8aoGJjsBPY04HOQCoVTsuHgjzKQAepALgszwES3KyeVW3j506m20z7puNJp++DQ/kPvoI+rXZSNgwAeY2EX8FUFsb5OylM0yxpvP7r6tkKT+I1iU8qO204e6lQ6faborocv29A6lJMAHEFzVOWviLft9ZWFbM1K56Gy0KF2pSxkLzslpQFouyMoPgPf6L5gGC9turVf4qN0GW5yICOKciU6OIw2/dBeODnbWDUGhfOxv06e/VhW2fwr6W57C5mXck43o/63CzAqAJpBewVlB7TXlPYKZYp8bKpb2cDbupW1FlvIFoRO6Tz0jj0seNFQMP/r7fiUTCBstAfX
*/