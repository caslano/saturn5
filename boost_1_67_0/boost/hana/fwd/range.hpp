/*!
@file
Forward declares `boost::hana::range`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_RANGE_HPP
#define BOOST_HANA_FWD_RANGE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    //! @ingroup group-datatypes
    //! Compile-time half-open interval of `hana::integral_constant`s.
    //!
    //! A `range` represents a half-open interval of the form `[from, to)`
    //! containing `hana::integral_constant`s of a given type. The `[from, to)`
    //! notation represents the values starting at `from` (inclusively) up
    //! to but excluding `from`. In other words, it is a bit like the list
    //! `from, from+1, ..., to-1`.
    //!
    //! In particular, note that the bounds of the range can be any
    //! `hana::integral_constant`s (negative numbers are allowed) and the
    //! range does not have to start at zero. The only requirement is that
    //! `from <= to`.
    //!
    //! @note
    //! The representation of `hana::range` is implementation defined. In
    //! particular, one should not take for granted the number and types
    //! of template parameters. The proper way to create a `hana::range`
    //! is to use `hana::range_c` or `hana::make_range`. More details
    //! [in the tutorial](@ref tutorial-containers-types).
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! Two ranges are equal if and only if they are both empty or they both
    //! span the same interval.
    //! @include example/range/comparable.cpp
    //!
    //! 2. `Foldable`\n
    //! Folding a `range` is equivalent to folding a list of the
    //! `integral_constant`s in the interval it spans.
    //! @include example/range/foldable.cpp
    //!
    //! 3. `Iterable`\n
    //! Iterating over a `range` is equivalent to iterating over a list of
    //! the values it spans. In other words, iterating over the range
    //! `[from, to)` is equivalent to iterating over a list containing
    //! `from, from+1, from+2, ..., to-1`. Also note that `operator[]` can
    //! be used in place of the `at` function.
    //! @include example/range/iterable.cpp
    //!
    //! 4. `Searchable`\n
    //! Searching a `range` is equivalent to searching a list of the values
    //! in the range `[from, to)`, but it is much more compile-time efficient.
    //! @include example/range/searchable.cpp
    template <typename T, T from, T to>
    struct range {
        //! Equivalent to `hana::equal`
        template <typename X, typename Y>
        friend constexpr auto operator==(X&& x, Y&& y);

        //! Equivalent to `hana::not_equal`
        template <typename X, typename Y>
        friend constexpr auto operator!=(X&& x, Y&& y);

        //! Equivalent to `hana::at`
        template <typename N>
        constexpr decltype(auto) operator[](N&& n);
    };
#else
    template <typename T, T from, T to>
    struct range;
#endif

    //! Tag representing a `hana::range`.
    //! @relates hana::range
    struct range_tag { };

#ifdef BOOST_HANA_DOXYGEN_INVOKED
    //! Create a `hana::range` representing a half-open interval of
    //! `integral_constant`s.
    //! @relates hana::range
    //!
    //! Given two `IntegralConstant`s `from` and `to`, `make<range_tag>`
    //! returns a `hana::range` representing the half-open interval of
    //! `integral_constant`s `[from, to)`. `from` and `to` must form a
    //! valid interval, which means that `from <= to` must be true. Otherwise,
    //! a compilation error is triggered. Also note that if `from` and `to`
    //! are `IntegralConstant`s with different underlying integral types,
    //! the created range contains `integral_constant`s whose underlying
    //! type is their common type.
    //!
    //!
    //! Example
    //! -------
    //! @include example/range/make.cpp
    template <>
    constexpr auto make<range_tag> = [](auto const& from, auto const& to) {
        return range<implementation_defined>{implementation_defined};
    };
#endif

    //! Alias to `make<range_tag>`; provided for convenience.
    //! @relates hana::range
    constexpr auto make_range = make<range_tag>;

    //! Shorthand to create a `hana::range` with the given bounds.
    //! @relates hana::range
    //!
    //! This shorthand is provided for convenience only and it is equivalent
    //! to `make_range`. Specifically, `range_c<T, from, to>` is such that
    //! @code
    //!     range_c<T, from, to> == make_range(integral_c<T, from>, integral_c<T, to>)
    //! @endcode
    //!
    //!
    //! @tparam T
    //! The underlying integral type of the `integral_constant`s in the
    //! created range.
    //!
    //! @tparam from
    //! The inclusive lower bound of the created range.
    //!
    //! @tparam to
    //! The exclusive upper bound of the created range.
    //!
    //!
    //! Example
    //! -------
    //! @include example/range/range_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename T, T from, T to>
    constexpr auto range_c = make_range(integral_c<T, from>, integral_c<T, to>);
#else
    template <typename T, T from, T to>
    constexpr range<T, from, to> range_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_RANGE_HPP

/* range.hpp
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
*/