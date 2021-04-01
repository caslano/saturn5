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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr take_front_t take_front{};
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
    constexpr take_front_c_t<n> take_front_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAKE_FRONT_HPP

/* take_front.hpp
44g8dMuL1q7/UW1qk2hjLzB8+sqr+WALxyWFvxA3r/a43bPQkFkZLlAiAV7kumlvv8zBzVDkSaJ3gUE41Jwo0XcQBv3UVxT044sGXT332GmD6u0tpso4hz9DFGSNl3tkruMs906Gc54VOeE/D07Igh72j9Vo42s97yC9QXLC+mRjJP+BdPUHvXu/cVehSB6ZlDSw2ilQMiT7C5EB3zIqkb/iLoZ1QOkBZko2I8N62UEqQjlnfzBxlc07ebgYwq1ej/pbFM2CqewhpUK/G/XBWuPm9tEItijQMEKLuXyTnWDa3hHfeD0uYQ6PdxGBoEEhtjSeA5ImW+7PRnkSI97LkKjMvd6VAmlIcuVtH2ksmUnDoPmocUkCbUDWajpuHPiDlbd2FY1+PJzEbSGLUFfyW0+CetkAfbVd/pB1TszUJH3tO/DN51TOtJaLpr/nk9BRQwGcz8crnWzDf06pjZ4FhwllnudpsXWemAUq6wghrjau5dlePSBxri/cvn67lDSkkplXRxxxNU0TTISyFrFqnO+YhPl2c0K1EfnL3q1r2S9WGBnIwnheVtxV3Q==
*/