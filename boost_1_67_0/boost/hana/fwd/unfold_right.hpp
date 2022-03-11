/*!
@file
Forward declares `boost::hana::unfold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNFOLD_RIGHT_HPP
#define BOOST_HANA_FWD_UNFOLD_RIGHT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Dual operation to `fold_right` for sequences.
    //! @ingroup group-Sequence
    //!
    //! While `fold_right` reduces a structure to a summary value from the
    //! right, `unfold_right` builds a sequence from a seed value and a
    //! function, starting from the right.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S`, an initial value `state` of tag `I`, an
    //! arbitrary Product `P` and a function \f$ f : I \to P(T, I) \f$,
    //! `unfold_right<S>` has the following signature:
    //! \f[
    //!     \mathtt{unfold\_right}_S : I \times (I \to P(T, I)) \to S(T)
    //! \f]
    //!
    //! @tparam S
    //! The tag of the sequence to build up.
    //!
    //! @param state
    //! An initial value to build the sequence from.
    //!
    //! @param f
    //! A function called as `f(state)`, where `state` is an initial value,
    //! and returning
    //! 1. `nothing` if it is done producing the sequence.
    //! 2. otherwise, `just(make<P>(x, state))`, where `state` is the new
    //!    initial value used in the next call to `f`, `x` is an element to
    //!    be prepended to the resulting sequence, and `P` is an arbitrary
    //!    `Product`.
    //!
    //!
    //! Fun fact
    //! ---------
    //! In some cases, `unfold_right` can undo a `fold_right` operation:
    //! @code
    //!     unfold_right<S>(fold_right(xs, state, f), g) == xs
    //! @endcode
    //!
    //! if the following holds
    //! @code
    //!     g(f(x, y)) == just(make_pair(x, y))
    //!     g(state) == nothing
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/unfold_right.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename S>
    constexpr auto unfold_right = [](auto&& state, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct unfold_right_impl : unfold_right_impl<S, when<true>> { };

    template <typename S>
    struct unfold_right_t;

    template <typename S>
    constexpr unfold_right_t<S> unfold_right{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNFOLD_RIGHT_HPP

/* unfold_right.hpp
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
*/