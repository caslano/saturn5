/*!
@file
Forward declares `boost::hana::scan_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SCAN_LEFT_HPP
#define BOOST_HANA_FWD_SCAN_LEFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Fold a Sequence to the left and return a list containing the
    //! successive reduction states.
    //! @ingroup group-Sequence
    //!
    //! Like `fold_left`, `scan_left` reduces a sequence to a single value
    //! using a binary operation. However, unlike `fold_left`, it builds up
    //! a sequence of the intermediary results computed along the way and
    //! returns that instead of only the final reduction state. Like
    //! `fold_left`, `scan_left` can be used with or without an initial
    //! reduction state.
    //!
    //! When the sequence is empty, two things may arise. If an initial state
    //! was provided, a singleton list containing that state is returned.
    //! Otherwise, if no initial state was provided, an empty list is
    //! returned. In particular, unlike for `fold_left`, using `scan_left`
    //! on an empty sequence without an initial state is not an error.
    //!
    //! More specifically, `scan_left([x1, ..., xn], state, f)` is a sequence
    //! whose `i`th element is equivalent to `fold_left([x1, ..., xi], state, f)`.
    //! The no-state variant is handled in an analogous way. For illustration,
    //! consider this left fold on a short sequence:
    //! @code
    //!     fold_left([x1, x2, x3], state, f) == f(f(f(state, x1), x2), x3)
    //! @endcode
    //!
    //! The analogous sequence generated with `scan_left` will be
    //! @code
    //!     scan_left([x1, x2, x3], state, f) == [
    //!         state,
    //!         f(state, x1),
    //!         f(f(state, x1), x2),
    //!         f(f(f(state, x1), x2), x3)
    //!     ]
    //! @endcode
    //!
    //! Similarly, consider this left fold (without an initial state) on
    //! a short sequence:
    //! @code
    //!     fold_left([x1, x2, x3, x4], f) == f(f(f(x1, x2), x3), x4)
    //! @endcode
    //!
    //! The analogous sequence generated with `scan_left` will be
    //! @code
    //!     scan_left([x1, x2, x3, x4], f) == [
    //!         x1,
    //!         f(x1, x2),
    //!         f(f(x1, x2), x3),
    //!         f(f(f(x1, x2), x3), x4)
    //!     ]
    //! @endcode
    //!
    //! @param xs
    //! The sequence to scan from the left.
    //!
    //! @param state
    //! The (optional) initial reduction state.
    //!
    //! @param f
    //! A binary function called as `f(state, x)`, where `state` is the
    //! result accumulated so far and `x` is an element in the sequence.
    //! If no initial state is provided, `f` is called as `f(x1, x2)`,
    //! where `x1` and `x2` are both elements of the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/scan_left.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto scan_left = [](auto&& xs[, auto&& state], auto const& f) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct scan_left_impl : scan_left_impl<S, when<true>> { };

    struct scan_left_t {
        template <typename Xs, typename State, typename F>
        constexpr auto operator()(Xs&& xs, State&& state, F const& f) const;

        template <typename Xs, typename F>
        constexpr auto operator()(Xs&& xs, F const& f) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr scan_left_t scan_left{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_SCAN_LEFT_HPP

/* scan_left.hpp
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
*/