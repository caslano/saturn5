/*!
@file
Forward declares `boost::hana::remove_at` and `boost::hana::remove_at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_AT_HPP
#define BOOST_HANA_FWD_REMOVE_AT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


namespace boost { namespace hana {
    //! Remove the element at a given index from a sequence.
    //! @ingroup group-Sequence
    //!
    //! `remove_at` returns a new sequence identical to the original, except
    //! that the element at the given index is removed. Specifically,
    //! `remove_at([x0, ..., xn-1, xn, xn+1, ..., xm], n)` is a new
    //! sequence equivalent to `[x0, ..., xn-1, xn+1, ..., xm]`.
    //!
    //! @note
    //! The behavior is undefined if the index is out of the bounds of the
    //! sequence.
    //!
    //!
    //! @param xs
    //! A sequence from which an element is to be removed.
    //!
    //! @param n
    //! An non-negative `IntegralConstant` representing the index of the
    //! element to be removed from the sequence. The behavior is undefined
    //! if that index is not in the bounds of the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_at.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove_at = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct remove_at_impl : remove_at_impl<S, when<true>> { };

    struct remove_at_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr remove_at_t remove_at{};
#endif

    //! Equivalent to `remove_at`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_at_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto remove_at_c = [](auto&& xs) {
        return hana::remove_at(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n>
    struct remove_at_c_t;

    template <std::size_t n>
    BOOST_HANA_INLINE_VARIABLE constexpr remove_at_c_t<n> remove_at_c{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_REMOVE_AT_HPP

/* remove_at.hpp
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
*/