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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_range = make<range_tag>;

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
    BOOST_HANA_INLINE_VARIABLE constexpr range<T, from, to> range_c{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_RANGE_HPP

/* range.hpp
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
*/