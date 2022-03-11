/*!
@file
Defines `boost::hana::arg`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ARG_HPP
#define BOOST_HANA_FUNCTIONAL_ARG_HPP

#include <boost/hana/config.hpp>

#include <cstddef>
#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Return the `n`th passed argument.
    //!
    //! Specifically, `arg<n>(x1, ..., xn, ..., xm)` is equivalent to `xn`.
    //! Note that indexing starts at 1, so `arg<1>` returns the 1st argument,
    //! `arg<2>` the 2nd and so on. Using `arg<0>` is an error. Passing
    //! less than `n` arguments to `arg<n>` is also an error.
    //!
    //!
    //! @tparam n
    //! An unsigned integer representing the argument to return. `n` must be
    //! positive (meaning nonzero).
    //!
    //! @param x1, ..., xm
    //! A variadic pack of arguments from which the `n`th one is returned.
    //!
    //!
    //! @internal
    //! ### Discussion: could `n` be dynamic?
    //! We could have chosen `arg` to be used like `arg(n)(x...)` instead of
    //! `arg<n>(x...)`. Provided all the arguments were of the same type, it
    //! would then be possible for `n` to only be known at runtime. However,
    //! we would then lose the ability to assert the in-boundedness of `n`
    //! statically.
    //!
    //! ### Rationale for `n` being a non-type template parameter
    //! I claim that the only interesting use case is with a compile-time
    //! `n`, which means that the usage would become `arg(int_<n>)(x...)`,
    //! which is more cumbersome to write than `arg<n>(x...)`. This is open
    //! for discussion.
    //! @endinternal
    //!
    //! ### Example
    //! @include example/functional/arg.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto arg = [](auto&& x1, ..., auto&& xm) -> decltype(auto) {
        return forwarded(xn);
    };
#else
    template <std::size_t n, typename = void>
    struct arg_t;

    template <>
    struct arg_t<1> {
        template <typename X1, typename ...Xn>
        constexpr X1 operator()(X1&& x1, Xn&& ...) const
        { return static_cast<X1&&>(x1); }
    };

    template <>
    struct arg_t<2> {
        template <typename X1, typename X2, typename ...Xn>
        constexpr X2 operator()(X1&&, X2&& x2, Xn&& ...) const
        { return static_cast<X2&&>(x2); }
    };

    template <>
    struct arg_t<3> {
        template <typename X1, typename X2, typename X3, typename ...Xn>
        constexpr X3 operator()(X1&&, X2&&, X3&& x3, Xn&& ...) const
        { return static_cast<X3&&>(x3); }
    };

    template <>
    struct arg_t<4> {
        template <typename X1, typename X2, typename X3, typename X4, typename ...Xn>
        constexpr X4 operator()(X1&&, X2&&, X3&&, X4&& x4, Xn&& ...) const
        { return static_cast<X4&&>(x4); }
    };

    template <>
    struct arg_t<5> {
        template <typename X1, typename X2, typename X3, typename X4,
                  typename X5, typename ...Xn>
        constexpr X5 operator()(X1&&, X2&&, X3&&, X4&&, X5&& x5, Xn&& ...) const
        { return static_cast<X5&&>(x5); }
    };

    template <std::size_t n, typename>
    struct arg_t {
        static_assert(n > 0,
        "invalid usage of boost::hana::arg<n> with n == 0");

        template <typename X1, typename X2, typename X3, typename X4,
                  typename X5, typename ...Xn>
        constexpr decltype(auto)
        operator()(X1&&, X2&&, X3&&, X4&&, X5&&, Xn&& ...xn) const {
            static_assert(sizeof...(xn) >= n - 5,
            "invalid usage of boost::hana::arg<n> with too few arguments");

            // Since compilers will typically try to continue for a bit after
            // an error/static assertion, we must avoid sending the compiler
            // in a very long computation if n == 0.
            return arg_t<n == 0 ? 1 : n - 5>{}(static_cast<Xn&&>(xn)...);
        }
    };

    template <std::size_t n>
    struct arg_t<n, std::enable_if_t<(n > 25)>> {
        template <
            typename X1,  typename X2,  typename X3,  typename X4,  typename X5,
            typename X6,  typename X7,  typename X8,  typename X9,  typename X10,
            typename X11, typename X12, typename X13, typename X14, typename X15,
            typename X16, typename X17, typename X18, typename X19, typename X20,
            typename X21, typename X22, typename X23, typename X24, typename X25,
            typename ...Xn>
        constexpr decltype(auto)
        operator()(X1&&,  X2&&,  X3&&,  X4&&,  X5&&,
                   X6&&,  X7&&,  X8&&,  X9&&,  X10&&,
                   X11&&, X12&&, X13&&, X14&&, X15&&,
                   X16&&, X17&&, X18&&, X19&&, X20&&,
                   X21&&, X22&&, X23&&, X24&&, X25&&, Xn&& ...xn) const
        { return arg_t<n - 25>{}(static_cast<Xn&&>(xn)...); }
    };

    template <std::size_t n>
    constexpr arg_t<n> arg{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ARG_HPP

/* arg.hpp
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
*/