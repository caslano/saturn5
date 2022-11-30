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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr remove_range_t remove_range{};
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
    BOOST_HANA_INLINE_VARIABLE constexpr remove_range_c_t<from, to> remove_range_c{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_REMOVE_RANGE_HPP

/* remove_range.hpp
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
*/