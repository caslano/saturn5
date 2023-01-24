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
cPkxM3BTz0Ju9B3tUch1AAYs+dNeeTJaUFUBTis1BNKXI8CxAmBCnlAqPbknvEm+V3vAGyUq/QMVNScqmolgKy0wMPJXvT0uq8OE8loct9FwcItE8DXfBV3z5xcUB4oV36P0wrZgjDSszKERlvmhJXGr5ZCLv39OTbkrEe7iU86SeYLvaL1uLf9djyxPJLKgafeynRj+WLAEV6vskF8TcOJxgEneRmWG22l3SoBtwAEQhcTpjMIxOdBBpDSpqf6Mqgl2NVwNfVbJu+5awO9pWCzjkKSxhvEGaSxtF3Ynt9J/ahJXeTMLkJfMGt9YGOQrH8XxOVaAZn8s9uM4K5yRnkMneCCVSeETF9DLQ8MF2nfFZ2GXlMelwmZpS9MFsbGJtPgf3L+qu+rWdLjxAtYZny6e0ZzYF/wdZtuJwcl9QTRgo+4LvlCQui+I5fOptHeFr7hhve0EgfyMiIrvWJk5aEp4BW4M2mhjUKISwnJwjF/nFlkSUWElysJXIekbSYFf3oYIy9uQCrCCDmDPDR8g6MEMfgckbHlNI7yOVlBcA8UFmhNZSO6lCkXmax11q000dcUC+ZGIQjYd3wfDYiyz8s4C2u1DjID8VNXQTkykUYyPB6oZQXKJasEPxvLXrocmCzddEM4IIoRVMLNiiDmS16wkOY5OIfA4xwRVGoL7AOHmC7QZB8/AAFEXvuM01IM29MtHJTb0YzczamCR
*/