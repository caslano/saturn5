/*!
@file
Defines `boost::hana::partial`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_PARTIAL_HPP
#define BOOST_HANA_FUNCTIONAL_PARTIAL_HPP

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Partially apply a function to some arguments.
    //!
    //! Given a function `f` and some arguments, `partial` returns a new
    //! function corresponding to the partially applied function `f`. This
    //! allows providing some arguments to a function and letting the rest
    //! of the arguments be provided later. Specifically, `partial(f, x...)`
    //! is a function such that
    //! @code
    //!     partial(f, x...)(y...) == f(x..., y...)
    //! @endcode
    //!
    //! @note
    //! The arity of `f` must match the total number of arguments passed to
    //! it, i.e. `sizeof...(x) + sizeof...(y)`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/partial.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto partial = [](auto&& f, auto&& ...x) {
        return [perfect-capture](auto&& ...y) -> decltype(auto) {
            return forwarded(f)(forwarded(x)..., forwarded(y)...);
        };
    };
#else
    template <typename Indices, typename F, typename ...X>
    struct partial_t;

    struct make_partial_t {
        struct secret { };
        template <typename F, typename ...X>
        constexpr partial_t<
            std::make_index_sequence<sizeof...(X)>,
            typename detail::decay<F>::type,
            typename detail::decay<X>::type...
        >
        operator()(F&& f, X&& ...x) const {
            return {secret{}, static_cast<F&&>(f), static_cast<X&&>(x)...};
        }
    };

    template <std::size_t ...n, typename F, typename ...X>
    struct partial_t<std::index_sequence<n...>, F, X...> {
        partial_t() = default;

        template <typename ...T>
        constexpr partial_t(make_partial_t::secret, T&& ...t)
            : storage_{static_cast<T&&>(t)...}
        { }

        basic_tuple<F, X...> storage_;

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) const& {
            return hana::at_c<0>(storage_)(
                hana::at_c<n+1>(storage_)...,
                static_cast<Y&&>(y)...
            );
        }

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) & {
            return hana::at_c<0>(storage_)(
                hana::at_c<n+1>(storage_)...,
                static_cast<Y&&>(y)...
            );
        }

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) && {
            return static_cast<F&&>(hana::at_c<0>(storage_))(
                static_cast<X&&>(hana::at_c<n+1>(storage_))...,
                static_cast<Y&&>(y)...
            );
        }
    };

    constexpr make_partial_t partial{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_PARTIAL_HPP

/* partial.hpp
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
*/