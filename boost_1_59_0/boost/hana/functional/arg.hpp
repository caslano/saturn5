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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr arg_t<n> arg{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_ARG_HPP

/* arg.hpp
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
*/