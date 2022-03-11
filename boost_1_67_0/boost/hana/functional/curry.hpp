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


BOOST_HANA_NAMESPACE_BEGIN
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
    constexpr make_curry_t<n> curry{};

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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_CURRY_HPP

/* curry.hpp
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
*/