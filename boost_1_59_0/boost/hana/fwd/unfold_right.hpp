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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr unfold_right_t<S> unfold_right{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_UNFOLD_RIGHT_HPP

/* unfold_right.hpp
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
*/