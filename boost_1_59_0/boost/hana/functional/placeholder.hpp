/*!
@file
Defines `boost::hana::_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_PLACEHOLDER_HPP
#define BOOST_HANA_FUNCTIONAL_PLACEHOLDER_HPP

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>
#include <boost/hana/detail/decay.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana {
    //! @ingroup group-functional
    //! Create simple functions representing C++ operators inline.
    //!
    //! Specifically, `_` is an object used as a placeholder to build
    //! function objects representing calls to C++ operators. It works
    //! by overloading the operators between `_` and any object so that
    //! they return a function object which actually calls the corresponding
    //! operator on its argument(s). Hence, for any supported operator `@`:
    //! @code
    //!     (_ @ _)(x, y) == x @ y
    //! @endcode
    //!
    //! Operators may also be partially applied to one argument inline:
    //! @code
    //!     (x @ _)(y) == x @ y
    //!     (_ @ y)(x) == x @ y
    //! @endcode
    //!
    //! When invoked with more arguments than required, functions created with
    //! `_` will discard the superfluous instead of triggering an error:
    //! @code
    //!     (_ @ _)(x, y, z...) == x @ y
    //! @endcode
    //!
    //! This makes functions created with `_` easier to use in higher-order
    //! algorithms, which sometime provide more information than necessary
    //! to their callbacks.
    //!
    //! ### Supported operators
    //! - Arithmetic: binary `+`, binary `-`, `/`, `*`, `%`, unary `+`, unary `-`
    //! - Bitwise: `~`, `&`, `|`, `^`, `<<`, `>>`
    //! - Comparison: `==`, `!=`, `<`, `<=`, `>`, `>=`
    //! - %Logical: `||`, `&&`, `!`
    //! - Member access: `*` (dereference), `[]` (array subscript)
    //! - Other: `()` (function call)
    //!
    //! More complex functionality like the ability to compose placeholders
    //! into larger function objects inline are not supported. This is on
    //! purpose; you should either use C++14 generic lambdas or a library
    //! like [Boost.Phoenix][] if you need bigger guns. The goal here is
    //! to save you a couple of characters in simple situations.
    //!
    //! ### Example
    //! @include example/functional/placeholder.cpp
    //!
    //! [Boost.Phoenix]: http://www.boost.org/doc/libs/release/libs/phoenix/doc/html/index.html
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr unspecified _{};
#else
    namespace placeholder_detail {
        template <typename I>
        struct subscript {
            I i;

            template <typename Xs, typename ...Z>
            constexpr auto operator()(Xs&& xs, Z const& ...) const&
                -> decltype(static_cast<Xs&&>(xs)[i])
            { return static_cast<Xs&&>(xs)[i]; }

            template <typename Xs, typename ...Z>
            constexpr auto operator()(Xs&& xs, Z const& ...) &
                -> decltype(static_cast<Xs&&>(xs)[i])
            { return static_cast<Xs&&>(xs)[i]; }

            template <typename Xs, typename ...Z>
            constexpr auto operator()(Xs&& xs, Z const& ...) &&
                -> decltype(static_cast<Xs&&>(xs)[std::declval<I>()])
            { return static_cast<Xs&&>(xs)[std::move(i)]; }
        };

        template <typename F, typename Xs, std::size_t ...i>
        constexpr decltype(auto) invoke_impl(F&& f, Xs&& xs, std::index_sequence<i...>) {
            return static_cast<F&&>(f)(hana::at_c<i>(static_cast<Xs&&>(xs).storage_)...);
        }

        template <typename ...X>
        struct invoke;

        struct placeholder {
            struct secret { };

            template <typename X>
            constexpr decltype(auto) operator[](X&& x) const
            { return detail::create<subscript>{}(static_cast<X&&>(x)); }

            template <typename ...X>
            constexpr invoke<typename detail::decay<X>::type...>
            operator()(X&& ...x) const {
                return {secret{}, static_cast<X&&>(x)...};
            }
        };

        template <typename ...X>
        struct invoke {
            template <typename ...Y>
            constexpr invoke(placeholder::secret, Y&& ...y)
                : storage_{static_cast<Y&&>(y)...}
            { }

            basic_tuple<X...> storage_;

            template <typename F, typename ...Z>
            constexpr auto operator()(F&& f, Z const& ...) const& -> decltype(
                static_cast<F&&>(f)(std::declval<X const&>()...)
            ) {
                return invoke_impl(static_cast<F&&>(f), *this,
                                   std::make_index_sequence<sizeof...(X)>{});
            }

            template <typename F, typename ...Z>
            constexpr auto operator()(F&& f, Z const& ...) & -> decltype(
                static_cast<F&&>(f)(std::declval<X&>()...)
            ) {
                return invoke_impl(static_cast<F&&>(f), *this,
                                   std::make_index_sequence<sizeof...(X)>{});
            }

            template <typename F, typename ...Z>
            constexpr auto operator()(F&& f, Z const& ...) && -> decltype(
                static_cast<F&&>(f)(std::declval<X&&>()...)
            ) {
                return invoke_impl(static_cast<F&&>(f), static_cast<invoke&&>(*this),
                                   std::make_index_sequence<sizeof...(X)>{});
            }
        };

#define BOOST_HANA_PLACEHOLDER_BINARY_OP(op, op_name)                           \
    template <typename X>                                                       \
    struct op_name ## _left {                                                   \
        X x;                                                                    \
                                                                                \
        template <typename Y, typename ...Z>                                    \
        constexpr auto operator()(Y&& y, Z const& ...) const& -> decltype(      \
            std::declval<X const&>() op static_cast<Y&&>(y))                    \
        { return x op static_cast<Y&&>(y); }                                    \
                                                                                \
        template <typename Y, typename ...Z>                                    \
        constexpr auto operator()(Y&& y, Z const& ...) & -> decltype(           \
            std::declval<X&>() op static_cast<Y&&>(y))                          \
        { return x op static_cast<Y&&>(y); }                                    \
                                                                                \
        template <typename Y, typename ...Z>                                    \
        constexpr auto operator()(Y&& y, Z const& ...) && -> decltype(          \
            std::declval<X>() op static_cast<Y&&>(y))                           \
        { return std::move(x) op static_cast<Y&&>(y); }                         \
    };                                                                          \
                                                                                \
    template <typename Y>                                                       \
    struct op_name ## _right {                                                  \
        Y y;                                                                    \
                                                                                \
        template <typename X, typename ...Z>                                    \
        constexpr auto operator()(X&& x, Z const& ...) const& -> decltype(      \
            static_cast<X&&>(x) op std::declval<Y const&>())                    \
        { return static_cast<X&&>(x) op y; }                                    \
                                                                                \
        template <typename X, typename ...Z>                                    \
        constexpr auto operator()(X&& x, Z const& ...) & -> decltype(           \
            static_cast<X&&>(x) op std::declval<Y&>())                          \
        { return static_cast<X&&>(x) op y; }                                    \
                                                                                \
        template <typename X, typename ...Z>                                    \
        constexpr auto operator()(X&& x, Z const& ...) && -> decltype(          \
            static_cast<X&&>(x) op std::declval<Y>())                           \
        { return static_cast<X&&>(x) op std::move(y); }                         \
    };                                                                          \
                                                                                \
    struct op_name {                                                            \
        template <typename X, typename Y, typename ...Z>                        \
        constexpr auto operator()(X&& x, Y&& y, Z const& ...) const -> decltype(\
            static_cast<X&&>(x) op static_cast<Y&&>(y))                         \
        { return static_cast<X&&>(x) op static_cast<Y&&>(y); }                  \
    };                                                                          \
                                                                                \
    template <typename X>                                                       \
    constexpr decltype(auto) operator op (X&& x, placeholder)                   \
    { return detail::create<op_name ## _left>{}(static_cast<X&&>(x)); }         \
                                                                                \
    template <typename Y>                                                       \
    constexpr decltype(auto) operator op (placeholder, Y&& y)                   \
    { return detail::create<op_name ## _right>{}(static_cast<Y&&>(y)); }        \
                                                                                \
    inline constexpr decltype(auto) operator op (placeholder, placeholder)      \
    { return op_name{}; }                                                       \
/**/

#define BOOST_HANA_PLACEHOLDER_UNARY_OP(op, op_name)                        \
    struct op_name {                                                        \
        template <typename X, typename ...Z>                                \
        constexpr auto operator()(X&& x, Z const& ...) const                \
            -> decltype(op static_cast<X&&>(x))                             \
        { return op static_cast<X&&>(x); }                                  \
    };                                                                      \
                                                                            \
    inline constexpr decltype(auto) operator op (placeholder)               \
    { return op_name{}; }                                                   \
/**/
            // Arithmetic
            BOOST_HANA_PLACEHOLDER_UNARY_OP(+, unary_plus)
            BOOST_HANA_PLACEHOLDER_UNARY_OP(-, unary_minus)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(+, plus)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(-, minus)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(*, times)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(/, divide)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(%, modulo)

            // Bitwise
            BOOST_HANA_PLACEHOLDER_UNARY_OP(~, bitwise_not)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(&, bitwise_and)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(|, bitwise_or)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(^, bitwise_xor)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(<<, left_shift)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(>>, right_shift)

            // Comparison
            BOOST_HANA_PLACEHOLDER_BINARY_OP(==, equal)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(!=, not_equal)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(<, less)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(<=, less_equal)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(>, greater)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(>=, greater_equal)

            // Logical
            BOOST_HANA_PLACEHOLDER_BINARY_OP(||, logical_or)
            BOOST_HANA_PLACEHOLDER_BINARY_OP(&&, logical_and)
            BOOST_HANA_PLACEHOLDER_UNARY_OP(!, logical_not)

            // Member access (array subscript is a member function)
            BOOST_HANA_PLACEHOLDER_UNARY_OP(*, dereference)

            // Other (function call is a member function)

#undef BOOST_HANA_PREFIX_PLACEHOLDER_OP
#undef BOOST_HANA_BINARY_PLACEHOLDER_OP
    } // end namespace placeholder_detail

    BOOST_HANA_INLINE_VARIABLE constexpr placeholder_detail::placeholder _{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_PLACEHOLDER_HPP

/* placeholder.hpp
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
*/