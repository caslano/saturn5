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
5MjbjPAy8ZehNAH7u42tQRE16rP26m8ZqMQoA7RnmD41dE1+CyfPADIWoSzieBS/KM/Uh+H00KN6Q/i5Q15SoQ3Di/MlM+HCiJkboLEwlNYt7+MGJMGNs9pQ/2GwjsqbIJUMItuWgfAi1tWSeuKCku15+1FbsKZsKY1AphqHOtOD4y/Jzq+1v7IJT0JjCoJaTTDAWW43kOE7Biqk7Ve3qabf2slU7wlAKNJZ6nZUv0pRtqeeBHZbXWC+n9qGtyf245+zqIWNl6o1xSuxaekYExfbxdey0JIVoaPcN7aO5+Yj9P6NOPQmS1nYwLOhYS3FP3lFkpz+iHhEcku5OPLbHZHflZHIP5TBcZGOuDo9zhHK5LhPdsTdRgxPMY2fg8uIGnM5ga8jQQknyEwmmMYJhnUkGE5gL8/CBRB0GJpe2VYMgKF5nPYH77RBP0VM5qeznau/gnjNHmhtLBqNvnXYvCt+jJVDQ83rVKhdLKM2qutHxWuyQ+98YiC+/wS+13rOH/QSGiaTpdTnhyS5qu9S4HTj2m99bKBrwsxsassnjuJzZ1HcrxbDGNaS6Q9t/DLl95FxGv+x7NMg34wJgGrVnej9YaNW4N1GLdtlYbU4BzW/hGse4tqMytBqXn1tZDl4jyv0GrcPpuZ1haopGaSr+hiVmpTmNa21EfxBo94hw/MxcK7K4gyRSml8nxl8nLk/WfTjcfR1XR/hS+OBrknsccuXLuvjIBDX3y/SBkghoQVyLktVk5IIsJzmenHsejly3SAXUlWnQwhLgfX+/Haixq7sG1fldT6A1budOh61nF98p3+Sr6jpo2FZOZy42y5Wo6zYHXZEqcU007n9YlFHYl5hyaQO8XENrDscNFdgnYTe5G3w4Qb34YmEJpf8fmJxZoMv0y/cyaA1oS/qjZ24O0tcgyG/2ZdFtE98qS+b3kCdxDuHHkimXJyN4V7a+MV8iNQmp+Lsqpgvm/ECwFBJxLp04roQlEPtCz5noLiEsALjw5iRZCCR/aYmGvfS9TYbNVUuGazcqU0EHyQuZ7Z1WJv7hLuL/c6/13b1l3eND1E8iC3pxGPcLHqagPiUSy4BSIgUDOFz5uLJgQuIXS9pzgWa6xcQNVLKRiv3JqYkMjJNKGKuDI8pMMDx2ckAx+cFQcV8DlBJzJcJvM9Gg01RDeA20D7w49WApqG3fCTP4aDmfLtsXpL2X44xB2qJBb+n5nWJqy6Ti45iFy+y7uKIoHBysEPdcG5nZaLC3fDzlet0/Oj46zjP6kkpzmzqvl+tSpF6ZmigcJgO74ksIB47Qy3wsmV9QSbxWJj9xqgFRLqj1Juy6zYtQyTrCezY3dZg8dKeIkJAjOgGhqBkrdtqp2UWVVkHNVeePpXNsOT2stKcSbI+/yzuXp8yIlCXJEtxONEGZo9670bi42A09SkSZIilJ9p0MbizlvpgmbgNQZJ7YjkCWQKS+Cmy3ItJbi3z0JgE/JhPxUN9Na5u2XhMvRSi6iH3ZJZxkBehFeJSFK9NmNnMR9qz9GW3OdLPHpYTtFc0T9UXx1E70lGkq4wzsRP7ViFmdPCXr2iaF/HkqE55ZcjZ+p4Kv0g4dJ3J7ZF++a23hk0E4dMARYZmhD3IV+wYoJk3Q4TwZRqb2tKqxwOo1uvCKfTB6uQHV4RT6YPvJj+ovjXSZq7uC+OTajt9gfItXBdK9vYUrS5L8mtSI/2MxMAYWq8nPNYMR4IK8cRQHcDL+asK0Zz8xkGVMclvTFiWiFuOt6G9vpHCn6CPzK2c3VT5fpozee8OtkMGY1eLZQBWCmV+YyBW2gDVDTq4ZGVAWdyAZA9GQ487scgu7s/s1IjGxCKHqM7XQy4nb18=
*/