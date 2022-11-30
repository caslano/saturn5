/*!
@file
Forward declares `boost::hana::take_front` and `boost::hana::take_front_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_FRONT_HPP
#define BOOST_HANA_FWD_TAKE_FRONT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


namespace boost { namespace hana {
    //! Returns the first `n` elements of a sequence, or the whole sequence
    //! if the sequence has less than `n` elements.
    //! @ingroup group-Sequence
    //!
    //! Given a `Sequence` `xs` and an `IntegralConstant` `n`, `take_front(xs, n)`
    //! is a new sequence containing the first `n` elements of `xs`, in the
    //! same order. If `length(xs) <= n`, the whole sequence is returned and
    //! no error is triggered.
    //!
    //!
    //! @param xs
    //! The sequence to take the elements from.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to keep in the resulting sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_front.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_front = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_front_impl : take_front_impl<S, when<true>> { };

    struct take_front_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr take_front_t take_front{};
#endif

    //! Equivalent to `take_front`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_front_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto take_front_c = [](auto&& xs) {
        return hana::take_front(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n>
    struct take_front_c_t;

    template <std::size_t n>
    BOOST_HANA_INLINE_VARIABLE constexpr take_front_c_t<n> take_front_c{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_TAKE_FRONT_HPP

/* take_front.hpp
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
*/