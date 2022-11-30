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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_optional = make<optional_tag>;

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

    BOOST_HANA_INLINE_VARIABLE constexpr make_just_t just{};
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

    BOOST_HANA_INLINE_VARIABLE constexpr optional<> nothing{};
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

    BOOST_HANA_INLINE_VARIABLE constexpr maybe_t maybe{};
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

    BOOST_HANA_INLINE_VARIABLE constexpr sfinae_t sfinae{};
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

    BOOST_HANA_INLINE_VARIABLE constexpr is_just_t is_just{};
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

    BOOST_HANA_INLINE_VARIABLE constexpr is_nothing_t is_nothing{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_OPTIONAL_HPP

/* optional.hpp
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
*/