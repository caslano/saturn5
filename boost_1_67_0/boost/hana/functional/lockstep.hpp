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
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
*/