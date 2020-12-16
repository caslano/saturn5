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
U8Lzd3xFFU7bSsufpXQr81rjJ/MExxsb4/rW0PQVIv9MU/5K3kX4VlrTVC3v4gRpYV88LWyPp11TS7tWgrTQNy7t2lraUi1tP/rh1ZRyjuc76I+51SkOJW7K8Wk4nqceV0fQknq8xCGhbgxE/X5dQD2+Do6XxI8bAhg/TImfR8rA9I9T2h2Pv/TWx6OjtRp9GJSQIHYdfPzbulw+HwY/cme02xMa9Md1kRT66hLqU3LH5dz+ujWmfcjMpGWUO0y6kPkApNQ66HSM1cH1lfhnZ8TLosJSbhs4sGnlFtPKrVIrtw21tDUJ7Yg/Q6rboO8Y+W9kyr/alP/Glvw3cWCz5L+plv9maloiDiMBrTboNhgHzHbUmOzYwmRHrcWO6Q5sFjvqNDvqtbSztPqr8iAejI4N6XU3Pm6TlHkrKb7vzFHqss8T86j7ReCow0HPoCxto9XRLU11tERS5ostHumHTD7tQNcJXFJhdhatwKgY1qNanxCRxuLQYIrJ1paYbOPAZonJtlpMttPSbpPIHtWXcP9+aJW6MaZD5uuOHZLrSRoTRU8jW1eU64SOzp625lZdjemIEZcmVkc8Y6WAdRXGAbMdLZqOHbS64oqXsTcij0QDel1pjh9T5v5C4VjA69ePt8aPh5X5B7S5HByRcmbF+8TtRkIh3K31bR7zDO6gZN4z7ghyr9Dy2zGuI7L/SPxyStW7U1yHT1LqDpzKnG2qdw6pq7O9rXmPXedhjNoxq1N3bqWjyKNOywN9PT6+6brdFVJ8v87cFrBfr+zP1PzYOW5DcMg9a14HrtcwvvKNDA8fEPdlpaPIS2m7jaa2226qp3Ms9bTDgc1STzu1etqlpYW+ogzJcj7D8W4t3Vy97On2hXgbZW8cMJf9PEtevY7xee2m5bU7e443Th6zPMOBoH4Pdr3NpRQXnY9fLmp78dHkLavDjaMUlwemY/ns2AJuTM2kTVdKi8GVEKdqQdqXqo5zCczj8wnfB7RdkELLSK1C/tGkCxfSuN7bsqbY9ippTC2mqXoFQjNRGCk7YvQDmLYPTXDdxMq1Lj3L0E1zxfbX2CZfW574jQp2pSawGnRcX4yaMUE9asXQynMC3Vgqi1T1Ni/4fIPgwxDWWPePDAz4xfofwccybD3pkfyBE9EHWFJdeG/3WRrh53NsPfQj+iCRnaeTkj/xZIkZJISileZFsFYr4tcwgot/xNbOWnPA0zRJ3yji+c+vt02pJ0txQd//K3eFE4q3rb995a5YdROtv5O8HFfgpSLm5bhJ62Dqy33Vta1paYGDvqRjsn/RsteV+mnvjBqbY0efP+mJwyrisS/SHwwvGAjYv7KS/f6kJx6rjBeTIMFgwGNXLuDz25aJepN25yubJ4sNZf+OJcWTuUBYGWAKrCE09tzaYydJnp+JP0bfNxwbWwAcwSVI/A6Yz+nddFOnJ4a52f6RmNJd4KmmCDqOqFN/tmhjwUcd4zNVAo/8YN1MJCb8AOUC1YygVbEWCGAtgchDRKJrmRM+22TL5kGf+DO2+rOwYqWI/+RREPd8KPUH6+tSKkz7zxin/XE0Lap6HRYOV1ofwV05vXZlLvrQrvrAsUC1jz/pJramXPChyXSv7mSa7MrmBHGPFLqNvjsge9yeUU8g6OlXlwYPjX8cqrWjt60b9wp66wWLYaVn1pOa4B9Sbt0JBE7kEduUFgrabapQl2IrFV+GaJbCQ+/xQCZfGZboVRGpjS0n+pLasTdcpDq6nZQ3+E7sdax/wYtybY24Jvzm37/s/bIp6Uz4/tdUlf2V7wVNSduEXxKb2osvRd7/OZEXxf5F76RKPko3v8Yn/QtXTdoxa2mvCGIIbvotisnJLZk=
*/