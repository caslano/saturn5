/*!
@file
Forward declares `boost::hana::type` and related utilities.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TYPE_HPP
#define BOOST_HANA_FWD_TYPE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Base class of `hana::type`; used for pattern-matching.
    //! @relates hana::type
    //!
    //! Example
    //! -------
    //! @include example/type/basic_type.cpp
    template <typename T>
    struct basic_type;

    //! @ingroup group-datatypes
    //! C++ type in value-level representation.
    //!
    //! A `type` is a special kind of object representing a C++ type like
    //! `int`, `void`, `std::vector<float>` or anything else you can imagine.
    //!
    //! This page explains how `type`s work at a low level. To gain
    //! intuition about type-level metaprogramming in Hana, you should
    //! read the [tutorial section](@ref tutorial-type) on type-level
    //! computations.
    //!
    //!
    //! @note
    //! For subtle reasons, the actual representation of `hana::type` is
    //! implementation-defined. In particular, `hana::type` may be a dependent
    //! type, so one should not attempt to do pattern matching on it. However,
    //! one can assume that `hana::type` _inherits_ from `hana::basic_type`,
    //! which can be useful when declaring overloaded functions:
    //! @code
    //!     template <typename T>
    //!     void f(hana::basic_type<T>) {
    //!         // do something with T
    //!     }
    //! @endcode
    //! The full story is that [ADL][] causes template arguments to be
    //! instantiated. Hence, if `hana::type` were defined naively, expressions
    //! like `hana::type<T>{} == hana::type<U>{}` would cause both `T` and `U`
    //! to be instantiated. This is usually not a problem, except when `T` or
    //! `U` should not be instantiated. To avoid these instantiations,
    //! `hana::type` is implemented using some cleverness, and that is
    //! why the representation is implementation-defined. When that
    //! behavior is not required, `hana::basic_type` can be used instead.
    //!
    //!
    //! @anchor type_lvalues_and_rvalues
    //! Lvalues and rvalues
    //! -------------------
    //! When storing `type`s in heterogeneous containers, some algorithms
    //! will return references to those objects. Since we are primarily
    //! interested in accessing their nested `::%type`, receiving a reference
    //! is undesirable; we would end up trying to fetch the nested `::%type`
    //! inside a reference type, which is a compilation error:
    //! @code
    //!   auto ts = make_tuple(type_c<int>, type_c<char>);
    //!   using T = decltype(ts[0_c])::type; // error: 'ts[0_c]' is a reference!
    //! @endcode
    //!
    //! For this reason, `type`s provide an overload of the unary `+`
    //! operator that can be used to turn a lvalue into a rvalue. So when
    //! using a result which might be a reference to a `type` object, one
    //! can use `+` to make sure a rvalue is obtained before fetching its
    //! nested `::%type`:
    //! @code
    //!   auto ts = make_tuple(type_c<int>, type_c<char>);
    //!   using T = decltype(+ts[0_c])::type; // ok: '+ts[0_c]' is an rvalue
    //! @endcode
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! Two types are equal if and only if they represent the same C++ type.
    //! Hence, equality is equivalent to the `std::is_same` type trait.
    //! @include example/type/comparable.cpp
    //!
    //! 2. `Hashable`\n
    //! The hash of a type is just that type itself. In other words, `hash`
    //! is the identity function on `hana::type`s.
    //! @include example/type/hashable.cpp
    //!
    //! [ADL]: http://en.cppreference.com/w/cpp/language/adl
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename T>
    struct type {
        //! Returns rvalue of self.
        //! See @ref type_lvalues_and_rvalues "description".
        constexpr auto operator+() const;

        //! Equivalent to `hana::equal`
        template <typename X, typename Y>
        friend constexpr auto operator==(X&& x, Y&& y);

        //! Equivalent to `hana::not_equal`
        template <typename X, typename Y>
        friend constexpr auto operator!=(X&& x, Y&& y);
    };
#else
    template <typename T>
    struct type_impl;

    template <typename T>
    using type = typename type_impl<T>::_;
#endif

    //! Tag representing `hana::type`.
    //! @relates hana::type
    struct type_tag { };

    //! Creates an object representing the C++ type `T`.
    //! @relates hana::type
    template <typename T>
    constexpr type<T> type_c{};

    //! `decltype` keyword, lifted to Hana.
    //! @relates hana::type
    //!
    //! @deprecated
    //! The semantics of `decltype_` can be confusing, and `hana::typeid_`
    //! should be preferred instead. `decltype_` may be removed in the next
    //! major version of the library.
    //!
    //! `decltype_` is somewhat equivalent to `decltype` in that it returns
    //! the type of an object, except it returns it as a `hana::type` which
    //! is a first-class citizen of Hana instead of a raw C++ type.
    //! Specifically, given an object `x`, `decltype_` satisfies
    //! @code
    //!   decltype_(x) == type_c<decltype(x) with references stripped>
    //! @endcode
    //!
    //! As you can see, `decltype_` will strip any reference from the
    //! object's actual type. The reason for doing so is explained below.
    //! However, any `cv`-qualifiers will be retained. Also, when given a
    //! `hana::type`, `decltype_` is just the identity function. Hence,
    //! for any C++ type `T`,
    //! @code
    //!   decltype_(type_c<T>) == type_c<T>
    //! @endcode
    //!
    //! In conjunction with the way `metafunction` & al. are specified, this
    //! behavior makes it easier to interact with both types and values at
    //! the same time. However, it does make it impossible to create a `type`
    //! containing another `type` with `decltype_`. In other words, it is
    //! not possible to create a `type_c<decltype(type_c<T>)>` with this
    //! utility, because `decltype_(type_c<T>)` would be just `type_c<T>`
    //! instead of `type_c<decltype(type_c<T>)>`. This use case is assumed
    //! to be rare and a hand-coded function can be used if this is needed.
    //!
    //!
    //! ### Rationale for stripping the references
    //! The rules for template argument deduction are such that a perfect
    //! solution that always matches `decltype` is impossible. Hence, we
    //! have to settle on a solution that's good and and consistent enough
    //! for our needs. One case where matching `decltype`'s behavior is
    //! impossible is when the argument is a plain, unparenthesized variable
    //! or function parameter. In that case, `decltype_`'s argument will be
    //! deduced as a reference to that variable, but `decltype` would have
    //! given us the actual type of that variable, without references. Also,
    //! given the current definition of `metafunction` & al., it would be
    //! mostly useless if `decltype_` could return a reference, because it
    //! is unlikely that `F` expects a reference in its simplest use case:
    //! @code
    //!   int i = 0;
    //!   auto result = metafunction<F>(i);
    //! @endcode
    //!
    //! Hence, always discarding references seems to be the least painful
    //! solution.
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/decltype.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto decltype_ = see documentation;
#else
    struct decltype_t {
        template <typename T>
        constexpr auto operator()(T&&) const;
    };

    constexpr decltype_t decltype_{};
#endif

    //! Returns a `hana::type` representing the type of a given object.
    //! @relates hana::type
    //!
    //! `hana::typeid_` is somewhat similar to `typeid` in that it returns
    //! something that represents the type of an object. However, what
    //! `typeid` returns represent the _runtime_ type of the object, while
    //! `hana::typeid_` returns the _static_ type of the object. Specifically,
    //! given an object `x`, `typeid_` satisfies
    //! @code
    //!   typeid_(x) == type_c<decltype(x) with ref and cv-qualifiers stripped>
    //! @endcode
    //!
    //! As you can see, `typeid_` strips any reference and cv-qualifier from
    //! the object's actual type. The reason for doing so is that it faithfully
    //! models how the language's `typeid` behaves with respect to reference
    //! and cv-qualifiers, and it also turns out to be the desirable behavior
    //! most of the time. Also, when given a `hana::type`, `typeid_` is just
    //! the identity function. Hence, for any C++ type `T`,
    //! @code
    //!   typeid_(type_c<T>) == type_c<T>
    //! @endcode
    //!
    //! In conjunction with the way `metafunction` & al. are specified, this
    //! behavior makes it easier to interact with both types and values at
    //! the same time. However, it does make it impossible to create a `type`
    //! containing another `type` using `typeid_`. This use case is assumed
    //! to be rare and a hand-coded function can be used if this is needed.
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/typeid.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto typeid_ = see documentation;
#else
    struct typeid_t {
        template <typename T>
        constexpr auto operator()(T&&) const;
    };

    constexpr typeid_t typeid_{};
#endif

#ifdef BOOST_HANA_DOXYGEN_INVOKED
    //! Equivalent to `decltype_`, provided for convenience.
    //! @relates hana::type
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/make.cpp
    template <>
    constexpr auto make<type_tag> = hana::decltype_;
#endif

    //! Equivalent to `make<type_tag>`, provided for convenience.
    //! @relates hana::type
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/make.cpp
    constexpr auto make_type = hana::make<type_tag>;

    //! `sizeof` keyword, lifted to Hana.
    //! @relates hana::type
    //!
    //! `sizeof_` is somewhat equivalent to `sizeof` in that it returns the
    //! size of an expression or type, but it takes an arbitrary expression
    //! or a `hana::type` and returns its size as an `integral_constant`.
    //! Specifically, given an expression `expr`, `sizeof_` satisfies
    //! @code
    //!   sizeof_(expr) == size_t<sizeof(decltype(expr) with references stripped)>
    //! @endcode
    //!
    //! However, given a `type`, `sizeof_` will simply fetch the size
    //! of the C++ type represented by that object. In other words,
    //! @code
    //!   sizeof_(type_c<T>) == size_t<sizeof(T)>
    //! @endcode
    //!
    //! The behavior of `sizeof_` is consistent with that of `decltype_`.
    //! In particular, see `decltype_`'s documentation to understand why
    //! references are always stripped by `sizeof_`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/sizeof.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto sizeof_ = [](auto&& x) {
        using T = typename decltype(hana::decltype_(x))::type;
        return hana::size_c<sizeof(T)>;
    };
#else
    struct sizeof_t {
        template <typename T>
        constexpr auto operator()(T&&) const;
    };

    constexpr sizeof_t sizeof_{};
#endif

    //! `alignof` keyword, lifted to Hana.
    //! @relates hana::type
    //!
    //! `alignof_` is somewhat equivalent to `alignof` in that it returns the
    //! alignment required by any instance of a type, but it takes a `type`
    //! and returns its alignment as an `integral_constant`. Like `sizeof`
    //! which works for expressions and type-ids, `alignof_` can also be
    //! called on an arbitrary expression. Specifically, given an expression
    //! `expr` and a C++ type `T`, `alignof_` satisfies
    //! @code
    //!   alignof_(expr) == size_t<alignof(decltype(expr) with references stripped)>
    //!   alignof_(type_c<T>) == size_t<alignof(T)>
    //! @endcode
    //!
    //! The behavior of `alignof_` is consistent with that of `decltype_`.
    //! In particular, see `decltype_`'s documentation to understand why
    //! references are always stripped by `alignof_`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/alignof.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto alignof_ = [](auto&& x) {
        using T = typename decltype(hana::decltype_(x))::type;
        return hana::size_c<alignof(T)>;
    };
#else
    struct alignof_t {
        template <typename T>
        constexpr auto operator()(T&&) const;
    };

    constexpr alignof_t alignof_{};
#endif

    //! Checks whether a SFINAE-friendly expression is valid.
    //! @relates hana::type
    //!
    //! Given a SFINAE-friendly function, `is_valid` returns whether the
    //! function call is valid with the given arguments. Specifically, given
    //! a function `f` and arguments `args...`,
    //! @code
    //!   is_valid(f, args...) == whether f(args...) is valid
    //! @endcode
    //!
    //! The result is returned as a compile-time `Logical`. Furthermore,
    //! `is_valid` can be used in curried form as follows:
    //! @code
    //!   is_valid(f)(args...)
    //! @endcode
    //!
    //! This syntax makes it easy to create functions that check the validity
    //! of a generic expression on any given argument(s).
    //!
    //! @warning
    //! To check whether calling a nullary function `f` is valid, one should
    //! use the `is_valid(f)()` syntax. Indeed, `is_valid(f /* no args */)`
    //! will be interpreted as the currying of `is_valid` to `f` rather than
    //! the application of `is_valid` to `f` and no arguments.
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/is_valid.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_valid = [](auto&& f) {
        return [](auto&& ...args) {
            return whether f(args...) is a valid expression;
        };
    };
#else
    struct is_valid_t {
        template <typename F>
        constexpr auto operator()(F&&) const;

        template <typename F, typename ...Args>
        constexpr auto operator()(F&&, Args&&...) const;
    };

    constexpr is_valid_t is_valid{};
#endif

    //! Lift a template to a Metafunction.
    //! @ingroup group-Metafunction
    //!
    //! Given a template class or template alias `f`, `template_<f>` is a
    //! `Metafunction` satisfying
    //! @code
    //!     template_<f>(type_c<x>...) == type_c<f<x...>>
    //!     decltype(template_<f>)::apply<x...>::type == f<x...>
    //! @endcode
    //!
    //! @note
    //! In a SFINAE context, the expression `template_<f>(type_c<x>...)` is
    //! valid whenever the expression `f<x...>` is valid.
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/template.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <template <typename ...> class F>
    constexpr auto template_ = [](basic_type<T>...) {
        return hana::type_c<F<T...>>;
    };
#else
    template <template <typename ...> class F>
    struct template_t;

    template <template <typename ...> class F>
    constexpr template_t<F> template_{};
#endif

    //! Lift a MPL-style metafunction to a Metafunction.
    //! @ingroup group-Metafunction
    //!
    //! Given a MPL-style metafunction, `metafunction<f>` is a `Metafunction`
    //! satisfying
    //! @code
    //!     metafunction<f>(type_c<x>...) == type_c<f<x...>::type>
    //!     decltype(metafunction<f>)::apply<x...>::type == f<x...>::type
    //! @endcode
    //!
    //! @note
    //! In a SFINAE context, the expression `metafunction<f>(type_c<x>...)` is
    //! valid whenever the expression `f<x...>::%type` is valid.
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/metafunction.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <template <typename ...> class F>
    constexpr auto metafunction = [](basic_type<T>...) {
        return hana::type_c<typename F<T...>::type>;
    };
#else
    template <template <typename ...> class f>
    struct metafunction_t;

    template <template <typename ...> class f>
    constexpr metafunction_t<f> metafunction{};
#endif

    //! Lift a MPL-style metafunction class to a Metafunction.
    //! @ingroup group-Metafunction
    //!
    //! Given a MPL-style metafunction class, `metafunction_class<f>` is a
    //! `Metafunction` satisfying
    //! @code
    //!     metafunction_class<f>(type_c<x>...) == type_c<f::apply<x...>::type>
    //!     decltype(metafunction_class<f>)::apply<x...>::type == f::apply<x...>::type
    //! @endcode
    //!
    //! @note
    //! In a SFINAE context, the expression `metafunction_class<f>(type_c<x>...)`
    //! is valid whenever the expression `f::apply<x...>::%type` is valid.
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/metafunction_class.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename F>
    constexpr auto metafunction_class = [](basic_type<T>...) {
        return hana::type_c<typename F::template apply<T...>::type>;
    };
#else
    template <typename F>
    struct metafunction_class_t;

    template <typename F>
    constexpr metafunction_class_t<F> metafunction_class{};
#endif

    //! Turn a `Metafunction` into a function taking `type`s and returning a
    //! default-constructed object.
    //! @ingroup group-Metafunction
    //!
    //! Given a `Metafunction` `f`, `integral` returns a new `Metafunction`
    //! that default-constructs an object of the type returned by `f`. More
    //! specifically, the following holds:
    //! @code
    //!     integral(f)(t...) == decltype(f(t...))::type{}
    //! @endcode
    //!
    //! The principal use case for `integral` is to transform `Metafunction`s
    //! returning a type that inherits from a meaningful base like
    //! `std::integral_constant` into functions returning e.g. a
    //! `hana::integral_constant`.
    //!
    //! @note
    //! - This is not a `Metafunction` because it does not return a `type`.
    //!   As such, it would not make sense to make `decltype(integral(f))`
    //!   a MPL metafunction class like the usual `Metafunction`s are.
    //!
    //! - When using `integral` with metafunctions returning
    //!   `std::integral_constant`s, don't forget to include the
    //!   boost/hana/ext/std/integral_constant.hpp header to ensure
    //!   Hana can interoperate with the result.
    //!
    //! - In a SFINAE context, the expression `integral(f)(t...)` is valid
    //!   whenever the expression `decltype(f(t...))::%type` is valid.
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/integral.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto integral = [](auto f) {
        return [](basic_type<T>...) {
            return decltype(f)::apply<T...>::type{};
        };
    };
#else
    template <typename F>
    struct integral_t;

    struct make_integral_t {
        template <typename F>
        constexpr integral_t<F> operator()(F const&) const
        { return {}; }
    };

    constexpr make_integral_t integral{};
#endif

    //! Alias to `integral(metafunction<F>)`, provided for convenience.
    //! @ingroup group-Metafunction
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/trait.cpp
    template <template <typename ...> class F>
    constexpr auto trait = hana::integral(hana::metafunction<F>);
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TYPE_HPP

/* type.hpp
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
*/