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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr scan_left_t scan_left{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SCAN_LEFT_HPP

/* scan_left.hpp
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
*/