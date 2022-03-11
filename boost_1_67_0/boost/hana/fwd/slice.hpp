/*!
@file
Forward declares `boost::hana::slice` and `boost::hana::slice_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SLICE_HPP
#define BOOST_HANA_FWD_SLICE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Extract the elements of a `Sequence` at the given indices.
    //! @ingroup group-Sequence
    //!
    //! Given an arbitrary sequence of `indices`, `slice` returns a new
    //! sequence of the elements of the original sequence that appear at
    //! those indices. In other words,
    //! @code
    //!     slice([x1, ..., xn], [i1, ..., ik]) == [x_i1, ..., x_ik]
    //! @endcode
    //!
    //! The indices do not have to be ordered or contiguous in any particular
    //! way, but they must not be out of the bounds of the sequence. It is
    //! also possible to specify the same index multiple times, in which case
    //! the element at this index will be repeatedly included in the resulting
    //! sequence.
    //!
    //!
    //! @param xs
    //! The sequence from which a subsequence is extracted.
    //!
    //! @param indices
    //! A compile-time `Foldable` containing non-negative `IntegralConstant`s
    //! representing the indices. The indices are 0-based, and they must all
    //! be in bounds of the `xs` sequence. Note that any `Foldable` will
    //! really do (no need for an `Iterable`, for example); the linearization
    //! of the `indices` is used to determine the order of the elements
    //! included in the slice.
    //!
    //!
    //! Example
    //! -------
    //! @include example/slice.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto slice = [](auto&& xs, auto&& indices) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct slice_impl : slice_impl<S, when<true>> { };

    struct slice_t {
        template <typename Xs, typename Indices>
        constexpr auto operator()(Xs&& xs, Indices&& indices) const;
    };

    constexpr slice_t slice{};
#endif

    //! Shorthand to `slice` a contiguous range of elements.
    //! @ingroup group-Sequence
    //!
    //! `slice_c` is simply a shorthand to slice a contiguous range of
    //! elements. In particular, `slice_c<from, to>(xs)` is equivalent to
    //! `slice(xs, range_c<std::size_t, from, to>)`, which simply slices
    //! all the elements of `xs` contained in the half-open interval
    //! delimited by `[from, to)`. Like for `slice`, the indices used with
    //! `slice_c` are 0-based and they must be in the bounds of the sequence
    //! being sliced.
    //!
    //!
    //! @tparam from
    //! The index of the first element in the slice.
    //!
    //! @tparam to
    //! One-past the index of the last element in the slice. It must hold
    //! that `from <= to`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/slice_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t from, std::size_t to>
    constexpr auto slice_c = [](auto&& xs) {
        return hana::slice(forwarded(xs), hana::range_c<std::size_t, from, to>);
    };
#else
    template <std::size_t from, std::size_t to>
    struct slice_c_t;

    template <std::size_t from, std::size_t to>
    constexpr slice_c_t<from, to> slice_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SLICE_HPP

/* slice.hpp
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
*/