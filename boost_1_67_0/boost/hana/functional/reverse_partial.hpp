/*!
@file
Defines `boost::hana::reverse_partial`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_REVERSE_PARTIAL_HPP
#define BOOST_HANA_FUNCTIONAL_REVERSE_PARTIAL_HPP

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Partially apply a function to some arguments.
    //!
    //! Given a function `f` and some arguments, `reverse_partial` returns a
    //! new function corresponding to `f` whose last arguments are partially
    //! applied. Specifically, `reverse_partial(f, x...)` is a function such
    //! that
    //! @code
    //!     reverse_partial(f, x...)(y...) == f(y..., x...)
    //! @endcode
    //!
    //! @note
    //! The arity of `f` must match the total number of arguments passed to
    //! it, i.e. `sizeof...(x) + sizeof...(y)`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/reverse_partial.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto reverse_partial = [](auto&& f, auto&& ...x) {
        return [perfect-capture](auto&& ...y) -> decltype(auto) {
            return forwarded(f)(forwarded(y)..., forwarded(x)...);
        };
    };
#else
    template <typename Indices, typename F, typename ...X>
    struct reverse_partial_t;

    struct make_reverse_partial_t {
        struct secret { };
        template <typename F, typename ...X>
        constexpr reverse_partial_t<
            std::make_index_sequence<sizeof...(X)>,
            typename detail::decay<F>::type,
            typename detail::decay<X>::type...
        > operator()(F&& f, X&& ...x) const {
            return {secret{}, static_cast<F&&>(f), static_cast<X&&>(x)...};
        }
    };

    template <std::size_t ...n, typename F, typename ...X>
    struct reverse_partial_t<std::index_sequence<n...>, F, X...> {
        reverse_partial_t() = default;

        template <typename ...T>
        constexpr reverse_partial_t(make_reverse_partial_t::secret, T&& ...t)
            : storage_{static_cast<T&&>(t)...}
        { }

        basic_tuple<F, X...> storage_;

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) const& {
            return hana::at_c<0>(storage_)(
                static_cast<Y&&>(y)...,
                hana::at_c<n+1>(storage_)...
            );
        }

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) & {
            return hana::at_c<0>(storage_)(
                static_cast<Y&&>(y)...,
                hana::at_c<n+1>(storage_)...
            );
        }

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) && {
            return static_cast<F&&>(hana::at_c<0>(storage_))(
                static_cast<Y&&>(y)...,
                static_cast<X&&>(hana::at_c<n+1>(storage_))...
            );
        }
    };

    constexpr make_reverse_partial_t reverse_partial{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_REVERSE_PARTIAL_HPP

/* reverse_partial.hpp
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
*/