/*!
@file
Forward declares `boost::hana::string`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_STRING_HPP
#define BOOST_HANA_FWD_STRING_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/to.hpp>


BOOST_HANA_NAMESPACE_BEGIN
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    //! @ingroup group-datatypes
    //! Compile-time string.
    //!
    //! Conceptually, a `hana::string` is like a tuple holding
    //! `integral_constant`s of underlying type `char`. However, the
    //! interface of `hana::string` is not as rich as that of a tuple,
    //! because a string can only hold compile-time characters as opposed
    //! to any kind of object.
    //!
    //! Compile-time strings are used for simple purposes like being keys in a
    //! `hana::map` or tagging the members of a `Struct`. However, you might
    //! find that `hana::string` does not provide enough functionality to be
    //! used as a full-blown compile-time string implementation (e.g. regexp
    //! matching or substring finding). Indeed, providing a comprehensive
    //! string interface is a lot of job, and it is out of the scope of the
    //! library for the time being.
    //!
    //!
    //! @note
    //! The representation of `hana::string` is implementation-defined.
    //! In particular, one should not take for granted that the template
    //! parameters are `char`s. The proper way to access the contents of
    //! a `hana::string` as character constants is to use `hana::unpack`,
    //! `.c_str()` or `hana::to<char const*>`, as documented below. More
    //! details [in the tutorial](@ref tutorial-containers-types).
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! For most purposes, a `hana::string` is functionally equivalent to a
    //! tuple holding `Constant`s of underlying type `char`.
    //!
    //! 1. `Comparable`\n
    //! Two strings are equal if and only if they have the same number of
    //! characters and characters at corresponding indices are equal.
    //! @include example/string/comparable.cpp
    //!
    //! 2. `Orderable`\n
    //! The total order implemented for `Orderable` is the usual
    //! lexicographical comparison of strings.
    //! @include example/string/orderable.cpp
    //!
    //! 3. `Monoid`\n
    //! Strings form a monoid under concatenation, with the neutral element
    //! being the empty string.
    //! @include example/string/monoid.cpp
    //!
    //! 4. `Foldable`\n
    //! Folding a string is equivalent to folding the sequence of its
    //! characters.
    //! @include example/string/foldable.cpp
    //!
    //! 5. `Iterable`\n
    //! Iterating over a string is equivalent to iterating over the sequence
    //! of its characters. Also note that `operator[]` can be used instead of
    //! the `at` function.
    //! @include example/string/iterable.cpp
    //!
    //! 6. `Searchable`\n
    //! Searching through a string is equivalent to searching through the
    //! sequence of its characters.
    //! @include example/string/searchable.cpp
    //!
    //! 7. `Hashable`\n
    //! The hash of a compile-time string is a type uniquely representing
    //! that string.
    //! @include example/string/hashable.cpp
    //!
    //!
    //! Conversion to `char const*`
    //! ---------------------------
    //! A `hana::string` can be converted to a `constexpr` null-delimited
    //! string of type `char const*` by using the `c_str()` method or
    //! `hana::to<char const*>`. This makes it easy to turn a compile-time
    //! string into a runtime string. However, note that this conversion is
    //! not an embedding, because `char const*` does not model the same
    //! concepts as `hana::string` does.
    //! @include example/string/to.cpp
    //!
    //! Conversion from any Constant holding a `char const*`
    //! ----------------------------------------------------
    //! A `hana::string` can be created from any `Constant` whose underlying
    //! value is convertible to a `char const*` by using `hana::to`. The
    //! contents of the `char const*` are used to build the content of the
    //! `hana::string`.
    //! @include example/string/from_c_str.cpp
    //!
    //! Rationale for `hana::string` not being a `Constant` itself
    //! ----------------------------------------------------------
    //! The underlying type held by a `hana::string` could be either `char const*`
    //! or some other constexpr-enabled string-like container. In the first case,
    //! `hana::string` can not be a `Constant` because the models of several
    //! concepts would not be respected by the underlying type, causing `value`
    //! not to be structure-preserving. Providing an underlying value of
    //! constexpr-enabled string-like container type like `std::string_view`
    //! would be great, but that's a bit complicated for the time being.
    template <typename implementation_defined>
    struct string {
        // Default-construct a `hana::string`; no-op since `hana::string` is stateless.
        constexpr string() = default;

        // Copy-construct a `hana::string`; no-op since `hana::string` is stateless.
        constexpr string(string const&) = default;

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

        //! Performs concatenation; equivalent to `hana::plus`
        template <typename X, typename Y>
        friend constexpr auto operator+(X&& x, Y&& y);

        //! Equivalent to `hana::at`
        template <typename N>
        constexpr decltype(auto) operator[](N&& n);

        //! Returns a null-delimited C-style string.
        static constexpr char const* c_str();
    };
#else
    template <char ...s>
    struct string;
#endif

    //! Tag representing a compile-time string.
    //! @relates hana::string
    struct string_tag { };

#ifdef BOOST_HANA_DOXYGEN_INVOKED
    //! Create a compile-time `hana::string` from a parameter pack of `char`
    //! `integral_constant`s.
    //! @relates hana::string
    //!
    //! Given zero or more `integral_constant`s of underlying type `char`,
    //! `make<string_tag>` creates a `hana::string` containing those characters.
    //! This is provided mostly for consistency with the rest of the library,
    //! as `hana::string_c` is more convenient to use in most cases.
    //!
    //!
    //! Example
    //! -------
    //! @include example/string/make.cpp
    template <>
    constexpr auto make<string_tag> = [](auto&& ...chars) {
        return string<implementation_defined>{};
    };
#endif

    //! Alias to `make<string_tag>`; provided for convenience.
    //! @relates hana::string
    constexpr auto make_string = make<string_tag>;

    //! Equivalent to `to<string_tag>`; provided for convenience.
    //! @relates hana::string
    constexpr auto to_string = to<string_tag>;

    //! Create a compile-time string from a parameter pack of characters.
    //! @relates hana::string
    //!
    //!
    //! Example
    //! -------
    //! @include example/string/string_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <char ...s>
    constexpr string<implementation_defined> string_c{};
#else
    template <char ...s>
    constexpr string<s...> string_c{};
#endif

    //! Create a compile-time string from a string literal.
    //! @relates hana::string
    //!
    //! This macro is a more convenient alternative to `string_c` for creating
    //! compile-time strings. However, since this macro uses a lambda
    //! internally, it can't be used in an unevaluated context, or where
    //! a constant expression is expected before C++17.
    //!
    //!
    //! Example
    //! -------
    //! @include example/string/macro.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto BOOST_HANA_STRING(s) = see documentation;
    #define BOOST_HANA_STRING(s) see documentation

    // Note:
    // The trick above seems to exploit a bug in Doxygen, which makes the
    // BOOST_HANA_STRING macro appear in the related objects of hana::string
    // (as we want it to).
#else
    // defined in <boost/hana/string.hpp>
#endif

#ifdef BOOST_HANA_CONFIG_ENABLE_STRING_UDL
    namespace literals {
        //! Creates a compile-time string from a string literal.
        //! @relatesalso boost::hana::string
        //!
        //! The string literal is parsed at compile-time and the result is
        //! returned as a `hana::string`. This feature is an extension that
        //! is disabled by default; see below for details.
        //!
        //! @note
        //! Only narrow string literals are supported right now; support for
        //! fancier types of string literals like wide or UTF-XX might be
        //! added in the future if there is a demand for it. See [this issue]
        //! [Hana.issue80] if you need this.
        //!
        //! @warning
        //! This user-defined literal is an extension which requires a special
        //! string literal operator that is not part of the standard yet.
        //! That operator is supported by both Clang and GCC, and several
        //! proposals were made for it to enter C++17. However, since it is
        //! not standard, it is disabled by default and defining the
        //! `BOOST_HANA_CONFIG_ENABLE_STRING_UDL` config macro is required
        //! to get this operator. Hence, if you want to stay safe, just use
        //! the `BOOST_HANA_STRING` macro instead. If you want to be fast and
        //! furious (I do), define `BOOST_HANA_CONFIG_ENABLE_STRING_UDL`.
        //!
        //!
        //! Example
        //! -------
        //! @include example/string/literal.cpp
        //!
        //! [Hana.issue80]: https://github.com/boostorg/hana/issues/80
        template <typename CharT, CharT ...s>
        constexpr auto operator"" _s();
    }
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_STRING_HPP

/* string.hpp
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
*/