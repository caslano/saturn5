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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr make_pre_lockstep_t lockstep{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_LOCKSTEP_HPP

/* lockstep.hpp
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
*/