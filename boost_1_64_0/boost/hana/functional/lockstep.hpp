/*!
@file
Defines `boost::hana::lockstep`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_LOCKSTEP_HPP
#define BOOST_HANA_FUNCTIONAL_LOCKSTEP_HPP

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Invoke a function with the result of invoking other functions on its
    //! arguments, in lockstep.
    //!
    //! Specifically, `lockstep(f)(g1, ..., gN)` is a function such that
    //! @code
    //!     lockstep(f)(g1, ..., gN)(x1, ..., xN) == f(g1(x1), ..., gN(xN))
    //! @endcode
    //!
    //! Since each `g` is invoked on its corresponding argument in lockstep,
    //! the number of arguments must match the number of `g`s.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/lockstep.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto lockstep = [](auto&& f, auto&& ...g) {
        return [perfect-capture](auto&& ...x) -> decltype(auto) {
            return forwarded(f)(forwarded(g)(forwarded(x))...);
        };
    };
#else
    template <typename Indices, typename F, typename ...G>
    struct lockstep_t;

    template <typename F>
    struct pre_lockstep_t;

    struct make_pre_lockstep_t {
        struct secret { };
        template <typename F>
        constexpr pre_lockstep_t<typename detail::decay<F>::type> operator()(F&& f) const {
            return {static_cast<F&&>(f)};
        }
    };

    template <std::size_t ...n, typename F, typename ...G>
    struct lockstep_t<std::index_sequence<n...>, F, G...> {
        template <typename ...T>
        constexpr lockstep_t(make_pre_lockstep_t::secret, T&& ...t)
            : storage_{static_cast<T&&>(t)...}
        { }

        basic_tuple<F, G...> storage_;

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const& {
            return hana::at_c<0>(storage_)(
                hana::at_c<n+1>(storage_)(static_cast<X&&>(x))...
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) & {
            return hana::at_c<0>(storage_)(
                hana::at_c<n+1>(storage_)(static_cast<X&&>(x))...
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) && {
            return static_cast<F&&>(hana::at_c<0>(storage_))(
                static_cast<G&&>(hana::at_c<n+1>(storage_))(static_cast<X&&>(x))...
            );
        }
    };

    template <typename F>
    struct pre_lockstep_t {
        F f;

        template <typename ...G>
        constexpr lockstep_t<std::make_index_sequence<sizeof...(G)>, F,
                             typename detail::decay<G>::type...>
        operator()(G&& ...g) const& {
            return {make_pre_lockstep_t::secret{}, this->f, static_cast<G&&>(g)...};
        }

        template <typename ...G>
        constexpr lockstep_t<std::make_index_sequence<sizeof...(G)>, F,
                             typename detail::decay<G>::type...>
        operator()(G&& ...g) && {
            return {make_pre_lockstep_t::secret{}, static_cast<F&&>(this->f),
                                                   static_cast<G&&>(g)...};
        }
    };

    constexpr make_pre_lockstep_t lockstep{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_LOCKSTEP_HPP

/* lockstep.hpp
e/cDrNf7HmbmnDlzpk/M/bTpucxgYjAYTPX/798GQ4Thz/88DP/7n6WRwWBf5IS9IdzqatEIo9ZXi3Ye5D/KZURgwMDAvsNcfPsOHx4w2qXfAJfAMcNd/Ie7eLbr5DIsoP8ANzs76xJ/4ZG/3bJlPm6/zv/1/85dh51vob/xbX+f65399+e5btl/s/7y9/u5rvpbadRv/aXO7/Pp+vuy3fdzhvL8/XXOOztvdP7Pf39k5zv6+w6C/3/qS/smBkNrIwvD8Zrlevy17LHBuKiNkb21wSmnkFbZZcOdBXLo/0oqUyo7bWwwmGdj//bXcLDgnwc1G+1hJNLs//72989/HkfmM1SvLAZ/KGDobKSCMwUM28z/jYAJBQyXTmhetuYz1PwvczJe+H+Yu2UFEOo//nMbPWD8aP0tmSNntkDZfTX9RxoXg6GPW2D/vqP7Ggx5oiz+3PdT+ptHf//un4f+c/szmWH0MoF3Gixv/b3p/M90Z9z8/0w4ucBfZCzImBb4V36VKvn6DZRIRoyp8Mb62/rf0AWOCvRVOnvszghvqb9t/x3dgKEBImx6889jakjS367/QtfI8H/yL45/qXNX5TCkFh1nbEiN2+JoSA1ua2tI7WgpsL+WgyG1dDELQ+qs3MKeqqZsmc9CXOhjbUhNBqwrZG5IvTXOyZC6ubqlIbUV2erUfRJgakgNWiPOF33NDKmNbonBsOLKptiKSydvgeH2AhOGiNjzsFi1G6Nsz2t2htTVG1RjxE7JMqmdQMwvkWxZKfbl/6jsxWZq4ymNXzURv3yr7Q2p5zcrFXoOfmdF92mZ6NpVFKs9I63Er7lqbC6ufnjFi+RlFYEOe5EvwaD+Rol9o9aSr80ycRmUrhrbDonBox0qq4UE/auLQcAfhS37ycaQ2sRCoE+gGpr0QazmVlNqxmzJ/OaaZHn1U9gPA4WY8kASRORStSqfBdr6SYLLlcV0dB2BgGRz8Zshklu3TAyp79yNDKlZR0V31B35Cgt78oboXJeqbGYJMd34TnTzN0mgTjHKTs2p7N3y8NutsmlL1SPnMpJ+TAthPXzE5T4MdowRcLRSL8vfUxvHXoi4Y1mN31t3CT7eW4J/fCfB6zPidzeqtU+1VGPpR3G5d0ltdDFWWaXaKotcJxJzZ9Ud2VidGfpQ0t+2Ucp9nthX6CZsygkRf3wlMX51UBd2B2ptzBktkDFLYF1+1S1ZTGDEV8ZvskCSu7H41VHdukGqMXCzQKNDIrGrLC5rwpStEqO+/fG92pgAg6r091oBNTTxuY3666tspUwL8fNTDXOEXD5MqYK0uzOfqhl3VbWfZdRQ804COanWtijLB/mq9lAb7ZI0YC0nqGy1tVIHvcTgygaxqn5MZU/WKhWXLkSzygJb86m1Kc3EanyiQBiND/dSG2cWit/Nn2ryAINofUZ1x1g5CFHCUvz2wC9Tjc+oKezQhqKr4SFwLkUrcfFEEXffoa769hO/U+uVqpVTdJ5mQlwbaq/+ztBsvTit7OZrQkzarVSpkUpt2Sxi24qaX1dvpZ5WYj1vFahJqsp1SRA6RUwX7LOWfKOVavBeoPYqEZs1EYlHDYEsalSH36GyApO9RfKF/jbyUvatr7I1Kyh1Pkpg6l0hUmvCr7m4bApXP04Ul3whiZIqoacQkSypl35KNTypsvJltV66NVfdjlPFKuq+GFgetRI/hm7qJJVZNRU2nF226aWGZE8jMc2dX9PzmKVcro+Ix4aIeEa8peRrpXaPXRaiGNV8gtTGmvwCOe8J+4jGW1QyEr+bwjpUViqtnFKrX4izIVTY1xZin1Se/UF/vdOsxI9BvMFM+/xB7JsjZJUXQkxlcPJfFec=
*/