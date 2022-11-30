/*!
@file
Defines `boost::hana::curry`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_CURRY_HPP
#define BOOST_HANA_FUNCTIONAL_CURRY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/functional/apply.hpp>
#include <boost/hana/functional/partial.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


namespace boost { namespace hana {
    //! @ingroup group-functional
    //! Curry a function up to the given number of arguments.
    //!
    //! [Currying][Wikipedia.currying] is a technique in which we consider a
    //! function taking multiple arguments (or, equivalently, a tuple of
    //! arguments), and turn it into a function which takes a single argument
    //! and returns a function to handle the remaining arguments. To help
    //! visualize, let's denote the type of a function `f` which takes
    //! arguments of types `X1, ..., Xn` and returns a `R` as
    //! @code
    //!     (X1, ..., Xn) -> R
    //! @endcode
    //!
    //! Then, currying is the process of taking `f` and turning it into an
    //! equivalent function (call it `g`) of type
    //! @code
    //!     X1 -> (X2 -> (... -> (Xn -> R)))
    //! @endcode
    //!
    //! This gives us the following equivalence, where `x1`, ..., `xn` are
    //! objects of type `X1`, ..., `Xn` respectively:
    //! @code
    //!     f(x1, ..., xn) == g(x1)...(xn)
    //! @endcode
    //!
    //! Currying can be useful in several situations, especially when working
    //! with higher-order functions.
    //!
    //! This `curry` utility is an implementation of currying in C++.
    //! Specifically, `curry<n>(f)` is a function such that
    //! @code
    //!     curry<n>(f)(x1)...(xn) == f(x1, ..., xn)
    //! @endcode
    //!
    //! Note that the `n` has to be specified explicitly because the existence
    //! of functions with variadic arguments in C++ make it impossible to know
    //! when currying should stop.
    //!
    //! Unlike usual currying, this implementation also allows a curried
    //! function to be called with several arguments at a time. Hence, the
    //! following always holds
    //! @code
    //!     curry<n>(f)(x1, ..., xk) == curry<n - k>(f)(x1)...(xk)
    //! @endcode
    //!
    //! Of course, this requires `k` to be less than or equal to `n`; failure
    //! to satisfy this will trigger a static assertion. This syntax is
    //! supported because it makes curried functions usable where normal
    //! functions are expected.
    //!
    //! Another "extension" is that `curry<0>(f)` is supported: `curry<0>(f)`
    //! is a nullary function; whereas the classical definition for currying
    //! seems to leave this case undefined, as nullary functions don't make
    //! much sense in purely functional languages.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/curry.cpp
    //!
    //!
    //! [Wikipedia.currying]: http://en.wikipedia.org/wiki/Currying
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto curry = [](auto&& f) {
        return [perfect-capture](auto&& x1) {
            return [perfect-capture](auto&& x2) {
                ...
                    return [perfect-capture](auto&& xn) -> decltype(auto) {
                        return forwarded(f)(
                            forwarded(x1), forwarded(x2), ..., forwarded(xn)
                        );
                    };
            };
        };
    };
#else
    template <std::size_t n, typename F>
    struct curry_t;

    template <std::size_t n>
    struct make_curry_t {
        template <typename F>
        constexpr curry_t<n, typename detail::decay<F>::type>
        operator()(F&& f) const { return {static_cast<F&&>(f)}; }
    };

    template <std::size_t n>
    BOOST_HANA_INLINE_VARIABLE constexpr make_curry_t<n> curry{};

    namespace curry_detail { namespace {
        template <std::size_t n>
        constexpr make_curry_t<n> curry_or_call{};

        template <>
        constexpr auto curry_or_call<0> = apply;
    }}

    template <std::size_t n, typename F>
    struct curry_t {
        F f;

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const& {
            static_assert(sizeof...(x) <= n,
            "too many arguments provided to boost::hana::curry");
            return curry_detail::curry_or_call<n - sizeof...(x)>(
                partial(f, static_cast<X&&>(x)...)
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) & {
            static_assert(sizeof...(x) <= n,
            "too many arguments provided to boost::hana::curry");
            return curry_detail::curry_or_call<n - sizeof...(x)>(
                partial(f, static_cast<X&&>(x)...)
            );
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) && {
            static_assert(sizeof...(x) <= n,
            "too many arguments provided to boost::hana::curry");
            return curry_detail::curry_or_call<n - sizeof...(x)>(
                partial(std::move(f), static_cast<X&&>(x)...)
            );
        }
    };

    template <typename F>
    struct curry_t<0, F> {
        F f;

        constexpr decltype(auto) operator()() const&
        { return f(); }

        constexpr decltype(auto) operator()() &
        { return f(); }

        constexpr decltype(auto) operator()() &&
        { return std::move(f)(); }
    };
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_CURRY_HPP

/* curry.hpp
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
*/