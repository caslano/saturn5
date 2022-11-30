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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr make_reverse_partial_t reverse_partial{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_REVERSE_PARTIAL_HPP

/* reverse_partial.hpp
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
*/