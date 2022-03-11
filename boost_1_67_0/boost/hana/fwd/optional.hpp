/*!
@file
Forward declares `boost::hana::optional`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_OPTIONAL_HPP
#define BOOST_HANA_FWD_OPTIONAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/operators/adl.hpp>
#include <boost/hana/fwd/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-datatypes
    //! Optional value whose optional-ness is known at compile-time.
    //!
    //! An `optional` either contains a value (represented as `just(x)`), or
    //! it is empty (represented as `nothing`). In essence, `hana::optional`
    //! is pretty much like a `boost::optional` or the upcoming `std::optional`,
    //! except for the fact that whether a `hana::optional` is empty or not is
    //! known at compile-time. This can be particularly useful for returning
    //! from a function that might fail, but whose reason for failing is not
    //! important. Of course, whether the function will fail has to be known
    //! at compile-time.
    //!
    //! This is really an important difference between `hana::optional` and
    //! `std::optional`. Unlike `std::optional<T>{}` and `std::optional<T>{x}`
    //! who share the same type (`std::optional<T>`), `hana::just(x)` and
    //! `hana::nothing` do not share the same type, since the state of the
    //! optional has to be known at compile-time. Hence, whether a `hana::just`
    //! or a `hana::nothing` will be returned from a function has to be known
    //! at compile-time for the return type of that function to be computable
    //! by the compiler. This makes `hana::optional` well suited for static
    //! metaprogramming tasks, but very poor for anything dynamic.
    //!
    //! @note
    //! When you use a container, remember not to make assumptions about its
    //! representation, unless the documentation gives you those guarantees.
    //! More details [in the tutorial](@ref tutorial-containers-types).
    //!
    //!
    //! Interoperation with `type`s
    //! ---------------------------
    //! When a `just` contains an object of type `T` which is a `type`,
    //! it has a nested `::%type` alias equivalent to `T::%type`. `nothing`,
    //! however, never has a nested `::%type` alias. If `t` is a `type`,
    //! this allows `decltype(just(t))` to be seen as a nullary metafunction
    //! equivalent to `decltype(t)`. Along with the `sfinae` function,
    //! this allows `hana::optional` to interact seamlessly with
    //! SFINAE-friendly metafunctions.
    //! Example:
    //! @include example/optional/sfinae_friendly_metafunctions.cpp
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! Two `optional`s are equal if and only if they are both empty or they
    //! both contain a value and those values are equal.
    //! @include example/optional/comparable.cpp
    //!
    //! 2. `Orderable`\n
    //! Optional values can be ordered by considering the value they are
    //! holding, if any. To handle the case of an empty optional value, we
    //! arbitrarily set `nothing` as being less than any other `just`. Hence,
    //! @code
    //!     just(x) < just(y) if and only if x < y
    //!     nothing < just(anything)
    //! @endcode
    //! Example:
    //! @include example/optional/orderable.cpp
    //!
    //! 3. `Functor`\n
    //! An optional value can be seen as a list containing either one element
    //! (`just(x)`) or no elements at all (`nothing`). As such, mapping
    //! a function over an optional value is equivalent to applying it to
    //! its value if there is one, and to `nothing` otherwise:
    //! @code
    //!     transform(just(x), f) == just(f(x))
    //!     transform(nothing, f) == nothing
    //! @endcode
    //! Example:
    //! @include example/optional/functor.cpp
    //!
    //! 4. `Applicative`\n
    //! First, a value can be made optional with `lift<optional_tag>`, which
    //! is equivalent to `just`. Second, one can feed an optional value to an
    //! optional function with `ap`, which will return `just(f(x))` if there
    //! is both a function _and_ a value, and `nothing` otherwise:
    //! @code
    //!     ap(just(f), just(x)) == just(f(x))
    //!     ap(nothing, just(x)) == nothing
    //!     ap(just(f), nothing) == nothing
    //!     ap(nothing, nothing) == nothing
    //! @endcode
    //! A simple example:
    //! @include example/optional/applicative.cpp
    //! A more complex example:
    //! @include example/optional/applicative.complex.cpp
    //!
    //! 5. `Monad`\n
    //! The `Monad` model makes it easy to compose actions that might fail.
    //! One can feed an optional value if there is one into a function with
    //! `chain`, which will return `nothing` if there is no value. Finally,
    //! optional-optional values can have their redundant level of optionality
    //! removed with `flatten`. Also note that the `|` operator can be used in
    //! place of the `chain` function.
    //! Example:
    //! @include example/optional/monad.cpp
    //!
    //! 6. `MonadPlus`\n
    //! The `MonadPlus` model allows choosing the first valid value out of
    //! two optional values with `concat`. If both optional values are
    //! `nothing`s, `concat` will return `nothing`.
    //! Example:
    //! @include example/optional/monad_plus.cpp
    //!
    //! 7. `Foldable`\n
    //! Folding an optional value is equivalent to folding a list containing
    //! either no elements (for `nothing`) or `x` (for `just(x)`).
    //! Example:
    //! @include example/optional/foldable.cpp
    //!
    //! 8. `Searchable`\n
    //! Searching an optional value is equivalent to searching a list
    //! containing `x` for `just(x)` and an empty list for `nothing`.
    //! Example:
    //! @include example/optional/searchable.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename ...T>
    struct optional {
        // 5.3.1, Constructors

        //! Default-construct an `optional`. Only exists if the optional
        //! contains a value, and if that value is DefaultConstructible.
        constexpr optional() = default;

        //! Copy-construct an `optional`.
        //! An empty optional may only be copy-constructed from another
        //! empty `optional`, and an `optional` with a value may only be
        //! copy-constructed from another `optional` with a value.
        //! Furthermore, this constructor only exists if the value
        //! held in the `optional` is CopyConstructible.
        optional(optional const&) = default;

        //! Move-construct an `optional`.
        //! An empty optional may only be move-constructed from another
        //! empty `optional`, and an `optional` with a value may only be
        //! move-constructed from another `optional` with a value.
        //! Furthermore, this constructor only exists if the value
        //! held in the `optional` is MoveConstructible.
        optional(optional&&) = default;

        //! Construct an `optional` holding a value of type `T` from another
        //! object of type `T`. The value is copy-constructed.
        constexpr optional(T const& t)
            : value_(t)
        { }

        //! Construct an `optional` holding a value of type `T` from another
        //! object of type `T`. The value is move-constructed.
        constexpr optional(T&& t)
            : value_(static_cast<T&&>(t))
        { }

        // 5.3.3, Assignment

        //! Copy-assign an `optional`.
        //! An empty optional may only be copy-assigned from another empty
        //! `optional`, and an `optional` with a value may only be copy-assigned
        //! from another `optional` with a value. Furthermore, this assignment
        //! operator only exists if the value held in the `optional` is
        //! CopyAssignable.
        constexpr optional& operator=(optional const&) = default;

        //! Move-assign an `optional`.
        //! An empty optional may only be move-assigned from another empty
        //! `optional`, and an `optional` with a value may only be move-assigned
        //! from another `optional` with a value. Furthermore, this assignment
        //! operator only exists if the value held in the `optional` is
        //! MoveAssignable.
        constexpr optional& operator=(optional&&) = default;

        // 5.3.5, Observers

        //! Returns a pointer to the contained value, or a `nullptr` if the
        //! `optional` is empty.
        //!
        //!
        //! @note Overloads of this method are provided for both the `const`
        //! and the non-`const` cases.
        //!
        //!
        //! Example
        //! -------
        //! @include example/optional/value.cpp
        constexpr T* operator->();

        //! Extract the content of an `optional`, or fail at compile-time.
        //!
        //! If `*this` contains a value, that value is returned. Otherwise,
        //! a static assertion is triggered.
        //!
        //! @note
        //! Overloads of this method are provided for the cases where `*this`
        //! is a reference, a rvalue-reference and their `const` counterparts.
        //!
        //!
        //! Example
        //! -------
        //! @include example/optional/value.cpp
        constexpr T& value();

        //! Equivalent to `value()`, provided for convenience.
        //!
        //! @note
        //! Overloads of this method are provided for the cases where `*this`
        //! is a reference, a rvalue-reference and their `const` counterparts.
        //!
        //!
        //! Example
        //! -------
        //! @include example/optional/value.cpp
        constexpr T& operator*();

        //! Return the contents of an `optional`, with a fallback result.
        //!
        //! If `*this` contains a value, that value is returned. Otherwise,
        //! the default value provided is returned.
        //!
        //! @note
        //! Overloads of this method are provided for the cases where `*this`
        //! is a reference, a rvalue-reference and their `const` counterparts.
        //!
        //!
        //! @param default_
        //! The default value to return if `*this` does not contain a value.
        //!
        //!
        //! Example
        //! -------
        //! @include example/optional/value_or.cpp
        template <typename U>
        constexpr decltype(auto) value_or(U&& default_);

        //! Equivalent to `hana::chain`.
        template <typename ...T, typename F>
        friend constexpr auto operator|(optional<T...>, F);

        //! Equivalent to `hana::equal`
        template <typename X, typename Y>
        friend constexpr auto operator==(X&& x, Y&& y);

        //! Equivalent to `hana::not_equal`
        template <typename X, typename Y>
        friend constexpr auto operator!=(X&& x, Y&& y);

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
    template <typename ...T>
    struct optional;
#endif

    //! Tag representing a `hana::optional`.
    //! @relates hana::optional
    struct optional_tag { };

    //! Create an optional value.
    //! @relates hana::optional
    //!
    //! Specifically, `make<optional_tag>()` is equivalent to `nothing`, and
    //! `make<optional_tag>(x)` is equivalent to `just(x)`. This is provided
    //! for consistency with the other `make<...>` functions.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/make.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <>
    constexpr auto make<optional_tag> = []([auto&& x]) {
        return optional<std::decay<decltype(x)>::type>{forwarded(x)};
    };
#endif

    //! Alias to `make<optional_tag>`; provided for convenience.
    //! @relates hana::optional
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/make.cpp
    constexpr auto make_optional = make<optional_tag>;

    //! Create an optional value containing `x`.
    //! @relates hana::optional
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/just.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto just = [](auto&& x) {
        return optional<std::decay<decltype(x)>::type>{forwarded(x)};
    };
#else
    struct make_just_t {
        template <typename T>
        constexpr auto operator()(T&&) const;
    };

    constexpr make_just_t just{};
#endif

    //! An empty optional value.
    //! @relates hana::optional
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/nothing.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr optional<> nothing{};
#else
    template <>
    struct optional<> : detail::operators::adl<optional<>> {
        // 5.3.1, Constructors
        constexpr optional() = default;
        constexpr optional(optional const&) = default;
        constexpr optional(optional&&) = default;

        // 5.3.3, Assignment
        constexpr optional& operator=(optional const&) = default;
        constexpr optional& operator=(optional&&) = default;

        // 5.3.5, Observers
        constexpr decltype(nullptr) operator->() const { return nullptr; }

        template <typename ...dummy>
        constexpr auto value() const;

        template <typename ...dummy>
        constexpr auto operator*() const;

        template <typename U>
        constexpr U&& value_or(U&& u) const;
    };

    constexpr optional<> nothing{};
#endif

    //! Apply a function to the contents of an optional, with a fallback
    //! result.
    //! @relates hana::optional
    //!
    //! Specifically, `maybe` takes a default value, a function and an
    //! optional value. If the optional value is `nothing`, the default
    //! value is returned. Otherwise, the function is applied to the
    //! content of the `just`.
    //!
    //!
    //! @param default_
    //! A default value returned if `m` is `nothing`.
    //!
    //! @param f
    //! A function called as `f(x)` if and only if `m` is an optional value
    //! of the form `just(x)`. In that case, the result returend by `maybe`
    //! is the result of `f`.
    //!
    //! @param m
    //! An optional value.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/maybe.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto maybe = [](auto&& default_, auto&& f, auto&& m) -> decltype(auto) {
        if (m is a just(x)) {
            return forwarded(f)(forwarded(x));
        else
            return forwarded(default_);
        }
    };
#else
    struct maybe_t {
        template <typename Def, typename F, typename T>
        constexpr decltype(auto) operator()(Def&&, F&& f, optional<T> const& m) const
        { return static_cast<F&&>(f)(m.value_); }

        template <typename Def, typename F, typename T>
        constexpr decltype(auto) operator()(Def&&, F&& f, optional<T>& m) const
        { return static_cast<F&&>(f)(m.value_); }

        template <typename Def, typename F, typename T>
        constexpr decltype(auto) operator()(Def&&, F&& f, optional<T>&& m) const
        { return static_cast<F&&>(f)(static_cast<optional<T>&&>(m).value_); }

        template <typename Def, typename F>
        constexpr Def operator()(Def&& def, F&&, optional<> const&) const
        { return static_cast<Def&&>(def); }
    };

    constexpr maybe_t maybe{};
#endif

    //! Calls a function if the call expression is well-formed.
    //! @relates hana::optional
    //!
    //! Given a function `f`, `sfinae` returns a new function applying `f`
    //! to its arguments and returning `just` the result if the call is
    //! well-formed, and `nothing` otherwise. In other words, `sfinae(f)(x...)`
    //! is `just(f(x...))` if that expression is well-formed, and `nothing`
    //! otherwise. Note, however, that it is possible for an expression
    //! `f(x...)` to be well-formed as far as SFINAE is concerned, but
    //! trying to actually compile `f(x...)` still fails. In this case,
    //! `sfinae` won't be able to detect it and a hard failure is likely
    //! to happen.
    //!
    //!
    //! @note
    //! The function given to `sfinae` must not return `void`, since
    //! `just(void)` does not make sense. A compilation error is
    //! triggered if the function returns void.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/sfinae.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto sfinae = [](auto&& f) {
        return [perfect-capture](auto&& ...x) {
            if (decltype(forwarded(f)(forwarded(x)...)) is well-formed)
                return just(forwarded(f)(forwarded(x)...));
            else
                return nothing;
        };
    };
#else
    struct sfinae_t {
        template <typename F>
        constexpr decltype(auto) operator()(F&& f) const;
    };

    constexpr sfinae_t sfinae{};
#endif

    //! Return whether an `optional` contains a value.
    //! @relates hana::optional
    //!
    //! Specifically, returns a compile-time true-valued `Logical` if `m` is
    //! of the form `just(x)` for some `x`, and a false-valued one otherwise.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/is_just.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_just = [](auto const& m) {
        return m is a just(x);
    };
#else
    struct is_just_t {
        template <typename ...T>
        constexpr auto operator()(optional<T...> const&) const;
    };

    constexpr is_just_t is_just{};
#endif

    //! Return whether an `optional` is empty.
    //! @relates hana::optional
    //!
    //! Specifically, returns a compile-time true-valued `Logical` if `m` is
    //! a `nothing`, and a false-valued one otherwise.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/is_nothing.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_nothing = [](auto const& m) {
        return m is a nothing;
    };
#else
    struct is_nothing_t {
        template <typename ...T>
        constexpr auto operator()(optional<T...> const&) const;
    };

    constexpr is_nothing_t is_nothing{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_OPTIONAL_HPP

/* optional.hpp
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
*/