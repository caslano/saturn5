/*!
@file
Forward declares `boost::hana::remove_range` and `boost::hana::remove_range_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_RANGE_HPP
#define BOOST_HANA_FWD_REMOVE_RANGE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Remove the elements inside a given range of indices from a sequence.
    //! @ingroup group-Sequence
    //!
    //! `remove_range` returns a new sequence identical to the original,
    //! except that elements at indices in the provided range are removed.
    //! Specifically, `remove_range([x0, ..., xn], from, to)` is a new
    //! sequence equivalent to `[x0, ..., x_from-1, x_to, ..., xn]`.
    //!
    //!
    //! @note
    //! The behavior is undefined if the range contains any index out of the
    //! bounds of the sequence.
    //!
    //!
    //! @param xs
    //! A sequence from which elements are removed.
    //!
    //! @param [from, to)
    //! An half-open interval of `IntegralConstant`s representing the indices
    //! of the elements to be removed from the sequence. The `IntegralConstant`s
    //! in the half-open interval must be non-negative and in the bounds of
    //! the sequence. The half-open interval must also be valid, meaning that
    //! `from <= to`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_range.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove_range = [](auto&& xs, auto const& from, auto const& to) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct remove_range_impl : remove_range_impl<S, when<true>> { };

    struct remove_range_t {
        template <typename Xs, typename From, typename To>
        constexpr auto operator()(Xs&& xs, From const& from, To const& to) const;
    };

    constexpr remove_range_t remove_range{};
#endif

    //! Equivalent to `remove_range`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_range_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t from, std::size_t to>
    constexpr auto remove_range_c = [](auto&& xs) {
        return hana::remove_range(forwarded(xs), hana::size_c<from>, hana::size_c<to>);
    };
#else
    template <std::size_t from, std::size_t to>
    struct remove_range_c_t;

    template <std::size_t from, std::size_t to>
    constexpr remove_range_c_t<from, to> remove_range_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REMOVE_RANGE_HPP

/* remove_range.hpp
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
*/