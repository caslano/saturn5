// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_OPS_FIELDS_HPP
#define BOOST_PFR_OPS_FIELDS_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <boost/pfr/core.hpp>
#include <boost/pfr/detail/functional.hpp>

/// \file boost/pfr/ops_fields.hpp
/// Contains field-by-fields comparison and hash functions.
///
/// \b Example:
/// \code
///     #include <boost/pfr/ops_fields.hpp>
///     struct comparable_struct {      // No operators defined for that structure
///         int i; short s;
///     };
///     // ...
///
///     comparable_struct s1 {0, 1};
///     comparable_struct s2 {0, 2};
///     assert(boost::pfr::lt_fields(s1, s2));
/// \endcode
///
/// \podops for other ways to define operators and more details.
///
/// \b Synopsis:
namespace boost { namespace pfr {

    /// Does a field-by-field equality comparison.
    ///
    /// \returns `L == R && tuple_size_v<T> == tuple_size_v<U>`, where `L` and
    /// `R` are the results of calling `std::tie` on first `N` fields of `lhs` and
    // `rhs` respectively; `N` is `std::min(tuple_size_v<T>, tuple_size_v<U>)`.
    template <class T, class U>
    constexpr bool eq_fields(const T& lhs, const U& rhs) noexcept {
        return detail::binary_visit<detail::equal_impl>(lhs, rhs);
    }


    /// Does a field-by-field inequality comparison.
    ///
    /// \returns `L != R || tuple_size_v<T> != tuple_size_v<U>`, where `L` and
    /// `R` are the results of calling `std::tie` on first `N` fields of `lhs` and
    // `rhs` respectively; `N` is `std::min(tuple_size_v<T>, tuple_size_v<U>)`.
    template <class T, class U>
    constexpr bool ne_fields(const T& lhs, const U& rhs) noexcept {
        return detail::binary_visit<detail::not_equal_impl>(lhs, rhs);
    }

    /// Does a field-by-field greter comparison.
    ///
    /// \returns `L > R || (L == R && tuple_size_v<T> > tuple_size_v<U>)`, where `L` and
    /// `R` are the results of calling `std::tie` on first `N` fields of `lhs` and
    // `rhs` respectively; `N` is `std::min(tuple_size_v<T>, tuple_size_v<U>)`.
    template <class T, class U>
    constexpr bool gt_fields(const T& lhs, const U& rhs) noexcept {
        return detail::binary_visit<detail::greater_impl>(lhs, rhs);
    }


    /// Does a field-by-field less comparison.
    ///
    /// \returns `L < R || (L == R && tuple_size_v<T> < tuple_size_v<U>)`, where `L` and
    /// `R` are the results of calling `std::tie` on first `N` fields of `lhs` and
    // `rhs` respectively; `N` is `std::min(tuple_size_v<T>, tuple_size_v<U>)`.
    template <class T, class U>
    constexpr bool lt_fields(const T& lhs, const U& rhs) noexcept {
        return detail::binary_visit<detail::less_impl>(lhs, rhs);
    }


    /// Does a field-by-field greater equal comparison.
    ///
    /// \returns `L > R || (L == R && tuple_size_v<T> >= tuple_size_v<U>)`, where `L` and
    /// `R` are the results of calling `std::tie` on first `N` fields of `lhs` and
    // `rhs` respectively; `N` is `std::min(tuple_size_v<T>, tuple_size_v<U>)`.
    template <class T, class U>
    constexpr bool ge_fields(const T& lhs, const U& rhs) noexcept {
        return detail::binary_visit<detail::greater_equal_impl>(lhs, rhs);
    }


    /// Does a field-by-field less equal comparison.
    ///
    /// \returns `L < R || (L == R && tuple_size_v<T> <= tuple_size_v<U>)`, where `L` and
    /// `R` are the results of calling `std::tie` on first `N` fields of `lhs` and
    // `rhs` respectively; `N` is `std::min(tuple_size_v<T>, tuple_size_v<U>)`.
    template <class T, class U>
    constexpr bool le_fields(const T& lhs, const U& rhs) noexcept {
        return detail::binary_visit<detail::less_equal_impl>(lhs, rhs);
    }


    /// Does a field-by-field hashing.
    ///
    /// \returns combined hash of all the fields
    template <class T>
    std::size_t hash_fields(const T& x) {
        constexpr std::size_t fields_count_val = boost::pfr::detail::fields_count<std::remove_reference_t<T>>();
#if BOOST_PFR_USE_CPP17 || BOOST_PFR_USE_LOOPHOLE
        return detail::hash_impl<0, fields_count_val>::compute(detail::tie_as_tuple(x));
#else
        std::size_t result = 0;
        ::boost::pfr::detail::for_each_field_dispatcher(
            x,
            [&result](const auto& lhs) {
                // We can not reuse `fields_count_val` in lambda because compilers had issues with
                // passing constexpr variables into lambdas. Computing is again is the most portable solution.
                constexpr std::size_t fields_count_val_lambda = boost::pfr::detail::fields_count<std::remove_reference_t<T>>();
                result = detail::hash_impl<0, fields_count_val_lambda>::compute(lhs);
            },
            detail::make_index_sequence<fields_count_val>{}
        );

        return result;
#endif
    }
}} // namespace boost::pfr

#endif // BOOST_PFR_OPS_HPP

/* ops_fields.hpp
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
*/