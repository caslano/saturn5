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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr slice_t slice{};
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
    BOOST_HANA_INLINE_VARIABLE constexpr slice_c_t<from, to> slice_c{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_SLICE_HPP

/* slice.hpp
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
*/