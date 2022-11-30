/*!
@file
Forward declares `boost::hana::scan_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SCAN_RIGHT_HPP
#define BOOST_HANA_FWD_SCAN_RIGHT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Fold a Sequence to the right and return a list containing the
    //! successive reduction states.
    //! @ingroup group-Sequence
    //!
    //! Like `fold_right`, `scan_right` reduces a sequence to a single value
    //! using a binary operation. However, unlike `fold_right`, it builds up
    //! a sequence of the intermediary results computed along the way and
    //! returns that instead of only the final reduction state. Like
    //! `fold_right`, `scan_right` can be used with or without an initial
    //! reduction state.
    //!
    //! When the sequence is empty, two things may arise. If an initial state
    //! was provided, a singleton list containing that state is returned.
    //! Otherwise, if no initial state was provided, an empty list is
    //! returned. In particular, unlike for `fold_right`, using `scan_right`
    //! on an empty sequence without an initial state is not an error.
    //!
    //! More specifically, `scan_right([x1, ..., xn], state, f)` is a sequence
    //! whose `i`th element is equivalent to `fold_right([x1, ..., xi], state, f)`.
    //! The no-state variant is handled in an analogous way. For illustration,
    //! consider this right fold on a short sequence:
    //! @code
    //!     fold_right([x1, x2, x3], state, f) == f(x1, f(x2, f(x3, state)))
    //! @endcode
    //!
    //! The analogous sequence generated with `scan_right` will be
    //! @code
    //!     scan_right([x1, x2, x3], state, f) == [
    //!         f(x1, f(x2, f(x3, state))),
    //!               f(x2, f(x3, state)),
    //!                     f(x3, state),
    //!                           state
    //!     ]
    //! @endcode
    //!
    //! Similarly, consider this right fold (without an initial state) on
    //! a short sequence:
    //! @code
    //!     fold_right([x1, x2, x3, x4], f) == f(x1, f(x2, f(x3, x4)))
    //! @endcode
    //!
    //! The analogous sequence generated with `scan_right` will be
    //! @code
    //!     scan_right([x1, x2, x3, x4], f) == [
    //!         f(x1, f(x2, f(x3, x4))),
    //!               f(x2, f(x3, x4)),
    //!                     f(x3, x4),
    //!                           x4
    //!     ]
    //! @endcode
    //!
    //! @param xs
    //! The sequence to scan from the right.
    //!
    //! @param state
    //! The (optional) initial reduction state.
    //!
    //! @param f
    //! A binary function called as `f(x, state)`, where `state` is the
    //! result accumulated so far and `x` is an element in the sequence.
    //! When no initial state is provided, `f` is called as `f(x1, x2)`,
    //! where `x1` and `x2` are elements of the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/scan_right.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto scan_right = [](auto&& xs[, auto&& state], auto const& f) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct scan_right_impl : scan_right_impl<S, when<true>> { };

    struct scan_right_t {
        template <typename Xs, typename State, typename F>
        constexpr auto operator()(Xs&& xs, State&& state, F const& f) const;

        template <typename Xs, typename F>
        constexpr auto operator()(Xs&& xs, F const& f) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr scan_right_t scan_right{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_SCAN_RIGHT_HPP

/* scan_right.hpp
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
*/