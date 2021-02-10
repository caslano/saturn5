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
gSs8gLAG4kVck/xBecQZUhzVnkigEyHdZL5qND6R1ltreL8gLzIiihIiOxjBguZYHGJ98XZfmmGGxEcjtk7GHSi6Ih1eX0XC9nTpgQwj6eLWk9FLGTOSZB1FuEq/VZF6lCNebgFkNKLvxjqnqkdm5vRQXzZjfaJGSRQwPfcOCaFX15gB+q6YHEXtAypJ6uDd4Ogka0KpVKrZQtiDvJ1Q0rwt77EZX6jY+nh0cmC6whS7kLsgIynR+/aTR+YctZQk9TenRtxsaR8tEmNJFiQ7lZbNhkZquGyxk0hSau0gW0b+g1ftevo1udRDDwDls2Ju8/geJjdhJZYnWfq7wIiQURoUrJozRMhG5AdfdIeeWvKxEZCFhO5DRE3JyNaVLwZBifcdIfh1FQlUS4XoWXAPqRC2slp5UFroGkqCPG9kn/vPEghhrH+QKEiLAAlMrXk0U1iWPJn8NYSZK//B10p/VthJ+IDC6WDSaXF81M0FVMg6UiRiG5HKImswdUv8YVu8XWdL3gPJgunSsZDD50Iizqqw8me9toXUzWBdr4BroU0cTU1SUkTZTnE0nYrRRLsiJ3g8FcIjoqnXE6c9WVZwrLaTVRuBmEXxT/ESDEUh0z0ASbjVwsjP/GQqbY7b2aTUhiFuED64ODe6E2b9
*/