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
1obp87TnYGdUPBAyZB9gA1eCLy7pr9Drb34eAU91EpnnKfYv6zZWB4zenZWnFxH64V4FmU8LGow/su9EsiWyt2kYlKlPKVi2cQqp5wxZisn5CJt6nABXM+r808+heayyBIsvZAjlQUwAgrNTwD0Ah2A01mVlC0HDqDorfO3hPo3XeL9Xj9fD5n7aAmfl5qp2yK6o7ZNX73UogRCqyhqnBwVj9Dm2yyIqjVWn8ePxGTCcCzdTCJKk4P3t5y8BCI/CHq8uNEy7/taRu0tHRIXoCZexEvVvyn/A2jER/t+VRNlE9n82sMiUDu1pZFXnVjC/QwUlj8yp0Bgp3RLAqD7bxVBi6tRS2Zee1g6c6oLwFS/iOnvHQlllGsToZPVYyxCD5S8M55C7Xdn+4O8vDp+dkPYKBCqgHICVmP65vX/9tzoEOZ2xdQsMn2xboX2tzyyq9k1j1eqkAJbuUQI9f0erMxdR7amvNO1GRSzJuTANPkHkrkuO+uzXKZnOeuZNsY7ragBQVB/bLxaVR9o7GcwmffpsdPdpt01B/sBep4KQoXL2KvVAlq7uF4m4sQ==
*/