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
sSgRBzYfp2Uu4ts4SeMJNBRX4qaqluXzg4PpqkiB+oNZPi0Pprr7+zfVwvTkExCxiO9FvqxElYtVKXsCa/bEIp8lc/wEhkDhcjVJk/KmZ6mBprLZQV6IUqYp4gK4RJZMthQjxZ4eVhNLoDip8KPMsxKburvJF15F4CNima+KDBoCPkClWQ5s7olVNpMFVaae6yYUT4nBrUNj6Z2JPANixO7xSJyNdsUkLpOyJ347G7+7+DgWvx1fXR0Px5/ExRtxPPyEyN6fDU9h6BNorBDy27KQJTReiGSxTBM5U23+vL+DnZ0D1QUSGvxUzcmFzKoku4bhTsXutcxkkUx3xWh0DhzLpigbwNabuKIKaTLBwd+BSZFkwLMMhEQLG4zxvjirEDn0KwO5K5cAnKDwYGtTQIANIYeXRQ5Dhmh2J/H0q8xmu6a5/R0sBwL2LAEg8app3RpiE16FikdoVUx5arCAZHmF6GDM4+xelEs5TebJlNCn8b0suLUTwByVZRrB1IXRmCffiGTFDhhfWVK9YQ7iSdxwW5vmM4ndL3laGqKUOE3zbJ5crwoQFGgW0ag+i9skphrXaT6JU0MF9Kas4mwqmbhdgDoYn49AjxQ5MHCQTYv7JTbxXBxn4iyD4tmK2tzF+nqa4udsP17G0xu5
*/