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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
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
*/