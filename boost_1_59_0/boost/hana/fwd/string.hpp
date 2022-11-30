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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_string = make<string_tag>;

    //! Equivalent to `to<string_tag>`; provided for convenience.
    //! @relates hana::string
    BOOST_HANA_INLINE_VARIABLE constexpr auto to_string = to<string_tag>;

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
    BOOST_HANA_INLINE_VARIABLE constexpr string<s...> string_c{};
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_STRING_HPP

/* string.hpp
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
*/