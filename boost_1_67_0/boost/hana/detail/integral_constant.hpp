/*!
@file
Defines the barebones `boost::hana::integral_constant` template, but no
operations on it.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_INTEGRAL_CONSTANT_HPP
#define BOOST_HANA_DETAIL_INTEGRAL_CONSTANT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/operators/adl.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! Tag representing `hana::integral_constant`.
    //! @relates hana::integral_constant
    template <typename T>
    struct integral_constant_tag {
        using value_type = T;
    };

    namespace ic_detail {
        template <typename T, T v>
        struct with_index_t {
            template <typename F>
            constexpr void operator()(F&& f) const;
        };

        template <typename T, T v>
        struct times_t {
            static constexpr with_index_t<T, v> with_index{};

            template <typename F>
            constexpr void operator()(F&& f) const;
        };
    }

    //! @ingroup group-datatypes
    //! Compile-time value of an integral type.
    //!
    //! An `integral_constant` is an object that represents a compile-time
    //! integral value. As the name suggests, `hana::integral_constant` is
    //! basically equivalent to `std::integral_constant`, except that
    //! `hana::integral_constant` also provide other goodies to make them
    //! easier to use, like arithmetic operators and similar features. In
    //! particular, `hana::integral_constant` is guaranteed to inherit from
    //! the corresponding `std::integral_constant`, and hence have the same
    //! members and capabilities. The sections below explain the extensions
    //! to `std::integral_constant` provided by `hana::integral_constant`.
    //!
    //!
    //! Arithmetic operators
    //! --------------------
    //! `hana::integral_constant` provides arithmetic operators that return
    //! `hana::integral_constant`s to ease writing compile-time arithmetic:
    //! @snippet example/integral_constant.cpp operators
    //!
    //! It is pretty important to realize that these operators return other
    //! `integral_constant`s, not normal values of an integral type.
    //! Actually, all those operators work pretty much in the same way.
    //! Simply put, for an operator `@`,
    //! @code
    //!     integral_constant<T, x>{} @ integral_constant<T, y>{} == integral_constant<T, x @ y>{}
    //! @endcode
    //!
    //! The fact that the operators return `Constant`s is very important
    //! because it allows all the information that's known at compile-time
    //! to be conserved as long as it's only used with other values known at
    //! compile-time. It is also interesting to observe that whenever an
    //! `integral_constant` is combined with a normal runtime value, the
    //! result will be a runtime value (because of the implicit conversion).
    //! In general, this gives us the following table
    //!
    //! left operand        | right operand       | result
    //! :-----------------: | :-----------------: | :-----------------:
    //! `integral_constant` | `integral_constant` | `integral_constant`
    //! `integral_constant` | runtime             | runtime
    //! runtime             | `integral_constant` | runtime
    //! runtime             | runtime             | runtime
    //!
    //! The full range of provided operators is
    //! - Arithmetic: binary `+`, binary `-`, `/`, `*`, `%`, unary `+`, unary `-`
    //! - Bitwise: `~`, `&`, `|`, `^`, `<<`, `>>`
    //! - Comparison: `==`, `!=`, `<`, `<=`, `>`, `>=`
    //! - %Logical: `||`, `&&`, `!`
    //!
    //!
    //! Construction with user-defined literals
    //! ---------------------------------------
    //! `integral_constant`s of type `long long` can be created with the
    //! `_c` user-defined literal, which is contained in the `literals`
    //! namespace:
    //! @snippet example/integral_constant.cpp literals
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Constant` and `IntegralConstant`\n
    //! An `integral_constant` is a model of the `IntegralConstant` concept in
    //! the most obvious way possible. Specifically,
    //! @code
    //!     integral_constant<T, v>::value == v // of type T
    //! @endcode
    //! The model of `Constant` follows naturally from the model of `IntegralConstant`, i.e.
    //! @code
    //!     value<integral_constant<T, v>>() == v // of type T
    //! @endcode
    //!
    //! 2. `Comparable`, `Orderable`, `Logical`, `Monoid`, `Group`, `Ring`, and `EuclideanRing`, `Hashable`\n
    //! Those models are exactly those provided for `Constant`s, which are
    //! documented in their respective concepts.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename T, T v>
    struct integral_constant {
        //! Call a function n times.
        //!
        //! `times` allows a nullary function to be invoked `n` times:
        //! @code
        //!     int_<3>::times(f)
        //! @endcode
        //! should be expanded by any decent compiler to
        //! @code
        //!     f(); f(); f();
        //! @endcode
        //!
        //! This can be useful in several contexts, e.g. for loop unrolling:
        //! @snippet example/integral_constant.cpp times_loop_unrolling
        //!
        //! Note that `times` is really a static function object, not just a
        //! static function. This allows `int_<n>::%times` to be passed to
        //! higher-order algorithms:
        //! @snippet example/integral_constant.cpp times_higher_order
        //!
        //! Also, since static members can be accessed using both the `.` and
        //! the `::` syntax, one can take advantage of this (loophole?) to
        //! call `times` on objects just as well as on types:
        //! @snippet example/integral_constant.cpp from_object
        //!
        //! @note
        //! `times` is equivalent to the `hana::repeat` function, which works
        //! on an arbitrary `IntegralConstant`.
        //!
        //! Sometimes, it is also useful to know the index we're at inside the
        //! function. This can be achieved by using `times.with_index`:
        //! @snippet example/integral_constant.cpp times_with_index_runtime
        //!
        //! Remember that `times` is a _function object_, and hence it can
        //! have subobjects. `with_index` is just a function object nested
        //! inside `times`, which allows for this nice little interface. Also
        //! note that the indices passed to the function are `integral_constant`s;
        //! they are known at compile-time. Hence, we can do compile-time stuff
        //! with them, like indexing inside a tuple:
        //! @snippet example/integral_constant.cpp times_with_index_compile_time
        //!
        //! @note
        //! `times.with_index(f)` guarantees that the calls to `f` will be
        //! done in order of ascending index. In other words, `f` will be
        //! called as `f(0)`, `f(1)`, `f(2)`, etc., but with `integral_constant`s
        //! instead of normal integers. Side effects can also be done in the
        //! function passed to `times` and `times.with_index`.
        template <typename F>
        static constexpr void times(F&& f) {
            f(); f(); ... f(); // n times total
        }

        //! Equivalent to `hana::plus`
        template <typename X, typename Y>
        friend constexpr auto operator+(X&& x, Y&& y);

        //! Equivalent to `hana::minus`
        template <typename X, typename Y>
        friend constexpr auto operator-(X&& x, Y&& y);

        //! Equivalent to `hana::negate`
        template <typename X>
        friend constexpr auto operator-(X&& x);

        //! Equivalent to `hana::mult`
        template <typename X, typename Y>
        friend constexpr auto operator*(X&& x, Y&& y);

        //! Equivalent to `hana::div`
        template <typename X, typename Y>
        friend constexpr auto operator/(X&& x, Y&& y);

        //! Equivalent to `hana::mod`
        template <typename X, typename Y>
        friend constexpr auto operator%(X&& x, Y&& y);

        //! Equivalent to `hana::equal`
        template <typename X, typename Y>
        friend constexpr auto operator==(X&& x, Y&& y);

        //! Equivalent to `hana::not_equal`
        template <typename X, typename Y>
        friend constexpr auto operator!=(X&& x, Y&& y);

        //! Equivalent to `hana::or_`
        template <typename X, typename Y>
        friend constexpr auto operator||(X&& x, Y&& y);

        //! Equivalent to `hana::and_`
        template <typename X, typename Y>
        friend constexpr auto operator&&(X&& x, Y&& y);

        //! Equivalent to `hana::not_`
        template <typename X>
        friend constexpr auto operator!(X&& x);

        //! Equivalent to `hana::less`
        template <typename X, typename Y>
        friend constexpr auto operator<(X&& x, Y&& y);

        //! Equivalent to `hana::greater`
        template <typename X, typename Y>
        friend constexpr auto operator>(X&& x, Y&& y);

        //! Equivalent to `hana::less_equal`
        template <typename X, typename Y>
        friend constexpr auto operator<=(X&& x, Y&& y);

        //! Equivalent to `hana::greater_equal`
        template <typename X, typename Y>
        friend constexpr auto operator>=(X&& x, Y&& y);
    };
#else
    template <typename T, T v>
#ifdef BOOST_HANA_WORKAROUND_MSVC_EMPTYBASE
    struct __declspec(empty_bases) integral_constant
#else
    struct integral_constant
#endif
        : std::integral_constant<T, v>
        , detail::operators::adl<integral_constant<T, v>>
    {
        using type = integral_constant; // override std::integral_constant::type
        static constexpr ic_detail::times_t<T, v> times{};
        using hana_tag = integral_constant_tag<T>;
    };
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
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
*/