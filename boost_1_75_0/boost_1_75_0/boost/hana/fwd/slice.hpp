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
NHdjTFYqdzSvOI03LXVDufAHNIej3oVyGZigOAJvWo69AZgjdAr9Pq5pxYm8aZsbaoU/oMkp01W7fQPTcWjyyda7fQPXUF3XtN19vsGYwGLSwsAuNDnqgYtZ1ss9HGd3WH1I5HCNcS9oy9w1O4DZ1yt3hqVd+oF1PEdGiT3A6g2mr2CsL6pH+4Ftgjpy5YCjWaMyLR3Aapzz4T06IijSeoA9JCTuAbYFKrflA9l4WFall7KGLvIh9HunbHyAaluz8bCkST+wniWA9fqyoHfAxqOBtUblRHrZ2LSFgqLfh2HjAcDWbDwsA9JLWcsQCop+Hz8bO4cBa2tCQdHv42dj9zA2tl2hoOi32x2xTMszbdXscUee2SrtzLQ89bgyMHyW7JFO+EwWiFGQ38OEzzPunjRhf1Y5LM/GeSx3AP/dTfvUlH+mqZrTniJ+5rli5Yx4d4xIZeLenJ2x5Mb8hdGavvAXyZwaqQpEHblNgKfb1gbt8ciQsOPlv/qupH1o4hzieaq7wSD0LXJCEr3q8Q/uZzL8XuZ+AK+lbWHAFRjAqxYGGnD/60z/PPM0z9zAgOZpAgN41ZtC/NeYAXrmkiPRAh9PTA6+y32LhwT/zieBnrmm422Ab4oAgb9ag7/hXNm6oWqe7fQ4VxptWjIsrXs1zX2oj5GuVe+JQk0T29z4XWgPvff7uB7WIASsJ8YOmBeb7GDdr3vVD7zxCLaB
*/