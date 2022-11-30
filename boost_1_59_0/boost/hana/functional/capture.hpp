/*!
@file
Defines `boost::hana::capture`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_CAPTURE_HPP
#define BOOST_HANA_FUNCTIONAL_CAPTURE_HPP

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/functional/partial.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana {
    //! @ingroup group-functional
    //! Create a function capturing the given variables.
    //!
    //! Given 0 or more variables, `capture` creates a closure that can be
    //! used to partially apply a function. This is very similar to `partial`,
    //! except that `capture` allows the partially applied function to be
    //! specified later. Specifically, `capture(vars...)` is a function object
    //! taking a function `f` and returning `f` partially applied to `vars...`.
    //! In other words,
    //! @code
    //!     capture(vars...)(f)(args...) == f(vars..., args...)
    //! @endcode
    //!
    //! @note
    //! The arity of `f` must match the total number of arguments passed to
    //! it, i.e. `sizeof...(vars) + sizeof...(args)`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/capture.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto capture = [](auto&& ...variables) {
        return [perfect-capture](auto&& f) {
            return [perfect-capture](auto&& ...args) -> decltype(auto) {
                return forwarded(f)(forwarded(variables)..., forwarded(args)...);
            };
        };
    };
#else
    namespace detail {
        template <typename F, typename Closure, std::size_t ...i>
        constexpr auto apply_capture(F&& f, Closure&& closure, std::index_sequence<i...>) {
            return hana::partial(static_cast<F&&>(f),
                hana::at_c<i>(static_cast<Closure&&>(closure).storage_)...
            );
        }
    }

    template <typename ...X>
    struct capture_t;

    struct make_capture_t {
        struct secret { };
        template <typename ...X>
        constexpr capture_t<typename detail::decay<X>::type...>
        operator()(X&& ...x) const {
            return {secret{}, static_cast<X&&>(x)...};
        }
    };

    template <typename ...X>
    struct capture_t {
        template <typename ...Y>
        constexpr capture_t(make_capture_t::secret, Y&& ...y)
            : storage_{static_cast<Y&&>(y)...}
        { }

        basic_tuple<X...> storage_;

        template <typename F>
        constexpr auto operator()(F&& f) const& {
            return detail::apply_capture(
                static_cast<F&&>(f), *this,
                std::make_index_sequence<sizeof...(X)>{}
            );
        }

        template <typename F>
        constexpr auto operator()(F&& f) & {
            return detail::apply_capture(
                static_cast<F&&>(f), *this,
                std::make_index_sequence<sizeof...(X)>{}
            );
        }

        template <typename F>
        constexpr auto operator()(F&& f) && {
            return detail::apply_capture(
                static_cast<F&&>(f), static_cast<capture_t&&>(*this),
                std::make_index_sequence<sizeof...(X)>{}
            );
        }
    };

    BOOST_HANA_INLINE_VARIABLE constexpr make_capture_t capture{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_CAPTURE_HPP

/* capture.hpp
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
*/