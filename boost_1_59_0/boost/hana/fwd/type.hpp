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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr type<T> type_c{};

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

    BOOST_HANA_INLINE_VARIABLE constexpr decltype_t decltype_{};
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

    BOOST_HANA_INLINE_VARIABLE constexpr typeid_t typeid_{};
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
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_type = hana::make<type_tag>;

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

    BOOST_HANA_INLINE_VARIABLE constexpr sizeof_t sizeof_{};
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

    BOOST_HANA_INLINE_VARIABLE constexpr alignof_t alignof_{};
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

    BOOST_HANA_INLINE_VARIABLE constexpr is_valid_t is_valid{};
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
    BOOST_HANA_INLINE_VARIABLE constexpr template_t<F> template_{};
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
    BOOST_HANA_INLINE_VARIABLE constexpr metafunction_t<f> metafunction{};
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
    BOOST_HANA_INLINE_VARIABLE constexpr metafunction_class_t<F> metafunction_class{};
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

    BOOST_HANA_INLINE_VARIABLE constexpr make_integral_t integral{};
#endif

    //! Alias to `integral(metafunction<F>)`, provided for convenience.
    //! @ingroup group-Metafunction
    //!
    //!
    //! Example
    //! -------
    //! @include example/type/trait.cpp
    template <template <typename ...> class F>
    BOOST_HANA_INLINE_VARIABLE constexpr auto trait = hana::integral(hana::metafunction<F>);
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_TYPE_HPP

/* type.hpp
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
*/