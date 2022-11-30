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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr make_partial_t partial{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_PARTIAL_HPP

/* partial.hpp
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
*/