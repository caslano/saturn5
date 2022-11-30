/*!
@file
Forward declares `boost::hana::take_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_BACK_HPP
#define BOOST_HANA_FWD_TAKE_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


namespace boost { namespace hana {
    //! Returns the last `n` elements of a sequence, or the whole sequence
    //! if the sequence has less than `n` elements.
    //! @ingroup group-Sequence
    //!
    //! Given a `Sequence` `xs` and an `IntegralConstant` `n`, `take_back(xs, n)`
    //! is a new sequence containing the last `n` elements of `xs`, in the
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
    //! @include example/take_back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_back = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_back_impl : take_back_impl<S, when<true>> { };

    struct take_back_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr take_back_t take_back{};
#endif

    //! Equivalent to `take_back`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_back_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto take_back_c = [](auto&& xs) {
        return hana::take_back(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n>
    struct take_back_c_t;

    template <std::size_t n>
    BOOST_HANA_INLINE_VARIABLE constexpr take_back_c_t<n> take_back_c{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_TAKE_BACK_HPP

/* take_back.hpp
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
*/